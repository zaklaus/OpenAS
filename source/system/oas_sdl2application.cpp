/*
	The MIT License

	Copyright (c) 2014 Aurora Internet

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <system\oas_sdl2application.h>
#include <system\oas_game.h>
#include <SDL_opengl.h>
#include <gl\gl.h>
#include <gl\glu.h>

int SKIP_TICKS = 1;
DWORD nextTick;



namespace OpenAS {

	namespace System {

		void SDLApplication::glPrint(int x, int y, const char *fmt, ...)					// Custom GL "Print" Routine
		{
			char		text[256];								// Holds Our String
			va_list		ap;										// Pointer To List Of Arguments

			if (fmt == NULL)									// If There's No Text
				return;											// Do Nothing

			va_start(ap, fmt);									// Parses The String For Variables
			vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
			va_end(ap);											// Results Are Stored In Text

			glRasterPos2i(x, y);

			glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
			glListBase(this->m_baseFont - 32);								// Sets The Base Character to 32
			glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
			glPopAttrib();										// Pops The Display List Bits
		}

		void SDLApplication::BuildFont()								// Build Our Bitmap Font
		{
			HFONT	font;										// Windows Font ID
			HFONT	oldfont;									// Used For Good House Keeping
			HDC hDC = wglGetCurrentDC();

			if (hDC == NULL)
			{
				_printf("hDC not found");
			}

			this->m_baseFont = glGenLists(96);								// Storage For 96 Characters

			font = CreateFont(-24,							// Height Of Font
				0,								// Width Of Font
				0,								// Angle Of Escapement
				0,								// Orientation Angle
				FW_BOLD,						// Font Weight
				FALSE,							// Italic
				FALSE,							// Underline
				FALSE,							// Strikeout
				ANSI_CHARSET,					// Character Set Identifier
				OUT_TT_PRECIS,					// Output Precision
				CLIP_DEFAULT_PRECIS,			// Clipping Precision
				ANTIALIASED_QUALITY,			// Output Quality
				FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
				"Courier New");					// Font Name

			oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
			wglUseFontBitmaps(hDC, 32, 96, this->m_baseFont);				// Builds 96 Characters Starting At Character 32
			SelectObject(hDC, oldfont);							// Selects The Font We Want
			DeleteObject(font);									// Delete The Font
		}

		unsigned __stdcall startInputT(void *f){
			Input* i = reinterpret_cast<Input*>(f);
			while (1)
				i->Update();
		}

		SDLApplication::SDLApplication(const std::string& title)
			: m_title(title)

		{
			m_initialized = true;
			this->m_surface = SDL_CreateRGBSurface(0, 800, 600, 32, 0, 0, 0, 0);
			
		}

		SDLApplication::~SDLApplication()
		{
			SDL_GL_DeleteContext(m_context);
			
		}

		bool SDLApplication::initialized()
		{
			return m_initialized;
		}



		//main application loop
		int SDLApplication::run()
		{
			

			Game* g;
			g = Game::GetGame();

			if (!m_initialized) {
				return EXIT_FAILURE;
			}

			this->m_deltaTime = 1;

			//INITIALIZE SDL
			//
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
				printf("SDL encountered error on init: %s\n", SDL_GetError());
				SDL_Quit();
				return EXIT_FAILURE;
			}

			//Create window
			//
			m_window = SDL_CreateWindow(m_title.c_str(),
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				g->GetWindowWidth(), g->GetWindowHeight(),
				SDL_WINDOW_OPENGL);
			if (!m_window) {
				printf("SDL encountered error on window init: %s\n", SDL_GetError());
				SDL_Quit();
				return EXIT_FAILURE;
			}

			//Create opengl context
			//
			m_context = SDL_GL_CreateContext(m_window);
			SDL_GL_MakeCurrent(m_window, m_context);

			//Prepare scene
			//
			glViewport(0, 0, g->GetWindowWidth(), g->GetWindowHeight());

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			// Calculate The Aspect Ratio Of The Window
			//
			gluPerspective(60.0f, (GLfloat)g->GetWindowWidth() / (GLfloat)g->GetWindowHeight(), 0.1f, 1000.0f);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			//

			this->BuildFont();

			//Set-Up OpenGL
			//
			glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
			glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
			glClearDepth(1.0f);									// Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Enables Blending
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_LIGHTING);
			glEnable(GL_COLOR_MATERIAL);
			glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
			//

			nextTick = SDL_GetTicks();

			// TEST: Basic lighting
			//glEnable(GL_LIGHT0); float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f }; float diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f }; float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; float position[] = { 0.0f, 1.0f, 0.0f, 1.0f }; 
			//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); glLightfv(GL_LIGHT0, GL_POSITION, position);
			

			//glEnable(GL_LIGHT0);
		

			//this->BuildFont();

			// Load first map
			//
			char mapbuf[80] = "";
			sprintf(mapbuf, "%s", g->m_firstMap.c_str());
			_printf("First map: %s", mapbuf);
			g->GetMapManager()->InstallMap(mapbuf);
			g->GetMapManager()->LoadMap(0);

			m_running = true;
			int slptime = 0;
			
			// Main game loop
			//
			//return 0;
			while (m_running)
			{
				//SKIP_TICKS = 1000 / g->GetMaxFPS();
				
				
				//printf("Ticks Start: %d\n\n", SDL_GetTicks());
				//SDL_PumpEvents();
				// Process input
				//
				this->m_input.Update();


				SDL_Event event;
				
				while (SDL_PollEvent(&event))
				{
					
					switch (event.type)
					{
					case SDL_QUIT:
						m_running = false;
						PostQuitMessage(0);
						break;
					}
				}

				// Clear the scene
				//
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
				glLoadIdentity();									

				//printf("%s\n\n", g->GetEntityManager()->GetEntityByName("Cube")->GetScriptName());


				// Call event for all existing scripts
				//
				for (int i = 0; i < MAX_ENTITIES; i++)
				{
					Entity* e = g->GetEntityManager()->GetEntity(i);
					
					if (e)
					{
						if (e->GetScript() != NULL)
							//printf(e->GetScript()->GetScriptName());
							if (e->GetScript()->GetVM() != NULL)
								g->GetScriptsManager()->Call(e->GetScript(), "onUpdate", 0, NULL);
					}
				}
				glPrint(0,0,"test");

				//glMatrixMode(GL_MODELVIEW);
				//glLoadIdentity();
				
				//glMatrixMode(GL_PROJECTION);
				//glLoadIdentity();

				float roty = 360.0f - vRotation.y;

				glRotatef(-vRotation.x, 1, 0, 0);	// X
				glRotatef(roty, 0, 1, 0);	// Y
				glRotatef(-vRotation.z, 0, 0, 1);	// Z
				
				glTranslatef(-vPosition.x, -vPosition.y, -vPosition.z);

				//glMatrixMode(GL_MODELVIEW);
				//glLoadIdentity();	
				int textureID = 1;
				for (int i = 0; i < MAX_ENTITIES; i++){
					if(g->GetEntityManager()->GetEntity(i))
					{
						Entity* e = g->GetEntityManager()->GetEntity(i);
						if (g->GetEntityManager()->GetEntity(i)->HasModel() == false) continue;
						
						

						for (int j = 0; j < e->GetModels()->size(); j++)
						{
							Model* mdl = g->GetEntityManager()->GetEntity(i)->GetModel(j);
							glPushMatrix();
							//glLoadIdentity();
							glTranslatef(e->GetPosition().x, e->GetPosition().y, e->GetPosition().z);
							glRotatef(e->GetRotation().x, 1, 0, 0);	// X
							glRotatef(e->GetRotation().y, 0, 1, 0);	// Y
							glRotatef(e->GetRotation().z, 0, 0, 1);	// Z


							glBindTexture(GL_TEXTURE_2D, mdl->materials[0].GetTextureID());
							glCallList(mdl->listID);

							glPopMatrix();
						}
					}
				}
				glEnable(GL_LIGHT0);
				// Transform enabled lights
				//
				for (int i = 0; i < 8; i++)
				{
					Light* l = g->GetMapManager()->GetCurrentMap()->GetLightByGL(i);
					if (l)
					{
						glPushMatrix();
						glLoadIdentity();
						float pos[4] = { l->pos.x, l->pos.y, l->pos.z, 1.0f };
						float specularLight[3] = { l->spec.x, l->spec.y, l->spec.z };
						glLightfv(GL_LIGHT0 + i, GL_POSITION, pos);

						
						glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
						glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
						glMateriali(GL_FRONT, GL_SHININESS, 128);
						glPopMatrix();
					}
				}
				
				//printf("Ticks End: %d\n\n", SDL_GetTicks());

				slptime = SDL_GetTicks() - nextTick;

				if (slptime >= 0)
				{
					//printf("\n\noverfps: %d",slptime);
					//Sleep(slptime);
				}
				else
				{
					// TODO: Slow pc implementation
					//
					//printf("%d\n", slptime);
				}
				nextTick = SDL_GetTicks();
				SDL_GL_SwapWindow(m_window);
			}

			SDL_Quit();
			return EXIT_SUCCESS;
		}

	}
}

// TODO: Font drawin'
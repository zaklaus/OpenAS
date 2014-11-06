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

namespace OpenAS {

	namespace System {

		void SDLApplication::glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
		{
			char		text[256];								// Holds Our String
			va_list		ap;										// Pointer To List Of Arguments

			if (fmt == NULL)									// If There's No Text
				return;											// Do Nothing

			va_start(ap, fmt);									// Parses The String For Variables
			vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
			va_end(ap);											// Results Are Stored In Text

			glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
			glListBase(this->m_baseFont - 32);								// Sets The Base Character to 32
			glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
			glPopAttrib();										// Pops The Display List Bits
		}

		void SDLApplication::BuildFont()								// Build Our Bitmap Font
		{
			HFONT	font;										// Windows Font ID
			

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

			
			wglUseFontBitmaps(NULL, 32, 96, this->m_baseFont);				// Builds 96 Characters Starting At Character 3
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
			

			if (!m_initialized) {
				//note: these printf will eventually be removed for logger system
				printf("SDL Application failed to initialize\n");
				return EXIT_FAILURE;
			}

			//INITIALIZE SDL
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
				printf("SDL encountered error on init: %s\n", SDL_GetError());
				SDL_Quit();
				return EXIT_FAILURE;
			}

			//create window
			m_window = SDL_CreateWindow(m_title.c_str(),
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				1024, 768,
				SDL_WINDOW_OPENGL);
			if (!m_window) {
				printf("SDL encountered error on window init: %s\n", SDL_GetError());
				SDL_Quit();
				return EXIT_FAILURE;
			}

			//create opengl context
			m_context = SDL_GL_CreateContext(m_window);

			//Prepare scene
			//
			glViewport(0, 0, 1024,760);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			// Calculate The Aspect Ratio Of The Window
			//
			gluPerspective(60.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, 100.0f);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			//


			//Set-Up OpenGL
			//
			glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
			glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
			glClearDepth(1.0f);									// Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_LIGHTING);
			glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
			//

			glEnable(GL_LIGHTING); glEnable(GL_LIGHT0); float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f }; float diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f }; float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; float position[] = { 0.0f, 1.0f, 0.0f, 1.0f }; 
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); glLightfv(GL_LIGHT0, GL_POSITION, position);
			

			//glEnable(GL_LIGHT0);
		

			this->BuildFont();

			Game* g;
			g = Game::GetGame();

			char mapbuf[80] = "";
			sprintf(mapbuf, "%s", g->m_firstMap.c_str());

			g->GetMapManager()->InstallMap(mapbuf);
			g->GetMapManager()->LoadMap(0);

			m_running = true;

			//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)this->m_input.Update, NULL, 0, NULL);
			//_beginthreadex(NULL, NULL, startInputT, &this->m_input, 0, NULL);

			while (m_running)
			{
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

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
				glLoadIdentity();									

				//printf("%s\n\n", g->GetEntityManager()->GetEntityByName("Cube")->GetScriptName());



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
				glRasterPos2f(0, 0);
				glPrint("test");

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

						Model* mdl = g->GetEntityManager()->GetEntity(i)->GetModel();

						

						glPushMatrix();
						//glLoadIdentity();
						glTranslatef(-e->GetPosition().x, -e->GetPosition().y, -e->GetPosition().z);
						glRotatef(e->GetRotation().x, 1, 0, 0);	// X
						glRotatef(e->GetRotation().y, 0, 1, 0);	// Y
						glRotatef(e->GetRotation().z, 0, 0, 1);	// Z
						
						glBindTexture(GL_TEXTURE_2D, mdl->materials[0].GetTextureID());
						glBegin(GL_TRIANGLES);
						for (int j = 0; j < g->GetEntityManager()->GetEntity(i)->GetModel()->vertices.size(); j++){
							std::vector<Util::Vector3D>* tmp = &g->GetEntityManager()->GetEntity(i)->GetModel()->vertices;
							std::vector<Util::Vector2D>* tmpUV = &g->GetEntityManager()->GetEntity(i)->GetModel()->uvs;
							std::vector<Util::Vector3D>* tmpN = &g->GetEntityManager()->GetEntity(i)->GetModel()->normals;

							glTexCoord2f(tmpUV->at(j).x, tmpUV->at(j).y);
							glNormal3f(tmpN->at(j).x, tmpN->at(j).y, tmpN->at(j).z);
							glVertex3f(tmp->at(j).x, tmp->at(j).y, tmp->at(j).z);
						
						}
						glEnd();
						
						glPopMatrix();
					}
				}
				

				SDL_GL_SwapWindow(m_window);
			}

			SDL_Quit();
			return EXIT_SUCCESS;
		}

	}
}
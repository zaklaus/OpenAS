#include <system\vtx_sdl2application.h>

namespace Vortex {

	namespace System {

		SDLApplication::SDLApplication(const std::string& title)
			: m_title(title)

		{


			m_initialized = true;
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
				800, 600,
				SDL_WINDOW_OPENGL);
			if (!m_window) {
				printf("SDL encountered error on window init: %s\n", SDL_GetError());
				SDL_Quit();
				return EXIT_FAILURE;
			}

			//create opengl context
			m_context = SDL_GL_CreateContext(m_window);

			m_running = true;
			while (m_running)
			{

				SDL_Event event;
				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_QUIT:
						m_running = false;
						break;
					}
				}

				//update
				//render

				SDL_GL_SwapWindow(m_window);
			}

			SDL_Quit();
			return EXIT_SUCCESS;
		}

	}
}
#ifndef OAS_SDL2_APPLICATION_H
#define OAS_SDL2_APPLICATION_H

#include <system\oas_platform.h>
#include <system\oas_interfaces.h>
#include <util\oas_stringutil.h>
#include <SDL.h>

namespace OpenAS {

	namespace System {

		class OAS_API SDLApplication : public IApplication
		{
		public:
			SDLApplication(const std::string& title);

			~SDLApplication();

			bool initialized() override;
			int  run()         override;

		private:
			SDL_Window*   m_window;
			SDL_GLContext m_context;
			bool          m_initialized;
			bool          m_running;
			std::string   m_title;
		};

	}

}

#endif
#ifndef VTX_SDL2_APPLICATION_H
#define VTX_SDL2_APPLICATION_H

#include <system\vtx_platform.h>
#include <system\vtx_interfaces.h>
#include <util\vtx_stringutil.h>
#include <SDL.h>

namespace Vortex {

	namespace System {

		class VTX_API SDLApplication : public IApplication
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
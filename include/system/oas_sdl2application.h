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

#ifndef OAS_SDL2_APPLICATION_H
#define OAS_SDL2_APPLICATION_H

#include <system\oas_platform.h>
#include <system\oas_interfaces.h>
#include <system\oas_input.h>
#include <util\oas_stringutil.h>
#include <util\oas_math.h>
#include <vector>
#include <SDL.h>

namespace OpenAS {

	namespace System {

		class OAS_API SDLApplication : public IApplication
		{
		public:
			
			void BuildFont();
			SDLApplication(const std::string& title);

			~SDLApplication();

			bool initialized() override;
			int  run() override;

			SDL_Surface* GetSurface(){ return m_surface; };

			void SetPosition(float x, float y, float z){ vPosition.x = x; vPosition.y = y; vPosition.z = z; };
			void SetRotation(float x, float y, float z){ vRotation.x = x; vRotation.y = y; vRotation.z = z; };
			Util::Vector3D GetPosition(){ return vPosition; };
			Util::Vector3D GetRotation(){ return vRotation; };
			int GetKeyByName(const char* str){ return SDL_GetScancodeFromName(str); };
			void SDLApplication::glPrint(const char *fmt, ...);
			Input* GetInput(){ return &m_input; };
		private:
			SDL_Window*   m_window;
			SDL_GLContext m_context;
			SDL_Surface*  m_surface;
			Input  m_input;
			bool          m_initialized;
			bool          m_running;
			std::string   m_title;
			Util::Vector3D vPosition;
			Util::Vector3D vRotation;
			int        m_baseFont;
		};

	}

}

#endif
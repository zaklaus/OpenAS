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
#pragma once

#ifndef OAS_GAME_H
#define OAS_GAME_H

#include <system\oas_platform.h>
#include <system\oas_sdl2application.h>
#include <system\oas_logmanager.h>
#include <system\oas_entitymanager.h>
#include <system\oas_scriptsex.h>

namespace OpenAS
{
	namespace System
	{
		

		static class OAS_API Game
		{
		private:
			OpenAS::System::LogManager m_cLogManager;
			OpenAS::System::SDLApplication* m_cSDLApplication;
			OpenAS::System::EntityManager m_cEntityManager;
			OpenAS::System::ScriptsEx m_cScripts;
		public:
			Game(const std::string& title);
			~Game();


			// Member methods
			//
			OpenAS::System::LogManager* GetLogManager();
			OpenAS::System::SDLApplication* GetSDLApplication();
			OpenAS::System::EntityManager* GetEntityManager();
			OpenAS::System::ScriptsEx* GetScriptsManager();

			// Test methods
			//
			void dlltest();

		private:
			std::string m_title;
		};
	}
}
#endif
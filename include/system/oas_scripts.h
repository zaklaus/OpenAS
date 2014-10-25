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

#include <system\oas_platform.h>

#include <system\oas_script.h>
#include <util\sq_heads.h>
#include <vector>
#include <util\oas_stringutil.h>

#define MAX_SCRIPTS 10

namespace OpenAS
{
	namespace System
	{
		class OAS_API Scripts
		{
		private:
			Script** m_pScripts;
			char m_szScriptNames[MAX_SCRIPTS][256];

		public:
			Scripts();
			~Scripts();

			Script* GetScripts();

			int LoadScript(int _id, const char * szScriptName);
			bool UnloadScript(const char * szScriptName);
			//bool LoadFromConfig(CConfig * pConfig);

			Script * GetScript(int scriptID) {
				if (!m_pScripts[scriptID]) return NULL;
				return m_pScripts[scriptID];
			};

			Script * GetScriptByName(const char* name) {
				for(int i = 0; i < MAX_SCRIPTS; i++)
				{
					if(!strcmp(m_pScripts[i]->GetScriptName(),name))
					{
						return m_pScripts[i];
					}
					return NULL;
				}
				return NULL;
			};

			void Call(const char * szFunc, int iArgCount, SQObject * pArguments);
			void Call(int scriptid, const char * szFunc, int iArgCount, SQObject * pArguments);
			void onStart();
		};
	}
}
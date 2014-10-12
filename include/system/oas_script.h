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

#include <util\sq_heads.h>
#include <cstring>

namespace OpenAS
{
	namespace System
	{
		class Script
		{
		private:
			SQVM * m_pVM;
			char m_szScriptName[256];
			char m_szScriptAuthor[256];
			char m_szScriptVersion[256];
			int m_iEntityID;
			int m_iScriptID;
		public:
			Script(const char * szScriptName);
			~Script();

			SQVM * GetVM() { return m_pVM; };

			char * GetScriptName() { return (char*)&m_szScriptName; };
			char * GetScriptAuthor() { return (char*)&m_szScriptAuthor; };
			char * GetScriptVersion() { return (char*)&m_szScriptVersion; };
			int  GetScriptID() {return m_iScriptID; };
			int  GetEntityID() {return m_iEntityID; };
			void SetScriptAuthor(const char * szAuthor) { strncpy(m_szScriptAuthor, szAuthor, sizeof(m_szScriptAuthor)); };
			void SetScriptVersion(const char * szVersion) { strncpy(m_szScriptVersion, szVersion, sizeof(m_szScriptVersion)); };
			void SetEntityID(int id) {m_iEntityID = id; };
			void SetScriptID(int id) {m_iScriptID = id; };
		};

	}
}
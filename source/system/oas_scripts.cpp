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

#include <system\oas_scripts.h>

using namespace OpenAS::System;

Scripts::Scripts()
{
	//*m_pScripts = { };
	this->m_pScripts = new Script *[MAX_SCRIPTS];
	/*for (int i = 0; i < max_scripts; i++) {
		this->m_pscripts[i] = nullptr;
	}*/
}

Scripts::~Scripts()
{
	for (int i = 0; i < MAX_SCRIPTS; i++) {
		if (m_pScripts[i]) delete m_pScripts[i];
		m_pScripts[i] = NULL;
	}
}

int Scripts::LoadScript(int _id, const char * szScriptName)
{
	// make sure a script with the same entity id isn't already loaded
	for (int i = 0; i < MAX_SCRIPTS; i++) {
		if (m_pScripts[i] == NULL) continue;
		
		//if (!strcmp(m_pScripts[i]->GetScriptName(), szScriptName)) {
		if(m_pScripts[i]->GetEntityID() == _id){
			printf("sorry");
			return -1;
		}
	}

	// find a free script slot
	int iSlot = -1;

	for (int i = 0; i < MAX_SCRIPTS; i++) {
		if (!m_pScripts[i]) {
			// found a free slot
			iSlot = i;
			break;
		}
	}

	if (iSlot == -1) {
		// no free script slot found
		return -1;
	}

	if (m_pScripts[iSlot] == NULL)
	{
		printf(".");
		m_pScripts[iSlot] = new Script(szScriptName);
		m_pScripts[iSlot]->SetScriptID(iSlot);
		m_pScripts[iSlot]->SetEntityID(_id);
	}
	// script loaded successfully
	return iSlot;
}

bool Scripts::UnloadScript(const char * szScriptName)
{
	// find the script slot
	for (int i = 0; i < MAX_SCRIPTS; i++) {
		if (!strcmp(m_pScripts[i]->GetScriptName(), szScriptName)) {
			// found the script slot, unload the script

			delete m_pScripts[i];

			m_pScripts[i] = NULL;
			// script unloaded successfully
			return true;
		}
	}

	// script not found
	return false;
}

void Scripts::Call(const char * szFunc, int iArgCount, SQObject * pArguments)
{
	for (int i = 0; i < MAX_SCRIPTS; i++) {
		if (m_pScripts[i]) {
			// get the script vm pointer
			SQVM * pVM = m_pScripts[i]->GetVM();

			// Get the stack top
			int iTop = sq_gettop(pVM);

			// Push the root table onto the stack
			sq_pushroottable(pVM);

			// Push the function name onto the stack
			sq_pushstring(pVM, (char*)szFunc, -1);

			if (SQ_SUCCEEDED(sq_get(pVM, -2))) {
				// Push the root table onto the stack
				sq_pushroottable(pVM);

				if (pArguments != NULL)
				{
					for (int j = 0; j < iArgCount; ++j)
						sq_pushobject(pVM, pArguments[j]);
					//pVM->Push(pArguments[j]);
				}
				sq_call(pVM, iArgCount + 1, true, true);

			}

			// Restore the stack top
			sq_settop(pVM, iTop);
		}
	}
}

void Scripts::Call(int scriptid, const char * szFunc, int iArgCount, SQObject * pArguments)
{
	if (m_pScripts[scriptid]) {
		// get the script vm pointer
		SQVM * pVM = m_pScripts[scriptid]->GetVM();

		// Get the stack top
		int iTop = sq_gettop(pVM);

		// Push the root table onto the stack
		sq_pushroottable(pVM);

		// Push the function name onto the stack
		sq_pushstring(pVM, (SQChar*)szFunc, -1);

		if (SQ_SUCCEEDED(sq_get(pVM, -2))) {
			// Push the root table onto the stack
			sq_pushroottable(pVM);

			if (pArguments != NULL)
			{
				for (int j = 0; j < iArgCount; ++j)
					sq_pushobject(pVM, pArguments[j]);
				//pVM->Push(pArguments[j]);
			}
			sq_call(pVM, iArgCount + 1, true, true);

		}

		// Restore the stack top
		sq_settop(pVM, iTop);
	}
}

Script* Scripts::GetScripts()
{
	return *this->m_pScripts;
}

void Scripts::onStart()
{
	for (int i = 0; i < MAX_SCRIPTS; i++) {
		if (m_pScripts[i]) {
			// get the script vm pointer
			SQVM * pVM = m_pScripts[i]->GetVM();

			// Get the stack top
			int iTop = sq_gettop(pVM);

			// Push the root table onto the stack
			sq_pushroottable(pVM);

			// Push the function name onto the stack
			sq_pushstring(pVM, (SQChar*)"onStart", -1);

			// Get the closure for the function
			if (SQ_SUCCEEDED(sq_get(pVM, -2))) {
				// Push the root table onto the stack
				sq_pushroottable(pVM);

				// Call the function
				sq_call(pVM, 1, true, true);
			}

			// Restore the stack top
			sq_settop(pVM, iTop);
		}
	}
}

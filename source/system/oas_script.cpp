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

#include <system\oas_script.h>
#include <util\sq_heads.h>
//#include <system\oas_game.h>
//#include <system\oas_logmanager.h>
#include <util\oas_timeutil.h>
#include <system\oas_game.h>

using namespace OpenAS::System;

extern Game* g;

void printfunc(SQVM * pVM, const char * szFormat, ...)
{
	va_list vl;
	char szBuffer[512];
	va_start(vl, szFormat);
	vsprintf(szBuffer, szFormat, vl);
	va_end(vl);
	g->GetLogManager()->AddLog("ERR_SQ_PRINT",szBuffer,time(NULL),1,"openlog.txt");
//	std::stringstream ss;
//	ss << szBuffer;
//	g->GetLogManager()->AddErrorLog("ERR_SQ_PRINT",ss.str(),time(NULL),g->GetLogManager()->GetDebugFlag(),LOG_FILE);
}

Script::Script(const char *szScriptName)
{
	// get the script path
	char szScriptPath[512];
	sprintf(szScriptPath, "%s", szScriptName);

	// make sure the script exists
	FILE * fp = fopen(szScriptPath, "rb");
	//g->GetLogManager()->AddErrorLog("ERR_FILE_NOT_FOUND",szScriptPath,time(NULL),g->GetLogManager()->GetDebugFlag(),LOG_FILE);
	if (!fp) {
		std::stringstream ss;
		ss << "File not found ["<<szScriptPath<<"]";
		g->GetLogManager()->AddLog("ERR_FILE_NOT_FOUND",ss.str(),time(NULL),1,"openlog.txt");

		this->m_pVM = NULL;

		return;
	}

	fclose(fp);

	// set the script name
	strcpy(m_szScriptName, szScriptName);

	// create the squirrel VM with an initial stack size of 1024 bytes
	m_pVM = sq_open(1024);

	// get the script vm pointer
	SQVM * pVM = m_pVM;

	// register the default error handlers
	sqstd_seterrorhandlers(pVM);

	// set the print and error functions
	sq_setprintfunc(pVM, printfunc, printfunc);

	// push the root table onto the stack
	sq_pushroottable(pVM);

	// register the string library
	sqstd_register_stringlib(pVM);

	// register the math library
	sqstd_register_mathlib(pVM);

	sqstd_register_systemlib(pVM);
	//sqstd_register_stringlib(pVM);

	// register the blob library
	/*sqstd_register_bloblib(pVM);

	// register the input/out library
	sqstd_register_iolib(pVM);
	*/
	// register the math library
	//sqstd_register_mathlib(pVM);
	/*
	// register the string library
	sqstd_register_stringlib(pVM);

	// register the system library
	sqstd_register_systemlib(pVM);

	// register the vcmp functions
	sq_register_natives(pVM);
	*/
	Init(pVM);	// register native functions
	// load and compile the script
	if (SQ_FAILED(sqstd_dofile(pVM, szScriptPath, SQFalse, SQTrue))) {
		// script compilation failed
		std::stringstream ss;
		ss << "Syntax/Runtime error occured ["<<szScriptPath<<"]";
		g->GetLogManager()->AddLog("ERR_SQ_ERROR",ss.str(),time(NULL),1,"openlog.txt");
		//g->GetLogManager()->AddLog("ERROR_SQ_ERROR","Error parsing file occured",time(NULL));
//		std::stringstream ss;
//		ss << szScriptPath;
//		g->GetLogManager()->AddErrorLog("ERR_SQ_ERROR",ss.str(),time(NULL),g->GetLogManager()->GetDebugFlag(),LOG_FILE);
		sq_close(pVM);
		this->m_pVM = NULL;
		//delete this;
		return;
	}

	// pop the root table from the stack
	sq_pop(pVM, 1);

	// call the plugins
	//pPlugins->OnScriptLoad(pVM);

	// script loaded successfully
	return;
}

Script::~Script()
{
	// kill all timers
	//pNetowkManager->GetTimerPool()->HandleScriptUnload(m_pVM);

	// call the plugins
	//pPlugins->OnScriptUnload(m_pVM);

	// close the script vm
	sq_close(m_pVM);

	// reset the script vm pointer
	m_pVM = NULL;
}
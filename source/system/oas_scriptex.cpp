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


#include<system\oas_scriptsex.h>

using namespace OpenAS::System;

void ScriptsEx::Call(Script* s, const char * szFunc, int iArgCount, SQObject * pArguments)
{
	if (s) {
//		printf("%s", s->GetVM());
		// get the script vm pointer

		SQVM * pVM = s->GetVM();

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
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
#include <util\sq_functions.h>


int Init(SQVM* vM)
{
	RegisterFunction(vM,(char*)"testf",(SQFUNCTION)sq_testf,0,(char*)"");
	RegisterFunction(vM, (char*)"print", (SQFUNCTION)sq_print, 2, (char*)".s");
	RegisterFunction(vM, (char*)"str", (SQFUNCTION)sq_str, 2, (char*)".f");
	RegisterFunction(vM, (char*)"inputGetKey", (SQFUNCTION)sq_inputGetKey, 2, (char*)".s");
	RegisterFunction(vM, (char*)"inputGetKeyUp", (SQFUNCTION)sq_inputGetKeyUp, 2, (char*)".s");
	RegisterFunction(vM, (char*)"inputGetKeyDown", (SQFUNCTION)sq_inputGetKeyDown, 2, (char*)".s");
	RegisterFunction(vM, (char*)"entityTranslate", (SQFUNCTION)sq_entityTranslate, 5, (char*)".dfff");
	RegisterFunction(vM, (char*)"camSetPosition", (SQFUNCTION)sq_camSetPosition, 4, (char*)".fff");
	RegisterFunction(vM, (char*)"camSetRotation", (SQFUNCTION)sq_camSetRotation, 4, (char*)".fff");
	RegisterFunction(vM, (char*)"entityRotate", (SQFUNCTION)sq_entityRotate, 5, (char*)".dfff");
	RegisterFunction(vM, (char*)"entityGetPosition", (SQFUNCTION)sq_entityGetPosition, 2, (char*)".d");
	RegisterFunction(vM, (char*)"entityGetRotation", (SQFUNCTION)sq_entityGetRotation, 2, (char*)".d");
	RegisterFunction(vM, (char*)"drawRect", (SQFUNCTION)sq_drawRect, 9, (char*)".dddddddd");
	return 1;
}
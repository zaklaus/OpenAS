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
#include <util\sq_utils.h>
//#include "sq_utils.h"
#include <iostream>
#include <stdio.h>

SQInteger sq_testf(SQVM* pVM);
SQInteger sq_print(SQVM*);
SQInteger sq_drawRect(SQVM*);
SQInteger sq_str(SQVM*);
SQInteger sq_entityRotate(SQVM*);
SQInteger sq_entityTranslate(SQVM*);
SQInteger sq_entityGetPosition(SQVM*);
SQInteger sq_entityGetRotation(SQVM*);
SQInteger sq_camSetPosition(SQVM*);
SQInteger sq_camSetRotation(SQVM*);
SQInteger sq_inputGetKey(SQVM*);
SQInteger sq_inputGetKeyUp(SQVM*);
SQInteger sq_inputGetKeyDown(SQVM*);

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

//-----------------------------------------------------
//
// VC:Players Multiplayer Modification For GTA:VC
// Copyright 2010 GTA:Online team
//
// File Authors: adamix
//
// License: See LICENSE in root directory
//
//-----------------------------------------------------

//#include "main.h"
//#include "CScripts.h"
#pragma once

#include <stdarg.h> 
#include <squirrel.h> 
#include <sqstdio.h> 
#include <sqstdaux.h> 
#include <system\oas_platform.h>

void OAS_API RegisterFunction(HSQUIRRELVM pVM, SQChar * szFunc, SQFUNCTION func, int params, const SQChar * szTemplate);
void OAS_API RegisterVariable(HSQUIRRELVM pVM, const SQChar * szVarName, bool bValue);
void OAS_API RegisterVariable(HSQUIRRELVM pVM, const SQChar * szVarName, int iValue);
void OAS_API RegisterVariable(HSQUIRRELVM pVM, const SQChar * szVarName, float fValue);
void OAS_API RegisterVariable(HSQUIRRELVM pVM, const SQChar * szVarName, const SQChar * szValue);
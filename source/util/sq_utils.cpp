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

#include <util\sq_utils.h>

void OAS_API RegisterFunction(HSQUIRRELVM pVM, SQChar * szFunc, SQFUNCTION func, int params, const SQChar * szTemplate)
{
	sq_pushroottable(pVM);

	sq_pushstring(pVM, szFunc, -1);
	sq_newclosure(pVM, func, 0);
	if (params != -1)
	{
		sq_setparamscheck(pVM, params, szTemplate);
	}
	sq_createslot(pVM, -3);
}

void OAS_API RegisterVariable(HSQUIRRELVM pVM, const SQChar * szVarName, bool bValue)
{
	sq_pushstring(pVM, szVarName, -1);
	sq_pushbool(pVM, bValue);
	sq_createslot(pVM, -3);
}

void OAS_API RegisterVariable(HSQUIRRELVM pVM, const SQChar * szVarName, int iValue)
{
	sq_pushstring(pVM, szVarName, -1);
	sq_pushinteger(pVM, iValue);
	sq_createslot(pVM, -3);
}

void OAS_API RegisterVariable(HSQUIRRELVM pVM, const SQChar * szVarName, float fValue)
{
	sq_pushstring(pVM, szVarName, -1);
	sq_pushfloat(pVM, fValue);
	sq_createslot(pVM, -3);
}

void OAS_API RegisterVariable(HSQUIRRELVM pVM, const SQChar * szVarName, const SQChar * szValue)
{
	sq_pushstring(pVM, szVarName, -1);
	sq_pushstring(pVM, szValue, -1);
	sq_createslot(pVM, -3);
}
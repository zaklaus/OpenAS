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

#include <system\oas_platform.h>
#include <vector>
#include <util\oas_math.h>
#include <system\oas_model.h>

#pragma once

namespace OpenAS
{
	namespace Parser
	{
		using namespace System;

		std::string OAS_API loadOBJ(
			const char * path,
			std::vector < Util::Vector3D > & out_vertices,
			std::vector < Util::Vector2D > & out_uvs,
			std::vector < Util::Vector3D > & out_normals,
			std::vector < int > & out_mtlPos
			//std::vector < std::string > & out_mtl,
			//std::string& mtlfile
			);
		std::string OAS_API loadMTL(
			const char * path,
			int pos
			//const char * mat,
			//std::string& texture
			);
		int OAS_API LoadTexBMP(const char*);
	}
}
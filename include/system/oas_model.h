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
#include <util\oas_math.h>
#include <vector>

namespace OpenAS
{
	namespace System
	{
		class OAS_API MaterialName
		{
		public:
			MaterialName(const char* p){ sprintf(name, "%s", p); };
			char name[128];
		};

		class OAS_API Material
		{
		public:
			Material(const std::string& texturePath);
			~Material(){};

			int GetTextureID(){ return textureID; };

		private:
			std::string texture;
			int textureID;
		};

		class OAS_API Model
		{
		public:

			Model(){};

			std::vector < Util::Vector3D >vertices;
			std::vector < Util::Vector2D >uvs;
			std::vector < Util::Vector3D >normals;
			std::vector < int >mtlPosX;
			std::vector < std::string > mtlX;
			std::vector < Material > materials;

			int TexID, VerID, NorID;
			//Util::Vector3D pos, rot;

//			Model();
			void LoadModel(const char* path);
		};
	}
}
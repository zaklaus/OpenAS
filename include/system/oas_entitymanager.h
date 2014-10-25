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

#ifndef OAS_ENTITYMANAGER_H
#define OAS_ENTITYMANAGER_H

#include<system\oas_defaults.h>
#include<system\oas_platform.h>
#include<system\oas_entity.h>
#include<util\oas_math.h>
#include<vector>



namespace OpenAS
{
	namespace System
	{
		class OAS_API EntityManager
		{
		public:
			EntityManager();
			~EntityManager();

			int CreateEntity(const char* _szEntityName, const char* _szScriptName, OpenAS::Util::Vector3D _vPosition, OpenAS::Util::Vector3D _vRotation, const char* _szModelName);
			int DestroyEntity(int id);
			int GetEntityCount();

			Entity* GetEntity(int id);
			Entity* GetEntityByName(const char* name);

		private:
			Entity* entities[MAX_ENTITIES];
		};
	}
}

#endif
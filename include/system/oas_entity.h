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

#ifndef OAS_ENTITY_H
#define OAS_ENTITY_H


#include<system\oas_platform.h>

#include<util\oas_stringutil.h>
#include <system\oas_script.h>
#include<util\oas_math.h>
#include <system\oas_model.h>

namespace OpenAS
{
	namespace System
	{
		class OAS_API Entity
		{
		public:

			// Construction
			//
			Entity(int _id, const char* _szEntityName, const char* _szScriptName, OpenAS::Util::Vector3D _vPosition, OpenAS::Util::Vector3D _vRotation, const char* _szModelName);
			~Entity();

			// *Get* methods (Reference returners)
			//

			char* GetEntityName();
			char* GetScriptName();
			char* GetModelName();
			OpenAS::Util::Vector3D GetPosition();
			OpenAS::Util::Vector3D GetRotation();
			int GetID();
			Script* GetScript(){ return scr; };
			int GetScriptID(){return ScriptID;};
			int SetID(int id);
			void SetScriptID(int id){ScriptID = id;};
			void SetScript(Script s){scr = &s;};
			bool HasModel(){ return hasModel; };
			void SetPosition(float x, float y, float z){ vPosition.x = x; vPosition.y = y; vPosition.z = z; };
			void SetRotation(float x, float y, float z){ vRotation.x = x; vRotation.y = y; vRotation.z = z; };
			Model* GetModel(int i){ return &model[i]; };
			std::vector<Model>* GetModels(){ return &model; };
		private:

			// Internal variables
			//

			char szEntityName[256], szModelName[256], szScriptName[256];
			OpenAS::Util::Vector3D vPosition, vRotation;
			std::vector<Model> model;
			int ID;
			int ScriptID;
			bool hasModel;
			Script* scr;
		};
	}
}

#endif
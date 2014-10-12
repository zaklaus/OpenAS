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

#include <system\oas_entity.h>
#include "system\oas_game.h"

__declspec(dllexport) OpenAS::System::Game *g;

OpenAS::System::Entity::Entity(int _id, const char* _szEntityName, const char* _szScriptName, OpenAS::Util::Vector3D _vPosition, OpenAS::Util::Vector3D _vRotation, const char* _szModelName)
{
	// Initialize internal variables
	//
	sprintf(this->szEntityName,"%s",_szEntityName);
	sprintf(this->szScriptName,"%s",_szScriptName);
	sprintf(this->szModelName,"%s",_szModelName);
	this->vPosition = _vPosition;
	this->vRotation = _vRotation;
	this->ID = _id;

	if(_szScriptName[0] != 0)
	{
		char tmp[256] = "";
		sprintf(tmp,"%s.nut",_szScriptName);
		//int sid = g->GetScriptsManager()->LoadScript(_id,tmp);

		//this->SetScriptID(sid);
		//g->GetScriptsManager()->Call(sid,"onStart",0,NULL);

		this->scr = new Script(tmp);
		g->GetScriptsManager()->Call(scr,"onStart",0,NULL);
	}
}

OpenAS::System::Entity::~Entity()
{

}

/* HELPER METHODS */
char* OpenAS::System::Entity::GetEntityName()
{
	return this->szEntityName;
}

char* OpenAS::System::Entity::GetScriptName()
{
	return this->szScriptName;
}

char* OpenAS::System::Entity::GetModelName()
{
	return this->szModelName;
}

OpenAS::Util::Vector3D OpenAS::System::Entity::GetPosition()
{
	return this->vPosition;
}

OpenAS::Util::Vector3D OpenAS::System::Entity::GetRotation()
{
	return this->vRotation;
}

int OpenAS::System::Entity::GetID()
{
	return this->ID;
}

int OpenAS::System::Entity::SetID(int id)
{
	this->ID = id;

	return 1;
}
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

#include <system\oas_entitymanager.h>
#include <system\oas_game.h>

extern Game* g;


OpenAS::System::EntityManager::EntityManager()
{
	for(int i = 0; i < MAX_ENTITIES; i++)
	{
		this->entities[i] = NULL;
	}
}

OpenAS::System::EntityManager::~EntityManager()
{

}

int OpenAS::System::EntityManager::CreateEntity(const char* _szEntityName, const char* _szScriptName, OpenAS::Util::Vector3D _vPosition, OpenAS::Util::Vector3D _vRotation, const char* _szModelName)
{
	// find a free entity slot
	int iSlot = -1;

	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (entities[i] == NULL) {
			// found a free slot
			iSlot = i;
			break;
		}
	}

	if (iSlot == -1) {
		g->GetLogManager()->AddErrorLog("ERR_LIMITS","entitycount",time(NULL),g->GetLogManager()->GetDebugFlag(),LOG_FILE);
		// no free entity slot found
		return -1;
	}

	if (entities[iSlot] == NULL)
	{
		entities[iSlot] = new OpenAS::System::Entity(iSlot,_szEntityName,_szScriptName,_vPosition,_vRotation,_szModelName);
	}
	
	return iSlot;
}

int OpenAS::System::EntityManager::DestroyEntity(int id)
{
	delete(entities[id]);
	entities[id] = NULL;

	return 1;
}

int OpenAS::System::EntityManager::GetEntityCount()
{
	int tmp = 0;
	for(int i = 0; i < MAX_ENTITIES; i++)
	{
		if(entities[i] == NULL)
			tmp++;
	}
	return (MAX_ENTITIES-tmp);
}

OpenAS::System::Entity* OpenAS::System::EntityManager::GetEntity(int id)
{
	if(entities[id] == NULL)
		return NULL;

	return this->entities[id];
}

OpenAS::System::Entity* OpenAS::System::EntityManager::GetEntityByName(const char* name)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if(entities[i] == NULL) continue;
		if(!strcmp(this->entities[i]->GetEntityName(),name))
		{
			return this->GetEntity(i);
		}
	}

	return 0;
}
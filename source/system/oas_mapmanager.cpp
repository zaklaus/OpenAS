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

#include <system\oas_mapmanager.h>
#include <system\oas_game.h>

using namespace OpenAS::System;

extern Game* g;

MapManager::MapManager()
{
	for (int i = 0; i < MAX_MAPS; i++)
		m_maps[i] = NULL;
};

int MapManager::InstallMap(const char* filename)
{
	int iSlot = -1;

	for (int i = 0; i < MAX_MAPS; i++) {
		if (m_maps[i] == NULL) {
			// found a free slot
			iSlot = i;
			break;
		}
	}

	if (iSlot == -1) {
		g->GetLogManager()->AddErrorLog("ERR_LIMITS", "mapcount", time(NULL), g->GetLogManager()->GetDebugFlag(), LOG_FILE);
		// no free entity slot found
		return -1;
	}

	if (m_maps[iSlot] == NULL)
	{
		m_maps[iSlot] = new OpenAS::System::Map(iSlot, filename);
		return iSlot;
	}
	return -1;
};

void MapManager::RemoveMap(int id)
{
	if (m_maps[id] != NULL) { delete m_maps[id]; m_maps[id] = NULL; }
};

void MapManager::LoadMap(int id)
{
	if (m_maps[id] != NULL)
		m_maps[id]->LoadThisMap();
};

void MapManager::UnloadMap(int id)
{
	if (m_maps[id] != NULL)
		m_maps[id]->UnloadThisMap();
};

void MapManager::SwitchMap(int id)
{
	for (int i = 0; i < MAX_MAPS; i++)
	{
		if (m_maps[i] != NULL)
		{
			if (m_maps[i]->GetMapID() != id)
				UnloadMap(i);
		}
	}
	m_maps[id]->LoadThisMap();
};

Map* MapManager::GetMap(int id)
{
	if (m_maps[id] != NULL)
		return m_maps[id];
	else return NULL;
};

Map* MapManager::GetMapByName(const char* name)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (m_maps[i] == NULL) continue;
		if (!strcmp(this->m_maps[i]->GetMapName(), name))
		{
			return this->GetMap(i);
		}
		return NULL;
	}

	return NULL;
};
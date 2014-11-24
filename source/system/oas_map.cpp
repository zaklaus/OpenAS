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

#include <system\oas_map.h>
#include <system\oas_game.h>
#include <gl\GL.h>

using namespace OpenAS::System;

extern Game* g;

Map::Map(int id, const char* mapfile)
{
	for (int i = 0; i<MAX_ENTITIES; i++)
		m_iEntities[i] = -1;
	for (int i = 0; i<8; i++)
		m_lid[i] = -1;

	Parser::GetMapName((char*)mapfile, this->m_szMapName);
	Parser::GetMapAuthor((char*)mapfile, this->m_szMapAuthor);
	Parser::GetMapVersion((char*)mapfile, this->m_szMapVersion);

	sprintf(m_szMapFileName, "%s", mapfile);

	m_bLoaded = false;
	m_iMapID = id;
};

void Map::UnloadThisMap()
{
	if (this->m_bLoaded == false)
		return;

	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (m_iEntities[i] != -1)
		{
			if (g->GetEntityManager()->GetEntity(i) != NULL)
			{
				g->GetEntityManager()->DestroyEntity(i);
			}
		}
	}

	this->m_bLoaded = false;
};

void Map::LoadThisMap()
{
	if (this->m_bLoaded == true)
		return;

	std::ifstream fp(this->m_szMapFileName);
	std::string line;
	while (std::getline(fp, line))
	{
		
		std::istringstream iss(line);
		std::string null, tmp;
		
		if ((iss >> null >> tmp))
		{
			if (null == "CreateEntity")
			{
				//printf(tmp.c_str());
				int start = line.find(" ");
				std::string args = line.substr(start+1, line.length()-1);
				int c = Parser::CreateMapEntity(tmp);

				if (c == -1)
					g->GetLogManager()->AddErrorLog("ERR_OMAP_SYNTAX", this->m_szMapFileName, time(NULL), 1, LOG_FILE);
				else
					m_iEntities[c] = c;
			}
			else if (null == "CreateLight")
			{
				int start = line.find(" ");
				std::string args = line.substr(start + 1, line.length() - 1);
				int c = Parser::CreateLight(this->m_iMapID,tmp);

				if (c == -1)
					g->GetLogManager()->AddErrorLog("ERR_OMAP_SYNTAX", this->m_szMapFileName, time(NULL), 1, LOG_FILE);
				
			}
		}
	}
	this->m_bLoaded = true;
};

int Map::EnableLight(int id)
{
	for (int i = 0; i < 8; i++)
	{
		if (m_lstatus[i] == 0)
		{
			if (m_cLights[id].exflag == 1)
			{
				glEnable(GL_LIGHT0 + i);

				float ambientLight[3] = { m_cLights[id].amb.x, m_cLights[id].amb.y, m_cLights[id].amb.z };
				float diffuseLight[3] = { m_cLights[id].diff.x, m_cLights[id].diff.y, m_cLights[id].diff.z };
				float specularLight[3] = { m_cLights[id].spec.x, m_cLights[id].spec.y, m_cLights[id].spec.z };
				float position[3] = { m_cLights[id].pos.x, m_cLights[id].pos.y, m_cLights[id].pos.z };

				glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambientLight); glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); glLightfv(GL_LIGHT0, GL_POSITION, position);
				m_cLights[id].lightID = i;
				m_lstatus[i] = true;
				m_lid[i] = id;
				return 1;
			}
		}
	}
	return 0;
};
int Map::DisableLight(int id)
{
	if (m_lstatus[m_cLights[id].lightID] == true)
	{
		m_lstatus[m_cLights[id].lightID] = false;
		glDisable(GL_LIGHT0 + m_cLights[id].lightID);
		m_cLights[id].lightID = -1;
		m_lid[id] = -1;
		return 1;
	}
	return 0;
};
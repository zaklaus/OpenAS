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

using namespace OpenAS::System;

extern Game* g;

Map::Map(int id, const char* mapfile)
{
	for (int i = 0; i<MAX_ENTITIES; i++)
		m_iEntities[i] = -1;

	Parser::GetMapName((char*)mapfile, this->m_szMapName);
	Parser::GetMapAuthor((char*)mapfile, this->m_szMapAuthor);
	Parser::GetMapVersion((char*)mapfile, this->m_szMapVersion);

	sprintf(m_szMapFileName, "%s", mapfile);

	m_bLoaded = false;
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
		}
	}
	this->m_bLoaded = true;
};
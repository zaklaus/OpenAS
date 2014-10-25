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

#include <parser\oas_mapparser.h>
#include <system\oas_game.h>

int OpenAS::Parser::CreateMapEntity(std::string tmp)
{
	//printf("%s", tmp.c_str());
	char _szEntityName[128] = ""; char _szScriptName[128] = ""; float posx, posy, posz, rotx, roty, rotz; char _szModelName[128] = "";
	//sscanf(out,"%s %s %f %f %f %f %f %f %s",_szEntityName,_szScriptName,&posx,&posy,&posz,&rotx,&roty,&rotz,_szModelName);
	//std::istringstream iss(tmp);

	//iss >> _szEntityName >> expect<'#'> >> _szScriptName >> expect<'#'> >> posx >> expect<'#'> >> posy >> expect<'#'> >> posz >> expect<'#'> >> rotx >> expect<'#'> >> roty >> expect<'#'> >> rotz >> expect<'#'> >> _szModelName;

	char* pch;
	char str[128] = "";
	sprintf(str, "%s", tmp.c_str());

	pch = strtok(str, " ");
	sprintf(_szEntityName, "%s", pch);
	int i = 0;
	while (pch != NULL)
	{
		pch = strtok(NULL, " ");
		i++;

		switch (i)
		{
		case 1:
			sprintf(_szScriptName, "%s", pch);
			break;
		case 2:
			posx = (float)atof(pch);
			break;
		case 3:
			posy = (float)atof(pch);
			break;
		case 4:
			posz = (float)atof(pch);
			break;
		case 5:
			rotx = (float)atof(pch);
			break;
		case 6:
			roty = (float)atof(pch);
			break;
		case 7:
			rotz = (float)atof(pch);
			break;
		case 8:
			sprintf(_szModelName, "%s", pch);
			break;
		}
	}

	delete pch;

	OpenAS::Util::Vector3D pos(posx, posy, posz);
	OpenAS::Util::Vector3D rot(rotx, roty, rotz);

	//printf("%s := %f\n", _szEntityName, posx);

	//delete _szEntityName, _szModelName, _szScriptName;

	//printf("%s", g->GetMapManager()->GetMap(0)->GetMapAuthor());
	Game* g = Game::GetGame();

	return g->GetEntityManager()->CreateEntity((const char*)_szEntityName, (const char*)_szScriptName, pos, rot, (const char*)_szModelName);
	//return -1;
}
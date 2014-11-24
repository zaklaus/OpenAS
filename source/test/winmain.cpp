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

#include<Windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include<system\oas_game.h>
#include<util\oas_bitstream.h>

using namespace OpenAS::System;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	// Enable console
	//
	AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 256);
    *stdin = *hf_in;

	// Test code
	//
	OpenAS::Util::BitStream bs;
	
	bs.Push("test");
	bs.Push(1); bs.Push(2); bs.Push(3);
	bs.Push(4.5f);
	bs.Push(true);

	int cisla[3] = { 0, 0, 0 };
	float cislo = 0.0f;
	std::string text = "";
	bool vyber = false;

	bs.Pop(cisla[0]); bs.Pop(cisla[1]); bs.Pop(cisla[2]);
	bs.Pop(cislo);
	bs.Pop(text);
	bs.Pop(vyber);

	printf("Vysledok: %s %d %d %d %f %b", text.c_str(), cisla[0], cisla[1], cisla[2], cislo, vyber);
	// Get settings from system.cfg
	//
	char width[128], height[128],mapname[128],models[128],scripts[128],maps[128], cfps[128];

	OpenAS::Parser::GetMapSetting("system.cfg", "width", width,"1024");
	OpenAS::Parser::GetMapSetting("system.cfg", "height", height,"768");
	OpenAS::Parser::GetMapSetting("system.cfg", "map", mapname,"menu.omap");
	OpenAS::Parser::GetMapSetting("system.cfg", "models", models,"models\\");
	OpenAS::Parser::GetMapSetting("system.cfg", "scripts", scripts,"scripts\\");
	OpenAS::Parser::GetMapSetting("system.cfg", "maps", maps,"maps\\");
	OpenAS::Parser::GetMapSetting("system.cfg", "fps", cfps, "60");

	OpenAS::Util::SettingsData sData;
	sData.maps = maps;
	sData.scripts = scripts;
	sData.models = models;
	sData.fps = atoi(cfps);

	// Init game
	//
	Game* g = new Game("OpenAS Test Project",mapname,atoi(width), atoi(height),sData);
	

	return 0;
}
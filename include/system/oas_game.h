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
#ifndef OAS_GAME_H
#define OAS_GAME_H

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <util\oas_generic.h>
#include <system\oas_interfaces.h>
#include <system\oas_singleton.h>
#include <system\oas_defaults.h>
#include <system\oas_platform.h>
#include <system\oas_sdl2application.h>
#include <system\oas_logmanager.h>
#include <system\oas_entitymanager.h>
#include <system\oas_scriptsex.h>
#include <system\oas_mapmanager.h>

class OAS_API Game
{
private:
	OpenAS::System::LogManager m_cLogManager;
	OpenAS::System::SDLApplication* m_cSDLApplication;
	OpenAS::System::EntityManager m_cEntityManager;
	OpenAS::System::ScriptsEx m_cScripts;
	OpenAS::System::MapManager* m_cMapManager;
	OpenAS::Util::SettingsData m_sData;
public:
	static Game* GetGame(){ return m_gInstance; };
	Game(const std::string& title,std::string, int,int,SettingsData);
	~Game();

	std::string m_firstMap;

	// Member methods
	//
	OpenAS::System::LogManager* GetLogManager();
	OpenAS::System::SDLApplication* GetSDLApplication();
	OpenAS::System::EntityManager* GetEntityManager();
	OpenAS::System::EntityManager GetStaticEntityManager();
	//OpenAS::System::EntityManager* GetCachedEntityManager(){ return (OpenAS::System::EntityManager*)ent; };
	OpenAS::System::ScriptsEx* GetScriptsManager();
	OpenAS::System::MapManager* GetMapManager();
	OpenAS::Util::SettingsData* GetSettings(){ return &m_sData; };

	int GetWindowWidth(){ return m_iWndW; };
	int GetWindowHeight(){ return m_iWndH; };
	int GetMaxFPS(){ return m_maxFPS; };
	void SetMaxFPS(int i){ m_maxFPS = i; };
	bool IsRunning(){ return m_bIsRunning; };
	// Test methods
	//
	void dlltest();

private:
	std::string m_title;
	unsigned int ent;
	int m_iWndW, m_iWndH;
	int m_maxFPS;
	static Game* m_gInstance;
	bool m_bIsRunning;
};
#endif
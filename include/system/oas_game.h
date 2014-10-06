#ifndef OAS_GAME_H
#define OAS_GAME_H

#include <system\oas_platform.h>
#include <system\oas_sdl2application.h>
#include <system\oas_logmanager.h>

class OAS_API Game
{
private:
	OpenAS::System::LogManager m_cLogManager;

public:
	Game();
	~Game();


	// Member methods
	//
	OpenAS::System::LogManager* GetLogManager();

	// Test methods
	//
	void dlltest();
};

#endif
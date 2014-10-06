#ifndef OAS_GAME_H
#define OAS_GAME_H

#include <system\oas_platform.h>
#include <system\oas_sdl2application.h>
#include <system\oas_logmanager.h>

class OAS_API Game
{
private:
	OpenAS::System::LogManager m_cLogManager;
	OpenAS::System::SDLApplication* m_cSDLApplication;
public:
	Game(const std::string& title);
	~Game();


	// Member methods
	//
	OpenAS::System::LogManager* GetLogManager();
	OpenAS::System::SDLApplication* GetSDLApplication();

	// Test methods
	//
	void dlltest();

private:
	std::string m_title;
};

#endif
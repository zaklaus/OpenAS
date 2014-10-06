#include <system/oas_game.h>


Game::Game(const std::string& title)
{
	m_title = title;
	m_cSDLApplication = new OpenAS::System::SDLApplication(title);
}

Game::~Game()
{

}

// Get member methods
//
OpenAS::System::LogManager* Game::GetLogManager()
{
	return &this->m_cLogManager;
}

OpenAS::System::SDLApplication* Game::GetSDLApplication()
{
	return this->m_cSDLApplication;
}

// Test code
//
void Game::dlltest()
{
	printf("Hello, DLL World!\n");
	this->GetLogManager()->AddLog("TestMethod","Testing DLL Log Manager",time(NULL),1,"test.txt");
}
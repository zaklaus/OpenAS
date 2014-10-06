#include <system/oas_game.h>


Game::Game()
{

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

void Game::dlltest()
{
	printf("Hello, DLL World!\n");
	this->GetLogManager()->AddLog("TestMethod","Testing DLL Log Manager",time(NULL),1,"test.txt");
}
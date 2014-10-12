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

#include <system/oas_game.h>


OpenAS::System::Game::Game(const std::string& title)
{
	m_title = title;
	m_cSDLApplication = new OpenAS::System::SDLApplication(title);
}

OpenAS::System::Game::~Game()
{

}

// Get member methods
//
OpenAS::System::LogManager* OpenAS::System::Game::GetLogManager()
{
	return &this->m_cLogManager;
}

OpenAS::System::SDLApplication* OpenAS::System::Game::GetSDLApplication()
{
	return this->m_cSDLApplication;
}

OpenAS::System::EntityManager* OpenAS::System::Game::GetEntityManager()
{
	return &this->m_cEntityManager;
}

OpenAS::System::ScriptsEx* OpenAS::System::Game::GetScriptsManager()
{
	return &this->m_cScripts;
}

// Test code
//
void OpenAS::System::Game::dlltest()
{
	printf("Hello, DLL World!\n");
	this->GetLogManager()->AddLog("TestMethod","Testing DLL Log Manager",time(NULL),1,"test.txt");
	this->GetLogManager()->AddLog("TestMethod","No Chance finding this line in test.txt",time(NULL));
	this->GetLogManager()->AddLog("TestMethod","Yet Another Test Message",time(NULL),1,"test.txt");
}
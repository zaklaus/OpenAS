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
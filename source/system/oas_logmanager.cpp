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

#include <system\oas_logmanager.h>

OpenAS::System::LogManager::LogManager(){}
OpenAS::System::LogManager::~LogManager(){}


// Adds log to file
//
void OpenAS::System::LogManager::AddLog(std::string title,std::string msg,const time_t ts,int cmd,std::string filename)
{
	// Prepare our log
	//
	std::string szTime = OpenAS::Util::TStoDT(ts);
	std::string log = std::string("Log: ["+szTime+"] "+title+": "+msg+"\n");
	
	// Write log to file
	//
	if(!OpenAS::Util::WriteFile(filename,log,std::ios::app))
	{
		// Write to file failed
		//
		if(cmd > 0)
		{
			this->AddLog("WriteFileERR","Could not write to file.",time(NULL));
		}
	}

	// Write to console
	//
	if(cmd > 0)
	{
		this->AddLog(title,msg,ts);
	}
}

// Adds log only to console
//
void OpenAS::System::LogManager::AddLog(std::string title,std::string msg,const time_t ts)
{
	// Prepare our log
	//
	std::string szTime = OpenAS::Util::TStoDT(ts);
	std::string log = std::string("Log: ["+szTime+"] "+title+": "+msg);

	// Write to console
	//
	std::cout << log << std::endl;
}
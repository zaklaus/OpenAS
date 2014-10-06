#include <system\oas_logmanager.h>

OpenAS::System::LogManager::LogManager(){}
OpenAS::System::LogManager::~LogManager(){}


// Adds log to file
//
void OpenAS::System::LogManager::AddLog(std::string title,std::string msg,const time_t ts,int cmd,std::string filename)
{
	// Prepare our log
	//
	std::string time = OpenAS::Util::TStoDT(ts);
	std::string log = std::string("Log: ["+time+"] "+title+": "+msg+"\n");
	
	// Write log to file
	//
	if(!OpenAS::Util::WriteFile(filename,log,std::ios::app))
	{
		// Write to file failed
		//
		if(cmd > 0)
		{
			this->AddLog("WriteFileERR","Could not write to file.",ts);
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
	std::string time = OpenAS::Util::TStoDT(ts);
	std::string log = std::string("Log: ["+time+"] "+title+": "+msg);

	// Write to console
	//
	std::cout << log << std::endl;
}
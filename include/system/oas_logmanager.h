#ifndef OAS_LOGMANAGER_H
#define OAS_LOGMANAGER_H

#include <system\oas_platform.h>
#include <util\oas_stringutil.h>
#include <util\oas_ioutil.h>
#include <util\oas_timeutil.h>


namespace OpenAS {
	namespace System {
		class OAS_API LogManager
		{
		public:
			LogManager();
			~LogManager();

			void AddLog(std::string title,std::string msg,const time_t ts,int cmd,std::string filename);
			void AddLog(std::string title,std::string msg,const time_t ts);
		};
	}
}
#endif
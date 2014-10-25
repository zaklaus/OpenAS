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
#pragma once
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
		private:
			bool bDebugCmd;
			

		public:
			LogManager();
			~LogManager();

			void AddLog(std::string title,std::string msg,const time_t ts,int cmd,std::string filename);
			void AddErrorLog(std::string err, std::string msg,const time_t ts,int cmd,std::string filename);
			void AddErrorLog(std::string err, std::string msg,const time_t ts);
			void AddLog(std::string title,std::string msg,const time_t ts);
			bool GetDebugFlag(){ return bDebugCmd; };
			void SetDebugFlag(bool _bDebugCmd){ bDebugCmd = _bDebugCmd; };
			//char** GetError(const char* err){ /*return err_msg[errno];*/ for(int i = 0; i < sizeof(err_str); i++) {if(!strcmp(err_str[i],err)){ return (char**){err_str[i],err_msg[i]}; }} return (char**){"",""}; };
			
		};
	}
}
#endif
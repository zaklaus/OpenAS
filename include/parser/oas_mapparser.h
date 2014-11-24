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

#ifndef OAS_MAPPARSER_H
#define OAS_MAPPARSER_H

#include <system\oas_platform.h>
#include <util\oas_math.h>
#include <util\oas_stringutil.h>

using namespace OpenAS::Util;

namespace OpenAS
{
	namespace Parser
	{
		inline OAS_API void GetMapName(char* file, char* out)
		{
			

			std::ifstream fp(file);
			std::string line;
			while(std::getline(fp,line))
			{
				std::istringstream iss(line);
				std::string null,tmp;

				if((iss >> null >> tmp))
				{
					if(null == "MapName")
					{
						sprintf(out,"%s",tmp.c_str());
						return;
					}
				}
			}
			return;
		}

		inline OAS_API void GetMapAuthor(char* file, char* out)
		{
			

			std::ifstream fp(file);
			std::string line;
			while(std::getline(fp,line))
			{
				std::istringstream iss(line);
				std::string null,tmp;

				if((iss >> null >> tmp))
				{
					if(null == "MapAuthor")
					{
						sprintf(out,"%s",tmp.c_str());
						return;// (char*)&out;
					}
				}
			}
			return;// (char*)&out;
		}

		inline OAS_API void GetMapVersion(const char* file, char* out)
		{
			

			std::ifstream fp(file);
			std::string line;
			while(std::getline(fp,line))
			{
				std::istringstream iss(line);
				std::string null,tmp;

				if((iss >> null >> tmp))
				{
					if(null == "MapVersion")
					{
						sprintf(out,"%s",tmp.c_str());
						return;// (char*)&out;
					}
				}
			}
			return;// (char*)&out;
		}

		inline OAS_API void GetMapSetting(const char* file, const char* item, char* out, const char* default)
		{

			std::ifstream fp(file);
			std::string line;
			while(std::getline(fp,line))
			{
				std::istringstream iss(line);
				std::string null,tmp;

				if((iss >> null >> tmp))
				{
					char cnull[256] = "";
					sprintf(cnull,"%s",null.c_str());
					if(!strcmp(cnull,item))
					{
						sprintf(out,"%s",tmp.c_str());
						return; // (char*)&out;
					}
				}
			}
			sprintf(out, "%s", default);
			return;
		}

		OAS_API int CreateMapEntity(std::string tmp);
		OAS_API int CreateLight(int,std::string tmp);
	}
}

#endif
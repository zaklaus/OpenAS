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

#ifndef OAS_IOUTIL_H
#define OAS_IOUTIL_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<Windows.h>

namespace OpenAS {

	namespace Util {
		inline OAS_API void getFilesList(std::string filePath, std::string extension, std::vector<std::string> & returnFileName)
		{
			WIN32_FIND_DATA fileInfo;
			HANDLE hFind;
			std::string  fullPath = filePath + extension;
			hFind = FindFirstFile(fullPath.c_str(), &fileInfo);
			if (hFind == INVALID_HANDLE_VALUE){ return; }
			else {
				returnFileName.push_back(filePath + fileInfo.cFileName);
				while (FindNextFile(hFind, &fileInfo) != 0){
					returnFileName.push_back(filePath + fileInfo.cFileName);
				}
			}
		}
		inline OAS_API int WriteFile(std::string filename, std::string msg, int flags=0)
		{
			std::ofstream file;
			file.open(filename,flags);
			if(file.is_open())
			{
				file << msg;
				file.close();
			}
			else return 0;

			return 1;
		}

		inline OAS_API int ReadFile(std::string filename, std::string* buffer, int flags=0)
		{
			std::ifstream file;
			std::stringstream ss;
			std::string line;
			file.open(filename,flags);
			if(file.is_open())
			{
				while(std::getline(file,line))
				{
					ss << line << "\n";
				}
				*buffer = ss.str();
				file.close();
			}
			else return 0;

			return 1;
		}
	}
}

#endif
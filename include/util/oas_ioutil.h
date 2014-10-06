#ifndef OAS_IOUTIL_H
#define OAS_IOUTIL_H

#include<iostream>
#include<fstream>
#include<sstream>

namespace OpenAS {

	namespace Util {

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
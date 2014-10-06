#ifndef OAS_TIMEUTIL_H
#define OAS_TIMEUTIL_H

#include <time.h>
#include <ctime>
#include <algorithm>

namespace OpenAS {

	namespace Util {


		inline OAS_API std::string TStoDT(const time_t rawtime)
		{
			std::string s = std::string(ctime(&rawtime));
			return std::string(s.substr(0,s.length()-1));
		}
	}
}

#endif
#ifndef OAS_INTERFACES_H
#define OAS_INTERFACES_H

#include<system\oas_platform.h>

namespace OpenAS {

	namespace System {

		class OAS_API IApplication
		{
		public:
			virtual ~IApplication(){}
			virtual bool initialized() = 0;
			virtual int run() = 0;
		};

	}

}

#endif
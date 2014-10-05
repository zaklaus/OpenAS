#ifndef VTX_INTERFACES_H
#define VTX_INTERFACES_H

#include<system\vtx_platform.h>

namespace Vortex {

	namespace System {

		class VTX_API IApplication
		{
		public:
			virtual ~IApplication(){}
			virtual bool initialized() = 0;
			virtual int run() = 0;
		};

	}

}

#endif
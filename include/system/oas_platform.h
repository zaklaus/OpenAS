#ifndef OAS_PLATFORM_H
#define OAS_PLATFORM_H

//
// NOTE:
//
//	Define pre-processor macros for DLL export import, and
//  system macros
//
#ifdef _WIN32

	#define OAS_SYS_WINDOWS
	//defined to disable <windows.h> from defining the min and max macros
	#ifndef NOMINMAX
	#define NOMINMAX
	#endif

#elif defined (__linux__)
#define OAS_SYS_LINUX
#elif defined (__APPLE__)
#define OAS_SYS_MACOS
#endif

#ifndef OAS_STATIC_BUILD
	#ifdef OAS_SYS_WINDOWS
		#ifndef OAS_NONCLIENT_BUILD
			#define OAS_API __declspec(dllexport)
		#else
			#define OAS_API __declspec(dllimport)
		#endif

		//Visual c++ compiler warning C4251 disable
		#ifdef _MSC_VER
			#pragma warning(disable : 4251)
		#endif
	#else
		#ifdef __GNUC__	 >= 4
			#define OAS_API __attribute__ ((__visibility__("default")))
		#else 
			#define OAS_API OAS_API
		#endif
	#endif
#else
	#define OAS_API OAS_API
#endif


#endif
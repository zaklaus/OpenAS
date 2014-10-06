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
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

#include <system\oas_platform.h>
#include <system\oas_defaults.h>
#include <util\oas_timeutil.h>

#pragma once

namespace OpenAS
{
	namespace System
	{
		class OAS_API TickManager
		{
		private:
			bool bAdaptive;
			int iTickrate,deltaTime;
			time_t lastTick;

		public:
			TickManager()
			{
				bAdaptive = TICKRATE_ADAPTIVE;
				iTickrate = TICKRATE;
				deltaTime = 1;
				lastTick = time(NULL);
			};

			void WaitForTick();
			int GetDeltaTime(){ return deltaTime; };
			void SetAdaptive(bool state){ bAdaptive = state; };
			bool GetAdaptive(){ return bAdaptive; };
			time_t GetLastTick(){ return lastTick; };
		};
	}
}
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
#include<system\oas_platform.h>
#include<vector>

namespace OpenAS
{
	namespace Util
	{
		

		class OAS_API BitStream
		{
		public:
			BitStream();
			~BitStream();

			void Push(int);
			void Push(float);
			void Push(double);
			void Push(const char*);
			void Push(bool);

			void Pop(int&);
			void Pop(float&);
			void Pop(double&);
			void Pop(std::string&);
			void Pop(bool&);
		private:
			std::vector<int> iData;
			std::vector<float> fData;
			std::vector<double> dData;
			std::vector<std::string> sData;
			std::vector<bool> bData;
		};
	}
}

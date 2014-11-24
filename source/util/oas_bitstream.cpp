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

#include <util\oas_bitstream.h>
#include <util\oas_stringutil.h>

using namespace OpenAS::Util;

BitStream::BitStream()
{
	
}

BitStream::~BitStream()
{
	
}
void BitStream::Push(int data)
{
	this->iData.push_back(data);
}
void BitStream::Push(float data)
{
	this->fData.push_back(data);
}
void BitStream::Push(double data)
{
	this->dData.push_back(data);
}
void BitStream::Push(const char* data)
{
	this->sData.push_back(data);
}
void BitStream::Push(bool data)
{
	this->bData.push_back(data);
}

void BitStream::Pop(float& variable)
{
	variable = this->fData[this->fData.size() - 1];
	this->fData.erase(this->fData.begin() + this->fData.size() - 1, this->fData.end());
}

void BitStream::Pop(int& variable)
{
	variable = this->iData[this->iData.size() - 1];
	this->iData.erase(this->iData.begin() + this->iData.size() - 1, this->iData.end());
}

void BitStream::Pop(double& variable)
{
	variable = this->dData[this->dData.size() - 1];
	this->dData.erase(this->dData.begin() + this->dData.size() - 1, this->dData.end());
}

void BitStream::Pop(std::string& variable)
{
	variable = this->sData[this->sData.size() - 1];
	this->sData.erase(this->sData.begin() + this->sData.size() - 1, this->sData.end());
}
void BitStream::Pop(bool& variable)
{
	variable = this->bData[this->bData.size() - 1];
	this->bData.erase(this->bData.begin() + this->bData.size() - 1, this->bData.end());
}
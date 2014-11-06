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

#ifndef OAS_INTERFACES_H
#define OAS_INTERFACES_H

#include<system\oas_platform.h>
#include<Windows.h>

namespace OpenAS {

	class OAS_API INonCopyable
	{
	protected:
		INonCopyable(){}
		~INonCopyable(){}
	private:
		INonCopyable(const INonCopyable& other);
		const INonCopyable& operator= (const INonCopyable& other);
	};

	class OAS_API IApplication : INonCopyable
	{
	public:
		virtual ~IApplication(){}
		virtual bool initialized() = 0;
		virtual int run() = 0;
	};

	class OAS_API IManager
	{
	public:
		virtual void VStart() = 0;
		virtual void VStop() = 0;
	};

	class Mutex{
		friend class Lock;
	public:
		Mutex()
		{
			InitializeCriticalSection(&_critSection);
		}

		~Mutex()
		{
			DeleteCriticalSection(&_critSection);
		}
	private:
		void Acquire()
		{
			EnterCriticalSection(&_critSection);
		}

		void Release()
		{
			LeaveCriticalSection(&_critSection);
		}
		CRITICAL_SECTION _critSection;
	};

	class Lock{
	public:
		// Acquire the state of the semaphore   
		Lock(Mutex & mutex)
			: _mutex(mutex)
		{
			_mutex.Acquire();
		}
		// Release the state of the semaphore   
		~Lock()
		{
			_mutex.Release();
		}
	private:
		Mutex & _mutex;
	};



	class varablelock{
	public:

		//method to get Instance of class 
		static varablelock *getInstance(void)
		{
			//Note that the class is only created when this method is called first time   
			if (!instance_)
				instance_ = new varablelock;
			return instance_;
		}

		//method to delete Instance of class 
		static void deleteInstance(void)
		{
			if (instance_)
				delete instance_;
			instance_ = NULL;

			//important as this can create dead reference problems 
		}
		Mutex mutex_;
		varablelock() {};
		~varablelock() {};

	private:
		//variable to store the instance of singleton 
		static varablelock *instance_;
		//default constructor should be private to prevent instantiation 
		//destructor should be made private so no one can delete this accidently 
		//We also need to prevent copy being created of the object 
		varablelock(const varablelock&);
	};
}

#endif
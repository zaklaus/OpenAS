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


#include <system\oas_input.h>
//#include <stdio.h>

using namespace OpenAS::System;

Input *Input::m_gInst;

Input& g_Input = Input::instance();

Input::Input() {
	textMode = false;
	this->m_gInst = this;
	for (int i = 0; i < INPUT_NUM_SCANCODES; i++) {
		currentKeys[i] = false;
	}
}

Input::~Input() {
}

void Input::Update(){
	
	for (int i = 0; i < INPUT_NUM_SCANCODES; i++) {
		downKeys[i] = false;
		upKeys[i] = false;
	}
	while (SDL_PollEvent(&event)) {
		if (SDL_KEYDOWN == event.type) {
			int value = event.key.keysym.scancode;
			//printf("%d\n\n", value);
			if (!currentKeys[value] && !textMode)
				downKeys[value] = true;
			else if (textMode)
				downKeys[value] = true;
			currentKeys[value] = true;
		}
		if (SDL_KEYUP == event.type) {
			int value = event.key.keysym.scancode;
			upKeys[value] = true;
			currentKeys[value] = false;
		}
	}
	
}

bool Input::GetKey(const int key) {
	return currentKeys[key];
}

bool Input::GetKeyDown(const int key) {
	return downKeys[key];
}

bool Input::GetKeyUp(const int key) {
	return upKeys[key];
}
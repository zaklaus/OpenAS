#include<Windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include<system\oas_game.h>

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	// Enable console
	//
	AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 256);
    *stdin = *hf_in;

	// Test code
	//
	Game* g = new Game("OpenAS Test Window");
	g->dlltest();
	g->GetSDLApplication()->run();
	system("pause>nul");
	return 0;
}
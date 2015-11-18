#include "System.h"

//	コンソール表示用
#include <io.h>
#include <fcntl.h>

// コンソール画面ハンドル保存用
int hConsole = 0;

///
// コンソール画面作成用
void CreateConsoleWindow(){

	::AllocConsole();
	hConsole = ::_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	*stdout = *::_fdopen(hConsole, "w");
	setvbuf(stdout, NULL, _IONBF, 0);

}

///
// コンソール画面終了用
void CloseConsoleWindow(){
	::_close(hConsole);
}
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow){

	std::unique_ptr<System> system = nullptr;
	bool result = false;

	system = std::make_unique<System>();
	if (!system)
	{
		
		return -1;
	}

	CreateConsoleWindow();
	result = system->Initialize();

	if (result)
	{
		system->Run();
	}

	CloseConsoleWindow();

	system->Shutdown();
	system.release();
	system = nullptr;

	return 0;
}
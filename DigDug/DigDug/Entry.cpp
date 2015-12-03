/*

	エントリーポイント
	プログラムが始まるとこ

*/


#include <iostream>

#pragma comment (lib,"Dx11FrameWork.lib")

#include "System.h"
#include "ConsoleWindow.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow){

	std::unique_ptr<ConsoleWindow> console = nullptr;
	std::unique_ptr<System> system = nullptr;
	bool result = false;
	console = std::make_unique<ConsoleWindow>();
	if (!console)
	{
		return -1;
	}
	system = std::make_unique<System>();
	if (!system)
	{
		std::cout << "Error: Coould not created System object" << std::endl;
		std::cout << "File: Entry.cpp 39 lines" << std::endl;
		return -1;
	}

	console->Create();
	
	result = system->Initialize();

	if (result)
	{
		std::cout << "Start system run" << std::endl;
		system->Run();
	}

	console->Close();


	system->Shutdown();
	system.release();
	system = nullptr;

	console.release();
	console = nullptr;
	return 0;
}
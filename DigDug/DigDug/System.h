#ifndef _SYSTEM_H
#define _SYSTEM_H

// �g���ĂȂ����C�u���������O
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <memory>
#include "GameController.h"
namespace{
	const bool FULL_SCREEN = false;
	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 1000.0f;
	const float SCREEN_NEAR = 0.1f;
}
class System
{
	public:
		System();
		System(const System&);
		~System();

		bool Initialize();
		void Shutdown();
		void Run();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		bool Frame();
		void InitializeWindows(POINT&);
		void ShutdownWindows();

	private:

		LPCWSTR m_appName;
		HINSTANCE m_hInstance;
		HWND m_hWnd;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM,LPARAM);

static System* g_applicationHandle = nullptr;

#endif
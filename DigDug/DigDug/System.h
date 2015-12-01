#ifndef _SYSTEM_H
#define _SYSTEM_H

// �g���ĂȂ����C�u���������O
#define WIN32_LEAN_AND_MEAN
// �W�����C�u����
#include <Windows.h>
#include <memory>
// ���색�C�u����

// ����N���X		
#include "GameController.h"
#include "SceneManager.h"
#include "GameFrame.h"
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
		std::unique_ptr<GameFrame> m_gameFrame;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM,LPARAM);

static System* g_applicationHandle = nullptr;

#endif
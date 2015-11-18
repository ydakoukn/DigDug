#include "System.h"
#include "GameController.h"

System::System(){


}

System::System(const System& other){


}


System::~System(){}


bool System::Initialize(){

	POINT screen = { 0, 0 };
	bool result;

	GameController::Create();
	GameController::GetPtr()->Initialize();

	InitializeWindows(screen);


	return true;

}

// 
void System::Shutdown(){

	this->ShutdownWindows();

	return;
}

// Application loop
void System::Run(){
	MSG msg;
	bool isEnd, result;

	SecureZeroMemory(&msg, sizeof(MSG));

	isEnd = false;

	while (!isEnd)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			isEnd = true;
		}
		else
		{
			
			result = Frame();

			if (!result)
			{
				isEnd = true;
			}
		}
	}

	// Exit application
	return;
}

bool System::Frame(){
	bool result;

	if (GameController::GetPtr()->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	return true;
}


LRESULT CALLBACK System::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	switch (uMsg)
	{
	
	case WM_KEYDOWN:

		GameController::GetPtr()->KeyDown(static_cast<unsigned int>(wParam));
		break;


	case WM_KEYUP:

		GameController::GetPtr()->KeyUp(static_cast<unsigned int>(wParam));
		break;


	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);

	}
	return S_OK;
}


void System::InitializeWindows(POINT& screen){
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	DEVMODE dmScreenSettings;
	ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));
	POINT position = { 0, 0 };

	// Get an extemal pointer to this object
	g_applicationHandle = this;

	// Get the instance of this application
	m_hInstance = ::GetModuleHandle(NULL);

	// Give the application a name
	m_appName = L"Engine";

	// Setup the windows class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_appName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class
	::RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen
	screen.x = ::GetSystemMetrics(SM_CXSCREEN);
	screen.y = ::GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);

		dmScreenSettings.dmPelsWidth = (unsigned int)screen.x;
		dmScreenSettings.dmPanningHeight = (unsigned int)screen.y;

		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		position.x = position.y = 0;
	}
	else
	{
		// If windowed then set it to 800�~600 resolution
		screen.x = 800;
		screen.y = 600;

		// Place the window in the middle of screen
		position.x = (::GetSystemMetrics(SM_CXSCREEN) - screen.x) / 2;
		position.y = (::GetSystemMetrics(SM_CYSCREEN) - screen.y) / 2;
	}

	// Create window eith the screen settings and get the handle to it
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_appName, m_appName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		position.x, position.y, screen.x, screen.y, NULL, NULL, m_hInstance, NULL);

	// Bring the window up on the screen and set it as main focus
	::ShowWindow(m_hWnd, SW_SHOW);
	::SetForegroundWindow(m_hWnd);
	::SetFocus(m_hWnd);

	// Hide the mouse cursor
	ShowCursor(false);

	return;
}


void System::ShutdownWindows(){
	// Show the mouse cursor
	::ShowCursor(true);

	// Remove the window
	::DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	// Remove the application instance
	::UnregisterClass(m_appName, m_hInstance);
	m_hInstance = NULL;

	// Release the pointer to this class
	g_applicationHandle = nullptr;

	return;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch (uMsg)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

		// Check if the window is being closed.
	case WM_CLOSE:
		::PostQuitMessage(0);
		break;
	default:
		return g_applicationHandle->MessageHandler(hWnd, uMsg, wParam, lParam);

	}
	return S_OK;
}
#ifndef _CONSOLEWINDOW_H
#define _CONSOLEWINDOW_H
/*
	コンソールウィンドウ作成クラス

*/

class ConsoleWindow
{
	public:
		ConsoleWindow();
		ConsoleWindow(ConsoleWindow&);
		~ConsoleWindow();
		void Create();
		void Close();
	private:

		int m_hConsole;
};

#endif
#ifndef _CONSOLEWINDOW_H
#define _CONSOLEWINDOW_H
/*
	�R���\�[���E�B���h�E�쐬�N���X

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
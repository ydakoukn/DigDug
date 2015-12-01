#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include "ConsoleWindow.h"
ConsoleWindow::ConsoleWindow(){
	m_hConsole = 0;
}
ConsoleWindow::ConsoleWindow(ConsoleWindow& other){

}

ConsoleWindow::~ConsoleWindow(){
	m_hConsole = 0;
}

void ConsoleWindow::Create(){

	::AllocConsole();
	m_hConsole = ::_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	*stdout = *::_fdopen(m_hConsole, "w");
	setvbuf(stdout, NULL, _IONBF, 0);

	return;
}

void ConsoleWindow::Close(){

	::_close(m_hConsole);

	return;
}
#include "SceneGame.h"

const std::string SceneGame::m_thisName = "Game";

SceneGame::SceneGame(SceneManager* manager) :
SceneBase(m_thisName,*manager)
{
}


SceneGame::~SceneGame()
{
}

void SceneGame::InitializeScene(){
	std::cout << "Start game" << std::endl;
	return;
}


void SceneGame::UpDataScene(){

	return;
}


void SceneGame::RenderScene(){

	return;
}

void SceneGame::ShutdownScene(){

	return;
}
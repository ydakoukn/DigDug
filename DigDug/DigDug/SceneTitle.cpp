#include "SceneTitle.h"
#include "SceneGame.h"
const std::string SceneTitle::m_thisName = "Title";
SceneTitle::SceneTitle(SceneManager* manager) :
SceneBase(m_thisName,*manager)
{
}


SceneTitle::~SceneTitle()
{
}


void SceneTitle::InitializeScene(){
	std::cout << "Start title" << std::endl;
	return;
}


void SceneTitle::UpDataScene(){

	return;
}


void SceneTitle::RenderScene(){

	return;
}

void SceneTitle::ShutdownScene(){

	return;
}
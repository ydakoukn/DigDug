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


void SceneTitle::Initialize(Dx11::Direct3DManager*, HWND){
	std::cout << "Start title" << std::endl;

	return;
}


void SceneTitle::Updata(){

	return;
}


void SceneTitle::Render(Dx11::Direct3DManager*){

	return;
}

void SceneTitle::Shutdown(){

	return;
}
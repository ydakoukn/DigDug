#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
std::unordered_map<std::string, std::shared_ptr<SceneBase>> SceneManager::m_scenes;
std::shared_ptr<SceneBase> SceneManager::m_currentScene = nullptr;
std::shared_ptr<SceneBase> SceneManager::m_nextScene = nullptr;

SceneManager::SceneManager()
{
	//　シーンが増えてくごとに追加していく
	Register(std::make_shared<SceneTitle>(this));
	Register(std::make_shared<SceneGame>(this));
	m_state = GameState::eInitialize;
	m_currentScene = GetScene(SceneTitle::m_thisName);
}


SceneManager::~SceneManager()
{
}


void SceneManager::Register(std::shared_ptr<SceneBase> registerScene){
	m_scenes.insert(std::make_pair(registerScene->GetName(), registerScene));
}

bool SceneManager::Frame(){
	bool result;
	result = Initialize();
	if (!result)
	{
		return false;
	}

	result = Render();
	if (!result)
	{
		return false;
	}

	result = UpData();
	if (!result)
	{
		return false;
	}
	return true;
}

bool SceneManager::Initialize(){
	if (m_state != GameState::eInitialize)
	{
		return true;
	}

	m_currentScene->InitializeScene();

	m_state = GameState::eRender;
	return true;
}

bool SceneManager::Render(){
	if (m_state != GameState::eRender)
	{
		return true;
	}

	m_currentScene->RenderScene();

	m_state = GameState::eUpData;
	return true;
}

bool SceneManager::UpData(){
	if (m_state != GameState::eUpData)
	{
		return true;
	}
	m_currentScene->UpDataScene();

	m_state = GameState::eRender;
	return true;
}


void SceneManager::Shutdown(){
	if (m_state != GameState::eShutdown)
	{
		return;
	}
	m_currentScene->ShutdownScene();
}


std::shared_ptr<SceneBase> SceneManager::GetScene(std::string name){
	return m_scenes[name];
}

void SceneManager::ChangeScene(std::string nextScene){
	std::cout << "Change scene" << std::endl;
	m_state = GameState::eShutdown;
	m_nextScene = m_scenes[nextScene];
	
	// TODO: フェードイン・フェードアウト処理

	m_currentScene->ShutdownScene();
	m_state = GameState::eInitialize;

	m_currentScene = m_nextScene;
	m_nextScene = nullptr;
	
}
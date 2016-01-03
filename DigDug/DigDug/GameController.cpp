#include "GameController.h"
#include "KeyCommandW.h"
#include "KeyCommandNull.h"
#include "KeyCommandA.h"
#include "KeyCommandD.h"
#include "KeyCommandS.h"

GameController* GameController::m_controller = nullptr;

GameController::GameController(){
	Initialize();
}

GameController::GameController(GameController& other){

}

GameController::~GameController(){
	
}

// 初期化
void GameController::Initialize(){

	for (int i = 0; i < kMaxKeyType; ++i)
	{
		m_keys[i] = false;
	}
	return;
}

// キーが押されているとき
void GameController::KeyDown(unsigned int input){
	m_keys[input] = true;
	return;
}

// キーが押されなくなった時
void GameController::KeyUp(unsigned int input){
	m_keys[input] = false;
	return;
}

// キーが押されたとき
bool GameController::IsKeyDown(unsigned int key){
	return m_keys[key];
}

// オブジェクト作成用関数
void GameController::Create(){
	if (m_controller == nullptr)
	{
		m_controller = new GameController;
	}
	return;
}

// 解放処理
// 必ず呼ぶ
void GameController::Shutdown(){
	if (m_controller)
	{
		delete m_controller;
		m_controller = nullptr;
	}
	return;
}

std::unique_ptr<KeyCommand>  GameController::GetKeyCommnad(){
	if (GameController::Get().IsKeyDown('W'))
	{
		return std::make_unique<KeyCommandW>();
	}
	else
		if (GameController::Get().IsKeyDown('A'))
	{
		return std::make_unique<KeyCommandA>();
	}
	else
	if (GameController::Get().IsKeyDown('S'))
	{
		return std::make_unique<KeyCommandS>();
	}
	else
	if (GameController::Get().IsKeyDown('D'))
	{
		return std::make_unique<KeyCommandD>();
	}
	else
	{
		return std::make_unique<KeyCommandNull>();
	}

}

// オブジェクトの取得
GameController& GameController::Get(){
	return *m_controller;
}
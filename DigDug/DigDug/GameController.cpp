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

// ������
void GameController::Initialize(){

	for (int i = 0; i < kMaxKeyType; ++i)
	{
		m_keys[i] = false;
	}
	return;
}

// �L�[��������Ă���Ƃ�
void GameController::KeyDown(unsigned int input){
	m_keys[input] = true;
	return;
}

// �L�[��������Ȃ��Ȃ�����
void GameController::KeyUp(unsigned int input){
	m_keys[input] = false;
	return;
}

// �L�[�������ꂽ�Ƃ�
bool GameController::IsKeyDown(unsigned int key){
	return m_keys[key];
}

// �I�u�W�F�N�g�쐬�p�֐�
void GameController::Create(){
	if (m_controller == nullptr)
	{
		m_controller = new GameController;
	}
	return;
}

// �������
// �K���Ă�
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

// �I�u�W�F�N�g�̎擾
GameController& GameController::Get(){
	return *m_controller;
}
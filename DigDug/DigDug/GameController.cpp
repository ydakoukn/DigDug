#include "GameController.h"

GameController* GameController::m_controller = nullptr;

GameController::GameController(){
	
}

GameController::GameController(GameController& other){

}

GameController::~GameController(){
	
}

void GameController::Initialize(){

	for (int i = 0; i < 256; ++i)
	{
		m_keys[i] = false;
	}
	return;
}

void GameController::KeyDown(unsigned int input){
	m_keys[input] = true;
	return;
}

void GameController::KeyUp(unsigned int input){
	m_keys[input] = false;
	return;
}

bool GameController::IsKeyDown(unsigned int key){
	return m_keys[key];
}

void GameController::Create(){
	if (m_controller == nullptr)
	{
		m_controller = new GameController;
	}
	return;
}

void GameController::Shutdown(){
	if (m_controller)
	{
		delete m_controller;
		m_controller = nullptr;
	}
	return;
}

GameController* GameController::GetPtr(){
	return m_controller;
}
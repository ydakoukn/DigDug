#include "EnemyManager.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

//
void EnemyManager::AddChild(std::shared_ptr<EnemyBase> child){
	m_enemyList.push_back(child);
	return;
}

//
void EnemyManager::Render(std::shared_ptr<DxShader::ShaderBase> shader){
	for (auto enemy : m_enemyList)
	{
		enemy->Render(shader);
	}

	return;
}

//
void EnemyManager::Updater(){
	for (auto enemy : m_enemyList)
	{
		enemy->Updater();
	}

	return;
}


void EnemyManager::Collide(){

	return;
}

std::list<std::shared_ptr<EnemyBase>> EnemyManager::GetEnemyList(){
	return m_enemyList;
}
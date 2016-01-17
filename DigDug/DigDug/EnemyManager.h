#pragma once
#include "EnemyBase.h"
#include <list>
#include <memory>
#include <ShaderBase.h>
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void AddChild(std::shared_ptr<EnemyBase>);

	void Render(std::shared_ptr<DxShader::ShaderBase>);

	void Updater();

	void Collide();

	std::list<std::shared_ptr<EnemyBase>> GetEnemyList();
private:
	std::list<std::shared_ptr<EnemyBase>> m_enemyList;
};



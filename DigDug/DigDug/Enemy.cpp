#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

//
void Enemy::CollideBuffer(){
	m_vec *= -1;
}

//
void Enemy::InitializeBuffer(){
	m_vec = 1.0f;
}

//
void Enemy::RenderBuffer(){

}


//
void Enemy::UpdateBuffer(){
	
	GetProperty()._transform._translation._x += m_vec;
}

#include "PlayerBase.h"

PlayerBase::Status PlayerBase::m_status;
PlayerBase::eKeyState PlayerBase::m_keyState = eKeyState::eNull;
PlayerBase::eActionState PlayerBase::m_actionState = eActionState::eNull;


PlayerBase::PlayerBase()
{
}


PlayerBase::~PlayerBase()
{
}

PlayerBase::Status& PlayerBase::GetStatus(){
	return m_status;
}

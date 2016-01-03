#ifndef _PLAYERBASE_H
#define _PLAYERBASE_H
/*
	プレイヤーの基底クラス
	updaterとrenderで共有するパラメーターを保持

*/
#include <Windows.h>
// 自作ライブラリ
#include <Direct3DManager.h>
#include <Rectangle.h>
#include <ViewCamera.h>
#include <Vector3.h>
class PlayerBase
{

	protected:
		struct Status{
			Status(){
				SecureZeroMemory(&_vector, sizeof(_vector));
				SecureZeroMemory(&_rotation, sizeof(_rotation));
				SecureZeroMemory(&_scale, sizeof(_scale));
				_speed = 0.0f;
			}
			DxMath::Vector3 _vector;
			DxMath::Vector3 _rotation;
			DxMath::Vector3 _scale;
			float _speed;
		};

		enum class eKeyState{
			eNull = 0,
			eLeft,
			eRight,
			eUp,
			eDown,
		};

		enum class eActionState{
			eNull = 0,
			eAttack,
		};
	public:
		PlayerBase();
		~PlayerBase();

		Status& GetStatus();
	private:
		static Status m_status;
		static eKeyState m_keyState;
		static eActionState m_actionState;
	private:
		
		virtual void Run() = 0;
		
};
#endif
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
namespace{
	const float kBaseVelocity = 1.0f;
	const int kBaseLife = 3;
}
class PlayerBase
{

	protected:
		struct Status{
			Status(){
				SecureZeroMemory(&_position, sizeof(_position));
				SecureZeroMemory(&_origin, sizeof(_origin));
				SecureZeroMemory(&_rotation, sizeof(_rotation));
				SecureZeroMemory(&_scale, sizeof(_scale));
				_speed = kBaseVelocity;
				_life = kBaseLife;
			}
			DxMath::Vector3 _position;
			DxMath::Vector3 _rotation;
			DxMath::Vector3 _scale;
			DxMath::Vector3 _origin; // 原点
			float _speed;
			int _life;
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
		virtual ~PlayerBase() = 0;

		Status& GetStatus();
	private:
		static Status m_status;
		static eKeyState m_keyState;
		static eActionState m_actionState;
};
#endif
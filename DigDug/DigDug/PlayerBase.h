#ifndef _PLAYERBASE_H
#define _PLAYERBASE_H
/*
	プレイヤーの基底クラス
	updaterとrenderで共有するパラメーターを保持

*/
#include <Windows.h>

	struct Vector3{
		Vector3() = default;
		Vector3(float x, float y, float z)
		{
			_x = x;
			_y = y;
			_z = z;
		}
		float _x, _y, _z;
	};

	struct Rotation{
		Rotation() = default;
		Rotation(float x, float y, float z)
		{
			_x = x;
			_y = y;
			_z = z;
		}
		float _x, _y, _z;
	};

	struct Scale{
		Scale() = default;
		Scale(float x, float y, float z)
		{
			_x = x;
			_y = y;
			_z = z;
		}
		float _x, _y, _z;
	};
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
			Vector3 _vector;
			Rotation _rotation;
			Scale _scale;
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
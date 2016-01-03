#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include "Vector3.h"
/*
	��]�ƃX�P�[���ƈړ��̏������N���X??

*/
namespace DxMath{
	class Transform
	{
		public:
			Transform();
			Transform(Vector3, Vector3, Vector3);
			Transform(Transform&);
			Transform(const Transform&);
			~Transform();

		public:
			Vector3 _rotation;
			Vector3 _scale;
			Vector3 _translation;
	};
}
#endif
#ifndef _ENEMYBASE_H
#define _ENEMYBASE_H
#include <Direct3DManager.h>
#include <Transform.h>
#include <Cube.h>
#include <string>
#include <memory>
#include <ViewCamera.h>
#include <ShaderBase.h>
class EnemyBase
{

	public:
		/*	�ǂ̌����ɐi�ނ��̗񋓌^	*/
		enum class eDirection{
			eLeft,
			eRight,
			eUp,
			eDown,
			eNull
		};

		struct Property{
			DxMath::Transform _transform; // �ʒu
			std::shared_ptr<DxModel::ModelBase> _enemy;// ���ۂɕ`�悳������
			eDirection _direction; // �i�ތ���
		};
	public:
		EnemyBase();
		~EnemyBase();
		virtual void Initialize(std::shared_ptr<DxCamera::ViewCamera>, std::string);
		virtual void Render(std::shared_ptr<DxShader::ShaderBase>);
		virtual void Updater();
		virtual void Collide();
		virtual Property& GetProperty();
		virtual void SetPosition(DxMath::Vector3);
	private:
		Property m_property;
		bool m_isColldie;

	private:
		virtual void CollideBuffer() = 0;
		virtual void InitializeBuffer() = 0;
		virtual void RenderBuffer() = 0;
		virtual void UpdateBuffer() = 0;
		
};

#endif
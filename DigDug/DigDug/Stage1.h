#ifndef _STAGE1_H
#define _STAGE1_H
// ���색�C�u����
#include <Cube.h>
#include <ShaderBase.h>
#include <Vector3.h>
// ����N���X
#include "PlayerBase.h"
namespace{

	/*	�v���p�e�B	*/
	const int kStageWidth = 16;
	const int kStageHeight = 20;
	const int kTipSize = 20;
	const int kResource = 7;

	/*	�`�敨	*/
	const int kSpace = 0;
	const int kSoilLevel4 = 1;
	const int kSoilLevel3 = 2;
	const int kSoilLevel2 = 3;
	const int kSoilLevel1 = 4;
	const int kSky = 5;
	const int kBlackSpace = 6;
	const int kPlayerLife = 7;
	const int kBanana = 8;
	
	/*	���̑��@*/
	const int kPlayer = 10;
	const int kStartPoint = 20;
}

class Stage1
{
	public:
		Stage1();
		Stage1(Stage1&);
		~Stage1();
		bool Initialize(const std::shared_ptr<DxCamera::ViewCamera>);
		void StageRender(const std::shared_ptr<DxShader::ShaderBase>);

		int GetStageData(const int,const int)const;

		int GetStageData(DxMath::Vector3);
		void ChangeStageNumber(DxMath::Vector3,const int);

	private:
		struct StageResorces{
			std::string m_fileName;
		};

	private:
		void ShutdownStage();

	private:

		static int m_stageData[kStageHeight][kStageWidth]; // ������ԕۑ��p
		std::shared_ptr<DxModel::ModelBase> m_stage[kStageHeight][kStageWidth];  // �I�u�W�F�N�g�쐬�p
		static StageResorces m_resource[];
		DxCamera::ViewCamera* m_cameraAddress;
};

#endif
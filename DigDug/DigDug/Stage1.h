#ifndef _STAGE1_H
#define _STAGE1_H
// 自作ライブラリ
#include <Cube.h>
#include <ShaderBase.h>
#include <Vector3.h>
// 自作クラス
#include "PlayerBase.h"
namespace{
	const int kStageWidth = 16;
	const int kStageHeight = 20;
	const int kTipSize = 20;
	const int kResource = 7;

	const int kSpace = 0;
	const int kSoilLevel4 = 1;
	const int kSoilLevel3 = 2;
	const int kSoilLevel2 = 3;
	const int kSoilLevel1 = 4;
	const int kSky = 5;
	const int kBlackSpace = 6;
	const int kPlayerLife = 7;

	const int kPlayer = 10;
}

class Stage1
{
	public:
		Stage1();
		Stage1(Stage1&);
		~Stage1();
		void Initialize(const std::shared_ptr<DxCamera::ViewCamera>);
		void StageRender(const std::shared_ptr<DxShader::ShaderBase>);
		void Shutdown();

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
		static int m_stageData[kStageHeight][kStageWidth];
		std::shared_ptr<DxModel::ModelBase> m_stage[kStageHeight][kStageWidth];
		static StageResorces m_resource[];
		DxCamera::ViewCamera* m_cameraAddress;
		POINT m_playerInitializePosition;
};

#endif
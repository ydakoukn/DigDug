#include "Stage1.h"
#include <iostream>
Stage1::StageResorces Stage1::m_resource[] = {
	{ "res/sky.png" },
	{ "res/soil04.png" },
	{ "res/soil03.png" },
	{ "res/soil02.png" },
	{ "res/soil01.png" },
	{ "res/sky.png" },
	{ "res/blackSpace.png" },
	{ "res/player.png" },
	{ "res/banana.png" }
};

int Stage1::m_stageData[kStageHeight][kStageWidth] = {

	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7 },

	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1 },

	{ 2, 2, 2, 6, 6, 6, 6, 2, 2, 2, 2, 6, 2, 2, 2, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 2, 2, 2, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },

	{ 3, 3, 3, 3, 3, 3, 6, 20, 6, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },

	{ 4, 4, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 6, 6, 6, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },

	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },

};

Stage1::Stage1(){

}

Stage1::Stage1(Stage1& other){}

Stage1::~Stage1(){
	ShutdownStage();
}

void Stage1::ShutdownStage(){
	for (int height = 0; height < kStageHeight; ++height)
	{
		for (int width = 0; width < kStageWidth; ++width)
		{
			const int y = height;
			const int x = width;
			m_stage[y][x]->Shutdown();
			m_stage[y][x].reset();
			m_stage[y][x] = nullptr;
		}
	}
	m_cameraAddress = nullptr;
}


bool Stage1::Initialize(const std::shared_ptr<DxCamera::ViewCamera> camera){
	m_cameraAddress = camera.get();
	for (int height = 0; height < kStageHeight; ++height)
	{
		for (int width = 0; width < kStageWidth; ++width)
		{
			const int y = height;
			const int x = width;
			m_stage[y][x] = std::make_unique<DxModel::Cube>();

			int stageNumber = m_stageData[y][x];
			
			float tipX = x*kTipSize;
			float tipY = y*kTipSize;

			if (stageNumber == kPlayer)
			{
				stageNumber = kBanana;
			}

			if (stageNumber == kStartPoint||stageNumber==kPlayerLife)
			{
				stageNumber = kBlackSpace;
			}
		
			m_stage[y][x]->Initialize(m_cameraAddress, m_resource[stageNumber].m_fileName);
			m_stage[y][x]->Translation(DxMath::Vector3(tipX, tipY, NULL));

			// オブジェクトが重ならない用にする
			// 独自フレームワークのオブジェクトは中心点が真中にある
			m_stage[y][x]->Scaling(DxMath::Vector3(kTipSize/2, kTipSize/2, kTipSize/2));

		}
	}
	return true;
}

//　
void Stage1::StageRender(const std::shared_ptr<DxShader::ShaderBase> shader){
	for (int height = 0; height < kStageHeight; ++height)
	{
		for (int width = 0; width < kStageWidth; ++width)
		{
			const int y = height;
			const int x = width;
			m_stage[y][x]->Render(shader, DxModel::eRenderWay::eTexture);
		}
	}
}

// 指定した場所のステージの番号を置き換える
void Stage1::ChangeStageNumber(DxMath::Vector3 position,const int stageNumber){
	int x = (position._x + (kTipSize/2)) / kTipSize;
	int y = (position._y + (kTipSize / 2)) / kTipSize;

	float tipX = x * kTipSize;
	float tipY = y * kTipSize;

	m_stage[y][x]->Initialize(m_cameraAddress, m_resource[stageNumber].m_fileName);
	m_stage[y][x]->Translation(DxMath::Vector3(tipX, tipY, 0));
	m_stage[y][x]->Scaling(DxMath::Vector3(kTipSize / 2, kTipSize / 2, 10));

	return;
}

// 指定番号のステージの番号を取得
int Stage1::GetStageData(const int x,const int y)const{
	return m_stageData[y][x];
}

// Vector3型から現在の位置を取得
int Stage1::GetStageData(DxMath::Vector3 input){
	int x = (input._x + (kTipSize / 2)) / kTipSize;
	int y = (input._y + (kTipSize / 2)) / kTipSize;

	return m_stageData[y][x];
}
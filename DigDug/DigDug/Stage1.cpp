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
	{ "res/player.png" }
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

	{ 3, 3, 3, 3, 3, 3, 6, 6, 6, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ 3, 3, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },

	{ 4, 4, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 6, 6, 6, 4 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },

	{ 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },

};

Stage1::Stage1(){

}

Stage1::Stage1(Stage1& other){}

Stage1::~Stage1(){
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


void Stage1::Initialize(const std::shared_ptr<DxCamera::ViewCamera> camera){

	for (int height = 0; height < kStageHeight; ++height)
	{
		for (int width = 0; width < kStageWidth; ++width)
		{
			const int y = height;
			const int x = width;
			m_stage[y][x] = std::make_unique<DxModel::Cube>();

			int stageNumber = m_stageData[y][x];
			
			float tipX = x*20;
			float tipY = y*20;

			if (stageNumber == kPlayer)
			{
				m_playerInitializePosition.x = tipX;
				m_playerInitializePosition.y = tipY;
				stageNumber = kSky;
			}
			m_cameraAddress = &(*camera.get());
			m_stage[y][x]->Initialize(m_cameraAddress, m_resource[stageNumber].m_fileName);
			m_stage[y][x]->Translation(DxMath::Vector3(tipX, tipY, 0));
			m_stage[y][x]->Scaling(DxMath::Vector3(kStageTipSize / 2, kStageTipSize / 2, 10));

		}
	}
}

void Stage1::StageRender(const std::shared_ptr<DxShader::ShaderBase> shader){
	for (int height = 0; height < kStageHeight; ++height)
	{
		for (int width = 0; width < kStageWidth; ++width)
		{
			const int y = height;
			const int x = width;
			m_stage[y][x]->Render(shader, DxModel::eRenderWay::eTexture);

			if (m_stageData[y][x] == kPlayerLife)
			{
				m_stage[y][x]->Rotation()._y -= 1;
			}
			
		}
	}
}

void Stage1::ChangeStageNumber(DxMath::Vector3 position,const int stageNumber){
	int x = (position._x + 5) / kStageTipSize;
	int y = (position._y + 5) / kStageTipSize;

	float tipX = x * 20;
	float tipY = y * 20;

	m_stage[y][x]->Initialize(m_cameraAddress, m_resource[stageNumber].m_fileName);
	m_stage[y][x]->Translation(DxMath::Vector3(tipX, tipY, 0));
	m_stage[y][x]->Scaling(DxMath::Vector3(kStageTipSize / 2, kStageTipSize / 2, 10));

	return;
}

void Stage1::Shutdown(){
	ShutdownStage();
}

int Stage1::GetStageData(const int x,const int y)const{
	return m_stageData[y][x];
}

int Stage1::GetStageData(DxMath::Vector3 input){
	int x = (input._x+5) / kStageTipSize;
	int y = (input._y+5) / kStageTipSize;

	return m_stageData[y][x];
}
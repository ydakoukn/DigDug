#include "Stage1.h"
#include <iostream>
Stage1::StageResorces Stage1::m_resource[] = {
	{ "res/sample.jpg" },
	{ "res/sample01.png" },
	{ "res/sample02.jpg" },
	{ "res/sample03.jpg" },
	{ "res/sample04.jpg" },
	{ "res/sky.png" },
};

int Stage1::m_stageData[kStageHeight][kStageWidth] = {

	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },

	{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
	{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
	{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
	{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },

	{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 },
	{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 },
	{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 },
	{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 },

	{ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 },
	{ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 },
	{ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 },
	{ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 },

	{ 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25 },
	{ 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25 },
	{ 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25 },

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
			m_stage[y][x].release();
			m_stage[y][x] = nullptr;
		}
	}
}


void Stage1::Initialize(std::shared_ptr<DxCamera::ViewCamera> camera){
	for (int height = 0; height < kStageHeight; ++height)
	{
		for (int width = 0; width < kStageWidth; ++width)
		{
			const int y = height;
			const int x = width;
			m_stage[y][x] = std::make_unique<DxModel::Rectangle>();

			int stageNumber = m_stageData[y][x] / 5;
			
			m_stage[y][x]->Initialize(camera.get(), m_resource[stageNumber].m_fileName);
			m_stage[y][x]->Translation(D3DXVECTOR3(x * kStageTipSize, y * kStageTipSize, 0));
			m_stage[y][x]->Scaling(D3DXVECTOR3(10, 10, 0));

		}
	}
}

void Stage1::StageRender(std::shared_ptr<DxShader::ShaderBase> shader){
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

void Stage1::Shutdown(){
	ShutdownStage();
}
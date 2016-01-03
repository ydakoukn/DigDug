#ifndef _FBXMODELPROPERTY_H
#define _FBXMODELPROPERTY_H
#include "Texture.h"
#include "ModelProperty.h"
#include "Transform.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <fbxsdk.h>
namespace FbxModelProperty
{
	// Fbx�����荞�ޗp
	struct FbxMeshNode{

		~FbxMeshNode(){
			Release();

		}

		void Release()
		{
			_material.clear();
		}

		ModelProperty::MeshElements _elements; // ���b�V�����ێ�����f�[�^�\��

		std::vector <ModelProperty::Material> _material; // �}�e���A��

		DxMath::Transform _transform;

		float _matrix4x4[16];
	};

	struct FbxMeshBuffer{
		FbxMeshBuffer(){
			_vertexBuffer = nullptr;
			_indexBuffer = nullptr;
		

		}

		~FbxMeshBuffer(){
			if (_vertexBuffer)
			{
				_vertexBuffer->Release();
				_vertexBuffer = nullptr;
			}

			if (_indexBuffer)
			{
				_indexBuffer->Release();
				_indexBuffer = nullptr;
			}
	
		}
		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;
		DxMath::Transform _transform;
		float _matrix4x4[16];
		DxModel::Texture* _texture;
		bool _isTexture;
	};

}

#endif
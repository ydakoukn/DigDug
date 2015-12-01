#ifndef _MODELPROPERTY_H
#define _MODELPROPERTY_H

#include <D3D11.h>
#include <D3DX10math.h>
#include <string>
#include <list>
#include <memory>
#include <unordered_map>
namespace ModelProperty{

	struct VertexPosition{
		VertexPosition(){
			_x = _y = _z = 0.0f;
		}
		~VertexPosition() = default;

		void operator =(D3DXVECTOR3 vector){
			_x = vector.x;
			_y = vector.y;
			_z = vector.z;
		}
		// ���W�̈ʒu
		float _x, _y, _z;
	};

	struct VertexNomal{
		VertexNomal(){

			_x = _y = _z = 0.0f;
		}
		~VertexNomal() = default;
		void operator =(D3DXVECTOR3 vector){
			_x = vector.x;
			_y = vector.y;
			_z = vector.z;
		}
		// �@���̈ʒu
		float _x, _y, _z;
	};

	struct UVPoint{
		UVPoint(){
			_u = _v = 0.0f;
		}
		UVPoint(const float u,const float v){
			_u = u;
			_v = v;
		}
		~UVPoint() = default;
		bool operator==(UVPoint& val)
		{
			if (this->_u == val._u&&this->_v == val._v)
			{
				return true;
			}
			return false;
		}

		void operator =(D3DXVECTOR2 vector){
			_u = vector.x;
			_v = vector.y;
		}

		float _u, _v;
	};

	struct UVSet{
		UVSet(){
			_uvSetName = "Null";
			_texture.clear();
		}
		~UVSet(){
			_texture.clear();
		}

		UVPoint _buffer;
		std::string _uvSetName;
		std::list<std::string> _texture;
		
		
	};

	struct VertexColor{
		VertexColor(){
			_red = _blue =
				_green = _alpha = 0.0f;
		}
		~VertexColor() = default;

		void operator =(D3DXVECTOR4 vector){
			_red = vector.x;
			_green = vector.y;
			_blue = vector.z;
			_alpha = vector.w;
		}
		float _red;
		float _green;
		float _blue;
		float _alpha;
	};

	struct VertexType{
		VertexType(){

			_normal = nullptr;
			_color = nullptr;
		
		}
		~VertexType(){
			Deleter();
		}

		void Deleter(){
			if (_normal)
			{
				delete _normal;
				_normal = nullptr;
			}

			if (_color)
			{
				delete[] _color;
				_color = nullptr;
			}
		
		}

		VertexPosition _position;
		UVSet _uv;
		VertexNomal* _normal;
		VertexColor* _color;
	};

	struct MeshElements{
		MeshElements(){
			_vertexCount = 0;
			_indexCount = 0;
			_uvCount = 0;
			_normalCount = 0;
			_materialCount = 0;

		}

		~MeshElements(){
			_vertexCount = 0;
			_uvCount = 0;
			_normalCount = 0;
			_materialCount = 0;
		}
		unsigned long _vertexCount;
		unsigned long _indexCount;
		unsigned long _uvCount;
		unsigned long _normalCount;
		unsigned int _materialCount;


	};

	struct MaterialColor{
		float _red, _green, _blue, _alpha;
	};
	struct MaterialElement{
		enum class eMaterialElementType{
			eElementNone = 0,
			eElementColor,
			eElementTexture,
			eElementBoth,
			eElementMax
		};

		// UV�Z�b�g��,�e�N�X�`���p�X��(1��UVSet�ɕ����̃e�N�X�`��������ꍇ������)
		std::unordered_map<std::string, std::vector<std::string>> _texture;
		eMaterialElementType _type;
		MaterialColor _color;
	};

	struct Material{
		// FBX�̃}�e���A���͓��ނ����Ȃ�
		enum class eMaterialType{
			eMaterialLambert = 0,
			eMaterialPhong
		};

		eMaterialType _type;
		MaterialElement _ambient;
		MaterialElement _diffuse;
		MaterialElement _emmisive;
		MaterialElement _specular;

		float _shininess; // ��
		float _transparencyFactor;	// ���ߓx
	};

	struct MaterialConstantData{
		MaterialColor _ambient;
		MaterialColor _diffuse;
		MaterialColor _specular;
		MaterialColor _emmisive;
	};

	struct MaterialData{
		MaterialColor _ambient;
		MaterialColor _diffuse;
		MaterialColor _specular;
		MaterialColor _emmisive;
		float _specularPower;
		float _tranceparencyFactory;
		MaterialConstantData _materialConstantData;
	};

	
}

#endif
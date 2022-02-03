#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// �з� : ����(Vertex) ����
// �뵵 : 
// ���� : ����(Vertex)�� �����ϰ� �����ϴ� Ŭ����
class GameEngineVertexBuffer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11Buffer* Buffer_;
	UINT Size_;
	UINT Offset_;
	D3D11_BUFFER_DESC BufferData_;				// ������ ������
	D3D11_SUBRESOURCE_DATA ResData_;	// �ʱⰪ���� ������(��������)

public:
	GameEngineVertexBuffer(); // default constructer ����Ʈ ������
	~GameEngineVertexBuffer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	template<typename VertexType>
	void Create(const std::vector<VertexType>& _Datas, D3D11_USAGE _Usage)
	{
		Create(reinterpret_cast<const void*>(&_Datas[0]), sizeof(VertexType), _Datas.size(), _Usage);
	}

	void Create(const void* _Data, size_t _Size, size_t _Count, D3D11_USAGE _Usage);

public:
	void Setting();
};


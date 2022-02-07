#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// 분류 : 정점(Vertex) 버퍼
// 용도 : 
// 설명 : 정점(Vertex)을 관리하고 제공하는 클래스
class GameEngineVertexBuffer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11Buffer*								Buffer_;				// 
	UINT													Size_;					// 바이트 크기
	UINT													Count_;				// 정점버퍼 수
	UINT													Offset_;				// 바이트 시작점
	D3D11_BUFFER_DESC					BufferData_;	// 버퍼의 데이터
	D3D11_SUBRESOURCE_DATA	ResData_;			// 초기값등의 데이터(원본버퍼)

public:
	GameEngineVertexBuffer();
	~GameEngineVertexBuffer();

protected:		// delete constructer
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _other) noexcept = delete;

private:		//delete operator
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _other) = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer&& _other) = delete;

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


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
	ID3D11Buffer* Buffer_;
	UINT Size_;
	UINT Offset_;
	D3D11_BUFFER_DESC BufferData_;				// 버퍼의 데이터
	D3D11_SUBRESOURCE_DATA ResData_;	// 초기값등의 데이터(원본버퍼)

public:
	GameEngineVertexBuffer(); // default constructer 디폴트 생성자
	~GameEngineVertexBuffer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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


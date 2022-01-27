#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDirectXDevice.h>

// 분류 : 인덱스(Index) 버퍼
// 용도 : 
// 설명 : 인덱스버퍼를 관리하고 제공하는 클래스
class GameEngineIndexBuffer : public GameEngineObjectNameBase
{
public:	// member Var
	ID3D11Buffer* Buffer_;
	D3D11_BUFFER_DESC BufferData_;
	D3D11_SUBRESOURCE_DATA ResData_;
	DXGI_FORMAT Format_;
	UINT Offset_;

public:
	GameEngineIndexBuffer(); // default constructer 디폴트 생성자
	~GameEngineIndexBuffer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void Create(const std::vector<UINT>& _Datas, D3D11_USAGE _Usage);
	void Create(const void* _Data, size_t _Size, size_t _Count, D3D11_USAGE _Usage);

public:
	void Setting();
};


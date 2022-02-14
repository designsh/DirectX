#pragma once
#include "GameEngineDevice.h"

// 분류 : 인덱스(Index) 버퍼
// 용도 : 
// 설명 : 인덱스버퍼를 관리하고 제공하는 클래스
class GameEngineIndexBuffer : public GameEngineObjectNameBase
{
public:	// member Var
	ID3D11Buffer*									Buffer_;					// 
	D3D11_BUFFER_DESC						BufferData_;		// 
	D3D11_SUBRESOURCE_DATA		ResData_;				// 
	DXGI_FORMAT									Format_;				// 
	UINT														Offset_;					// 
	int															IndexCount_;		// 

public:
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer();

protected:		// delete constructer
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _other) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) noexcept = delete;

private:		//delete operator
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _other) = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer&& _other) = delete;

public:
	int GetIndexCount() const;

public:
	void Create(const std::vector<UINT>& _Datas, D3D11_USAGE _Usage);
	void Create(const void* _Data, size_t _Size, size_t _Count, D3D11_USAGE _Usage);

public:
	void Setting();
};


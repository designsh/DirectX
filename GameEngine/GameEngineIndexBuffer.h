#pragma once
#include "GameEngineDevice.h"

// �з� : �ε���(Index) ����
// �뵵 : 
// ���� : �ε������۸� �����ϰ� �����ϴ� Ŭ����
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


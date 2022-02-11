#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// 분류 : 상수버퍼
// 용도 : 
// 설명 : 
class GameEngineConstantBuffer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11Buffer*																	Buffer_;						// 버퍼
	D3D11_BUFFER_DESC														BufferData_;			// 버퍼 리소스 정의
	D3D11_MAPPED_SUBRESOURCE									ResData_;					// 하위 리소스 데이터에 대한 액세스를 제공
	D3D11_SHADER_BUFFER_DESC									BufferDesc_;			// 셰이더 상수버퍼의 정의

private:
	std::vector<D3D11_SHADER_VARIABLE_DESC>		VarInfos_;					// 셰이더의 정보 관리 목록

public:
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

protected:		// delete constructer
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _other) noexcept = delete;

private:		//delete operator
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _other) = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer&& _other) = delete;

public:
	void Create(const D3D11_SHADER_BUFFER_DESC& _BufferDesc, ID3D11ShaderReflectionConstantBuffer* _VarInfo);

public:
	void ChangeData(void* _Data, size_t _Size);

public: // 인라인 함수 : 함수바디의 내용을 즉시 본문에 치환하여 처리하는 함수(매크로에 비해 구조적이며, 안전한 방식)
	inline unsigned int GetBufferSize()
	{
		return BufferData_.ByteWidth;
	}

	inline ID3D11Buffer*& GetBuffer()
	{
		return Buffer_;
	}
};


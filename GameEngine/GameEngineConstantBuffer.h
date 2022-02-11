#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// �з� : �������
// �뵵 : 
// ���� : 
class GameEngineConstantBuffer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11Buffer*																	Buffer_;						// ����
	D3D11_BUFFER_DESC														BufferData_;			// ���� ���ҽ� ����
	D3D11_MAPPED_SUBRESOURCE									ResData_;					// ���� ���ҽ� �����Ϳ� ���� �׼����� ����
	D3D11_SHADER_BUFFER_DESC									BufferDesc_;			// ���̴� ��������� ����

private:
	std::vector<D3D11_SHADER_VARIABLE_DESC>		VarInfos_;					// ���̴��� ���� ���� ���

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

public: // �ζ��� �Լ� : �Լ��ٵ��� ������ ��� ������ ġȯ�Ͽ� ó���ϴ� �Լ�(��ũ�ο� ���� �������̸�, ������ ���)
	inline unsigned int GetBufferSize()
	{
		return BufferData_.ByteWidth;
	}

	inline ID3D11Buffer*& GetBuffer()
	{
		return Buffer_;
	}
};


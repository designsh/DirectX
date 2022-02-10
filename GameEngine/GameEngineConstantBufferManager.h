#pragma once
#include "GameEngineDevice.h"

class GameEngineConstantBuffer;
class GameEngineConstantBufferManager
{
private:
	static GameEngineConstantBufferManager* Inst;

public:
	static GameEngineConstantBufferManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var
	std::map<std::string, GameEngineConstantBuffer*> ResourcesMap;

private:
	GameEngineConstantBufferManager();
	~GameEngineConstantBufferManager();

protected:		// delete constructer
	GameEngineConstantBufferManager(const GameEngineConstantBufferManager& _other) = delete;
	GameEngineConstantBufferManager(GameEngineConstantBufferManager&& _other) noexcept;

private:		//delete operator
	GameEngineConstantBufferManager& operator=(const GameEngineConstantBufferManager& _other) = delete;
	GameEngineConstantBufferManager& operator=(const GameEngineConstantBufferManager&& _other) = delete;

public:
	// ������� ����
	GameEngineConstantBuffer* Create(const std::string& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc, ID3D11ShaderReflectionConstantBuffer* _VarInfo);

	// ������ ��Ī�� ���� ������۰� �����Ѵٸ� �̹� �����ϴ� ������۸� ��ȯ, �ݴ��ǰ�� ������� ����
	GameEngineConstantBuffer* CreateAndFind(const std::string& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc, ID3D11ShaderReflectionConstantBuffer* _VarInfo);

public:
	GameEngineConstantBuffer* Load(const std::string& _Path);
	GameEngineConstantBuffer* Load(const std::string& _Name, const std::string& _Path);
	GameEngineConstantBuffer* Find(const std::string& _Name);
};





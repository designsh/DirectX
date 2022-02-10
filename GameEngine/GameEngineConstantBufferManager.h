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
	// 상수버퍼 생성
	GameEngineConstantBuffer* Create(const std::string& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc, ID3D11ShaderReflectionConstantBuffer* _VarInfo);

	// 동일한 명칭을 가진 상수버퍼가 존재한다면 이미 존재하는 상수버퍼를 반환, 반대의경우 상수버퍼 생성
	GameEngineConstantBuffer* CreateAndFind(const std::string& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc, ID3D11ShaderReflectionConstantBuffer* _VarInfo);

public:
	GameEngineConstantBuffer* Load(const std::string& _Path);
	GameEngineConstantBuffer* Load(const std::string& _Name, const std::string& _Path);
	GameEngineConstantBuffer* Find(const std::string& _Name);
};





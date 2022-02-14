#pragma once
#include "GameEngineDevice.h"

class GameEngineRasterizer;
class GameEngineRasterizerManager : public GameEngineObjectNameBase
{
private:
	static GameEngineRasterizerManager* Inst;

public:
	static GameEngineRasterizerManager& GetInst()
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
	std::map<std::string, GameEngineRasterizer*> ResourcesMap;

private:
	GameEngineRasterizerManager(); // default constructer ����Ʈ ������
	~GameEngineRasterizerManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRasterizerManager(const GameEngineRasterizerManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRasterizerManager(GameEngineRasterizerManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRasterizerManager& operator=(const GameEngineRasterizerManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRasterizerManager& operator=(const GameEngineRasterizerManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	GameEngineRasterizer* Create(const std::string& _Name, const D3D11_RASTERIZER_DESC& _RasterizerDesc);
	GameEngineRasterizer* Load(const std::string& _Path);
	GameEngineRasterizer* Load(const std::string& _Name, const std::string& _Path);
	GameEngineRasterizer* Find(const std::string& _Name);
};





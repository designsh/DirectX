#pragma once
#include "GameEngineDevice.h"

class GameEngineBlend;
class GameEngineBlendManager
{
private:
	static GameEngineBlendManager* Inst;

public:
	static GameEngineBlendManager& GetInst()
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
	std::map<std::string, GameEngineBlend*> ResourcesMap;

public:
	GameEngineBlend* Create(const std::string& _Name, const D3D11_BLEND_DESC& _Info, float4 _Fector = float4::ONE, unsigned int _Mask = 0xfffffff);
	GameEngineBlend* CreateAndFind(const std::string& _Name, const D3D11_BLEND_DESC& _Info, float4 _Fector = float4::ONE, unsigned int _Mask = 0xfffffff);
	GameEngineBlend* Find(const std::string& _Name);

private:
	GameEngineBlendManager(); // default constructer ����Ʈ ������
	~GameEngineBlendManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineBlendManager(const GameEngineBlendManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineBlendManager(GameEngineBlendManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineBlendManager& operator=(const GameEngineBlendManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineBlendManager& operator=(const GameEngineBlendManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:

};





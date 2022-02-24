#pragma once
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

// ���̴��� ������� ���ø��
enum class SettingMode
{
	LINK,		// �ּҰ��� �����͸� �����ϴ� ���(�����Ҵ� X) : �������Ӹ��� ����
	SET,		// �ѹ� ������ �����͸� �����ϴ� ���(�����Ҵ� O) : ���� ���� ������ ����
	MAX		// 
};

// �з� : ���������������� �ʿ����� ������� ���� ���� üũ �� ����
// �뵵 : 
// ���� : ������������������ �����ϴµ� �־ �ʿ��� ��������� ���ÿ����� üũ�ϴ� ����� ���� �� ����
class GameEngineConstantBufferSetting
{
public:
	GameEngineShader*					Shader;						// ���̴�
	GameEngineConstantBuffer*	Res_;							// �������
	SettingMode									Mode_;						// ������� ����Ÿ��
	char*													SettingData_;			// ������ ������ ���纻
	size_t													SettingDataSize_;	// ������ �������� ũ��(����Ʈũ��)
	int														SettingIndex_;			// Register No

public:
	GameEngineConstantBufferSetting() : 
		Shader(nullptr),
		Res_(nullptr),
		Mode_(SettingMode::MAX),
		SettingData_(nullptr),
		SettingDataSize_(0),
		SettingIndex_(-1)
	{
	}

	~GameEngineConstantBufferSetting()
	{
		Clear();
	}

public:
	void Clear()
	{
		// ������� ���ø�尡 SET�̸� CPU�� ���õ����͸�ŭ�� ũ�⸦ �����Ҵ��ϱ� ������
		// �Ҹ�� �ش� �����Ҵ��� ���� ��Ų��.
		if (SettingMode::SET == Mode_)
		{
			if (nullptr != SettingData_)
			{
				delete SettingData_;
				SettingData_ = nullptr;
			}
		}
	}

public:
	// CPU�� �Ҵ�Ǿ��ִ� ������۸� GPU�� ����
	// ��, CPU�� ������۸� GPU������ �Ҵ�Ǿ��ִ� ������۷�
	// �����Ѵ�.
	void ChangeData()
	{
		Res_->ChangeData(SettingData_, SettingDataSize_);
	}

	// gpu�� �Ҵ�� ������۸� ���̴��� �����Ѵ�.
	void ShaderSetting()
	{
		Shader->SetConstantBuffers(this);
	}

	// gpu�� �Ҵ�� ������۸� �����Ѵ�.
	void ShaderReSet()
	{
		Shader->ReSetConstantBuffers(this);
	}
};

class GameEngineShader;
class GameEngineSampler;
class GameEngineSamplerSetting
{
public:
	GameEngineShader* Shader;
	GameEngineSampler* Res_;
	int SettingIndex_;

public:
	GameEngineSamplerSetting() :
		Shader(nullptr),
		Res_(nullptr),
		SettingIndex_(-1)
	{
	}

	~GameEngineSamplerSetting()
	{
	}

public:
	void ShaderSetting()
	{
		Shader->SetSampler(this);
	}

	void ShaderReSet()
	{
		Shader->ReSetSampler(this);
	}
};

class GameEngineShader;
class GameEngineTexture;
class GameEngineTextureSetting
{
public:
	GameEngineShader* Shader;
	GameEngineTexture* Res_;
	int SettingIndex_;

public:
	GameEngineTextureSetting() :
		Res_(nullptr),
		Shader(nullptr),
		SettingIndex_(-1)
	{
	}

	~GameEngineTextureSetting()
	{
	}

public:
	void ShaderSetting()
	{
		Shader->SetTexture(this);
	}

	void ShaderReSet()
	{
		Shader->ReSetTexture(this);
	}
};

#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineShader.h"

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
class GameEngineConstantBuffer;
class GameEngineConstantBufferSetting
{
public:
	GameEngineShader*					Shader;						// ���̴�
	GameEngineConstantBuffer*	Res_;							// �������
	SettingMode									Mode_;						// ������� ����Ÿ��
	char*													SettingData_;			// ������ ������ ���纻
	size_t													SettingDataSize_;	// ������ �������� ũ��(����Ʈũ��)
	int														SettingIndex_;			// Register No
	bool													IsSet_;						// 

public:
	GameEngineConstantBufferSetting() : SettingData_(nullptr), Mode_(SettingMode::MAX)
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
};


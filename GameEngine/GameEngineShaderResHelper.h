#pragma once
#include "GameEngineRenderingSettingData.h"
#include "GameEngine/GameEngineShader.h"

// �з� : ���̴� ���� �����
// �뵵 : 
// ���� : ���̴��� �����ϴ� ��� ������۸� �����ϸ� �ش� ������۰� ��ӵǾ� ���ŵǴ��� �ѹ��� ��������
//            �������� ����ϴ����� �Ǵ��Ͽ� ���̴� �����ϴ� ����� �����Ѵ�.
//            ��������� ������ ���̴����� ������ �����͵��(�������)�� �����Ͽ� �����ϴ� Ŭ����
class GameEngineShader;
class GameEngineConstantBuffer;
class GameEngineShaderResHelper
{
private:	// member Var
	std::map<std::string, GameEngineConstantBufferSetting*> AllSettingData_;

public:
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();

protected:		// delete constructer
	GameEngineShaderResHelper(const GameEngineShaderResHelper& _other) = delete;
	GameEngineShaderResHelper(GameEngineShaderResHelper&& _other) noexcept = delete;

private:		//delete operator
	GameEngineShaderResHelper& operator=(const GameEngineShaderResHelper& _other) = delete;
	GameEngineShaderResHelper& operator=(const GameEngineShaderResHelper&& _other) = delete;

public:
	void ShaderResourcesCheck(GameEngineShader* _Shader);
	void Setting();

public:
	// SettingMode::LINK�� �ش� ��������� ���� �����͸��� �����ϴ� ���
	// �ѹ� ���� �� ���̻��� ������ �ʿ���� ���
	template<typename T>
	void SettingConstantBufferLink(const std::string& _SettingName, T& _Data)
	{
		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllSettingData_.find(_SettingName);
		if (FindIter == AllSettingData_.end())
		{
			GameEngineDebug::MsgBoxError("�������� �ʴ� ������۸� �����Ϸ��� �߽��ϴ�." + _SettingName);
			return;
		}

		GameEngineConstantBufferSetting* SettingData = FindIter->second;

		SettingData->Mode_ = SettingMode::LINK;
		SettingData->SettingDataSize_ = sizeof(_Data);
		SettingData->SettingData_ = reinterpret_cast<char*>(&_Data);
	}

public:
	// SettingMode::SET���� �ش� ������۸� �����Ͽ� �����Ҵ��� �ϸ�, �ش� ������ ���õ����� ���ۿ� ��������� �����͸� �����ϴ� ���
	// ��, �ѹ� ���� �� ���������� ���Ǹ�, ����ڿ� ���ؼ� �ٽ� ������ �����ʴ��� �׻� �������� ����
	template<typename T>
	void SettingConstantBufferSet(const std::string& _SettingName, const T& _Data)
	{
		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllSettingData_.find(_SettingName);
		if (FindIter == AllSettingData_.end())
		{
			GameEngineDebug::MsgBoxError("�������� �ʴ� ������۸� �����Ϸ��� �߽��ϴ�." + _SettingName);
			return;
		}

		GameEngineConstantBufferSetting* SettingData = FindIter->second;
		SettingData->Mode_ = SettingMode::SET;
		SettingData->SettingDataSize_ = sizeof(_Data);

		if (nullptr == SettingData->SettingData_)
		{
			SettingData->SettingData_ = new char[sizeof(_Data)];
		}

		memcpy_s(SettingData->SettingData_, sizeof(_Data), &_Data, sizeof(_Data));
	}
};


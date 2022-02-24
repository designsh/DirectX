#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineSampler.h"
#include "GameEngineTexture.h"
#include "GameEngineTextureManager.h"

GameEngineShaderResHelper::GameEngineShaderResHelper()
{

}

GameEngineShaderResHelper::~GameEngineShaderResHelper()
{
	for (auto& Setting : AllTextureData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}

	for (auto& Setting : AllSamplerData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}

	for (auto& Setting : AllConstantBufferData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}
}

void GameEngineShaderResHelper::Setting()
{
	// ������ ���� or ������ ���� �� ���̴��� ������۸� ����
	for (auto& Setting : AllConstantBufferData_)
	{
		if (Setting.second->Mode_ == SettingMode::MAX)
		{
			GameEngineDebug::MsgBoxError("������۰� ���õ��� �ʾҽ��ϴ�. " + Setting.first);
		}

		Setting.second->ChangeData();
		Setting.second->ShaderSetting();
	}

	// �ؽ��ĸ� ����
	for (auto& Setting : AllTextureData_)
	{
		Setting.second->ShaderSetting();
	}

	// ���÷��� ����
	for (auto& Setting : AllSamplerData_)
	{
		Setting.second->ShaderSetting();
	}
}

void GameEngineShaderResHelper::ReSet()
{
	for (auto& Setting : AllConstantBufferData_)
	{
		if (Setting.second->Mode_ == SettingMode::MAX)
		{
			GameEngineDebug::MsgBoxError("������ ������۰� ���õ��� �ʾҽ��ϴ�. >>> " + Setting.first);
		}

		Setting.second->ChangeData();
		Setting.second->ShaderReSet();
	}

	for (auto& Setting : AllTextureData_)
	{
		Setting.second->ShaderReSet();
	}

	for (auto& Setting : AllSamplerData_)
	{
		Setting.second->ShaderReSet();
	}
}

bool GameEngineShaderResHelper::IsConstantBuffer(const std::string& _SettingName)
{
	std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllConstantBufferData_.find(_SettingName);
	if (FindIter == AllConstantBufferData_.end())
	{
		return false;
	}

	return true;
}

void GameEngineShaderResHelper::ShaderResourcesCheck(GameEngineShader* _Shader)
{
	// ���̴� ������� ���ҽ� üũ
	for (auto& ConstantBuffer : _Shader->GetConstantBuffers())
	{
		// ���õ����͸� �Ҵ��Ͽ� ���̴��� �������ִ� ��������� ������ �����Ͽ� ������Ͽ� �߰��Ѵ�.
		GameEngineConstantBufferSetting* SettingData = new GameEngineConstantBufferSetting();
		SettingData->Shader = _Shader;
		SettingData->Res_ = ConstantBuffer.second;
		SettingData->SettingIndex_ = ConstantBuffer.first;
		auto Result = AllConstantBufferData_.insert(std::make_pair(ConstantBuffer.second->GetName(), SettingData));
		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("���� �̸��� ������۰� �̹� �����մϴ�." + ConstantBuffer.second->GetName());
		}
	}

	// ���̴� ���÷� ���ҽ� üũ
	for (auto& Sampler : _Shader->GetSamplers())
	{
		GameEngineSamplerSetting* SettingData = new GameEngineSamplerSetting();
		SettingData->Shader = _Shader;
		SettingData->Res_ = Sampler.second;
		SettingData->SettingIndex_ = Sampler.first;
		auto Result = AllSamplerData_.insert(std::make_pair(Sampler.second->GetName(), SettingData));
		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("���� �̸��� ���÷��� �̹� �����մϴ�." + Sampler.second->GetName());
		}
	}

	// ���̴� �ؽ��� ���ҽ� üũ
	GameEngineTexture* ErrorTexture = GameEngineTextureManager::GetInst().Find("NotSettingError.png"); // �⺻������ �ش� �ؽ��ķ� �������õǸ�,
																																																			  // ���� ����ڿ� ���� �ش� �ؽ��� ������ ��ü�Ǵ� ����� ���
	for (auto& Texture : _Shader->GetTextures())
	{
		GameEngineTextureSetting* SettingData = new GameEngineTextureSetting();
		SettingData->Shader = _Shader;
		SettingData->Res_ = ErrorTexture;
		SettingData->SettingIndex_ = Texture.first;
		auto Result = AllTextureData_.insert(std::make_pair(Texture.second, SettingData));
		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("���� �̸��� �ؽ�ó�� �̹� �����մϴ�." + Texture.second);
		}
	}
}

void GameEngineShaderResHelper::SettingTexture(const std::string& _SettingName, const std::string& _ImageName)
{
	std::map<std::string, GameEngineTextureSetting*>::iterator FindIter = AllTextureData_.find(_SettingName);
	if (FindIter == AllTextureData_.end())
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó ���Կ� �����Ϸ��� �߽��ϴ�." + _SettingName);
		return;
	}

	GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);
	if (nullptr == FindTexture)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó�� �����Ϸ��� �߽��ϴ�. >>> " + _ImageName);
		return;
	}

	// ���� �����Ϸ��� �ؽ��������� ��ü
	FindIter->second->Res_ = FindTexture;
}

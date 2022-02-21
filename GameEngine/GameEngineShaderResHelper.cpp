#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"

GameEngineShaderResHelper::GameEngineShaderResHelper()
{

}

GameEngineShaderResHelper::~GameEngineShaderResHelper()
{
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
}

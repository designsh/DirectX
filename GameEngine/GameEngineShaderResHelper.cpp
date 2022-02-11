#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"

GameEngineShaderResHelper::GameEngineShaderResHelper()
{

}

GameEngineShaderResHelper::~GameEngineShaderResHelper()
{
	for (auto& Setting : AllSettingData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}
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
		auto Result = AllSettingData_.insert(std::make_pair(ConstantBuffer.second->GetName(), SettingData));
		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("���� �̸��� ������۰� �̹� �����մϴ�." + ConstantBuffer.second->GetName());
		}
	}
}

void GameEngineShaderResHelper::Setting()
{
	// ������ ���� or ������ ���� �� ���̴��� ������۸� ����
	for (auto& Setting : AllSettingData_)
	{
		Setting.second->ChangeData();
		Setting.second->ShaderSetting();
	}
}

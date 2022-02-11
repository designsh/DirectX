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
		// 세팅데이터를 할당하여 셰이더가 가지고있는 상수버퍼의 정보를 복사하여 관리목록에 추가한다.
		GameEngineConstantBufferSetting* SettingData = new GameEngineConstantBufferSetting();
		SettingData->Shader = _Shader;
		SettingData->Res_ = ConstantBuffer.second;
		SettingData->SettingIndex_ = ConstantBuffer.first;
		auto Result = AllSettingData_.insert(std::make_pair(ConstantBuffer.second->GetName(), SettingData));
		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("같은 이름의 상수버퍼가 이미 존재합니다." + ConstantBuffer.second->GetName());
		}
	}
}

void GameEngineShaderResHelper::Setting()
{
	// 데이터 갱신 or 데이터 세팅 및 셰이더에 상수버퍼를 세팅
	for (auto& Setting : AllSettingData_)
	{
		Setting.second->ChangeData();
		Setting.second->ShaderSetting();
	}
}

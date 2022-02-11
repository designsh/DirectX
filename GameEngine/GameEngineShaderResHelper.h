#pragma once
#include "GameEngineRenderingSettingData.h"
#include "GameEngine/GameEngineShader.h"

// 분류 : 셰이더 세팅 도우미
// 용도 : 
// 설명 : 셰이더에 세팅하는 모든 상수버퍼를 관리하며 해당 상수버퍼가 계속되어 갱신되는지 한번의 세팅으로
//            고정값을 사용하는지를 판단하여 셰이더 세팅하는 기능을 제공한다.
//            결론적으로 각각의 셰이더에서 세팅한 데이터덩어리(상수버퍼)를 복제하여 관리하는 클래스
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
	// SettingMode::LINK로 해당 상수버퍼의 내부 데이터만을 갱신하는 기능
	// 한번 세팅 후 더이상의 조작이 필요없는 기능
	template<typename T>
	void SettingConstantBufferLink(const std::string& _SettingName, T& _Data)
	{
		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllSettingData_.find(_SettingName);
		if (FindIter == AllSettingData_.end())
		{
			GameEngineDebug::MsgBoxError("존재하지 않는 상수버퍼를 세팅하려고 했습니다." + _SettingName);
			return;
		}

		GameEngineConstantBufferSetting* SettingData = FindIter->second;

		SettingData->Mode_ = SettingMode::LINK;
		SettingData->SettingDataSize_ = sizeof(_Data);
		SettingData->SettingData_ = reinterpret_cast<char*>(&_Data);
	}

public:
	// SettingMode::SET으로 해당 상수버퍼를 복제하여 동적할당을 하며, 해당 복제한 세팅데이터 버퍼에 상수버퍼의 데이터를 세팅하는 기능
	// 즉, 한번 세팅 후 고정값으로 사용되며, 사용자에 의해서 다시 세팅이 되지않는한 항상 고정값을 유지
	template<typename T>
	void SettingConstantBufferSet(const std::string& _SettingName, const T& _Data)
	{
		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllSettingData_.find(_SettingName);
		if (FindIter == AllSettingData_.end())
		{
			GameEngineDebug::MsgBoxError("존재하지 않는 상수버퍼를 세팅하려고 했습니다." + _SettingName);
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


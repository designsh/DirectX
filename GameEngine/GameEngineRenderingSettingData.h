#pragma once
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

// 셰이더에 상수버퍼 세팅모드
enum class SettingMode
{
	LINK,		// 주소값의 데이터를 갱신하는 모드(동적할당 X) : 매프레임마다 갱신
	SET,		// 한번 셋팅한 데이터를 고정하는 모드(동적할당 O) : 다음 셋팅 전까지 고정
	MAX		// 
};

// 분류 : 렌더링파이프라인 필요조건 상수버퍼 세팅 관련 체크 및 관리
// 용도 : 
// 설명 : 렌더링파이프라인이 가동하는데 있어서 필요한 상수버퍼의 세팅여부을 체크하는 기능을 제공 및 관리
class GameEngineConstantBufferSetting
{
public:
	GameEngineShader*					Shader;						// 셰이더
	GameEngineConstantBuffer*	Res_;							// 상수버퍼
	SettingMode									Mode_;						// 상수버퍼 세팅타입
	char*													SettingData_;			// 세팅한 데이터 복사본
	size_t													SettingDataSize_;	// 세팅한 데이터의 크기(바이트크기)
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
		// 상수버퍼 세팅모드가 SET이면 CPU에 세팅데이터만큼의 크기를 동적할당하기 때문에
		// 소멸시 해당 동적할당을 해제 시킨다.
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
	// CPU에 할당되어있는 상수버퍼를 GPU로 전송
	// 즉, CPU의 상수버퍼를 GPU공간에 할당되어있는 상수버퍼로
	// 복사한다.
	void ChangeData()
	{
		Res_->ChangeData(SettingData_, SettingDataSize_);
	}

	// gpu에 할당된 상수버퍼를 셰이더에 연결한다.
	void ShaderSetting()
	{
		Shader->SetConstantBuffers(this);
	}

	// gpu에 할당된 상수버퍼를 해제한다.
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

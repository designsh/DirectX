#pragma once
#include "GameEngineConstantBuffer.h"

enum SettingMode
{
	Link,
	New,
};

// 분류 : 렌더링파이프라인 필요조건 상수버퍼 세팅 관련 체크 및 관리
// 용도 : 
// 설명 : 렌더링파이프라인이 가동하는데 있어서 필요한 상수버퍼의 세팅여부을 체크하는 기능을 제공 및 관리
class GameEngineConstantBufferSetting
{
public:
	GameEngineConstantBuffer*	Res_;							// 상수버퍼
	SettingMode									Mode_;						// 상수버퍼 타입
	char*													SettingData_;			// 
	int														SettingIndex_;			// Register No
	bool													IsSet_;						// 
};


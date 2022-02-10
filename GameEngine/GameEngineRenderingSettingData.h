#pragma once
#include "GameEngineConstantBuffer.h"

enum SettingMode
{
	Link,
	New,
};

// �з� : ���������������� �ʿ����� ������� ���� ���� üũ �� ����
// �뵵 : 
// ���� : ������������������ �����ϴµ� �־ �ʿ��� ��������� ���ÿ����� üũ�ϴ� ����� ���� �� ����
class GameEngineConstantBufferSetting
{
public:
	GameEngineConstantBuffer*	Res_;							// �������
	SettingMode									Mode_;						// ������� Ÿ��
	char*													SettingData_;			// 
	int														SettingIndex_;			// Register No
	bool													IsSet_;						// 
};


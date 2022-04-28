#pragma once
#include <GameEngine/GameEngineActor.h>

enum class TakeInOutType
{
	NONE = -1,		// ������ �ʱ�ȭ��
	TakeIn,			// �ֱ�
	TakeOut,		// ������
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class TakeInOutGoldPopup : public GameEngineActor
{
private:	// member Var
	TakeInOutType PopupType_;			// �˾� Ÿ��
	int HaveGold_;						// ��差

private:
	GameEngineUIRenderer* Panel_;		// �ǳ� ������

private:


public:
	TakeInOutGoldPopup();
	~TakeInOutGoldPopup();

protected:		// delete constructer
	TakeInOutGoldPopup(const TakeInOutGoldPopup& _other) = delete;
	TakeInOutGoldPopup(TakeInOutGoldPopup&& _other) noexcept = delete;

private:		//delete operator
	TakeInOutGoldPopup& operator=(const TakeInOutGoldPopup& _other) = delete;
	TakeInOutGoldPopup& operator=(const TakeInOutGoldPopup&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void CreateTakePopup(TakeInOutType _PopupType, const float4& _InitPos);
};


#pragma once
#include <GameEngine/GameEngineActor.h>

enum class PortalType
{
	TOWN,			// ����(�Ķ�����Ż) - ������ ��ȯ�Ǿ�����
	BOSS			// ������(��������Ż) - ���� ����� ��ȯ
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineLevel;
class GameEngineImageRenderer;
class GameEngineCollision;
class Portal : public GameEngineActor
{
private:	// member Var
	PortalType PortalType_;

private:
	bool Moveable_; // ����ü���� ���� Flag(���콺�� Ŭ���� Ȱ��ȭ/���콺�� �ٸ���Ŭ���� ��Ȱ��ȭ)

private:
	GameEngineLevel* CurLevel_;
	GameEngineLevel* NextLevel_;

private:
	GameEngineImageRenderer* PortalEntityRenderer_;
	GameEngineImageRenderer* PortalShadowRenderer_;
	GameEngineCollision* PortalCollision_;

public:
	Portal();
	~Portal();

protected:		// delete constructer
	Portal(const Portal& _other) = delete;
	Portal(Portal&& _other) noexcept = delete;

private:		//delete operator
	Portal& operator=(const Portal& _other) = delete;
	Portal& operator=(const Portal&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	void MouseLButtonClick(GameEngineCollision* _Other);
	void PlayerCollisionCheck(GameEngineCollision* _Other);

private:
	void IdleAnimationEnd();

public:
	inline bool GetCurPortalMoveFlag()
	{
		return Moveable_;
	}

public: // ��ŻŸ�Կ� ���� ������ & �浹ü ���� �� �̵����� ����
	void CreateLevelChangePortal(PortalType _PortalType, GameEngineLevel* _NextLevel, bool _Open = false);

public: // �ܺο��� �̵����� Ȱ��ȭ Flag ������
	void PortMoveableFlagOff();

};


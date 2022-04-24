#pragma once
#include <GameEngine/GameEngineActor.h>

enum class PortalType
{
	TOWN,			// 마을(파란색포탈) - 마을에 소환되어있음
	BOSS			// 보스방(붉은색포탈) - 보스 사망시 소환
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineLevel;
class GameEngineImageRenderer;
class GameEngineCollision;
class Portal : public GameEngineActor
{
private:	// member Var
	PortalType PortalType_;

private:
	bool Moveable_; // 레벨체인지 가능 Flag(마우스로 클릭시 활성화/마우스가 다른곳클릭시 비활성화)

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

public: // 포탈타입에 따른 렌더러 & 충돌체 생성 및 이동레벨 결정
	void CreateLevelChangePortal(PortalType _PortalType, GameEngineLevel* _NextLevel, bool _Open = false);

public: // 외부에서 이동가능 활성화 Flag 해제용
	void PortMoveableFlagOff();

};


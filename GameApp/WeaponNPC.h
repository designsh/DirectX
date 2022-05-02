#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "FixedTileMap_Common.h"
#include "Navigation_Common.h"

enum class WeaponNPC_MoveDir
{
	DIR_B,
	DIR_LB,
	DIR_L,
	DIR_LT,
	DIR_T,
	DIR_RT,
	DIR_R,
	DIR_RB,
	MAX
};

enum class WeaponNPC_FSMState
{
	ST_IDLE,	// 대기상태
	ST_WALK,	// 걷기상태
	ST_CONV,	// 플레이어와 상호작용대기 상태
	ST_INTER,	// 플레이어와 상호작용중 상태
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineImageRenderer;
class GameEngineCollision;
class NPC_TopMenuBar;
class NPC_MessageView;
class NPC_BuySellView;
class WeaponNPC : public GameEngineActor
{
private:
	static bool FirstInteraction;
	static bool InteractionFlag;

public:
	static bool GetFirstInteaction();

private:	// member Var
	GameEngineImageRenderer* WeaponNPCRenderer_;
	GameEngineCollision* WeaponNPCCollision_;

private:
	WeaponNPC_MoveDir PrevMoveDir_;
	WeaponNPC_MoveDir CurMoveDir_;

private: // FSM
	GameEngineFSM State_;
	WeaponNPC_FSMState PrevState_;
	WeaponNPC_FSMState CurState_;

private: // 이동경로 및 자동이동관련
	float MoveDelayTime_;				// NPC의 다음이동까지 딜레이시간
	float MoveSpeed_;					// NPC의 이동속도
	float4 MoveStartPos_;				// 이동전위치
	float4 MoveCurPos_;					// 이동중위치

private:
	float4 MoveMinRange_;				// 최소이동범위(이동가능한 타일인덱스 계산용)
	float4 MoveMaxRange_;				// 최대이동범위(이동가능한 타일인덱스 계산용)

private: // UI관련
	NPC_MessageView* MessageView_;
	NPC_TopMenuBar* TopMenuBar_;

public:
	WeaponNPC();
	~WeaponNPC();

protected:		// delete constructer
	WeaponNPC(const WeaponNPC& _other) = delete;
	WeaponNPC(WeaponNPC&& _other) noexcept = delete;

private:		//delete operator
	WeaponNPC& operator=(const WeaponNPC& _other) = delete;
	WeaponNPC& operator=(const WeaponNPC&& _other) = delete;

private:
	void InitWeaponNPC();
	void TextureCutting();
	void CreateAnimation();
	void CreateFSMState();
	void CreateCollision();

private: // 상태/방향별 체크가하여 애니메이션 변경
	void ChangeAnimationCheck(const std::string& _StateName);

private: // 목표타일까지의 경로탐색
	std::list<PathIndex> SearchMovePath(WeaponNPC_MoveDir _MoveDir);

private:
	// 대기상태
	void StartIdle();
	void UpdateIdle();
	void EndIdle();

	// 이동상태
	void StartWalk();
	void UpdateWalk();
	void EndWalk();

	// 상호작용대기 상태
	void StartConversation();
	void UpdateConversation();
	void EndConversation();

	// 상호작용중 상태
	void StartInteraction();
	void UpdateInteraction();
	void EndInteraction();

private:
	void MouseLButtonClick(GameEngineCollision* _Other);
	
private:
	void InteractionDistanceCheck();

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	NPC_BuySellView* GetWeaponShop();

public:
	void SetMoveRange();
	void SetMessageBoxText(const std::string& _Text);
	void SetUIPosition();
	void SetTopMenu();

public:
	void TopMenuBarInactive();
	void TopMenuBarActive();

public:
	void InteractionEnd();
	void SelectConversationMenu();
};


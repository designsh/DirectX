#include "PreCompile.h"
#include "NPC_TopMenuBar.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

NPC_TopMenuBar::NPC_TopMenuBar() :
	TopMenuPanel_(nullptr),
	BuySellMenuRenderer_(nullptr),
	ButSellMenuCol_(nullptr),
	NPCClassType_(NPCClassType::MAX),
	NPCType_(NPCType::Normal)
{
}

NPC_TopMenuBar::~NPC_TopMenuBar()
{
}

void NPC_TopMenuBar::Start()
{
}

void NPC_TopMenuBar::Update(float _DeltaTime)
{
}

void NPC_TopMenuBar::CreateNPCTopMenu(NPCClassType _NPCClassType, NPCType _NPCType)
{
	// 기본정보 저장
	NPCClassType_ = _NPCClassType;
	NPCType_ = _NPCType;

	// NPC 클래스 타입에 따른 상단메뉴바 판넬 생성








}

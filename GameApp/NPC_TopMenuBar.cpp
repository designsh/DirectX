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
	// �⺻���� ����
	NPCClassType_ = _NPCClassType;
	NPCType_ = _NPCType;

	// NPC Ŭ���� Ÿ�Կ� ���� ��ܸ޴��� �ǳ� ����








}

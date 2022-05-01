#pragma once
#include <GameEngine/GameEngineActor.h>

#include "AllItemInfomation.h"
#include "AllNPCInfomation.h"

// 퀵슬롯 정보
class GameEngineUIRenderer;
class GameEngineCollision;
struct QuickSlotInfo
{
	bool ItemArrangementFlag_;								// 해당 타일의 배치완료 Flag(아이템이 배치되었다면 true)
	GameEngineUIRenderer* TileRenderer_;					// 해당 타일의 렌더러(아이템 배치시 Blue Color)
	GameEngineCollision* TileCollision_;					// 해당 타일의 충돌체

	// ItemArrangementFlag_이 true상태일때 아이템 존재
	ItemList ItemInfo_;										// 해당 아이템의 기본정보(이름, 판매금액, ...) 
	GameEngineUIRenderer* ItemRenderer_;					// 해당 아이템 렌더러
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_QuickSlot : public GameEngineActor
{
private:
	std::vector<QuickSlotInfo> QuickSlotInfo_;				// 퀵슬롯 정보(아이템정보, 배치상태정보, ...)

public:
	MainPlayer_QuickSlot();
	~MainPlayer_QuickSlot();

protected:		// delete constructer
	MainPlayer_QuickSlot(const MainPlayer_QuickSlot& _other) = delete;
	MainPlayer_QuickSlot(MainPlayer_QuickSlot&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_QuickSlot& operator=(const MainPlayer_QuickSlot& _other) = delete;
	MainPlayer_QuickSlot& operator=(const MainPlayer_QuickSlot&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

private:
	void QuickSlotClick(GameEngineCollision* _Other, int _Index);
	void ItemPlacement(int _ColTileIndex);
	void ItemDisposition(int _ColTileIndex);

private:
	void QuickSlotItemUse(int _Index);

private:
	void ItemSellProcess(int _TileIndex, NPCType _BuySellType);

public:
};


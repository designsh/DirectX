#pragma once
#include <GameEngine/GameEngineActor.h>

#include "AllItemInfomation.h"
#include "AllNPCInfomation.h"

// ������ ����
class GameEngineUIRenderer;
class GameEngineCollision;
struct QuickSlotInfo
{
	bool ItemArrangementFlag_;								// �ش� Ÿ���� ��ġ�Ϸ� Flag(�������� ��ġ�Ǿ��ٸ� true)
	GameEngineUIRenderer* TileRenderer_;					// �ش� Ÿ���� ������(������ ��ġ�� Blue Color)
	GameEngineCollision* TileCollision_;					// �ش� Ÿ���� �浹ü

	// ItemArrangementFlag_�� true�����϶� ������ ����
	ItemList ItemInfo_;										// �ش� �������� �⺻����(�̸�, �Ǹűݾ�, ...) 
	GameEngineUIRenderer* ItemRenderer_;					// �ش� ������ ������
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_QuickSlot : public GameEngineActor
{
private:
	std::vector<QuickSlotInfo> QuickSlotInfo_;				// ������ ����(����������, ��ġ��������, ...)

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


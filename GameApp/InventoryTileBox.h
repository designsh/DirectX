#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

#include "MainPlayerInfomation.h"

// 분류 : 타일
// 용도 : 인벤토리 아이템 배치
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InventoryTileBox : public GameEngineActor
{
private:	// member Var
	bool ItemArrangementFlag_;								// 배치 Flag(해당 박스에 아이템이 존재하면(배치되어있다면) true)
	ItemLocType BoxTileType_;								// 타일박스 타입(NORMAL : 플레이어의 장착상태와 무관)

private:
	GameEngineUIRenderer* TileBoxRenderer_;					// 타일박스 렌더러

private:
	int Index_;												// 총 인덱스
	int IndexX_;											// x 인덱스
	int IndexY_;											// y 인덱스
	float4 Pos_;											// 위치
	float4 Scale_;											// 크기

public:
	InventoryTileBox();
	~InventoryTileBox();

protected:		// delete constructer
	InventoryTileBox(const InventoryTileBox& _other) = delete;
	InventoryTileBox(InventoryTileBox&& _other) noexcept = delete;

private:		//delete operator
	InventoryTileBox& operator=(const InventoryTileBox& _other) = delete;
	InventoryTileBox& operator=(const InventoryTileBox&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline float4 GetTilePos()
	{
		return Pos_;
	}

	inline bool GetIsItemBatch()
	{
		return ItemArrangementFlag_;
	}

public:
	inline void SetItemArrangeFlagOn()
	{
		ItemArrangementFlag_ = true;
	}

	inline void SetItemArrangeFlagOff()
	{
		ItemArrangementFlag_ = false;
	}

public:
	void TileBoxActive();
	void TileBoxInactive();

public:
	void CreateNormalTileBox(bool _ArrangementFlag, ItemLocType _BoxTileType, int _X, int _Y, int _Index);
	void CreatePlayerEquipTileBox(const std::string& _TextureName, bool _ArrangementFlag, ItemLocType _BoxTileType, int _Index, float4 _Pos, float4 _Scale);

public:
};


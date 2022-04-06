#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

#include "MainPlayerInfomation.h"

// �з� : Ÿ��
// �뵵 : �κ��丮 ������ ��ġ
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InventoryTileBox : public GameEngineActor
{
private:	// member Var
	bool ItemArrangementFlag_;								// ��ġ Flag(�ش� �ڽ��� �������� �����ϸ�(��ġ�Ǿ��ִٸ�) true)
	ItemLocType BoxTileType_;								// Ÿ�Ϲڽ� Ÿ��(NORMAL : �÷��̾��� �������¿� ����)

private:
	GameEngineUIRenderer* TileBoxRenderer_;					// Ÿ�Ϲڽ� ������

private:
	int Index_;												// �� �ε���
	int IndexX_;											// x �ε���
	int IndexY_;											// y �ε���
	float4 Pos_;											// ��ġ
	float4 Scale_;											// ũ��

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


#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

enum class InvenTileBoxType
{
	NORMAL,		// 일반
	HELM,		// 투구
	ARMOR,		// 갑옷
	LRING,		// 왼쪽 링
	RRING,		// 오른쪽 링
	AMULET,		// 목걸이
	GLOVES,		// 장갑
	BOOTS,		// 부츠
	BELT,		// 벨트
	WEAPON,		// 무기
	SHIELD,		// 방패
	MAX
};

// 분류 : 타일
// 용도 : 인벤토리 아이템 배치
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InventoryTileBox : public GameEngineActor
{
private:	// member Var
	bool ArrangementFlag_;									// 배치 Flag(해당 박스에 아이템이 존재하면(배치되어있다면) true)
	InvenTileBoxType BoxTileType_;							// 타일박스 타입(NORMAL : 플레이어의 장착상태와 무관)
	int Index_;												// 총 인덱스
	int IndexX_;											// x 인덱스
	int IndexY_;											// y 인덱스
	float4 Pos_;											// 위치
	float4 Scale_;											// 크기

private:
	GameEngineUIRenderer* TileBoxRenderer_;					// 타일박스 렌더러
	GameEngineCollision* TileBoxCollider_;					// 타일박스 충돌체
	Button_State TileBoxButtonState_;						// 타일박스 충돌체 클릭 상태

private:
	GameEngineUIRenderer* TileBoxItemEquipRenderer_;		// 아이템용 렌더러(아이템배치시 생성)??

private:
	std::vector<std::string> TextImage_;

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

private:
	void BoxTileClick(GameEngineCollision* _Other);

public:
	void ItemEquipCheck(InvenTileBoxType _BoxTileType);

public:
	void TileBoxActive();
	void TileBoxInactive();

public:
	void CreateNormalTileBox(bool _ArrangementFlag, InvenTileBoxType _BoxTileType, int _X, int _Y, int _Index);
	void CreatePlayerEquipTileBox(const std::string& _TextureName, bool _ArrangementFlag, InvenTileBoxType _BoxTileType, int _Index, float4 _Pos, float4 _Scale);
};


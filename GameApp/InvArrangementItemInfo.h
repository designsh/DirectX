#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "MainPlayerInfomation.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InvArrangementItemInfo : public GameEngineActor
{
private: // 타일박스 정보와 연동을 위한 정보
	int ListIndex_;									// 목록에서의 인덱스
	ItemLocType TileLocType_;						// 해당 아이템이 차지하는 타일(칸)의 타입
	int TileIndex_;									// 해당 아이템이 차지하는 타일(칸) => 아이템크기가 1x1일때는 배치된 타일, 아니라면 배치된 타일시작점
	int WidthSize_;									// 해당 아이템의 높이 인덱스(차지하는 타일수)
	int HeightSize_;								// 해당 아이템의 너비 인덱스(차지하는 타일수)
	std::vector<int> ArrangementTileIdxList_;		// 해당 아이템이 차지하는 타일(칸)의 인덱스목록 => 인벤창의 하단 보관탭에 배치될때 정보가 저장됨
	
private: // 마우스와 연동을 위한 정보
	std::string ItemName_;							// 해당 아이템명
	std::string InvItemName_;						// 해당 인벤창에서의 아이템명
	std::string ItemTexutreName_;					// 해당 아이템의 텍스쳐명
	int ItemCode_;									// 해당 아이템의 코드
	float4 RenderPos_;								// 해당 아이템의 렌더러(or 충돌체) 위치
	float4 RenderScale_;							// 해당 아이템의 렌더러(or 충돌체 크기

private: // 
	GameEngineUIRenderer* InvItemRenderer_;			// 해당 아이템 이벤창에서의 렌더러

public:
	InvArrangementItemInfo();
	~InvArrangementItemInfo();

protected:		// delete constructer
	InvArrangementItemInfo(const InvArrangementItemInfo& _other) = delete;
	InvArrangementItemInfo(InvArrangementItemInfo&& _other) noexcept = delete;

private:		//delete operator
	InvArrangementItemInfo& operator=(const InvArrangementItemInfo& _other) = delete;
	InvArrangementItemInfo& operator=(const InvArrangementItemInfo&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline int GetItemIndexListSize()
	{
		return static_cast<int>(ArrangementTileIdxList_.size());
	}

	inline bool GetItemIndexListEmpty()
	{
		return ArrangementTileIdxList_.empty();
	}

	inline int GetStartTileIndex()
	{
		return TileIndex_;
	}

	inline std::string GetTextureName()
	{
		return ItemTexutreName_;
	}

	inline float4 GetRenderScale()
	{
		return RenderScale_;
	}

	inline ItemLocType GetLocType()
	{
		return TileLocType_;
	}

	inline int GetLocTypeInt()
	{
		return static_cast<int>(TileLocType_);
	}

	inline float4 GetArrangeItemSize()
	{
		return float4(static_cast<float>(WidthSize_), static_cast<float>(HeightSize_));
	}

	inline std::vector<int>& GetItemArrIndexList()
	{
		return ArrangementTileIdxList_;
	}

	inline std::string GetItemName()
	{
		return ItemName_;
	}

public:
	void SetItemRenderPos(const float4& _RenderPos);

public:
	void SetTileIndexList(std::vector<int> _TileIndexList);
	bool CreateItemInfo(int _ListIndex, int _TileIndex, ItemLocType _TileLocType, const std::string& _ItemName, const float4& _RenderPos, bool _CreateInfo = false);

public:
	bool ItemArrngeListFind(int _Index);
};


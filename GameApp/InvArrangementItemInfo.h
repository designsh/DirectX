#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "MainPlayerInfomation.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InvArrangementItemInfo : public GameEngineActor
{
private: // Ÿ�Ϲڽ� ������ ������ ���� ����
	int ListIndex_;									// ��Ͽ����� �ε���
	ItemLocType TileLocType_;						// �ش� �������� �����ϴ� Ÿ��(ĭ)�� Ÿ��
	int TileIndex_;									// �ش� �������� �����ϴ� Ÿ��(ĭ) => ������ũ�Ⱑ 1x1�϶��� ��ġ�� Ÿ��, �ƴ϶�� ��ġ�� Ÿ�Ͻ�����
	int WidthSize_;									// �ش� �������� ���� �ε���(�����ϴ� Ÿ�ϼ�)
	int HeightSize_;								// �ش� �������� �ʺ� �ε���(�����ϴ� Ÿ�ϼ�)
	std::vector<int> ArrangementTileIdxList_;		// �ش� �������� �����ϴ� Ÿ��(ĭ)�� �ε������ => �κ�â�� �ϴ� �����ǿ� ��ġ�ɶ� ������ �����
	
private: // ���콺�� ������ ���� ����
	std::string ItemName_;							// �ش� �����۸�
	std::string InvItemName_;						// �ش� �κ�â������ �����۸�
	std::string ItemTexutreName_;					// �ش� �������� �ؽ��ĸ�
	int ItemCode_;									// �ش� �������� �ڵ�
	float4 RenderPos_;								// �ش� �������� ������(or �浹ü) ��ġ
	float4 RenderScale_;							// �ش� �������� ������(or �浹ü ũ��

private: // 
	GameEngineUIRenderer* InvItemRenderer_;			// �ش� ������ �̺�â������ ������

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


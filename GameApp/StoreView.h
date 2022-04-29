#pragma once
#include <GameEngine/GameEngineActor.h>

#include "MainPlayerInfomation.h"
#include "GlobalEnumClass.h"

// â��â�� �����۹�ġŸ������
class GameEngineUIRenderer;
struct StoredArrangeTileInfo
{
	bool ItemArrangementFlag_;								// �ش� Ÿ���� ��ġ�Ϸ� Flag(�������� ��ġ�Ǿ��ٸ� true)
	int Index_;												// �ش� Ÿ���� �Ѱ��ε���
	int IndexX_;											// �ش� Ÿ���� X �ε���
	int IndexY_;											// �ش� Ÿ���� Y �ε���
	float4 TileScale_;										// �ش� Ÿ���� ũ��
	float4 TilePos_;										// �ش� Ÿ���� ��ġ
	GameEngineUIRenderer* TileRenderer_;					// �ش� Ÿ���� ������(������ ��ġ�� Blue Color)
};

// �������ִ� �������� ����
class GameEngineUIRenderer;
struct StoredItem
{
	bool OneSize_;											// �ش� �������� ũ�Ⱑ 1x1�϶� true
	int StartIndex;											// �ش� �������� ũ�Ⱑ 1x1�϶� �����ϴ� �ε���
	std::vector<int> ArrangeIndexs_;						// �ش� �������� ũ�Ⱑ 1x1�� �ƴҶ� �����ϴ� �ε������
	ItemList ItemInfo_;										// �ش� �������� �⺻����(�̸�, �Ǹűݾ�, ...)
	float4 RenderPos_;										// �ش� �����۷����� ��ġ
	GameEngineUIRenderer* ItemRenderer_;					// �ش� ������ ������
};

// â��â�� ���������� ��� ����
struct StoreViewInfo
{
	std::vector<StoredArrangeTileInfo> ArrangeTiles_;		// ��ġŸ������
	std::vector<StoredItem> HaveItemList_;					// �����ϰ��ִ� �����۸��
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class TakeInOutGoldPopup;
class StoreView : public GameEngineActor
{
private:
	bool StoreViewActive_;											// â��â Ȱ��/��Ȱ�� Flags
	int StoredGold_;												// â�� ����� ������差
	int StoredMaxGold_;												// â�� ���尡���� ��� �ִ뷮

private: // �ǳڰ���
	GameEngineUIRenderer* StoreViewPanel_;							// â��â �ǳڷ�����
	GameEngineCollision* StoreViewPanelCol_;						// â��â �ǳ��浹ü(�÷��̾� �̵��Ǵ� üũ��)

private: // ������
	// ��岨�����˾� ����
	GameEngineUIRenderer* StoreGoldTakeOutPopBtn_;					// â�� ����� ������差 ������ �˾���ư ������
	GameEngineCollision* StoreGoldTakeOutPopColBtn_;				// â�� ����� ������差 ������ �˾���ư �浹ü
	Button_State StoreGoldTakeOutPopBtnState_;						// â�� ����� ������差 ������ �˾���ư ����

	// ��差 ����
	GameEngineUIRenderer* StoreGold_;								// â�� ����� ������差
	GameEngineUIRenderer* StoreMaxGold_;							// â�� ����� ��� �ִ뷮

	// ����˾� ����
	TakeInOutGoldPopup* TakeOutGoldPopup_;							// â�� ����� ��差 ������ �˾�â

private: // â�ݱ��ư ����
	GameEngineUIRenderer* CloseButton_;								// â��â �����ư
	GameEngineCollision* CloseBtnCol_;								// â��â �����ư �浹ü
	Button_State CloseBtnState_;									// â��â �����ư ����

private: // ������ ��ġ����
	StoreViewInfo StoreViewInfo_;									// â��â ����(�����ۺ������, �����۹�ġ����, ...)
	std::vector<GameEngineCollision*> StoreArrTileCols_;			// �� â��â�� ��ġŸ�� �浹ü

public:
	StoreView();
	~StoreView();

protected:		// delete constructer
	StoreView(const StoreView& _other) = delete;
	StoreView(StoreView&& _other) noexcept = delete;

private:		//delete operator
	StoreView& operator=(const StoreView& _other) = delete;
	StoreView& operator=(const StoreView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void CloseButtonClick(GameEngineCollision* _Other);
	void GoldButtonClick(GameEngineCollision* _Other);
	void PrivateStoreViewActive();
	void GoldPopupViewActive();

public:
	void StoreViewOff();
	void StoreViewOn();

public:
	int StoredGoldAdd(int _Gold);
	int StoredGoldSub(int _Gold);
};


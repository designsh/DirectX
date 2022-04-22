#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

enum class StatPointType
{
	NONE = -1,
	STR,
	DEX,
	VIT,
	ENR,
	MAX
};

// �з� : ����â
// �뵵 : �÷��̾� ���� ǥ��
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineLevel;
class StatView : public GameEngineActor
{
private:
	static int StatPoint;

private:	// member Var
	GameEngineUIRenderer* PanelRenderer_;						// ����â(�ǳ�)
	GameEngineUIRenderer* IDRenderer_;							// ����â ID
	GameEngineUIRenderer* JobClassRenderer_;					// ����â ������
	GameEngineUIRenderer* CurLevelRenderer_;					// ����â ���� ����
	GameEngineUIRenderer* CurExpRenderer_;						// ����â ����ġ
	GameEngineUIRenderer* StrengthRenderer_;					// ����â ��
	GameEngineUIRenderer* DexterityRenderer_;					// ����â ��ø
	GameEngineUIRenderer* VitalityRenderer_;					// ����â �����
	GameEngineUIRenderer* EnergyRenderer_;						// ����â ������
	GameEngineUIRenderer* DamageRenderer_;						// ����â ���ݵ�����(�ּ�) -  ����â ���ݵ�����(�ִ�)
	GameEngineUIRenderer* AttackRatingRenderer_;				// ����â ���ݵ��
	GameEngineUIRenderer* DefenseRenderer_;						// ����â ���
	GameEngineUIRenderer* StaminaRenderer_;						// ����â ���¹̳�
	GameEngineUIRenderer* LifeRenderer_;						// ����â ������
	GameEngineUIRenderer* ManaRenderer_;						// ����â ����
	GameEngineUIRenderer* FireResistanceRenderer_;				// ����â ���̾� ���׷�
	GameEngineUIRenderer* ColdResistanceRenderer_;				// ����â �ݵ� ���׷�
	GameEngineUIRenderer* LightningResistanceRenderer_;			// ����â ����Ʈ�� ���׷�
	GameEngineUIRenderer* PoisonResistanceRenderer_;			// ����â ������ ���׷�

private:
	GameEngineUIRenderer* CloseButton_;							// ����â �����ư
	GameEngineCollision* MainCollider_;							// ����â �����ư �浹ü

private:
	std::string IDString_;										// ����â ID
	std::string JobClassString_;								// ����â ������
	std::string CurLevelString_;								// ����â ���� ����
	std::string CurExpString_;									// ����â ����ġ
	std::string StrengthString_;								// ����â ��
	std::string DexterityString_;								// ����â ��ø
	std::string VitalityString_;								// ����â �����
	std::string EnergyString_;									// ����â ������
	std::string MinDamageString_;								// ����â ���ݵ�����(�ּ�)
	std::string MaxDamageString_;								// ����â ���ݵ�����(�ִ�)
	std::string AttackRatingString_;							// ����â ���ݵ��
	std::string DefenseString_;									// ����â ���
	std::string StaminaString_;									// ����â ���¹̳�
	std::string LifeString_;									// ����â ������
	std::string ManaString_;									// ����â ����
	std::string FireResistanceString_;							// ����â ���̾� ���׷�
	std::string ColdResistanceString_;							// ����â �ݵ� ���׷�
	std::string LightningResistanceString_;						// ����â ����Ʈ�� ���׷�
	std::string PoisonResistanceString_;						// ����â ������ ���׷�

private:
	Button_State ButtonState_;

private: // �÷��̾� �������� Ȱ��ȭ�Ǿ� ������ ������Ű�� ��ư
	GameEngineUIRenderer* STRPointUpButton_;					// �� ������ư ������
	GameEngineCollision* STRPointUpButtonCollider_;				// �� ������ư �浹ü
	GameEngineUIRenderer* DEXPointUpButton_;					// ��ø ������ư ������
	GameEngineCollision* DEXPointUpButtonCollider_;				// ��ø ������ư �浹ü
	GameEngineUIRenderer* VITPointUpButton_;					// ����� ������ư ������
	GameEngineCollision* VITPointUpButtonCollider_;				// ����� ������ư �浹ü
	GameEngineUIRenderer* ENRPointUpButton_;					// ������ ������ư ������
	GameEngineCollision* ENRPointUpButtonCollider_;				// ������ ������ư �浹ü

	Button_State STRButtonState_;								// �� ������ư ����
	Button_State DEXButtonState_;								// ��ø ������ư ����
	Button_State VITButtonState_;								// ����� ������ư ����
	Button_State ENRButtonState_;								// ������ ������ư ����

public:
	StatView();
	~StatView();

protected:		// delete constructer
	StatView(const StatView& _other) = delete;
	StatView(StatView&& _other) noexcept = delete;

private:		//delete operator
	StatView& operator=(const StatView& _other) = delete;
	StatView& operator=(const StatView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
	void InitStatView();

public:
	void CloseButtonClick(GameEngineCollision* _Other);
	void STRButtonClick(GameEngineCollision* _Other);
	void DEXButtonClick(GameEngineCollision* _Other);
	void VITButtonClick(GameEngineCollision* _Other);
	void ENRButtonClick(GameEngineCollision* _Other);

public:
	void StatPointUP(StatPointType _Type);

public:
	void CurEXPUpdate(float _EXP);

public: // �������������� ��������Ʈ �ο�
	void LevelUpStatPointGrant();
};


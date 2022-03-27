#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �з� : ����â
// �뵵 : �÷��̾� ���� ǥ��
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class StatView : public GameEngineActor
{
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

public:
	void InitStatView();

public:
	void CloseButtonClick(GameEngineCollision* _Other);
};


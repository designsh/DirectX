#pragma once
#include "MainPlayerInfomation.h"
#include <GameEngineBase/ExcelControl.h>

// ���� Ŭ����
enum class MonsterClassType
{
	SpikeFiend,					// 
	Zombie,						// 
	Fallen,						// 
	Tainted,					// 
	Andariel,					// 
	Diablo,						// 
	MAX,
};

// ���� Ÿ��
enum class MonsterType
{
	Normal,						// �Ϲݸ���
	Boss,						// ��������
};

struct AllMonsterInfo
{
	// ============================ ���� �⺻���� ============================ //
	std::string								Name;								// ���� ��
	MonsterClassType						ClassType;							// ���� Ŭ���� Ÿ��
	MonsterType								Type;								// ���� Ÿ��
	
	int										Level;								// ���� ����
	int										Velocity;							// ���� �̵��ӵ�
	int										RunVelocity;						// ���� �ٱ���¿����� �̵��ӵ�
	int										MinGrp;								// �ѹ��� �����Ǵ� ������ �ּ� ��
	int										MaxGrp;								// �ѹ��� �����Ǵ� ������ �ִ� ��

	int										DropEXP;							// ���� ����� �÷��̾�� �ִ� ����ġ��
	int										DropItemPercent;					// ���� ����� ������ �����
	int										DropItemType;						// ���� ����� ����Ǵ� ������ Ÿ��
	int										DropGoldPercent;					// ���� ����� ��� �����
	int										DropGoldMin;						// ���� ����� ����Ǵ� �ּ� ��差
	int										DropGoldMax;						// ���� ����� ����Ǵ� �ִ� ��差

	bool									IsSpawn;							// ������ ����(�����) Flag
	bool									IsDoorOpen;							// ���Ͱ� ���� �����ִ��� �Ǵ� Flag
	bool									IsInTown;							// ���� ���� ���԰��� �Ǵ� Flag
	bool									IsCourpseSel;						// �ش� ���� ��ü�� Ư����ų ��밡�� Flag(Ex. �÷��̾� ��ȯ�� ��ų ��)
	bool									IsRun;								// ���Ͱ� �ٱⰡ �������� �Ǵ� Flag
	bool									IsSpecialAttack;					// ���� Ư�� ���ݰ��� ���� Flag

	// ============================ ���� ������ ============================ //
	int										MinHP;								// ���� �ּ� �����
	int										MaxHP;								// ���� �ִ� �����
	int										HPRegen;							// ���� ����� ȸ����
	int										Block;								// ���� ����
	int										Damage;								// ���� �Ϲݰ��ݷ�

	int										SpeAtkCoolTime;						// ���� Ư������ ��Ÿ��
	int										SpeAtkDamage;						// ���� Ư�����ݷ�

	int										DamageResist;						// �Ϲݰ��� ���׷�
	int										SpecialDamageResist;				// Ư������ ���׷�
	int										FireResist;							// ȭ�� ���׷�
	int										LightningResist;					// ����Ʈ�� ���׷�
	int										ColdResist;							// �ñ� ���׷�
	int										PosionResist;						// �� ���׷�
};

// �з� : ����
// �뵵 : �������� ������
// ���� : ��� ���������� ����
class AllMonsterInfomation
{
private:
	static AllMonsterInfomation* Inst;

public:
	static AllMonsterInfomation& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var
	std::vector<AllMonsterInfo> AllMonsterList_;

private:
	bool ExcelZFlag_;

private:
	AllMonsterInfomation();
	~AllMonsterInfomation();

protected:		// delete constructer
	AllMonsterInfomation(const AllMonsterInfomation& _other) = delete;
	AllMonsterInfomation(AllMonsterInfomation&& _other) noexcept = delete;

private:		//delete operator
	AllMonsterInfomation& operator=(const AllMonsterInfomation& _other) = delete;
	AllMonsterInfomation& operator=(const AllMonsterInfomation&& _other) = delete;

public:
	bool MonsterInfoFind(MonsterClassType _ClassType, AllMonsterInfo& _ClassMonsterInfo);

public:
	void CreateAllMonsterInfomation(bool _ExcelFile = false);
	void LoadMonsterExcelFile();
	void LoadMonsterBinaryFile();

public:
	void SaveMonsterBinaryFile();
};


#pragma once

// ����Ÿ��
enum class JobType
{
	None = -1,
	Necromancer = 0,		// ��ũ�θǼ�
	amazon,						// �Ƹ���
	barbarian,						// �ٹٸ���
	paladin							// �ȶ��
};

// �з� : �÷��̾� �⺻����
// �뵵 : 
// ���� : 
class CommonInfomation
{
private:	// �⺻����
	std::string ID_;
	std::string JobName_;
	JobType JobType_;
	int Level_;
	float Exp_;

private: // �⺻��������
	int Strength_; // ��
	int Dexterity_; // ��ø
	int Vitality_; // �����
	int Energy_; // ������

private: // ����������


private: // ��ų����


public:
	CommonInfomation();
	~CommonInfomation();

protected:		// delete constructer
	CommonInfomation(const CommonInfomation& _other) = delete;
	CommonInfomation(CommonInfomation&& _other) noexcept = delete;

private:		//delete operator
	CommonInfomation& operator=(const CommonInfomation& _other) = delete;
	CommonInfomation& operator=(const CommonInfomation&& _other) = delete;

public:
	void CreateCommonInfo();
};


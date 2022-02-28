#pragma once

// �з� : �÷��̾� �⺻����
// �뵵 : 
// ���� : 
class CommonInfomation
{
private:	// �⺻����
	std::string ID_;
	std::string JobName_;
	int Level_;
	float Exp_;

private: // �⺻��������
	int Strength_; // ��
	int Dexterity_; // ��ø
	int Vitality_; // �����
	int Energy_; // ������

private: // �󼼽�������


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


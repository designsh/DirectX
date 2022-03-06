#pragma once

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
	void CreateAllMonsterInfomation();
};


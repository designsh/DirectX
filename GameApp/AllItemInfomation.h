#pragma once

// �з� : ����
// �뵵 : ���������� ������
// ���� : ��� ������������ ����
class AllItemInfomation
{
private:
	static AllItemInfomation* Inst;

public:
	static AllItemInfomation& GetInst()
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
	AllItemInfomation();
	~AllItemInfomation();

protected:		// delete constructer
	AllItemInfomation(const AllItemInfomation& _other) = delete;
	AllItemInfomation(AllItemInfomation&& _other) noexcept = delete;

private:		//delete operator
	AllItemInfomation& operator=(const AllItemInfomation& _other) = delete;
	AllItemInfomation& operator=(const AllItemInfomation&& _other) = delete;

public:
	void CreateAllItemInfomation();
};


#pragma once

// 분류 : 정보
// 용도 : 아이템정보 관리용
// 설명 : 모든 아이템정보를 관리
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


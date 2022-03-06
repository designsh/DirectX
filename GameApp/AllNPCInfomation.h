#pragma once

// 분류 : 정보
// 용도 : NPC정보 관리용
// 설명 : 모든 NPC정보를 관리
class AllNPCInfomation
{
private:
	static AllNPCInfomation* Inst;

public:
	static AllNPCInfomation& GetInst()
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
	AllNPCInfomation();
	~AllNPCInfomation();

protected:		// delete constructer
	AllNPCInfomation(const AllNPCInfomation& _other) = delete;
	AllNPCInfomation(AllNPCInfomation&& _other) noexcept = delete;

private:		//delete operator
	AllNPCInfomation& operator=(const AllNPCInfomation& _other) = delete;
	AllNPCInfomation& operator=(const AllNPCInfomation&& _other) = delete;

public:
	void CreateAllNPCInfomation();
};


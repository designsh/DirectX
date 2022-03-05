#pragma once

struct MainPlayerInfo
{

};

class MainPlayerInfomation
{
private:
	static MainPlayerInfomation* Inst;

public:
	static MainPlayerInfomation& GetInst()
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
	MainPlayerInfo MainPlayerInfo_;

private:
	MainPlayerInfomation();
	~MainPlayerInfomation();

protected:		// delete constructer
	MainPlayerInfomation(const MainPlayerInfomation& _other) = delete;
	MainPlayerInfomation(MainPlayerInfomation&& _other) noexcept = delete;

private:		//delete operator
	MainPlayerInfomation& operator=(const MainPlayerInfomation& _other) = delete;
	MainPlayerInfomation& operator=(const MainPlayerInfomation&& _other) = delete;

public:

};





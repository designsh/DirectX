#pragma once

// 직업타입
enum class JobType
{
	None = -1,
	Necromancer = 0,		// 네크로맨서
	amazon,						// 아마존
	barbarian,						// 바바리안
	paladin							// 팔라딘
};

// 분류 : 플레이어 기본정보
// 용도 : 
// 설명 : 
class CommonInfomation
{
private:	// 기본정보
	std::string ID_;
	std::string JobName_;
	JobType JobType_;
	int Level_;
	float Exp_;

private: // 기본스텟정보
	int Strength_; // 힘
	int Dexterity_; // 민첩
	int Vitality_; // 생명력
	int Energy_; // 에너지

private: // 아이템정보


private: // 스킬정보


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


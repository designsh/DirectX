#pragma once

// 분류 : 플레이어 기본정보
// 용도 : 
// 설명 : 
class CommonInfomation
{
private:	// 기본정보
	std::string ID_;
	std::string JobName_;
	int Level_;
	float Exp_;

private: // 기본스텟정보
	int Strength_; // 힘
	int Dexterity_; // 민첩
	int Vitality_; // 생명력
	int Energy_; // 에너지

private: // 상세스텟정보


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


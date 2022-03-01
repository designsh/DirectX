#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class NecromancerInfo
{
private:	// 상세스텟정보

private: // 스킬정보

public:
	NecromancerInfo();
	~NecromancerInfo();

protected:		// delete constructer
	NecromancerInfo(const NecromancerInfo& _other) = delete;
	NecromancerInfo(NecromancerInfo&& _other) noexcept = delete;

private:		//delete operator
	NecromancerInfo& operator=(const NecromancerInfo& _other) = delete;
	NecromancerInfo& operator=(const NecromancerInfo&& _other) = delete;

public:
};


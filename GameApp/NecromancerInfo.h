#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class NecromancerInfo
{
private:	// �󼼽�������

private: // ��ų����

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


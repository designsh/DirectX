#pragma once

// �з� : 
// �뵵 : 
// ���� : �� ������ �ʷε�� �ڵ����� �������� �̿��Ͽ� �׺���̼� ������ �����ϱ� ���� �������̽� ����
class Navigation
{
private:	// member Var

protected:
	Navigation();
	virtual ~Navigation() = 0;

public:
	virtual bool FindPath(const float4& _Start, const float4& _Goal, std::vector<float4>& _vecPath) = 0;
};

#include "PreCompile.h"
#include "GlobalValue.h"

// ���� ������ ������ �����÷��̾�
MainPlayer* GlobalValue::CurPlayer = nullptr;

// ���� ������ �÷��̾��� �̸�(ID)
// ĳ���ͻ����������� ĳ���͸� ����� �⺻������ �����Ͽ� ���Ϸ� ����(ID.txt)
// �ε��������� ������ ĳ���� ������ �ε��Ͽ� �÷��̾� ��������
// �÷��̷������� ��������� ���� ���ŵ� �÷��̾� ������ �̿��Ͽ� �������� ������
std::string GlobalValue::CurPlayerID = "";

// ���� ������ ������ ���� ���콺������Ʈ
MouseObject* GlobalValue::CurMouse = nullptr;

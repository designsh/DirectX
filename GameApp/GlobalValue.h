#pragma once

// �з� : �۷ι� 
// �뵵 : �������
// ���� : �����÷��̾�� ���� ���� �������� ����ؾ��ϴ� ������ ���� ��ü�� �ش� Ŭ�������� ����
//            (����!!!) �ش� ���� �����Ҷ� �����ؾ��Ѵ�.
class MainPlayer;
class MouseObject;
class GlobalValue
{
public: // �÷��̾� ����
	static MainPlayer* CurPlayer;
	static std::string CurPlayerID;

public: // ���콺����
	static MouseObject* CurMouse;
};


#pragma once
#include <GameEngine/GameEngineGUI.h>

// �з� : 
// �뵵 : 
// ���� : 
class CameraComponent;
class EditorRandomMap;
class CreateRandomMapWindow : public GameEngineGUIWindow
{
public:	// member Var
	EditorRandomMap* RandomMap_;

public: // ī�޶����
	float Zoom_;
	float ZoomMin_;
	float ZoomMax_;

private: // ���� �����Ϸ��� ���� ��ü �ε���
	int MaxIndexX_;
	int MaxIndexY_;

private: // �ڵ� �����Ϸ��� ���� ����, ����/���� �ε���(ũ��)
	int RoomCnt_;
	int RoomWidth_;
	int RoomHeight_;

public:
	CreateRandomMapWindow();
	~CreateRandomMapWindow();

protected:		// delete constructer
	CreateRandomMapWindow(const CreateRandomMapWindow& _other) = delete;
	CreateRandomMapWindow(CreateRandomMapWindow&& _other) noexcept = delete;

private:		//delete operator
	CreateRandomMapWindow& operator=(const CreateRandomMapWindow& _other) = delete;
	CreateRandomMapWindow& operator=(const CreateRandomMapWindow&& _other) = delete;

protected:
	virtual void OnGUI() override;

public:
};


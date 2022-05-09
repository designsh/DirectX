#pragma once
#include <GameEngine/GameEngineGUI.h>

// 분류 : 
// 용도 : 
// 설명 : 
class CameraComponent;
class EditorRandomMap;
class CreateRandomMapWindow : public GameEngineGUIWindow
{
public:	// member Var
	EditorRandomMap* RandomMap_;

public: // 카메라관련
	float Zoom_;
	float ZoomMin_;
	float ZoomMax_;

private: // 현재 생성하려는 맵의 전체 인덱스
	int MaxIndexX_;
	int MaxIndexY_;

private: // 자동 생성하려는 룸의 갯수, 가로/세로 인덱스(크기)
	int RoomCnt_;
	int RoomWidth_;
	int RoomHeight_;

private: // 랜덤맵관련
	// 복도(생성반복횟수, 복도두께, 생성시타일갯수, 방랜덤방향)
	int CreateCorridorCnt_;
	int CorridorThick_;
	int CorridorLenCnt_;
	int CorridorDirCnt_;

	// 룸


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


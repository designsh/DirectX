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

private: // 랜덤맵관련
	// 복도(생성반복횟수, 복도두께, 생성시타일갯수, 방랜덤방향)
	int CreateCorridorCnt_;
	int CorridorThick_;
	int CorridorLenCnt_;
	int CorridorDirCnt_;

	// 룸(복도타일 기준으로 생성)
	int RoomCount_;
	int RoomMaxWidthIndex_;
	int RoomMaxHeightIndex_;

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


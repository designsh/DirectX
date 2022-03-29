#include "PreCompile.h"
#include "MapEditorLevel.h"

#include "EditorControlWindow.h"

MapEditorLevel::MapEditorLevel()
{
}

MapEditorLevel::~MapEditorLevel()
{
}

void MapEditorLevel::LevelChangeEndEvent()
{
}

void MapEditorLevel::LevelChangeStartEvent()
{

}

void MapEditorLevel::LevelStart()
{
	// IMGUI Ã¢ »ý¼º

	// MapEditor Control Window
	GameEngineGUI::GetInst()->CreateGUIWindow<EditorControlWindow>("EditorControlWindow");

	// 


}

void MapEditorLevel::LevelUpdate(float _DeltaTime)
{
}

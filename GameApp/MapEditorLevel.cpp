#include "PreCompile.h"
#include "MapEditorLevel.h"

#include "EditorControlWindow.h"
#include "IsoTileMap.h"
#include <GameEngine\GameEngineInput.h>

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


	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// MapEditor Control Window
	EditorControlWindow* Ptr = GameEngineGUI::GetInst()->CreateGUIWindow<EditorControlWindow>("EditorControlWindow");


	Map = CreateActor<IsoTileMap>();

	Ptr->Map = Map;

}

void MapEditorLevel::LevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		Map->SetTile(GameEngineInput::GetInst().GetMouse3DPos());
	}
}

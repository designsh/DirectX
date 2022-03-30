#include "PreCompile.h"
#include "GameEngineLevelControlWindow.h"
#include "GameEngineCore.h"
#include "GameEngineLevel.h"
#include <GameEngineBase\GameEngineTime.h>
#include "GameEngineActor.h"

GameEngineLevelControlWindow::GameEngineLevelControlWindow()
{
}

GameEngineLevelControlWindow::~GameEngineLevelControlWindow()
{
}

void GameEngineLevelControlWindow::OnGUI()
{
	static float Acc = 1.0f;
	static std::string FrameText = "Frame : " + std::to_string(1.0f / GameEngineTime::GetInst().GetDeltaTime());

	Acc -= GameEngineTime::GetInst().GetDeltaTime();
	if (0 >= Acc)
	{
		FrameText = "Frame : " + std::to_string(1.0f / GameEngineTime::GetInst().GetDeltaTime());
		Acc = 1.0f;
	}
	ImGui::Text(FrameText.c_str());

	int Count = static_cast<int>(GameEngineCore::AllLevel_.size());
	int SameLineIndex = 0;

	for (auto& Level : GameEngineCore::AllLevel_)
	{
		if (true == ImGui::Button(Level.first.c_str()))
		{
			GameEngineCore::LevelChange(Level.first);
		}

		--Count;
		
		if (Count != 0)
		{
			if (SameLineIndex % 2 == 0)
			{
				ImGui::SameLine();
			}
		}

		++SameLineIndex;
	}
}

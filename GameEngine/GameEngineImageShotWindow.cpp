#include "PreCompile.h"
#include "GameEngineImageShotWindow.h"

GameEngineImageShotWindow::GameEngineImageShotWindow() :
	View_(nullptr),
	Size_(float4::ZERO)
{
}

GameEngineImageShotWindow::~GameEngineImageShotWindow()
{
}

void GameEngineImageShotWindow::Start()
{
	Style_ = ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize;
}

void GameEngineImageShotWindow::OnGUI()
{
	ImTextureID Id = reinterpret_cast<ImTextureID>(View_);
	if (true == ImGui::ImageButton(Id, { Size_.x, Size_.y }))
	{
		Off();
	}
}

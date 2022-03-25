#include "PreCompile.h"
#include "GameEngineRenderWindow.h"

GameEngineRenderWindow::GameEngineRenderWindow()
{
}

GameEngineRenderWindow::~GameEngineRenderWindow()
{
}

void GameEngineRenderWindow::OnGUI()
{
	for (size_t i = 0; i < DrawRenderTarget_.size(); i++)
	{
		ImGui::Text(GameEngineString::AnsiToUTF8Return(DrawRenderTarget_[i].Name).c_str());
		ImTextureID Id = reinterpret_cast<ImTextureID>(DrawRenderTarget_[i].Target->GetShaderResourcesView(0));
		float4& Size = DrawRenderTarget_[i].Size_;


		if (true == ImGui::ImageButton(Id, { Size.x, Size.y }))
		{
			int a = 0;
		}
	}
}

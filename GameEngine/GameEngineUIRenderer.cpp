#include "PreCompile.h"
#include "GameEngineUIRenderer.h"
#include "GameEngineLevel.h"
#include "CameraComponent.h"
#include "GameEngineTransform.h"
#include "GameEngineTextureManager.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineFontManager.h"
#include "GameEngineFont.h"
#include "GameEngineWindow.h"

GameEngineUIRenderer::GameEngineUIRenderer() :
	IsText_(false),
	FontName_("궁서"),
	PrintText_(""),
	FontSize_(20),
	FontPivot_(float4::ZERO),
	Color_(float4::WHITE),
	Flags_(FW1_CENTER | FW1_VCENTER)
{
}

GameEngineUIRenderer::~GameEngineUIRenderer()
{
}

void GameEngineUIRenderer::Start()
{
	GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);

	SetRenderingPipeLine("TextureUI");
	ImageRendererStart();
}

void GameEngineUIRenderer::Render()
{
	GameEngineRenderer::Render();

	// 텍스트 셋팅이 되지않았다면 처리안함
	if (false == IsText_)
	{
		return;
	}

	// UIRenderer는 화면의 중앙을 원점(0,0,0)을 기준으로 설정되어있고,
	// GameEngineFont는 스크린좌표(윈도우좌표)를 기준으로 설정되어있으므로,
	// 윈도우의 크기와 UIRenderer의 위치를 이용하여 스크린좌표계에서의 Font의 위치를 
	// 계산한다.

	// 윈도우 크기 Get
	float4 ScreenSize = GameEngineWindow::GetInst().GetSize();
	ScreenSize = ScreenSize.halffloat4();

	// UIRenderer 월드위치 Get
	float4 UIPos = GetTransform()->GetWorldPosition();

	// 폰트 렌더링 위치 계산
	// UIPos가 음수이면 x = ScreenSize - UIPos
	// UIPos가 양수이면 x = ScreenSize + UIPos
	float4 RenderPos = float4::ZERO;
	RenderPos.x = ScreenSize.x + UIPos.x;
	RenderPos.y = ScreenSize.y - UIPos.y;

	// 
	GameEngineFont* Font = GameEngineFontManager::GetInst().Find(FontName_);
	if (nullptr != Font)
	{
		Font->DrawFont(PrintText_, FontSize_, RenderPos, FontPivot_, Color_, Flags_);
	}

	// Shader Reset
	GameEngineDevice::ShaderReset();
}

void GameEngineUIRenderer::SetRenderGroup(int _Order)
{
	GetLevel()->GetUICamera()->ChangeRendererGroup(_Order, this);
}

void GameEngineUIRenderer::TextSetting(std::string _FontName, std::string _PrintText, float _FontSize, unsigned int _Flags, float4 _Color, const float4& _FontPivot)
{
	// 해당 UIRenderer는 텍스트를 사용하므로 Flag On
	IsText_ = true;

	// 텍스트 렌더링에 필요한 기본데이터 저장
	FontName_ = _FontName;
	PrintText_ = _PrintText;
	FontSize_ = _FontSize;
	Color_ = _Color;
	Flags_ = _Flags;
	FontPivot_ = _FontPivot;
}

void GameEngineUIRenderer::AddText(std::string _PrintText)
{
	// 기존의 문자열에 해당 문자열을 병합한다.
	// PrintText_


}

void GameEngineUIRenderer::DelText()
{
	// 기존 문자열의 끝의 문자열을 삭제한다.
	// PrintText_


}

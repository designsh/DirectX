#include "PreCompile.h"
#include "MainPlayer_SkillIcon.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

MainPlayer_SkillIcon::MainPlayer_SkillIcon() :
	PageNo_(SkillPageNo::NONE),
	SkillName_{},
	SkillCode_(-1),
	SkillActive_(false),
	SkillPageRow_(-1),
	SkillPageColumn_(-1),
	SkillPos_(float4::ZERO),
	CurSkillLevel_(0),
	IconRenderer_(nullptr),
	IconCollision_(nullptr),
	CurLevelRenderer_(nullptr)
{
}

MainPlayer_SkillIcon::~MainPlayer_SkillIcon()
{
}

void MainPlayer_SkillIcon::Start()
{
}

void MainPlayer_SkillIcon::Update(float _DeltaTime)
{

}

void MainPlayer_SkillIcon::CreateSkillIcon(SkillPageNo _PageNo, const std::string& _SkillName, int _SkillCode, bool _SkillActiveFlag, int _Row, int _Column, int _CurSkillLevel)
{
	// 기본정보 셋팅
	PageNo_ = _PageNo;
	SkillName_ = _SkillName;
	SkillCode_ = _SkillCode;
	SkillActive_ = _SkillActiveFlag;
	SkillPageRow_ = _Row;
	SkillPageColumn_ = _Column;
	CurSkillLevel_ = _CurSkillLevel;

	// Screen Harf Size Get
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// Create SkillIcon Renderer



	// Create SkillIcon Collsion



	// Create Skill CurLevel Text Renderer





}

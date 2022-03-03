#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTransform.h"
#include "GameEngineTextureManager.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"

GameEngineImageRenderer::GameEngineImageRenderer() :
	CurAnimation_(nullptr),
	CurTexture_(nullptr),
	CutData_(0, 0, 1, 1)
{
}

GameEngineImageRenderer::~GameEngineImageRenderer()
{
	for (auto& Animation : AllAnimations_)
	{
		if (nullptr == Animation.second)
		{
			continue;
		}

		delete Animation.second;
		Animation.second = nullptr;
	}
}

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");
	ShaderHelper.SettingConstantBufferLink("TextureCutData", CutData_);
}

void GameEngineImageRenderer::SetImage(const std::string& _ImageName, const float4& _RenderSize)
{
	CurTexture_ = GameEngineTextureManager::GetInst().Find(_ImageName);
	if (nullptr == CurTexture_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 텍스처를 세팅하려고 했습니다");
		return;
	}

	ShaderHelper.SettingTexture("Tex", _ImageName);

	// 크기지정을 해주지않았다면 이미지크기대로 크기를 설정하고,
	if (true == _RenderSize.IsZero())
	{
		GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);
		if (nullptr != FindTexture)
		{
			float4 ImageSize = FindTexture->GetImageSize();
			GetTransform()->SetLocalScaling(float4(ImageSize));
		}
	}
	else // 크기를 지정했다면 해당 크기로 셰이더크기정보를 셋팅
	{
		GetTransform()->SetLocalScaling(float4(_RenderSize));
	}
}

// ================================== Animation 관련 ================================== //
void GameEngineImageRenderer::Update(float _DeltaTime)
{
	if (nullptr == CurAnimation_)
	{
		return;
	}

	CurAnimation_->Update(_DeltaTime);
}

void GameEngineImageRenderer::CreateAnimation(const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("이미 존재하는 애니메이션을 또 만들었습니다.");
		return;
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->FolderTextures_ = nullptr;

	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->CurFrame_ = _StartFrame;
	NewAnimation->EndFrame_ = _EndFrame;
	NewAnimation->StartFrame_ = _StartFrame;
	NewAnimation->Renderer_ = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::CreateAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("이미 존재하는 애니메이션을 또 만들었습니다.");
	}

	GameEngineFolderTexture* FolderTexture = GameEngineFolderTextureManager::GetInst().Find(_FolderTexName);
	if (nullptr == FolderTexture)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 폴더 텍스처를 세팅하려고 했습니다..");
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->FolderTextures_ = FolderTexture;

	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->CurFrame_ = 0;
	NewAnimation->EndFrame_ = FolderTexture->GetTextureCount() - 1;
	NewAnimation->StartFrame_ = 0;
	NewAnimation->Renderer_ = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::SetChangeAnimation(const std::string& _Name, bool _IsForce)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("애니메이션의 애니메이션 nullptr 입니다");
	}

	if (false == _IsForce && CurAnimation_ == FindIter->second)
	{
		return;
	}

	CurAnimation_ = FindIter->second;
	CurAnimation_->Reset();
	CurAnimation_->CallStart();
}

void GameEngineImageRenderer::SetIndex(const int _Index)
{
	if (nullptr == CurTexture_)
	{
		GameEngineDebug::MsgBoxError("텍스처가 존재하지 않는데 인덱스를 지정하려고 했습니다");
	}

	if (false == CurTexture_->IsCut())
	{
		GameEngineDebug::MsgBoxError("잘리지 않은 텍스처의 인덱스를 지정하려고 했습니다.");
	}

	CutData_ = CurTexture_->GetCutData(_Index);
}

void GameEngineImageRenderer::SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("애니메이션의 애니메이션 nullptr 입니다");
	}

	FindIter->second->StartCallBack_.push_back(_CallBack);
}

void GameEngineImageRenderer::SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("애니메이션의 애니메이션 nullptr 입니다");
	}

	FindIter->second->EndCallBack_.push_back(_CallBack);
}

void GameEngineImageRenderer::SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("애니메이션의 애니메이션 nullptr 입니다");
	}

	FindIter->second->FrameCallBack_[_Index].push_back(_CallBack);
}

void GameEngineImageRenderer::Animation2D::Reset()
{
	IsEnd_ = false;
	CurTime_ = InterTime_;
	CurFrame_ = StartFrame_;
}

void GameEngineImageRenderer::Animation2D::CallStart()
{
	for (auto& CallBack : StartCallBack_)
	{
		CallBack();
	}
}

void GameEngineImageRenderer::Animation2D::CallEnd()
{
	for (auto& CallBack : EndCallBack_)
	{
		CallBack();
	}
}

void GameEngineImageRenderer::Animation2D::CallFrame()
{
	for (auto& CallBack : FrameCallBack_)
	{
		if (CallBack.first != CurFrame_)
		{
			continue;
		}

		if (CallBack.second.size() == 0)
		{
			continue;
		}

		for (size_t i = 0; i < CallBack.second.size(); i++)
		{
			CallBack.second[i]();
		}
	}
}

void GameEngineImageRenderer::Animation2D::Update(float _DeltaTime)
{
	CurTime_ -= _DeltaTime;
	if (CurTime_ <= 0.0f)
	{
		++CurFrame_;
		CurTime_ = InterTime_;
		if (true == Loop_ && CurFrame_ > EndFrame_)
		{
			CallEnd();
			CurFrame_ = StartFrame_;
		}
		else if (false == Loop_ && CurFrame_ > EndFrame_)
		{
			if (false == IsEnd_)
			{
				CallEnd();
			}

			IsEnd_ = true;
			CurFrame_ = EndFrame_;
		}
	}

	CallFrame();

	if (nullptr == FolderTextures_)
	{
		Renderer_->SetIndex(CurFrame_);
	}
	else
	{
		Renderer_->CutData_ = float4(0, 0, 1, 1);
		Renderer_->ShaderHelper.SettingTexture("Tex", FolderTextures_->GetTextureIndex(CurFrame_));
	}
}

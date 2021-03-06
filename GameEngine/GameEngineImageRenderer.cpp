#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTransform.h"
#include "GameEngineTextureManager.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"

GameEngineImageRenderer::GameEngineImageRenderer() :
	CurAnimation_(nullptr),
	CurTexture_(nullptr),
	CutData_(0, 0, 1, 1),
	ResultColor_(float4::ONE)
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

void GameEngineImageRenderer::SetResultColor(float4 _Color)
{
	ResultColor_ = _Color;
}

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");
	//ImageRendererStart();
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
			float4 ImageSize = FindTexture->GetTextureSize();
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

void GameEngineImageRenderer::SetRenderingPipeLineSettingNext()
{
	ShaderHelper.SettingConstantBufferLink("TextureCutData", CutData_);

	ResultColor_ = float4::ONE;
	ShaderHelper.SettingConstantBufferLink("ResultColor", ResultColor_);
}

void GameEngineImageRenderer::ChangeAnimationImage(const std::string _Name, const std::string& _TextureName)
{
	// 상태 찾기
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하는 애니메이션이 아닙니다!!" + _Name);
		return;
	}

	// 텍스쳐 찾기
	GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_TextureName);
	if (nullptr == FindTexture)
	{
		GameEngineDebug::MsgBoxError("존재하는 텍스쳐가 아닙니다!!" + _TextureName);
		return;
	}

	FindIter->second->ChangeAnimationTexture(FindTexture);
}

void GameEngineImageRenderer::CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("이미 존재하는 애니메이션을 또 만들었습니다.");
		return;
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->FolderTextures_ = nullptr;
	NewAnimation->AnimationTexture_ = GameEngineTextureManager::GetInst().Find(_TextureName);
	if (nullptr == NewAnimation->AnimationTexture_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 텍스쳐로 애니메이션을 만들려고 했습니다.");
	}

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->Manual = false;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->CurFrame_ = _StartFrame;
	NewAnimation->EndFrame_ = _EndFrame;
	NewAnimation->StartFrame_ = _StartFrame;
	NewAnimation->Renderer_ = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::CreateAnimationFolder(const std::string& _FolderTexName, const std::string& _Name, float _InterTime, bool _Loop)
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

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->Manual = false;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->CurFrame_ = 0;
	NewAnimation->EndFrame_ = FolderTexture->GetTextureCount() - 1;
	NewAnimation->StartFrame_ = 0;
	NewAnimation->Renderer_ = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::CreateAnimationManual(const std::string& _Name, int _StartFrame, int _EndFrame, bool _Manual)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);
	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("이미 존재하는 애니메이션을 또 만들었습니다.");
		return;
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->FolderTextures_ = nullptr;

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = false;
	NewAnimation->Manual = _Manual;
	NewAnimation->InterTime_ = 0.0f;
	NewAnimation->CurTime_ = 0.0f;

	NewAnimation->CurFrame_ = _StartFrame;
	NewAnimation->EndFrame_ = _EndFrame;
	NewAnimation->StartFrame_ = _StartFrame;
	NewAnimation->Renderer_ = this;
	NewAnimation->Renderer_->SetIndex(NewAnimation->CurFrame_);

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::CreateAnimationManualFolder(const std::string& _Name, const std::string& _FolderTexName, bool _Manual)
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

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = false;
	NewAnimation->Manual = false;
	NewAnimation->InterTime_ = 0.0f;
	NewAnimation->CurTime_ = 0.0f;

	NewAnimation->CurFrame_ = 0;
	NewAnimation->EndFrame_ = FolderTexture->GetTextureCount() - 1;
	NewAnimation->StartFrame_ = 0;
	NewAnimation->Renderer_ = this;
	NewAnimation->Renderer_->SetIndex(NewAnimation->CurFrame_);

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
	if (nullptr == CurAnimation_->FolderTextures_)
	{
		ShaderHelper.SettingTexture("Tex", CurAnimation_->AnimationTexture_);
	}
	else
	{
		ShaderHelper.SettingTexture("Tex", CurAnimation_->FolderTextures_->GetTextureIndex(CurAnimation_->CurFrame_));
	}
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

void GameEngineImageRenderer::LoopOff()
{
	// 강제 루프 종료
	CurAnimation_->Loop_ = false;
}

void GameEngineImageRenderer::LoopOn()
{
	// 강제 루프 실행
	CurAnimation_->Loop_ = true;
}

void GameEngineImageRenderer::ManualNextFrame()
{
	// 수동 프레임 진행
	if (CurAnimation_->CurFrame_ == CurAnimation_->EndFrame_)
	{
		// 마지막 애니메이션 실행하였으므로 종료 Callback Function 호출
		if (false == CurAnimation_->IsEnd_)
		{
			CurAnimation_->CallEnd();
		}

		CurAnimation_->IsEnd_ = true;
		CurAnimation_->CurFrame_ = CurAnimation_->EndFrame_;
	}
	else
	{
		++CurAnimation_->CurFrame_;
		CurAnimation_->CallFrame();

		if (nullptr == CurAnimation_->FolderTextures_)
		{
			CurAnimation_->Renderer_->SetIndex(CurAnimation_->CurFrame_);
		}
		else
		{
			CurAnimation_->Renderer_->CutData_ = float4(0, 0, 1, 1);
			CurAnimation_->Renderer_->ShaderHelper.SettingTexture("Tex", CurAnimation_->FolderTextures_->GetTextureIndex(CurAnimation_->CurFrame_));
		}
	}
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
	// 자동 프레임 진행
	if (false == Manual)
	{
		CurTime_ -= _DeltaTime;
		if (StartFrame_ < EndFrame_)
		{
			FrameUpdate();
		}
		else
		{
			ReverseFrameUpdate();
		}

		CallFrame();

		if (nullptr == FolderTextures_)
		{
			Renderer_->ShaderHelper.SettingTexture("Tex", AnimationTexture_);
			Renderer_->CurTexture_ = AnimationTexture_;
			Renderer_->SetIndex(CurFrame_);
		}
		else
		{
			Renderer_->CutData_ = float4(0, 0, 1, 1);
			Renderer_->ShaderHelper.SettingTexture("Tex", FolderTextures_->GetTextureIndex(CurFrame_));
		}
	}
}

void GameEngineImageRenderer::Animation2D::FrameUpdate()
{
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
}

void GameEngineImageRenderer::Animation2D::ReverseFrameUpdate()
{
	if (CurTime_ <= 0.0f)
	{
		--CurFrame_;
		CurTime_ = InterTime_;
		if (true == Loop_ && CurFrame_ < EndFrame_)
		{
			CallEnd();
			CurFrame_ = StartFrame_;
		}
		else if (false == Loop_ && CurFrame_ < EndFrame_)
		{
			if (false == IsEnd_)
			{
				CallEnd();
			}

			IsEnd_ = true;

			CurFrame_ = EndFrame_;
		}
	}
}

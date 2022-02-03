#include "PreCompile.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTextureManager.h"
#include "GameEngineTexture.h"

GameEngineRenderTarget::GameEngineRenderTarget() // default constructer ����Ʈ ������
{

}

GameEngineRenderTarget::~GameEngineRenderTarget() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineRenderTarget::GameEngineRenderTarget(GameEngineRenderTarget&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void GameEngineRenderTarget::Clear()
{
	// Context�� ����� �̿��ؾ��ϹǷ� ������ �ʿ�
	for (size_t i = 0; i < RenderTargetViews_.size(); i++)
	{
		GameEngineDevice::GetContext()->ClearRenderTargetView(RenderTargetViews_[i], ClearColor_[i].Arr1D);
	}
}

void GameEngineRenderTarget::Setting(int _Index)
{
	if (0 >= RenderTargetViews_.size())
	{
		GameEngineDebug::MsgBoxError("Render Target Setting Error Size Zero");
	}

	if (-1 == _Index)
	{
		GameEngineDevice::GetContext()->OMSetRenderTargets(static_cast<UINT>(RenderTargetViews_.size()), &RenderTargetViews_[0], nullptr);
	}
	else
	{
		GameEngineDevice::GetContext()->OMSetRenderTargets(1, &RenderTargetViews_[_Index], nullptr);
	}
}

void GameEngineRenderTarget::Create(const std::string _TextureName, float4 _ClearColor)
{
	GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_TextureName);
	if (nullptr == FindTexture)
	{
		GameEngineDebug::MsgBoxError("FindTexture Is null Create Render Target Error");
	}

	Textures_.push_back(FindTexture);
	RenderTargetViews_.push_back(FindTexture->CreateRenderTargetView());
	ClearColor_.push_back(_ClearColor);
}


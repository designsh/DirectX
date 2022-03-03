#pragma once
#include "GameEngineRenderer.h"

// �з� : Image Renderer
// �뵵 : 
// ���� : 
class GameEngineTexture;
class GameEngineFolderTexture;
class GameEngineImageRenderer : public GameEngineRenderer
{
// ================================== Animation ���� ================================== //
private:
	struct Animation2D
	{
	public:
		GameEngineFolderTexture*											FolderTextures_;	// 
		GameEngineImageRenderer*										Renderer_;			// 
		
		float																						InterTime_;			// ��������ȯ �ð�(����)
		float																						CurTime_;				// ��ŸŸ�� ����(�ʱⰪ : InterTime_)

		bool																						IsEnd_;					// Loop_ = false�϶��� �ִϸ��̼� ������ ����
		bool																						Loop_;					// �ִϸ��̼� �ݺ����� Flag
		int																							CurFrame_;			// �ִϸ��̼��� ���� ������(�ʱⰪ : StartFrame_)
		int																							StartFrame_;		// �ִϸ��̼��� ���� ������
		int																							EndFrame_;			// �ִϸ��̼��� �� ������

		std::map<int, std::vector<std::function<void()>>>	FrameCallBack_;	// ���� �����ӿ� ȣ���ϴ� �Լ�
		std::vector<std::function<void()>>								EndCallBack_;		// �ִϸ��̼� �� �����ӿ� ȣ���ϴ� �Լ�
		std::vector<std::function<void()>>								StartCallBack_;	// �ִϸ��̼� ������ ù�����ӿ� ȣ���ϴ� �Լ�

	public:
		void Reset();
		void CallStart();
		void CallEnd();
		void CallFrame();
		void Update(float _DeltaTime);
	};

private:
	std::map<std::string, Animation2D*>								AllAnimations_;	// �ִϸ��̼� ���� ���
	Animation2D*																		CurAnimation_;	// ���� �ִϸ��̼�
	float4																							CutData_;				// UV(x��ġ��, y��ġ��, uv�ʺ�, uv����)

// ==================================== Image ���� ==================================== //
private:
	GameEngineTexture*															CurTexture_;		// SetImage()ȣ���Ҷ� ����(������)

public:
	GameEngineImageRenderer(); // default constructer ����Ʈ ������
	~GameEngineImageRenderer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineImageRenderer(const GameEngineImageRenderer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineImageRenderer(GameEngineImageRenderer&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;

// ==================================== Image ���� ==================================== //
public:
	void SetImage(const std::string& _ImageName, const float4& _RenderSize = float4::ZERO);

// ================================== Animation ���� ================================== //
protected:
	void Update(float _DeltaTime) override;

public:
	void CreateAnimation(const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop = true);
	void CreateAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop = true);
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);
	void SetIndex(const int _Index);

public:
	void SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack);
};


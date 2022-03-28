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
	struct Animation2D : public GameEngineObjectNameBase
	{
	public:
		GameEngineFolderTexture*										FolderTextures_;		// ���ҽ� �����ε�
		GameEngineTexture*												AnimationTexture_;		// ���ҽ� �ε�
		GameEngineImageRenderer*										Renderer_;				// 

		float															InterTime_;				// ��������ȯ �ð�(����)
		float															CurTime_;				// ��ŸŸ�� ����(�ʱⰪ : InterTime_)

		bool															IsEnd_;					// Loop_ = false�϶��� �ִϸ��̼� ������ ����
		bool															Loop_;					// �ִϸ��̼� �ݺ����� Flag
		bool															Manual;					// �ִϸ��̼� �������� ���������࿩�� Flag
		int																CurFrame_;				// �ִϸ��̼��� ���� ������(�ʱⰪ : StartFrame_)
		int																StartFrame_;			// �ִϸ��̼��� ���� ������
		int																EndFrame_;				// �ִϸ��̼��� �� ������

		std::map<int, std::vector<std::function<void()>>>				FrameCallBack_;			// ���� �����ӿ� ȣ���ϴ� �Լ�
		std::vector<std::function<void()>>								EndCallBack_;			// �ִϸ��̼� �� �����ӿ� ȣ���ϴ� �Լ�
		std::vector<std::function<void()>>								StartCallBack_;			// �ִϸ��̼� ������ ù�����ӿ� ȣ���ϴ� �Լ�

	public:
		void Reset();
		void CallStart();
		void CallEnd();
		void CallFrame();
		void Update(float _DeltaTime);

	public:
		void FrameUpdate();
		void ReverseFrameUpdate();

	public:
		void SetCurrentIndex(int _Index)
		{
			CurFrame_ = _Index;
		}

	public:
		void ChangeAnimationTexture(GameEngineTexture* Texture) 
		{
			AnimationTexture_ = Texture;
		}
	};

private:
	std::map<std::string, Animation2D*>									AllAnimations_;			// �ִϸ��̼� ���� ���
	Animation2D*														CurAnimation_;			// ���� �ִϸ��̼�


// ==================================== Image ���� ==================================== //
private:
	GameEngineTexture* CurTexture_;		// SetImage()ȣ���Ҷ� ����(������)

public:
	GameEngineImageRenderer(); // default constructer ����Ʈ ������
	~GameEngineImageRenderer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	float4																CutData_;				// UV(x��ġ��, y��ġ��, uv�ʺ�, uv����)
	float4																ResultColor_;			// ���� ������

	GameEngineImageRenderer(const GameEngineImageRenderer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineImageRenderer(GameEngineImageRenderer&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	inline GameEngineTexture* GetCurrentTexture()
	{
		return CurTexture_;
	}

	inline std::string GetCurrentAnimationName()
	{
		return CurAnimation_->GetName();
	}

	inline bool IsCurrentAnimationString(const std::string& _Name)
	{
		return CurAnimation_->GetName() == _Name;
	}

	inline bool IsCurrentAnimationPtr(const char* _Name)
	{
		return CurAnimation_->GetName() == _Name;
	}

	inline void SetAlpha(float _Value)
	{
		ResultColor_.a = _Value;
	}

	inline int GetCurAnimationFrame() const
	{
		return CurAnimation_->CurFrame_;
	}

	inline int GetStartAnimationFrame() const
	{
		return CurAnimation_->StartFrame_;
	}

	inline int GetEndAnimationFrame() const
	{
		return CurAnimation_->EndFrame_;
	}

	inline void IsCurrentAnimationIndex(const int _Index)
	{
		CurAnimation_->SetCurrentIndex(_Index);
	}

private:
	void Start() override;

	// ==================================== Image ���� ==================================== //
public:
	void SetImage(const std::string& _ImageName, const float4& _RenderSize = float4::ZERO);

	// ================================== Animation ���� ================================== //
protected:
	void Update(float _DeltaTime) override;
	void ImageRendererStart();

public:
	// �ִϸ��̼� �ؽ��ĸ� ����
	void ChangeAnimationImage(const std::string _Name, const std::string& _TextureName);

public:
	// ������ �ڵ� ����
	void CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop = true);
	void CreateAnimationFolder(const std::string& _FolderTexName, const std::string& _Name, float _InterTime, bool _Loop = true);

	// ������ ��������
	void CreateAnimationManual(const std::string& _Name, int _StartFrame, int _EndFrame, bool _Manual = true);
	void CreateAnimationManualFolder(const std::string& _Name, const std::string& _FolderTexName, bool _Manual = true);

public:
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);
	void SetIndex(const int _Index);

public: // ���� ���� ���� �� ����
	void LoopOff();
	void LoopOn();

public:
	// �ش� �ִϸ��̼��� CreateAnimationManual() or CreateAnimationManualFolder()�� ���Ͽ� ������ �ִϸ��̼� ��� �������� ���������ϱ⶧����
	// �ش� �Լ��� ȣ���Ͽ� ����ڰ� ���ϴ� ������ ������ ������ �Ѵ�.
	void ManualNextFrame();

public:
	void SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack);
};


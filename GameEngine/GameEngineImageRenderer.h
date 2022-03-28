#pragma once
#include "GameEngineRenderer.h"

// 분류 : Image Renderer
// 용도 : 
// 설명 : 
class GameEngineTexture;
class GameEngineFolderTexture;
class GameEngineImageRenderer : public GameEngineRenderer
{
	// ================================== Animation 관련 ================================== //
private:
	struct Animation2D : public GameEngineObjectNameBase
	{
	public:
		GameEngineFolderTexture*										FolderTextures_;		// 리소스 폴더로드
		GameEngineTexture*												AnimationTexture_;		// 리소스 로드
		GameEngineImageRenderer*										Renderer_;				// 

		float															InterTime_;				// 프레임전환 시간(고정)
		float															CurTime_;				// 델타타임 누적(초기값 : InterTime_)

		bool															IsEnd_;					// Loop_ = false일때의 애니메이션 프레임 종료
		bool															Loop_;					// 애니메이션 반복여부 Flag
		bool															Manual;					// 애니메이션 수동으로 프레임진행여부 Flag
		int																CurFrame_;				// 애니메이션의 현재 프레임(초기값 : StartFrame_)
		int																StartFrame_;			// 애니메이션의 시작 프레임
		int																EndFrame_;				// 애니메이션의 끝 프레임

		std::map<int, std::vector<std::function<void()>>>				FrameCallBack_;			// 지정 프레임에 호출하는 함수
		std::vector<std::function<void()>>								EndCallBack_;			// 애니메이션 끝 프레임에 호출하는 함수
		std::vector<std::function<void()>>								StartCallBack_;			// 애니메이션 생성시 첫프레임에 호출하는 함수

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
	std::map<std::string, Animation2D*>									AllAnimations_;			// 애니메이션 관리 목록
	Animation2D*														CurAnimation_;			// 현재 애니메이션


// ==================================== Image 관련 ==================================== //
private:
	GameEngineTexture* CurTexture_;		// SetImage()호출할때 지정(관리용)

public:
	GameEngineImageRenderer(); // default constructer 디폴트 생성자
	~GameEngineImageRenderer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	float4																CutData_;				// UV(x위치값, y위치값, uv너비, uv높이)
	float4																ResultColor_;			// 알파 조절값

	GameEngineImageRenderer(const GameEngineImageRenderer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineImageRenderer(GameEngineImageRenderer&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

	// ==================================== Image 관련 ==================================== //
public:
	void SetImage(const std::string& _ImageName, const float4& _RenderSize = float4::ZERO);

	// ================================== Animation 관련 ================================== //
protected:
	void Update(float _DeltaTime) override;
	void ImageRendererStart();

public:
	// 애니메이션 텍스쳐만 변경
	void ChangeAnimationImage(const std::string _Name, const std::string& _TextureName);

public:
	// 프레임 자동 진행
	void CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop = true);
	void CreateAnimationFolder(const std::string& _FolderTexName, const std::string& _Name, float _InterTime, bool _Loop = true);

	// 프레임 수동진행
	void CreateAnimationManual(const std::string& _Name, int _StartFrame, int _EndFrame, bool _Manual = true);
	void CreateAnimationManualFolder(const std::string& _Name, const std::string& _FolderTexName, bool _Manual = true);

public:
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);
	void SetIndex(const int _Index);

public: // 강제 루프 종료 및 시작
	void LoopOff();
	void LoopOn();

public:
	// 해당 애니메이션이 CreateAnimationManual() or CreateAnimationManualFolder()에 의하여 생성된 애니메이션 경우 프레임을 수동진행하기때문에
	// 해당 함수를 호출하여 사용자가 원하는 시점에 프레임 진행을 한다.
	void ManualNextFrame();

public:
	void SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack);
};


#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 플레이어
// 용도 : 
// 설명 : 직업에 따라 정보가 다름
class BottomStateBar;
class CommonInfomation;
class GameEngineImageRenderer;
class MainPlayer : public GameEngineActor
{
private:	// 플레이어 정보
	CommonInfomation* PlayerInfomation_;

private: // 플레이어 UI
	BottomStateBar* BottomStateBar_;

private: // 플레이어 부위별 애니메이션렌더러
	GameEngineImageRenderer* HD_Renderer_;
	GameEngineImageRenderer* LA_Renderer_;
	GameEngineImageRenderer* LG_Renderer_;
	GameEngineImageRenderer* RA_Renderer_;
	GameEngineImageRenderer* RH_Renderer_;
	GameEngineImageRenderer* S1_Renderer_;
	GameEngineImageRenderer* S2_Renderer_;
	GameEngineImageRenderer* SH_Renderer_;
	GameEngineImageRenderer* TR_Renderer_;

public:
	MainPlayer();
	~MainPlayer();

protected:		// delete constructer
	MainPlayer(const MainPlayer& _other) = delete;
	MainPlayer(MainPlayer&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer& operator=(const MainPlayer& _other) = delete;
	MainPlayer& operator=(const MainPlayer&& _other) = delete;

private:
	void AllAnimationCut();
	void AnimationA1Cut();
	void AnimationA2Cut();
	void AnimationBLCut();
	void AnimationDDCut();
	void AnimationDTCut();
	void AnimationGHCut();
	void AnimationKKCut();
	void AnimationNUCut();
	void AnimationRNCut();
	void AnimationS1Cut();
	void AnimationSCCut();
	void AnimationTNCut();
	void AnimationTWCut();
	void AnimationWLCut();

private:
	void CreateAnimation();
	void CreateA1Animation();
	void CreateA2Animation();
	void CreateBLAnimation();
	void CreateDDAnimation();
	void CreateDTAnimation();
	void CreateGHAnimation();
	void CreateKKAnimation();
	void CreateNUAnimation();
	void CreateRNAnimation();
	void CreateS1Animation();
	void CreateSCAnimation();
	void CreateTNAnimation();
	void CreateTWAnimation();
	void CreateWLAnimation();

private:
	// 상태변경시 애니메이션 변경을 위한 기능으로, 방향과 상태명을 수신받아 변경해야하는 애니메이션으로 변경하는 기능
	void ChangeAnimaton(const std::string& _Name);

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


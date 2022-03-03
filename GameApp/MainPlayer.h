#pragma once
#include <GameEngine/GameEngineActor.h>

// 플레이어는 총 16방향의 애니메이션을 소유한다.
// 그러므로 현재 플레이어의 위치와 마우스커서가 클릭한 위치의
// 각도를 계산하여 플레이어의 포커스방향을 결정한다.
enum class TargetDirect
{
	None = -1,
	DIR_L1,
	DIR_L2,

};

// 분류 : 플레이어
// 용도 : 
// 설명 : 직업에 따라 정보가 다름
class BottomStateBar;
class CommonInfomation;
class GameEngineImageRenderer;
class MainPlayer : public GameEngineActor
{
private:
	TargetDirect PrevDirect_;
	TargetDirect CurDirect_;

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

private: // 텍스쳐 컷팅관련
	void AllAnimationCut();							// 플레이어의 전체 애니메이션에 필요한 모든 텍스쳐 컷팅처리
	void AnimationA1Cut();							// 공격모션1
	void AnimationA2Cut();							// 공격모션2
	void AnimationBLCut();							// 방어모션
	void AnimationDDCut();							// 시체모션
	void AnimationDTCut();							// 사망모션
	void AnimationGHCut();							// 피격모션
	void AnimationKKCut();							// 킥모션
	void AnimationNUCut();							// 필드_대기모션
	void AnimationRNCut();							// 뛰기모션
	void AnimationS1Cut();							// 스킬공격모션
	void AnimationSCCut();							// 스킬캐스팅모션
	void AnimationTNCut();							// 마을_대기모션
	void AnimationTWCut();							// 마을_걷기모션
	void AnimationWLCut();							// 필드_걷기모션

private: // 애니메이션 생성관련
	void SetPlayerCurImage();						// 최초 텍스쳐 지정
	void SetFirstAnimation();							// 최초 애니메이션 지정
	void SetRenderSize();								// 최초 렌더링크기 지정
	void CreateAnimation();							// 플레이어의 전체 애니메이션 모두 생성
	void CreateA1Animation();						// 
	void CreateA2Animation();						// 
	void CreateBLAnimation();						// 
	void CreateDDAnimation();						// 
	void CreateDTAnimation();						// 
	void CreateGHAnimation();					// 
	void CreateKKAnimation();						// 
	void CreateNUAnimation();
	void CreateRNAnimation();
	void CreateS1Animation();
	void CreateSCAnimation();
	void CreateTNAnimation();
	void CreateTWAnimation();
	void CreateWLAnimation();

private:
	// 상태변경시 애니메이션 변경을 위한 기능으로, 방향과 상태명을 수신받아 변경해야하는 애니메이션으로 변경하는 기능
	void ChangeAnimaton(const std::string& _AnimationName, TargetDirect _Direct);

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �÷��̾�
// �뵵 : 
// ���� : ������ ���� ������ �ٸ�
class BottomStateBar;
class CommonInfomation;
class GameEngineImageRenderer;
class MainPlayer : public GameEngineActor
{
private:	// �÷��̾� ����
	CommonInfomation* PlayerInfomation_;

private: // �÷��̾� UI
	BottomStateBar* BottomStateBar_;

private: // �÷��̾� ������ �ִϸ��̼Ƿ�����
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
	// ���º���� �ִϸ��̼� ������ ���� �������, ����� ���¸��� ���Ź޾� �����ؾ��ϴ� �ִϸ��̼����� �����ϴ� ���
	void ChangeAnimaton(const std::string& _Name);

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


#pragma once
#include <GameEngine/GameEngineActor.h>

// �÷��̾�� �� 16������ �ִϸ��̼��� �����Ѵ�.
// �׷��Ƿ� ���� �÷��̾��� ��ġ�� ���콺Ŀ���� Ŭ���� ��ġ��
// ������ ����Ͽ� �÷��̾��� ��Ŀ�������� �����Ѵ�.
enum class TargetDirect
{
	None = -1,
	DIR_L1,
	DIR_L2,

};

// �з� : �÷��̾�
// �뵵 : 
// ���� : ������ ���� ������ �ٸ�
class BottomStateBar;
class CommonInfomation;
class GameEngineImageRenderer;
class MainPlayer : public GameEngineActor
{
private:
	TargetDirect PrevDirect_;
	TargetDirect CurDirect_;

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

private: // �ؽ��� ���ð���
	void AllAnimationCut();							// �÷��̾��� ��ü �ִϸ��̼ǿ� �ʿ��� ��� �ؽ��� ����ó��
	void AnimationA1Cut();							// ���ݸ��1
	void AnimationA2Cut();							// ���ݸ��2
	void AnimationBLCut();							// �����
	void AnimationDDCut();							// ��ü���
	void AnimationDTCut();							// ������
	void AnimationGHCut();							// �ǰݸ��
	void AnimationKKCut();							// ű���
	void AnimationNUCut();							// �ʵ�_�����
	void AnimationRNCut();							// �ٱ���
	void AnimationS1Cut();							// ��ų���ݸ��
	void AnimationSCCut();							// ��ųĳ���ø��
	void AnimationTNCut();							// ����_�����
	void AnimationTWCut();							// ����_�ȱ���
	void AnimationWLCut();							// �ʵ�_�ȱ���

private: // �ִϸ��̼� ��������
	void SetPlayerCurImage();						// ���� �ؽ��� ����
	void SetFirstAnimation();							// ���� �ִϸ��̼� ����
	void SetRenderSize();								// ���� ������ũ�� ����
	void CreateAnimation();							// �÷��̾��� ��ü �ִϸ��̼� ��� ����
	void CreateA1Animation();						// ���ݸ��1
	void CreateA2Animation();						// ���ݸ��2
	void CreateBLAnimation();						// �����
	void CreateDDAnimation();						// ��ü���
	void CreateDTAnimation();						// ������
	void CreateGHAnimation();					// �ǰݸ��
	void CreateKKAnimation();						// ű���
	void CreateNUAnimation();						// �ʵ�_�����
	void CreateRNAnimation();						// �ٱ���
	void CreateS1Animation();						// ��ų���ݸ��
	void CreateSCAnimation();						// ��ųĳ���ø��
	void CreateTNAnimation();						// ����_�����
	void CreateTWAnimation();					// ����_�ȱ���
	void CreateWLAnimation();						// �ʵ�_�ȱ���

private: // ���� or �ִϸ��̼� �������
	void ChangeAnimaton(const std::string& _AnimationName, TargetDirect _Direct); // ���º���� �ִϸ��̼� ������ ���� �������, ����� ���¸��� ���Ź޾� �����ؾ��ϴ� �ִϸ��̼����� �����ϴ� ���
	void ChangeState(const std::string& _StateName);																// ���º���� SetImage()�� ����Ͽ� �ؽ��������� �����ؾ��Ѵ�.

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


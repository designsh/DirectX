#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>

// �з� : ���� �ھ�
// �뵵 : 
// ���� : ���� ������ �ʿ��� �⺻������ �����ϸ�, �ش� Ŭ������ ��ӹ޴� ��ü�� �ݵ�� �ʱ�ȭ/���ҽ��ε�/���ӷ���/���������� �����ϵ��� ����
class GameEngineCore : public GameEngineObjectBase
{
private:
	static GameEngineCore* MainCore_;

private:
	static void WindowCreate();
	static void Loop();
	static void MainLoop();

public:
	template<typename UserGameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		// ������ ����
		WindowCreate();

		UserGameType NewUserGame;

		// ���� �ʱ�ȭ �� ���ҽ� �ε�
		NewUserGame.Initialize();
		NewUserGame.ResourcesLoad();

		// ���ΰ��� �ھ� ����
		MainCore_ = &NewUserGame;

		// Game Loop
		Loop();

		// ���� �޸� �Ҹ�
		NewUserGame.Release();
	}

private:	// member Var

protected:
	GameEngineCore(); // default constructer ����Ʈ ������
	~GameEngineCore(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineCore(const GameEngineCore& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineCore(GameEngineCore&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineCore& operator=(const GameEngineCore& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void EngineDestory();

protected:
	virtual void Initialize() = 0;
	virtual void ResourcesLoad() = 0;
	virtual void GameLoop() = 0;
	virtual void Release() = 0;
};


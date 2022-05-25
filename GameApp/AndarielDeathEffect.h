#pragma once
#include <GameEngine/GameEngineActor.h>

#include "FixedTileMap_Common.h"

enum class CamShakeDir
{
	CS_B,
	CS_LB,
	CS_L,
	CS_LT,
	CS_T,
	CS_RT,
	CS_R,
	CS_RB
};

enum class MoveDeathFireDir
{
	DIR_T,
	DIR_RT,
	DIR_R,
	DIR_RB,
	DIR_B,
	DIR_LB,
	DIR_L,
	DIR_LT
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class AndarielDeathEffect : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* DeathFire_;

private:
	bool CamShakeStart_;
	bool Shake_;
	float ShakeDelayTime_;

private:
	float4 InitCamPos_;

private:
	std::vector<GameEngineImageRenderer*> MoveDeathFireList_;
	MoveDeathFireDir CurMoveDeathFireDir_;
	bool MoveDeathFireSpawn_;
	int MoveDeathFireSpawnCnt_;
	float MoveDeathFireSpawnTime_;

public:
	AndarielDeathEffect();
	~AndarielDeathEffect();

protected:		// delete constructer
	AndarielDeathEffect(const AndarielDeathEffect& _other) = delete;
	AndarielDeathEffect(AndarielDeathEffect&& _other) noexcept = delete;

private:		//delete operator
	AndarielDeathEffect& operator=(const AndarielDeathEffect& _other) = delete;
	AndarielDeathEffect& operator=(const AndarielDeathEffect&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitDeathEffect();
	void TextureCutting();
	void CreateAnimation();

private: // Animation EndFrame Callback Function
	void NormalDeathFire1();
	void NormalDeathFire2();
	void NormalDeathFire3();
	void DirDeathFireFrameCallback();			// �̵��� �ϴ� �Ҳ� �ִϸ��̼��� 10 �����ӿ� ȣ��

private: // Animation Special Frame Callback Function
	void DirDeathFireEndCallback();				// �̵��� �ϴ� �Ҳ� �ִϸ��̼��� ���������ӿ� ȣ��

private:
	void CamShakeEffect();
	void MoveDeathFireSpawn();

public:
	void CreateDeathFire();
};


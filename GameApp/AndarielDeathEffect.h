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

// 분류 : 
// 용도 : 
// 설명 : 
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

private:
	void CamShakeEffect();

public:
	void CreateDeathFire();
};


#pragma once
#include <GameEngine/GameEngineActor.h>

// »ç¸Á ºÒ²É ÀÌÆåÆ® Å¸ÀÔ
enum class DeathFireType
{
	NONE = -1,
	NORMAL,
	TOP,
	RIGHTTOP,
	RIGHT,
	RIGHTBOTTOM,
	BOTTOM,
	LEFTBOTTOM,
	LEFT,
	LEFTTOP,
};

// ºÐ·ù : 
// ¿ëµµ : 
// ¼³¸í : 
class GameEngineImageRenderer;
class AndarielDeathEffect : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* DeathFire_;

private:
	DeathFireType FireType_;
	bool CamShaking_;

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

public:
	inline void CamShakeEffectOn()
	{
		CamShaking_ = true;
	}

	inline void CamShakeEffectOff()
	{
		CamShaking_ = false;
	}

public:

};


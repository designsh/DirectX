#pragma once
#include "GameEngineActor.h"
#include "GameEngineUIRenderer.h"

// 분류 : 
// 용도 : 
// 설명 : 
class MouseActor : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* UIRenderer_;

public:
	MouseActor();
	~MouseActor();

protected:		// delete constructer
	MouseActor(const MouseActor& _other) = delete;
	MouseActor(MouseActor&& _other) noexcept = delete;

private:		//delete operator
	MouseActor& operator=(const MouseActor& _other) = delete;
	MouseActor& operator=(const MouseActor&& _other) = delete;

public:
	GameEngineUIRenderer* GetUIRenderer()
	{
		return UIRenderer_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetCurSor(std::string _Name);
	void SetCurSor(std::string _Name, int _Index);
};


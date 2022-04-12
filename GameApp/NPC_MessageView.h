#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class NPC_MessageView : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* MsgPanel_;

private:
	float TextMoveSpeed_;

private:
	std::string SaveMsgText_;
	int CurTextLineIdx_;
	bool MessageLoadStart_;
	bool MessageLoadEnd_;
	float4 TextMoveEndPos_;

private: // 메세지텍스트 목록
	std::vector<GameEngineUIRenderer*> PrintTextList_;
	
public:
	NPC_MessageView();
	~NPC_MessageView();

protected:		// delete constructer
	NPC_MessageView(const NPC_MessageView& _other) = delete;
	NPC_MessageView(NPC_MessageView&& _other) noexcept = delete;

private:		//delete operator
	NPC_MessageView& operator=(const NPC_MessageView& _other) = delete;
	NPC_MessageView& operator=(const NPC_MessageView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline bool GetMessageLoadEnd()
	{
		return MessageLoadEnd_;
	}

public:
	void CreateNPCMessageTextList(const std::string& _Text);

public:
	void FirstInteractionActive();
};


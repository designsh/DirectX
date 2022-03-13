#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����â
// �뵵 : ���ӳ� �����޼��� ǥ��
// ���� : 
class ErrorMsgPanel;
class ErrorMsgButton;
class ErrorMsgPopup : public GameEngineActor
{
private:	// member Var
	std::string ErrorMsgText_;

private:
	ErrorMsgPanel* ErrorMsgPanel_;
	ErrorMsgButton* ErrorMsgButton_;

public:
	ErrorMsgPopup();
	~ErrorMsgPopup();

protected:		// delete constructer
	ErrorMsgPopup(const ErrorMsgPopup& _other) = delete;
	ErrorMsgPopup(ErrorMsgPopup&& _other) noexcept = delete;

private:		//delete operator
	ErrorMsgPopup& operator=(const ErrorMsgPopup& _other) = delete;
	ErrorMsgPopup& operator=(const ErrorMsgPopup&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void ErrorMsgPopupActive(const std::string& _ErrorMsg);
	void ErrorMsgPopupDeactive();
};


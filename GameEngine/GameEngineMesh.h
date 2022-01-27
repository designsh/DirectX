#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

// 분류 : 
// 용도 : 
// 설명 : 정점버퍼(Vertex Buffer)와 인덱스버퍼(Index Buffer)를 갖고 화면에 렌더링하려는 물체의
//			   골격(부피)등을 제어하는 것을 메쉬(Mesh)라고한다.
//			   해당 클래스는 이 메쉬를 관리하는 클래스이다.
class GameEngineMesh : public GameEngineObjectNameBase
{
private:	// member Var
	GameEngineVertexBuffer* VertexBuffer_;
	GameEngineIndexBuffer* IndexBuffer_;

public:
	GameEngineMesh(); // default constructer 디폴트 생성자
	~GameEngineMesh(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineMesh(const GameEngineMesh& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineMesh(GameEngineMesh&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineMesh& operator=(const GameEngineMesh& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineMesh& operator=(const GameEngineMesh&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};


#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// 상수버퍼 
class ConstanceBuffer
{

};

// 분류 : 셰이더
// 용도 : 
// 설명 : 각 셰이더가 해당 클래스를 상속받으며, 셰이더의 공통정보 및 기능을 관리
//            단, 해당 클래스 자체로 객체화 하면 문제가 발생하므로 순수가상소멸자를 이용하여
//            객체화를 막는다.
class GameEngineShader : public GameEngineObjectNameBase
{
private:
	std::map<std::string, ConstanceBuffer>				ConstanceBuffer_;				// 상수버퍼 관리 목록

protected:
	UINT																				VersionHigh_;						// HLSL Version Hight
	UINT																				VersionLow_;						// HLSL Version Low
	ID3DBlob*																	CodeBlob_;							// 바이트코드(바이너리)버퍼로 셰이더 생성 시 결과값
	std::string																		Version_;								// Ex) vs_VersionHigh_VersionLow_ -> vs_5_0 으로 편집한 버전
	std::string																		EntryPoint_;							// 셰이더 진입함수명
	std::string																		Code_;									// 셰이더 코드

public:
	GameEngineShader(); // default constructer 디폴트 생성자
	virtual ~GameEngineShader() = 0;

protected:		// delete constructer
	GameEngineShader(const GameEngineShader& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineShader(GameEngineShader&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineShader& operator=(const GameEngineShader& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineShader& operator=(const GameEngineShader&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected: // Setting Vertex Shader
	void SetVersion(UINT _VersionHigh, UINT _VersionLow);
	void SetCode(const std::string& _Code);
	void SetEntryPoint(const std::string& _EntryPoint);

protected: // Create HLSL Version String
	// 수신받은 VersionHigh_와 VersionLow_를 이용하여 VertexShader 생성시 전달할 최종적인 Version 문자열을 생성
	void CreateVersion(const std::string& _ShaderType);

public:
	void ResCheck();
};


#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// 분류 : 정점(Vertex) 셰이더 & 입력레이아웃(InputLayout)
// 용도 : 
// 설명 : 코드를 입력하고 그 코드 자체를 GPU에 전달하는 기능을 수행
//            사용자가 입력한 셰이더 코드를 수신받아 ID3DBlob(바이트코드)를 반환하며
//            해당 바이트코드를 사용하여 사용자가 정점을 어떠한 방법으로 위치/크기/회전을 시키는지를
//            GPU가 알수있도록 하며, GPU는 정점을 제어하여 공간변환을 일으킨다.
//            또한 CPU에서 관리중인 데이터의 타입과 포맷, 바이트위치 등을 알려주기위하여 내부적으로
//            InputLayout 생성 및 관리 기능을 포함한다.
class GameEngineVertexShader : public GameEngineObjectNameBase
{
//======================================== Vertex Shader 관련 ========================================//
private:
	ID3D11VertexShader*												VertexShader_;					// VertexShader Pointer
	UINT																				VersionHigh_;						// HLSL Version Hight
	UINT																				VersionLow_;						// HLSL Version Low
	ID3DBlob*																	CodeBlob_;							// 바이트코드(바이너리)버퍼로 셰이더 생성 시 결과값
	std::string																		Version_;								// vs_VersionHigh_VersionLow_ -> vs_5_0 으로 편집한 버전
	std::string																		EntryPoint_;							// 셰이더 진입함수명
	std::string																		Code_;									// 셰이더 코드

//========================================= InputLayout 관련 =========================================//
private:
	ID3D11InputLayout*													LayOut_;								// InputLayout Pointer
	unsigned int																	LayOutOffset_;					// 해당 데이터가 있는 바이트 위치
	std::vector<std::string>												SemanticName_;				// Semantic(의미체계) : 매개 변수의 용도에 대 한 정보를 제공 하는 셰이더 입력 또는 출력에 연결 된 문자열 관리목록
																																			// (Ex POSITION, COLOR, TEXCOORD, ...)
	std::vector<D3D11_INPUT_ELEMENT_DESC>	InputLayoutDesc_;				// HLSL에 정의된 함수(기능)에 전달되는 입력인자(Input Arg)의 속성을 정의하는것들의 관리목록

public:
	GameEngineVertexShader(); // default constructer 디폴트 생성자
	~GameEngineVertexShader(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

//======================================== Vertex Shader 관련 기능함수 ========================================//
private: // Create HLSL Version String
	// 수신받은 VersionHigh_와 VersionLow_를 이용하여 VertexShader 생성시 전달할 최종적인 Version 문자열을 생성(내부함수)
	void CreateVersion();

public: // Create Vertex Shader
	bool Create(const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Setting Vertex Shader
	void SetVersion(UINT _VersionHigh, UINT _VersionLow);
	void SetEntryPoint(const std::string& _EntryPoint);
	void SetCode(const std::string& _Code);

public: // Compile Vertex Shader
	bool Compile();

public: // Vertex Shader Setting
	void Setting();

//========================================= InputLayout 관련 기능함수 =========================================//
private: // InputLayout Check
	void LayOutCheck();

private: // Clear InputLayout
	void LayOutClear();

private: // Add InpuLayout
	void AddInputLayOut(const char* _SemanticName, unsigned int _Index, unsigned int _AlignedByteOffset, DXGI_FORMAT _Format, unsigned int _InputSlot, unsigned int _InstanceDataStepRate, D3D11_INPUT_CLASSIFICATION _inputClass);

private: // Create Layout
	void CreateLayOut();

public: // InputLayout Setting
	void InputLayOutSetting();
};


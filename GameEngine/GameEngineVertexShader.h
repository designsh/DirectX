#pragma once
#include "GameEngineShader.h"
#include "GameEngineDevice.h"

// 분류 : 정점(Vertex) 셰이더 & 입력레이아웃(InputLayout)
// 용도 : 
// 설명 : 코드를 입력하고 그 코드 자체를 GPU에 전달하는 기능을 수행
//            사용자가 입력한 셰이더 코드를 수신받아 ID3DBlob(바이트코드)를 반환하며
//            해당 바이트코드를 사용하여 사용자가 정점을 어떠한 방법으로 위치/크기/회전을 시키는지를
//            GPU가 알수있도록 하며, GPU는 정점을 제어하여 공간변환을 일으킨다.
//            또한 CPU에서 관리중인 데이터의 타입과 포맷, 바이트위치 등을 알려주기위하여 내부적으로
//            InputLayout 생성 및 관리 기능을 포함한다.
class GameEngineVertexShader : public GameEngineShader
{
//======================================== Vertex Shader 관련 ========================================//
private:
	ID3D11VertexShader*												Shader_;								// VertexShader Pointer

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
public: // Create Vertex Shader(D3DCompile() 사용) - 문자열로 수신한 셰이더 코드를 이용하여 셰이더를 생성
	bool Create(const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Compile Vertex Shader(D3DCompile() 사용)
	bool StringCompile();

public:  // Load Vertex Shader(D3DCompileFromFile() 사용) - 파일명을 이용하여 해당 경로의 있는 셰이더 파일을 이용하여 셰이더 생성
	bool Load(const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Compile Vertex Shader(D3DCompileFromFile() 사용) - 경로 필요
	bool FileCompile(const std::string& _Path);

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

//========================================= 상수버퍼 세팅관련 기능함수 =========================================//
public:
	void SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override;

//========================================== 텍스쳐 세팅관련 기능함수 =========================================//
public:
	void SetTexture(const GameEngineTextureSetting* _Setting) override;

//========================================== 샘플러 세팅관련 기능함수 =========================================//
public:
	void SetSampler(const GameEngineSamplerSetting* _Setting) override;

//======================================== 세이더 리소스 리셋관련 기능함수 =======================================//
public:
	void ReSetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override;
	void ReSetTexture(const GameEngineTextureSetting* _Setting) override;
	void ReSetSampler(const GameEngineSamplerSetting* _Setting) override;
};


#include "PreCompile.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader() :
	VersionHigh_(5),
	VersionLow_(0),
	CodeBlob_(nullptr),
	Version_{},
	EntryPoint_{},
	Code_{},
	LayOut_(nullptr),
	LayOutOffset_(0)
{
}

GameEngineVertexShader::~GameEngineVertexShader()
{
	// InputLayout Release
	if (nullptr != LayOut_)
	{
		LayOut_->Release();
		LayOut_ = nullptr;
	}

	// Vertex Shader BinaryCode Buffer Release
	if (nullptr != CodeBlob_)
	{
		CodeBlob_->Release();
		CodeBlob_ = nullptr;
	}
}

//======================================== Vertex Shader 관련 기능함수 ========================================//
void GameEngineVertexShader::CreateVersion()
{
	Version_ = "";
	Version_ += "vs_";
	Version_ += std::to_string(VersionHigh_);
	Version_ += "_";
	Version_ += std::to_string(VersionLow_);
}

bool GameEngineVertexShader::Create(const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	// HLSL Version Setting
	SetVersion(_VersionHigh, _VersionLow);

	// Shader EntryPoint(진입함수명) Setting
	SetEntryPoint(_EntryPoint);

	// Shader Code Setting
	SetCode(_ShaderCode);

	// Create Shader Compile HLSL Version String
	CreateVersion();

	// 생성과 동시에 설정된 정보를 이용하여 컴파일
	return Compile();
}

void GameEngineVertexShader::SetVersion(UINT _VersionHigh, UINT _VersionLow)
{
	VersionHigh_ = _VersionHigh;
	VersionLow_ = _VersionLow;
}

void GameEngineVertexShader::SetEntryPoint(const std::string& _EntryPoint)
{
	EntryPoint_ = _EntryPoint;
}

void GameEngineVertexShader::SetCode(const std::string& _Code)
{
	Code_ = _Code;
}

bool GameEngineVertexShader::Compile()
{
	// 사용자가 원함에 따라 셰이더 코드를 수정하게되었을때 생성이 아닌 컴파일만 진행하기 위한 함수

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR; // CPU에서 GPU로 행렬이 넘어갈때 전치되므로 이를 방지하기 위한 옵션

	ID3DBlob* ResultBlob = nullptr;		// 바이트코드결과값
	ID3DBlob* ErrorBlob = nullptr;		// 컴파일 에러코드

	if (S_OK != D3DCompile(Code_.c_str(), Code_.size(), "", nullptr, nullptr, EntryPoint_.c_str(), Version_.c_str(), 0, 0, &ResultBlob, &ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	// 컴파일 성공시에만 바이트 코드 저장
	CodeBlob_ = ResultBlob;

	return true;
}

//========================================= InputLayout 관련 기능함수 =========================================//
void GameEngineVertexShader::CreateLayOut()
{
	
}

void GameEngineVertexShader::AddInputLayOut(const char* _SemanticName, unsigned int _Index, unsigned int _AlignedByteOffset, DXGI_FORMAT _Format, unsigned int _InputSlot, unsigned int _InstanceDataStepRate, D3D11_INPUT_CLASSIFICATION _inputClass)
{
	// Semantic(의미체계) : 매개 변수의 용도에 대 한 정보를 제공 하는 셰이더 입력 또는 출력에 연결 된 문자열로
	// 셰이더 단계 간에 전달 되는 모든 변수에는 의미 체계가 필요하므로 관리목록으로 관리
	SemanticName_.push_back(_SemanticName);

	// INPUT_ELEMENT으로 INPUTLAYOUT을 셰이더에 전달
	D3D11_INPUT_ELEMENT_DESC LayOutDesc = { 0, };
	LayOutDesc.SemanticName = _SemanticName;									// 의미체계(Ex POSITION, COLOR, TEXCOORD, ...)
	LayOutDesc.SemanticIndex = _Index;														// 같은 의미체계가 존재할때 Index를 부여함(Ex POSITION0 POSITION1, ...)
	LayOutDesc.Format = _Format;																	// 해당 리소스데이터(HLSL코드에 사용하는 Input인자)의 Data Format
	LayOutDesc.InputSlot = _InputSlot;															// 이 성분의 자료가 공급될 정점버퍼의 슬롯(보통 0으로 셋팅)
	LayOutDesc.InstanceDataStepRate = _InstanceDataStepRate;			// 인스턴싱 용도의 속성이며, 인스턴스별 데이터를 사용하여 그릴 인스턴스 수
	LayOutDesc.AlignedByteOffset = LayOutOffset_;									// 해당 데이터가 있는 바이트 위치


}

void GameEngineVertexShader::LayOutClear()
{
	if (nullptr != LayOut_)
	{
		LayOut_->Release();
	}

	LayOut_ = nullptr;
	InputLayoutDesc_.clear();
	SemanticName_.clear();
	LayOutOffset_ = 0;
}

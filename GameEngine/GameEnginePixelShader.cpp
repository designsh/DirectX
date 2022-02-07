#include "PreCompile.h"
#include "GameEnginePixelShader.h"

GameEnginePixelShader::GameEnginePixelShader() :
	Shader_(nullptr)
{
}

GameEnginePixelShader::~GameEnginePixelShader()
{
	// Pixel Shader Release
	if (nullptr != Shader_)
	{
		Shader_->Release();
		Shader_ = nullptr;
	}
}

bool GameEnginePixelShader::Create(const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	// HLSL Version Setting
	SetVersion(_VersionHigh, _VersionLow);

	// Shader EntryPoint(진입함수명) Setting
	SetEntryPoint(_EntryPoint);

	// Shader Code Setting
	SetCode(_ShaderCode);

	// Create Shader Compile HLSL Version String
	CreateVersion("ps");

	// 생성과 동시에 설정된 정보를 이용하여 컴파일
	return Compile();
}

bool GameEnginePixelShader::Compile()
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

	// 컴파일 성공시 해당 Vertex Shader 생성
	if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(CodeBlob_->GetBufferPointer(), CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBox("Create Pixel Shader Error.");
		return false;
	}

	return true;
}

void GameEnginePixelShader::Setting()
{
	GameEngineDevice::GetInst().GetContext()->PSSetShader(Shader_, nullptr, 0);
}


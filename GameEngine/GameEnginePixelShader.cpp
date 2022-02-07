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

	// Shader EntryPoint(�����Լ���) Setting
	SetEntryPoint(_EntryPoint);

	// Shader Code Setting
	SetCode(_ShaderCode);

	// Create Shader Compile HLSL Version String
	CreateVersion("ps");

	// ������ ���ÿ� ������ ������ �̿��Ͽ� ������
	return Compile();
}

bool GameEnginePixelShader::Compile()
{
	// ����ڰ� ���Կ� ���� ���̴� �ڵ带 �����ϰԵǾ����� ������ �ƴ� �����ϸ� �����ϱ� ���� �Լ�

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR; // CPU���� GPU�� ����� �Ѿ�� ��ġ�ǹǷ� �̸� �����ϱ� ���� �ɼ�

	ID3DBlob* ResultBlob = nullptr;		// ����Ʈ�ڵ�����
	ID3DBlob* ErrorBlob = nullptr;		// ������ �����ڵ�

	if (S_OK != D3DCompile(Code_.c_str(), Code_.size(), "", nullptr, nullptr, EntryPoint_.c_str(), Version_.c_str(), 0, 0, &ResultBlob, &ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	// ������ �����ÿ��� ����Ʈ �ڵ� ����
	CodeBlob_ = ResultBlob;

	// ������ ������ �ش� Vertex Shader ����
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


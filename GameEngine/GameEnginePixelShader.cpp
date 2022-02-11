#include "PreCompile.h"
#include "GameEnginePixelShader.h"
#include "GameEngineShaderResHelper.h"

GameEnginePixelShader::GameEnginePixelShader() :
	Shader_(nullptr),
	GameEngineShader(ShaderType::PS)
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
	return StringCompile();
}

bool GameEnginePixelShader::StringCompile()
{
	// ����ڰ� ���Կ� ���� ���̴� �ڵ带 �����ϰԵǾ����� ������ �ƴ� �����ϸ� �����ϱ� ���� �Լ�

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR; // CPU���� GPU�� ����� �Ѿ�� ��ġ�ǹǷ� �̸� �����ϱ� ���� �ɼ�

	ID3DBlob* ResultBlob = nullptr;		// ����Ʈ�ڵ�����
	ID3DBlob* ErrorBlob = nullptr;		// ������ �����ڵ�

	if (S_OK != D3DCompile(Code_.c_str(), Code_.size(), "", nullptr, nullptr, EntryPoint_.c_str(), Version_.c_str(), Flag, 0, &ResultBlob, &ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(GetName() + " String Complie Error.");
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

	ResCheck();			// Create Constant Buffer Infomation

	return true;
}

bool GameEnginePixelShader::Load(const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	// HLSL Version Setting
	SetVersion(_VersionHigh, _VersionLow);

	// Shader EntryPoint(�����Լ���) Setting
	SetEntryPoint(_EntryPoint);

	// Create Shader Compile HLSL Version String
	CreateVersion("ps");

	// ������ ���ÿ� ������ ������ �̿��Ͽ� ������
	return FileCompile(_Path);
}

bool GameEnginePixelShader::FileCompile(const std::string& _Path)
{
	// ���ڿ��� ������ ���̴��ڵ尡 �ƴ� �����̸��� ���̴������� ��θ� �̿��Ͽ� ���̴��� �����ϴ� �Լ�

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR; // CPU���� GPU�� ����� �Ѿ�� ��ġ�ǹǷ� �̸� �����ϱ� ���� �ɼ�

	ID3DBlob* ResultBlob = nullptr;		// ����Ʈ�ڵ�����
	ID3DBlob* ErrorBlob = nullptr;		// ������ �����ڵ�

	// D3DCompileFromFile�� ù��°���ڷ� LPCWSTR Ÿ���� �����Ƿ� ��θ� WideByte ������������ ��ȯ
	std::wstring Path = L"";
	GameEngineString::StringToWString(_Path, Path);

	// D3D_COMPILE_STANDARD_FILE_INCLUDE : �ش� ������ ����(#include)�ϰ��ִ� ������ ��� ã�Ƴ��� ������
	if (S_OK != D3DCompileFromFile(Path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryPoint_.c_str(), Version_.c_str(), Flag, 0, &ResultBlob, &ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(GetName() + " File Complie Error.");
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

	ResCheck();			// Create Constant Buffer Infomation

	return true;
}

void GameEnginePixelShader::Setting()
{
	GameEngineDevice::GetInst().GetContext()->PSSetShader(Shader_, nullptr, 0);
}

void GameEnginePixelShader::SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting)
{
	GameEngineDevice::GetContext()->PSSetConstantBuffers(_Setting->SettingIndex_, 1, &_Setting->Res_->GetBuffer());
}


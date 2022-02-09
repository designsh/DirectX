#include "PreCompile.h"
#include "GameEngineShader.h"

GameEngineShader::GameEngineShader() :
	VersionHigh_(5),
	VersionLow_(0),
	CodeBlob_(nullptr),
	Version_{},
	EntryPoint_{},
	Code_{}
{
}

GameEngineShader::~GameEngineShader()
{
}

void GameEngineShader::SetVersion(UINT _VersionHigh, UINT _VersionLow)
{
	VersionHigh_ = _VersionHigh;
	VersionLow_ = _VersionLow;
}

void GameEngineShader::SetCode(const std::string& _Code)
{
	Code_ = _Code;
}

void GameEngineShader::SetEntryPoint(const std::string& _EntryPoint)
{
	EntryPoint_ = _EntryPoint;
}

void GameEngineShader::CreateVersion(const std::string& _ShaderType)
{
	Version_ = "";
	Version_ += _ShaderType + "_";
	Version_ += std::to_string(VersionHigh_);
	Version_ += "_";
	Version_ += std::to_string(VersionLow_);
}

void GameEngineShader::ResCheck()
{
	// ������ ���̴��� ������ ����Ʈ�ڵ�(CodeBlob_)�� �̿��Ͽ� ������ ���´�.
	if (nullptr == CodeBlob_)
	{
		return;
	}

	ID3D11ShaderReflection* CompilInfo = nullptr;
	if (S_OK != D3DReflect(CodeBlob_->GetBufferPointer(), CodeBlob_->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompilInfo)))
	{
		GameEngineDebug::MsgBoxError("Get Shader Compile Infomation Error.");
		return;
	}

	// D3D11_SHADER_DESC
	// LPCSTR														Name;					// Name of the resource
	// D3D_SHADER_INPUT_TYPE				Type;						// Type of resource (e.g. texture, cbuffer, etc.)
	// UINT															BindPoint;				// Starting bind point
	// UINT															BindCount;			// Number of contiguous bind points (for arrays)
	// UINT															uFlags;					// Input binding flags
	// D3D_RESOURCE_RETURN_TYPE		ReturnType;			// Return type (if texture) 
	// D3D_SRV_DIMENSION							Dimension;			// Dimension (if texture) // 3���� �ؽ�ó
	// UINT															NumSamples;		// Number of samples (0 if not MS texture)
	D3D11_SHADER_DESC Info;
	CompilInfo->GetDesc(&Info);

	// ���̴� �ڵ忡�� ����ϴ� �����Ͱ� � ������ۿ� �����ִ��� ã�Ƴ���,
	// �ش� ��������� ������ ���´�.
	D3D11_SHADER_INPUT_BIND_DESC ResInfo = {};
	for (unsigned int i = 0; i < Info.BoundResources; i++)
	{
		CompilInfo->GetResourceBindingDesc(i, &ResInfo);

		std::string BufferName = ResInfo.Name;								// �ش� ��������� �̸�
		unsigned int BindPoint = ResInfo.BindPoint;						// �ش� ������۰� �Ҵ�� �������� No
		D3D_SHADER_INPUT_TYPE ResType = ResInfo.Type;		// �ش� ������ Ÿ��(Ex. D3D_SIT_CBUFFER(�������), D3D_SIT_TEXTURE(�ؽ���), ...)
		switch (ResType)
		{
			case D3D_SIT_CBUFFER:	// �ش� ���۰� ��������� ���
			{

			}
			break;
		}
	}
}

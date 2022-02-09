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
	// 각각의 셰이더가 생성한 바이트코드(CodeBlob_)를 이용하여 정보를 얻어온다.
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
	// D3D_SRV_DIMENSION							Dimension;			// Dimension (if texture) // 3차원 텍스처
	// UINT															NumSamples;		// Number of samples (0 if not MS texture)
	D3D11_SHADER_DESC Info;
	CompilInfo->GetDesc(&Info);

	// 셰이더 코드에서 사용하는 데이터가 어떤 상수버퍼에 속해있는지 찾아내며,
	// 해당 상수버퍼의 정보를 얻어온다.
	D3D11_SHADER_INPUT_BIND_DESC ResInfo = {};
	for (unsigned int i = 0; i < Info.BoundResources; i++)
	{
		CompilInfo->GetResourceBindingDesc(i, &ResInfo);

		std::string BufferName = ResInfo.Name;								// 해당 상수버퍼의 이름
		unsigned int BindPoint = ResInfo.BindPoint;						// 해당 상수버퍼가 할당된 레지스터 No
		D3D_SHADER_INPUT_TYPE ResType = ResInfo.Type;		// 해당 버퍼의 타입(Ex. D3D_SIT_CBUFFER(상수버퍼), D3D_SIT_TEXTURE(텍스쳐), ...)
		switch (ResType)
		{
			case D3D_SIT_CBUFFER:	// 해당 버퍼가 상수버퍼인 경우
			{

			}
			break;
		}
	}
}

#include "PreCompile.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBufferManager.h"
#include "GameEngineSamplerManager.h"

GameEngineShader::GameEngineShader(ShaderType _Type) :
	VersionHigh_(5),
	VersionLow_(0),
	CodeBlob_(nullptr),
	Version_{},
	EntryPoint_{},
	Code_{},
	Type_(_Type)
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

unsigned int GameEngineShader::GetTypeIndex()
{
	return static_cast<unsigned int>(Type_);
}

std::map<unsigned int, GameEngineConstantBuffer*>& GameEngineShader::GetConstantBuffers()
{
	return ConstanceBuffers_;
}

std::map<unsigned int, GameEngineSampler*>& GameEngineShader::GetSamplers()
{
	return Samplers_;
}

std::map<unsigned int, std::string>& GameEngineShader::GetTextures()
{
	return Textures_;
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
				// 해당 상수버퍼를 얻어온다.
				ID3D11ShaderReflectionConstantBuffer* Buffer = CompilInfo->GetConstantBufferByName(BufferName.c_str());

				// 상수버퍼 내의 데이터 정보를 얻어온다.
				D3D11_SHADER_BUFFER_DESC BufferDesc;
				Buffer->GetDesc(&BufferDesc);

				// 상수버퍼를 생성하며, 이미 생성되어 관리중인 버퍼와 같은 이름이 존재한다면 이미 생성되어있는 상수버퍼를 반환하고, 아니라면 새로 생성한 버퍼를 반환한다.
				GameEngineConstantBuffer* NewBuffer = GameEngineConstantBufferManager::GetInst().CreateAndFind(BufferName, BufferDesc, Buffer);

				// 현재 생성하려는 버퍼와 생성한 버퍼(or 이미 생성되어 동일한 명칭을 같는 버퍼)의 버퍼크기를 비교하여 다르다면 프로그램을 터뜨린다.
				// 동일한 명칭을 가지는 상수버퍼를 이미 GPU에 할당하여 생성했다고 가정했을때 반드시 동일한 명칭을 생성하려고 하면 이미 존재하는 상수버퍼와의
				// 구조가 동일해야한다. 즉, 버퍼의 크기가 동일해야한다.
				if (BufferDesc.Size != NewBuffer->GetBufferSize())
				{
					GameEngineDebug::MsgBoxError("구조가 다른 상수버퍼가 존재합니다.");
					return;
				}

				// 성공적으로 상수버퍼를 생성하였다면 관리목록에 추가
				ConstanceBuffers_.insert(std::make_pair(ResInfo.BindPoint, NewBuffer));

				break;
			}
			case D3D_SIT_SAMPLER:
			{
				D3D11_SAMPLER_DESC Smp_Decs = {};

				memset(&Smp_Decs, 0, sizeof(D3D11_SAMPLER_DESC));

				// D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR or D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT 은 그림자샘플러에 주로 사용
				//Smp_Decs.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;	// 색뭉개기
				//Smp_Decs.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;		// 색도트화

				// 색도트화(기본)
				Smp_Decs.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
				//Smp_Decs.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

				Smp_Decs.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
				Smp_Decs.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
				Smp_Decs.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

				Smp_Decs.MipLODBias = 0.0f;
				Smp_Decs.MaxAnisotropy = 1;
				Smp_Decs.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
				Smp_Decs.MinLOD = -FLT_MAX;
				Smp_Decs.MaxLOD = FLT_MAX;

				GameEngineSampler* NewRes = GameEngineSamplerManager::GetInst().CreateAndFind(BufferName, Smp_Decs);
				Samplers_.insert(std::make_pair(ResInfo.BindPoint, NewRes));
				break;
			}
			case D3D_SIT_TEXTURE:
			{
				Textures_.insert(std::make_pair(ResInfo.BindPoint, BufferName));
				break;
			}
			default:
			{
				GameEngineDebug::MsgBoxError("처리하지 못하는 Buffer Type의 Shader Resource가 발견되었습니다.");
				break;
			}
		}
	}
}

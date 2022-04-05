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
				// �ش� ������۸� ���´�.
				ID3D11ShaderReflectionConstantBuffer* Buffer = CompilInfo->GetConstantBufferByName(BufferName.c_str());

				// ������� ���� ������ ������ ���´�.
				D3D11_SHADER_BUFFER_DESC BufferDesc;
				Buffer->GetDesc(&BufferDesc);

				// ������۸� �����ϸ�, �̹� �����Ǿ� �������� ���ۿ� ���� �̸��� �����Ѵٸ� �̹� �����Ǿ��ִ� ������۸� ��ȯ�ϰ�, �ƴ϶�� ���� ������ ���۸� ��ȯ�Ѵ�.
				GameEngineConstantBuffer* NewBuffer = GameEngineConstantBufferManager::GetInst().CreateAndFind(BufferName, BufferDesc, Buffer);

				// ���� �����Ϸ��� ���ۿ� ������ ����(or �̹� �����Ǿ� ������ ��Ī�� ���� ����)�� ����ũ�⸦ ���Ͽ� �ٸ��ٸ� ���α׷��� �Ͷ߸���.
				// ������ ��Ī�� ������ ������۸� �̹� GPU�� �Ҵ��Ͽ� �����ߴٰ� ���������� �ݵ�� ������ ��Ī�� �����Ϸ��� �ϸ� �̹� �����ϴ� ������ۿ���
				// ������ �����ؾ��Ѵ�. ��, ������ ũ�Ⱑ �����ؾ��Ѵ�.
				if (BufferDesc.Size != NewBuffer->GetBufferSize())
				{
					GameEngineDebug::MsgBoxError("������ �ٸ� ������۰� �����մϴ�.");
					return;
				}

				// ���������� ������۸� �����Ͽ��ٸ� ������Ͽ� �߰�
				ConstanceBuffers_.insert(std::make_pair(ResInfo.BindPoint, NewBuffer));

				break;
			}
			case D3D_SIT_SAMPLER:
			{
				D3D11_SAMPLER_DESC Smp_Decs = {};

				memset(&Smp_Decs, 0, sizeof(D3D11_SAMPLER_DESC));

				// D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR or D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT �� �׸��ڻ��÷��� �ַ� ���
				//Smp_Decs.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;	// ��������
				//Smp_Decs.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;		// ����Ʈȭ

				// ����Ʈȭ(�⺻)
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
				GameEngineDebug::MsgBoxError("ó������ ���ϴ� Buffer Type�� Shader Resource�� �߰ߵǾ����ϴ�.");
				break;
			}
		}
	}
}

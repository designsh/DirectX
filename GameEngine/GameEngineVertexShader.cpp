#include "PreCompile.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader() :
	Shader_(nullptr),
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

	// Vertex Shader Release
	if (nullptr != Shader_)
	{
		Shader_->Release();
		Shader_ = nullptr;
	}

	// Vertex Shader BinaryCode Buffer Release
	if (nullptr != CodeBlob_)
	{
		CodeBlob_->Release();
		CodeBlob_ = nullptr;
	}
}

//======================================== Vertex Shader ���� ����Լ� ========================================//
bool GameEngineVertexShader::Create(const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	// HLSL Version Setting
	SetVersion(_VersionHigh, _VersionLow);

	// Shader EntryPoint(�����Լ���) Setting
	SetEntryPoint(_EntryPoint);

	// Shader Code Setting
	SetCode(_ShaderCode);

	// Create Shader Compile HLSL Version String
	CreateVersion("vs");

	// ������ ���ÿ� ������ ������ �̿��Ͽ� ������
	return Compile();
}

bool GameEngineVertexShader::Compile()
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
	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(CodeBlob_->GetBufferPointer(), CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBox("Create Vertex Shader Error.");
		return false;
	}

	LayOutCheck();

	return true;
}

void GameEngineVertexShader::Setting()
{
	GameEngineDevice::GetInst().GetContext()->VSSetShader(Shader_, nullptr, 0);
}

//========================================= InputLayout ���� ����Լ� =========================================//
void GameEngineVertexShader::LayOutCheck()
{
	// ���� ���̾ƿ� ������ Ŭ����
	LayOutClear();

	// InputLayout�� �ݵ�� VertexShader�� �����Ǿ� GPU���� �ش� ������������
	// �˷��ٶ� ����ϹǷ� BiteCodeBuffer�� �����ؾ� ���������ϴ�.
	if (nullptr == CodeBlob_)
	{
		return;
	}

	// ID3D11ShaderReflection : �����(������)�� ���̴����� ����� ����, �Լ�, ����, ������۵���
	//                                                   ������ �˰��ִ� ����ü
	ID3D11ShaderReflection* CompilInfo = nullptr;
	if (S_OK != D3DReflect(CodeBlob_->GetBufferPointer(), CodeBlob_->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompilInfo)))
	{
		GameEngineDebug::MsgBoxError("���̴� ������ ������ ������ ���߽��ϴ�.");
		return;
	}

	// ���̴� ������ ������ ���Դٸ� CompilInfo�� �̿��Ͽ� ���̴� ������ ��� �����´�.
	D3D11_SHADER_DESC Info = { 0, };
	CompilInfo->GetDesc(&Info);

	// Semantic Name�� üũ�Ͽ� Semantic Index�� ������������ �����ϸ�,
	// ����ڿ� ���� �߸��� �ε����� ����Ͽ� ���ڸ� �Ѱ��־��ٸ� �ش� ���α׷��� �Ͷ߸���.
	std::string Name = "";
	int PrevIndex = 0;
	unsigned int ParameterSize = 0;

	// Info.InputParameters : ���̴��ڵ忡�� �Լ��� ���� Parameter���� ��ŭ �ݺ�����
	for (unsigned int i = 0; i < Info.InputParameters; i++)
	{
		// D3D11_SIGNATURE_PARAMETER_DESC : ���̴��ڵ忡�� �Լ� ����(Input Parameter)�� �������� ���´�.
		//                                                                                 SemanticName, SemanticIndex ���
		D3D11_SIGNATURE_PARAMETER_DESC Input = { 0, };
		CompilInfo->GetInputParameterDesc(i, &Input);

		// D3D11_SIGNATURE_PARAMETER_DESC���� ���ڿ� ���� ����Ʈ ������ ���� ������ 
		// Input.Mask ������ �̿��Ͽ� ������ ����Ʈũ�⸦ ���´�.
		DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;

		// D3D_REGISTER_COMPONENT_TYPE : Input Parameter�� Ÿ��(�Ǽ�,����), ��ȣ(��ȣ���ִ�, ��ȣ������)�� ���´�.
		// DXGI_FORMAT::DXGI_FORMAT_UNKNOWN : �˼�����
		// DXGI_FORMAT::DXGI_FORMAT_R32 : 4����Ʈ 1
		// DXGI_FORMAT::DXGI_FORMAT_R32G32 : 4����Ʈ 2
		// DXGI_FORMAT::DXGI_FORMAT_R32G32B32 : 4����Ʈ 3
		// DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32 : 4����Ʈ 4
		D3D_REGISTER_COMPONENT_TYPE Reg = Input.ComponentType;

		// Input.Mask : D3D_REGISTER_COMPONENT_TYPE���� �˾Ƴ� Ÿ���� �����Ʈ ���� �˾Ƴ��� ���� ���
		// GPU�� �����Ͱ����� �⺻������ 4����Ʈ�� �������� �Ѵ�.
		//							float4 : 1111 = 15
		//							float3 : 0111 =   7
		//                         float2 : 0011 =   3
		//							float   : 0001 =   1
		switch (Input.Mask)
		{
			case 1: // 4����Ʈ 1��
			{
				ParameterSize = 4;
				switch (Reg)
				{
					case D3D_REGISTER_COMPONENT_UNKNOWN:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
						break;
					}
					case D3D_REGISTER_COMPONENT_UINT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
						break;
					}
					case D3D_REGISTER_COMPONENT_SINT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
						break;
					}
					case D3D_REGISTER_COMPONENT_FLOAT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
						break;
					}
				}
				break;
			}
			case 3: // 4����Ʈ 2��
			{
				ParameterSize = 8;
				switch (Reg)
				{
					case D3D_REGISTER_COMPONENT_UNKNOWN:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
						break;
					}
					case D3D_REGISTER_COMPONENT_UINT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_UINT;
						break;
					}
					case D3D_REGISTER_COMPONENT_SINT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
						break;
					}
					case D3D_REGISTER_COMPONENT_FLOAT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
						break;
					}
				}
				break;
			}
			case 7: // 4����Ʈ 3��
			{
				ParameterSize = 12;
				switch (Reg)
				{
					case D3D_REGISTER_COMPONENT_UNKNOWN:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
						break;
					}
					case D3D_REGISTER_COMPONENT_UINT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_UINT;
						break;
					}
					case D3D_REGISTER_COMPONENT_SINT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
						break;
					}
					case D3D_REGISTER_COMPONENT_FLOAT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
						break;
					}
				}
				break;
			}
			case 15: // 4����Ʈ 4��
			{
				ParameterSize = 16;
				switch (Reg)
				{
					case D3D_REGISTER_COMPONENT_UNKNOWN:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
						break;
					}
					case D3D_REGISTER_COMPONENT_UINT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT;
						break;
					}
					case D3D_REGISTER_COMPONENT_SINT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
						break;
					}
					case D3D_REGISTER_COMPONENT_FLOAT32:
					{
						Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
						break;
					}
				}
				break;
			}
		}

		// ���� ���̴� �Է����� ������ ������ ������ '�˼�����'�̸� ����
		if (DXGI_FORMAT::DXGI_FORMAT_UNKNOWN == Format)
		{
			GameEngineDebug::MsgBox("���̴� ��ǲ �Ķ���� Ÿ���� ���������� �ʽ��ϴ�.");
			return;
		}

		// SemanticIndex�� ����ڿ����� �����ϱ� ���� ����
		std::string NextName = Input.SemanticName;

		// ���� ����
		if (Name == "")
		{
			Name = NextName;
			++PrevIndex;
		}
		else // ������ �ø�ƽ �̸��� �����ϸ� Index�� üũ(������������ üũ)
		{
			if (Name == NextName)
			{
				if (PrevIndex != Input.SemanticIndex)
				{
					GameEngineDebug::MsgBoxError("SemanticIndex ������ ���������� �ƴմϴ�.");
					return;
				}

				++PrevIndex;
			}
			else
			{
				Name = NextName;
				PrevIndex = 0;
			}
		}

		AddInputLayOut(Input.SemanticName, Input.SemanticIndex, ParameterSize, Format, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	}

	// Create InputLayout
	CreateLayOut();
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

void GameEngineVertexShader::AddInputLayOut(const char* _SemanticName, unsigned int _Index, unsigned int _AlignedByteOffset, DXGI_FORMAT _Format, unsigned int _InputSlot, unsigned int _InstanceDataStepRate, D3D11_INPUT_CLASSIFICATION _inputClass)
{
	// Semantic(�ǹ�ü��) : �Ű� ������ �뵵�� �� �� ������ ���� �ϴ� ���̴� �Է� �Ǵ� ��¿� ���� �� ���ڿ���
	// ���̴� �ܰ� ���� ���� �Ǵ� ��� �������� �ǹ� ü�谡 �ʿ��ϹǷ� ����������� ����
	SemanticName_.push_back(_SemanticName);

	// INPUT_ELEMENT���� INPUTLAYOUT�� ���̴��� ����
	D3D11_INPUT_ELEMENT_DESC LayOutDesc = { 0, };
	LayOutDesc.SemanticName = _SemanticName;									// �ǹ�ü��(Ex POSITION, COLOR, TEXCOORD, ...)
	LayOutDesc.SemanticIndex = _Index;														// ���� �ǹ�ü�谡 �����Ҷ� Index�� �ο���(Ex POSITION0 POSITION1, ...)
	LayOutDesc.Format = _Format;																	// �ش� ���ҽ�������(HLSL�ڵ忡 ����ϴ� Input����)�� Data Format
	LayOutDesc.InputSlot = _InputSlot;															// �� ������ �ڷᰡ ���޵� ���������� ����(���� 0���� ����)
	LayOutDesc.InstanceDataStepRate = _InstanceDataStepRate;			// �ν��Ͻ� �뵵�� �Ӽ��̸�, �ν��Ͻ��� �����͸� ����Ͽ� �׸� �ν��Ͻ� ��
	LayOutDesc.AlignedByteOffset = LayOutOffset_;									// �ش� �����Ͱ� �ִ� ����Ʈ ��ġ(������ġ)
	LayOutOffset_ += _AlignedByteOffset;													// �ش� VertexShader�� �Է·��̾ƿ�(InputLayout)�� �Է�����(Input Parameter)�� �������ΰ��
																																// �ش� �Լ��� �Է����ڼ���ŭ ȣ��Ǹ� ������ ������ġ�� �޶����Ƿ� _AlignedByteOffset�� ���Ͽ� 
																																// ����Ʈ �ڵ忡���� �������ڿ����� ������ġ�� �����Ѵ�.

	// Add InputLayOut
	InputLayoutDesc_.push_back(LayOutDesc);
}

void GameEngineVertexShader::CreateLayOut()
{
	if (S_OK != GameEngineDevice::GetInst().GetDevice()->CreateInputLayout(&InputLayoutDesc_[0], static_cast<unsigned int>(InputLayoutDesc_.size()), CodeBlob_->GetBufferPointer(), CodeBlob_->GetBufferSize(), &LayOut_))
	{
		GameEngineDebug::MsgBoxError("Create InputLayout Error.");
		return;
	}
}

void GameEngineVertexShader::InputLayOutSetting()
{
	if (nullptr == LayOut_)
	{
		GameEngineDebug::MsgBoxError("VertexShader Input Parameter�� �������� �ʽ��ϴ�.");
	}

	GameEngineDevice::GetInst().GetContext()->IASetInputLayout(LayOut_);
}

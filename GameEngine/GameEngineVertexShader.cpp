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

//======================================== Vertex Shader 관련 기능함수 ========================================//
bool GameEngineVertexShader::Create(const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	// HLSL Version Setting
	SetVersion(_VersionHigh, _VersionLow);

	// Shader EntryPoint(진입함수명) Setting
	SetEntryPoint(_EntryPoint);

	// Shader Code Setting
	SetCode(_ShaderCode);

	// Create Shader Compile HLSL Version String
	CreateVersion("vs");

	// 생성과 동시에 설정된 정보를 이용하여 컴파일
	return Compile();
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

	// 컴파일 성공시 해당 Vertex Shader 생성
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

//========================================= InputLayout 관련 기능함수 =========================================//
void GameEngineVertexShader::LayOutCheck()
{
	// 기존 레이아웃 정보를 클리어
	LayOutClear();

	// InputLayout은 반드시 VertexShader가 생성되어 GPU에게 해당 정점정보들을
	// 알려줄때 사용하므로 BiteCodeBuffer가 존재해야 생성가능하다.
	if (nullptr == CodeBlob_)
	{
		return;
	}

	// ID3D11ShaderReflection : 사용자(개발자)가 셰이더에서 사용한 변수, 함수, 인자, 상수버퍼등의
	//                                                   정보를 알고있는 구조체
	ID3D11ShaderReflection* CompilInfo = nullptr;
	if (S_OK != D3DReflect(CodeBlob_->GetBufferPointer(), CodeBlob_->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompilInfo)))
	{
		GameEngineDebug::MsgBoxError("셰이더 컴파일 정보를 얻어오지 못했습니다.");
		return;
	}

	// 셰이더 컴파일 정보를 얻어왔다면 CompilInfo를 이용하여 셰이더 정보를 모두 가져온다.
	D3D11_SHADER_DESC Info = { 0, };
	CompilInfo->GetDesc(&Info);

	// Semantic Name을 체크하여 Semantic Index를 오름차순으로 설정하며,
	// 사용자에 의해 잘못된 인덱스를 사용하여 인자를 넘겨주었다면 해당 프로그램을 터뜨린다.
	std::string Name = "";
	int PrevIndex = 0;
	unsigned int ParameterSize = 0;

	// Info.InputParameters : 셰이더코드에서 함수의 인자 Parameter개수 만큼 반복수행
	for (unsigned int i = 0; i < Info.InputParameters; i++)
	{
		// D3D11_SIGNATURE_PARAMETER_DESC : 셰이더코드에서 함수 인자(Input Parameter)의 상세정보를 얻어온다.
		//                                                                                 SemanticName, SemanticIndex 등등
		D3D11_SIGNATURE_PARAMETER_DESC Input = { 0, };
		CompilInfo->GetInputParameterDesc(i, &Input);

		// D3D11_SIGNATURE_PARAMETER_DESC내에 인자에 대한 바이트 정보가 없기 때문에 
		// Input.Mask 정보를 이용하여 인자의 바이트크기를 얻어온다.
		DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;

		// D3D_REGISTER_COMPONENT_TYPE : Input Parameter의 타입(실수,정수), 부호(부호가있는, 부호가없는)를 얻어온다.
		// DXGI_FORMAT::DXGI_FORMAT_UNKNOWN : 알수없음
		// DXGI_FORMAT::DXGI_FORMAT_R32 : 4바이트 1
		// DXGI_FORMAT::DXGI_FORMAT_R32G32 : 4바이트 2
		// DXGI_FORMAT::DXGI_FORMAT_R32G32B32 : 4바이트 3
		// DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32 : 4바이트 4
		D3D_REGISTER_COMPONENT_TYPE Reg = Input.ComponentType;

		// Input.Mask : D3D_REGISTER_COMPONENT_TYPE에서 알아낸 타입이 몇바이트 인지 알아내기 위해 사용
		// GPU는 데이터관리를 기본적으로 4바이트를 기준으로 한다.
		//							float4 : 1111 = 15
		//							float3 : 0111 =   7
		//                         float2 : 0011 =   3
		//							float   : 0001 =   1
		switch (Input.Mask)
		{
			case 1: // 4바이트 1개
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
			case 3: // 4바이트 2개
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
			case 7: // 4바이트 3개
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
			case 15: // 4바이트 4개
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

		// 만약 셰이더 입력인자 정보의 데이터 포맷이 '알수없음'이면 에러
		if (DXGI_FORMAT::DXGI_FORMAT_UNKNOWN == Format)
		{
			GameEngineDebug::MsgBox("쉐이더 인풋 파라미터 타입이 정상적이지 않습니다.");
			return;
		}

		// SemanticIndex의 사용자오류를 제거하기 위한 조건
		std::string NextName = Input.SemanticName;

		// 최초 생성
		if (Name == "")
		{
			Name = NextName;
			++PrevIndex;
		}
		else // 동일한 시멘틱 이름이 존재하면 Index를 체크(오름차순인지 체크)
		{
			if (Name == NextName)
			{
				if (PrevIndex != Input.SemanticIndex)
				{
					GameEngineDebug::MsgBoxError("SemanticIndex 순서가 오름차순이 아닙니다.");
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
	LayOutDesc.AlignedByteOffset = LayOutOffset_;									// 해당 데이터가 있는 바이트 위치(시작위치)
	LayOutOffset_ += _AlignedByteOffset;													// 해당 VertexShader의 입력레이아웃(InputLayout)의 입력인자(Input Parameter)가 여러개인경우
																																// 해당 함수가 입력인자수만큼 호출되며 각각의 시작위치가 달라지므로 _AlignedByteOffset를 더하여 
																																// 바이트 코드에서의 다음인자에대한 시작위치를 저장한다.

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
		GameEngineDebug::MsgBoxError("VertexShader Input Parameter가 존재하지 않습니다.");
	}

	GameEngineDevice::GetInst().GetContext()->IASetInputLayout(LayOut_);
}

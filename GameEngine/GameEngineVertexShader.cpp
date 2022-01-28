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

//======================================== Vertex Shader ���� ����Լ� ========================================//
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

	// Shader EntryPoint(�����Լ���) Setting
	SetEntryPoint(_EntryPoint);

	// Shader Code Setting
	SetCode(_ShaderCode);

	// Create Shader Compile HLSL Version String
	CreateVersion();

	// ������ ���ÿ� ������ ������ �̿��Ͽ� ������
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

	return true;
}

//========================================= InputLayout ���� ����Լ� =========================================//
void GameEngineVertexShader::CreateLayOut()
{
	
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
	LayOutDesc.AlignedByteOffset = LayOutOffset_;									// �ش� �����Ͱ� �ִ� ����Ʈ ��ġ


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

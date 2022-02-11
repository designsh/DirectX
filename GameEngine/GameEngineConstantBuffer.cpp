#include "PreCompile.h"
#include "GameEngineConstantBuffer.h"

GameEngineConstantBuffer::GameEngineConstantBuffer() :
	Buffer_(nullptr),
	BufferData_{},
	ResData_{},
	BufferDesc_{}
{
}

GameEngineConstantBuffer::~GameEngineConstantBuffer()
{
	// Constant Buffer Release
	if (nullptr != Buffer_)
	{
		Buffer_->Release();
		Buffer_ = nullptr;
	}
}

void GameEngineConstantBuffer::Create(const D3D11_SHADER_BUFFER_DESC& _BufferDesc, ID3D11ShaderReflectionConstantBuffer* _VarInfo)
{
	BufferDesc_ = _BufferDesc;

	BufferData_.ByteWidth = BufferDesc_.Size;
	BufferData_.CPUAccessFlags = 0;

	// ���� �� �����Ͱ� ���ŵǾ���ϹǷ� D3D11_USAGE_DYNAMIC �뵵�� ����
	BufferData_.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	if (BufferData_.Usage == D3D11_USAGE::D3D11_USAGE_DYNAMIC)
	{
		BufferData_.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	}

	BufferData_.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferData_.StructureByteStride = 0;
	BufferData_.MiscFlags = 0;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferData_, nullptr, &Buffer_))
	{
		GameEngineDebug::MsgBoxError("������� ������ ������ �ֽ��ϴ�." + GetName());
		return;
	}

	// ���̴� ��������� ���ǿ��� �������� ������ �о�´�.
	for (unsigned int i = 0; i < BufferDesc_.Variables; i++)
	{
		ID3D11ShaderReflectionVariable* Var = _VarInfo->GetVariableByIndex(i);

		D3D11_SHADER_VARIABLE_DESC VarDesc;
		Var->GetDesc(&VarDesc);
		VarInfos_.push_back(VarDesc);
	}
}

void GameEngineConstantBuffer::ChangeData(void* _Data, size_t _Size)
{
	// ����ó�� : ���� ������ۿ� �����Ϸ��� �����͵��(�������)�� ũ�Ⱑ �ٸ���
	// ������ �ٸ��ٰ� �Ǵ��Ͽ� ���α׷��� �Ͷ߸���.
	if (BufferData_.ByteWidth != _Size)
	{
		GameEngineDebug::MsgBoxError("������� ������ ũ�Ⱑ �ٸ��ϴ�.");
	}

	memset(&ResData_, 0, sizeof(ResData_));

	// ������ۿ� ���Ե� �����Ϳ� ���� �����͸� �������� �ش� ������ۿ� ���� GPU �׼����� �ź��մϴ�.'
	// ���� : ������ ���� �� GPU�� �ش� ������ۿ� �����ϴ°��� �����ϱ� ���Ͽ� ����ϸ�, ������ ���� ��
	//            GPU�� �������� �ߴ��Ѵ�.(CPU->GPU ������ ���� ����)
	GameEngineDevice::GetContext()->Map(Buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &ResData_);
	
	// GPU�� �������� �����ϰ� CPU�� �ش� ������ۿ� �����Ͽ� �����Ϸ��� �����͸� ����(CPU->GPU ������ ������)
	memcpy_s(ResData_.pData, BufferData_.ByteWidth, _Data, BufferData_.ByteWidth);

	// CPU�� ������۸� GPU�� ������ۿ� ��� �����Ͽ����Ƿ� �ش� ���ۿ� ���� GPU �׼��� ������ ��ȯ
	// ��� �����Ϳ� ���� ������ �Ϸ� �Ǿ����Ƿ� GPU�� �ٽ� �������� �� �ְ� �ȴ�.
	GameEngineDevice::GetContext()->Unmap(Buffer_, 0);
}

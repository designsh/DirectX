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

	// 가동 중 데이터가 갱신되어야하므로 D3D11_USAGE_DYNAMIC 용도로 설정
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
		GameEngineDebug::MsgBoxError("상수버퍼 생성에 오류가 있습니다." + GetName());
		return;
	}

	// 셰이더 상수버퍼의 정의에서 데이터의 정보를 읽어온다.
	for (unsigned int i = 0; i < BufferDesc_.Variables; i++)
	{
		ID3D11ShaderReflectionVariable* Var = _VarInfo->GetVariableByIndex(i);

		D3D11_SHADER_VARIABLE_DESC VarDesc;
		Var->GetDesc(&VarDesc);
		VarInfos_.push_back(VarDesc);
	}
}

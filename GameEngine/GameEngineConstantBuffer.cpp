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

void GameEngineConstantBuffer::ChangeData(void* _Data, size_t _Size)
{
	// 예외처리 : 현재 상수버퍼와 세팅하려는 데이터덩어리(상수버퍼)의 크기가 다르면
	// 구조가 다르다고 판단하여 프로그램을 터뜨린다.
	if (BufferData_.ByteWidth != _Size)
	{
		GameEngineDebug::MsgBoxError("상수버퍼 세팅의 크기가 다릅니다.");
	}

	memset(&ResData_, 0, sizeof(ResData_));

	// 상수버퍼에 포함된 데이터에 대한 포인터를 가져오고 해당 상수버퍼에 대한 GPU 액세스를 거부합니다.'
	// 이유 : 데이터 갱신 중 GPU가 해당 상수버퍼에 접근하는것을 제한하기 위하여 사용하며, 데이터 갱신 중
	//            GPU는 렌더링을 중단한다.(CPU->GPU 데이터 전송 시작)
	GameEngineDevice::GetContext()->Map(Buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &ResData_);
	
	// GPU가 렌더링을 중지하고 CPU가 해당 상수버퍼에 접근하여 갱신하려는 데이터를 복제(CPU->GPU 데이터 전송중)
	memcpy_s(ResData_.pData, BufferData_.ByteWidth, _Data, BufferData_.ByteWidth);

	// CPU의 상수버퍼를 GPU의 상수버퍼에 모두 전송하였으므로 해당 버퍼에 대한 GPU 액세스 권한을 반환
	// 모든 데이터에 대한 갱신이 완료 되었으므로 GPU는 다시 렌더링할 수 있게 된다.
	GameEngineDevice::GetContext()->Unmap(Buffer_, 0);
}

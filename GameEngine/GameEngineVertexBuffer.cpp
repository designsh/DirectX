#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBuffer::GameEngineVertexBuffer() : 
	Buffer_(nullptr), 
	Size_(0), 
	Count_(0),
	Offset_(0), 
	BufferData_(), 
	ResData_()
{
	memset(&BufferData_, 0, sizeof(BufferData_));
	memset(&ResData_, 0, sizeof(ResData_));
}

GameEngineVertexBuffer::~GameEngineVertexBuffer() // default destructer 디폴트 소멸자
{
	if (nullptr != Buffer_)
	{
		Buffer_->Release();
		Buffer_ = nullptr;
	}
}

void GameEngineVertexBuffer::Create(const void* _Data, size_t _Size, size_t _Count, D3D11_USAGE _Usage)
{
	// MemberValue Save
	Size_ = static_cast<UINT>(_Size);
	Count_ = static_cast<UINT>(_Count);

	// 그래픽카드는 그냥 N바이트 자기 메모리에 할당하려고 하기때문에 버퍼에 대한 정보를 전달해야한다.
	ResData_.pSysMem = _Data;

	BufferData_.ByteWidth = static_cast<UINT>(_Size) * static_cast<UINT>(_Count);
	BufferData_.Usage = _Usage;

	BufferData_.CPUAccessFlags = 0;
	if (BufferData_.Usage == D3D11_USAGE::D3D11_USAGE_DYNAMIC)
	{
		BufferData_.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	}

	BufferData_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferData_.StructureByteStride = 0;
	BufferData_.MiscFlags = 0;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferData_, &ResData_, &Buffer_))
	{
		GameEngineDebug::MsgBoxError("버텍스 버퍼 생성 에러");
		return;
	}
}

void GameEngineVertexBuffer::Setting()
{
	GameEngineDevice::GetContext()->IASetVertexBuffers(0, 1, &Buffer_, &Size_, &Offset_);
}

#include "PreCompile.h"
#include "GameEngineDirectXDevice.h"

// �������� �̱���
GameEngineDirectXDevice* GameEngineDirectXDevice::Inst = new GameEngineDirectXDevice();

GameEngineDirectXDevice::GameEngineDirectXDevice() :
	Device_(nullptr),
	Context_(nullptr)
{
}

GameEngineDirectXDevice::~GameEngineDirectXDevice()
{
}



#include "PreCompile.h"
#include "GameEngineDirectXDevice.h"

// Æ÷ÀÎÅÍÇü ½Ì±ÛÅæ
GameEngineDirectXDevice* GameEngineDirectXDevice::Inst = new GameEngineDirectXDevice();

GameEngineDirectXDevice::GameEngineDirectXDevice() :
	Device_(nullptr),
	Context_(nullptr)
{
}

GameEngineDirectXDevice::~GameEngineDirectXDevice()
{
}



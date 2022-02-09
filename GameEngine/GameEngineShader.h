#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// ������� 
class ConstanceBuffer
{

};

// �з� : ���̴�
// �뵵 : 
// ���� : �� ���̴��� �ش� Ŭ������ ��ӹ�����, ���̴��� �������� �� ����� ����
//            ��, �ش� Ŭ���� ��ü�� ��üȭ �ϸ� ������ �߻��ϹǷ� ��������Ҹ��ڸ� �̿��Ͽ�
//            ��üȭ�� ���´�.
class GameEngineShader : public GameEngineObjectNameBase
{
private:
	std::map<std::string, ConstanceBuffer>				ConstanceBuffer_;				// ������� ���� ���

protected:
	UINT																				VersionHigh_;						// HLSL Version Hight
	UINT																				VersionLow_;						// HLSL Version Low
	ID3DBlob*																	CodeBlob_;							// ����Ʈ�ڵ�(���̳ʸ�)���۷� ���̴� ���� �� �����
	std::string																		Version_;								// Ex) vs_VersionHigh_VersionLow_ -> vs_5_0 ���� ������ ����
	std::string																		EntryPoint_;							// ���̴� �����Լ���
	std::string																		Code_;									// ���̴� �ڵ�

public:
	GameEngineShader(); // default constructer ����Ʈ ������
	virtual ~GameEngineShader() = 0;

protected:		// delete constructer
	GameEngineShader(const GameEngineShader& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineShader(GameEngineShader&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineShader& operator=(const GameEngineShader& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineShader& operator=(const GameEngineShader&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected: // Setting Vertex Shader
	void SetVersion(UINT _VersionHigh, UINT _VersionLow);
	void SetCode(const std::string& _Code);
	void SetEntryPoint(const std::string& _EntryPoint);

protected: // Create HLSL Version String
	// ���Ź��� VersionHigh_�� VersionLow_�� �̿��Ͽ� VertexShader ������ ������ �������� Version ���ڿ��� ����
	void CreateVersion(const std::string& _ShaderType);

public:
	void ResCheck();
};


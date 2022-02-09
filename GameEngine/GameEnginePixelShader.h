#pragma once
#include "GameEngineShader.h"
#include "GameEngineDevice.h"

// �з� : �ȼ�(Pixel) ���̴�
// �뵵 : 
// ���� : �ȼ� ���̴��� ������ �� ������ �ȼ����� ���� ����Ѵ�. �׷��Ƿ� �ȼ� ���̴��� ���������� �ȼ��� ��� �������� �����Ѵ�. 
//            �ȼ� ���̴��� �����ϰ� ������ ���� ���� ����ϴ� ������ �Ͽ�������, �ؽ�ó�κ��� ���� �о���ų�, ���� �����ϴ� ��, 
//            ���� ����, �׸���, �ݻ籤, ����ó�� �� ������ ���� ���� ������ �� �ִ�.
class GameEnginePixelShader : public GameEngineShader
{
private:	// member Var
	ID3D11PixelShader*				Shader_;		// 

public:
	GameEnginePixelShader();
	~GameEnginePixelShader();

protected:		// delete constructer
	GameEnginePixelShader(const GameEnginePixelShader& _other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _other) noexcept = delete;

private:		//delete operator
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _other) = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader&& _other) = delete;

public: // Create Pixel Shader(D3DCompile() ���) - ���ڿ��� ������ ���̴� �ڵ带 �̿��Ͽ� ���̴��� ����
	bool Create(const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Create Pixel Compile(D3DCompile() ���)
	bool StringCompile();

public: // Load Pixel Shader(D3DCompileFromFile() ���) - ���ϸ��� �̿��Ͽ� �ش� ����� �ִ� ���̴� ������ �̿��Ͽ� ���̴� ����
	bool Load(const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Compile Vertex Shader(D3DCompileFromFile() ���) - ��� �ʿ�
	bool FileCompile(const std::string& _Path);

public: // Create Pixel Setting
	void Setting();
};


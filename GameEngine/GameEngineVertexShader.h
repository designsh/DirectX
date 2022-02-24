#pragma once
#include "GameEngineShader.h"
#include "GameEngineDevice.h"

// �з� : ����(Vertex) ���̴� & �Է·��̾ƿ�(InputLayout)
// �뵵 : 
// ���� : �ڵ带 �Է��ϰ� �� �ڵ� ��ü�� GPU�� �����ϴ� ����� ����
//            ����ڰ� �Է��� ���̴� �ڵ带 ���Ź޾� ID3DBlob(����Ʈ�ڵ�)�� ��ȯ�ϸ�
//            �ش� ����Ʈ�ڵ带 ����Ͽ� ����ڰ� ������ ��� ������� ��ġ/ũ��/ȸ���� ��Ű������
//            GPU�� �˼��ֵ��� �ϸ�, GPU�� ������ �����Ͽ� ������ȯ�� ����Ų��.
//            ���� CPU���� �������� �������� Ÿ�԰� ����, ����Ʈ��ġ ���� �˷��ֱ����Ͽ� ����������
//            InputLayout ���� �� ���� ����� �����Ѵ�.
class GameEngineVertexShader : public GameEngineShader
{
//======================================== Vertex Shader ���� ========================================//
private:
	ID3D11VertexShader*												Shader_;								// VertexShader Pointer

//========================================= InputLayout ���� =========================================//
private:
	ID3D11InputLayout*													LayOut_;								// InputLayout Pointer
	unsigned int																	LayOutOffset_;					// �ش� �����Ͱ� �ִ� ����Ʈ ��ġ
	std::vector<std::string>												SemanticName_;				// Semantic(�ǹ�ü��) : �Ű� ������ �뵵�� �� �� ������ ���� �ϴ� ���̴� �Է� �Ǵ� ��¿� ���� �� ���ڿ� �������
																																			// (Ex POSITION, COLOR, TEXCOORD, ...)
	std::vector<D3D11_INPUT_ELEMENT_DESC>	InputLayoutDesc_;				// HLSL�� ���ǵ� �Լ�(���)�� ���޵Ǵ� �Է�����(Input Arg)�� �Ӽ��� �����ϴ°͵��� �������

public:
	GameEngineVertexShader(); // default constructer ����Ʈ ������
	~GameEngineVertexShader(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

//======================================== Vertex Shader ���� ����Լ� ========================================//
public: // Create Vertex Shader(D3DCompile() ���) - ���ڿ��� ������ ���̴� �ڵ带 �̿��Ͽ� ���̴��� ����
	bool Create(const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Compile Vertex Shader(D3DCompile() ���)
	bool StringCompile();

public:  // Load Vertex Shader(D3DCompileFromFile() ���) - ���ϸ��� �̿��Ͽ� �ش� ����� �ִ� ���̴� ������ �̿��Ͽ� ���̴� ����
	bool Load(const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Compile Vertex Shader(D3DCompileFromFile() ���) - ��� �ʿ�
	bool FileCompile(const std::string& _Path);

public: // Vertex Shader Setting
	void Setting();

//========================================= InputLayout ���� ����Լ� =========================================//
private: // InputLayout Check
	void LayOutCheck();

private: // Clear InputLayout
	void LayOutClear();

private: // Add InpuLayout
	void AddInputLayOut(const char* _SemanticName, unsigned int _Index, unsigned int _AlignedByteOffset, DXGI_FORMAT _Format, unsigned int _InputSlot, unsigned int _InstanceDataStepRate, D3D11_INPUT_CLASSIFICATION _inputClass);

private: // Create Layout
	void CreateLayOut();

public: // InputLayout Setting
	void InputLayOutSetting();

//========================================= ������� ���ð��� ����Լ� =========================================//
public:
	void SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override;

//========================================== �ؽ��� ���ð��� ����Լ� =========================================//
public:
	void SetTexture(const GameEngineTextureSetting* _Setting) override;

//========================================== ���÷� ���ð��� ����Լ� =========================================//
public:
	void SetSampler(const GameEngineSamplerSetting* _Setting) override;

//======================================== ���̴� ���ҽ� ���°��� ����Լ� =======================================//
public:
	void ReSetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override;
	void ReSetTexture(const GameEngineTextureSetting* _Setting) override;
	void ReSetSampler(const GameEngineSamplerSetting* _Setting) override;
};


#include "Precompile.h"
#include "UserGame_Resources_Shader.h"

void AppShaderLoad()
{
	// ���̴� ���͸����� �̵�
	//GameEngineDirectory Dir;
	//Dir.MoveParent("DirectX");
	//Dir.MoveChild("Resources");
	//Dir.MoveChild("Shader");

	//// .fx ����(���̴�����)�� ��� �����´�
	//std::vector<GameEngineFile> AllShader = Dir.GetAllFile("fx");
	//for (auto& ShaderFile : AllShader)
	//{
	//	// ��� ���̴����Ͽ� ���Ͽ� ó��

	//	// ���� ���̴������� �б����� �ؽ�Ʈ���Ϸ� Open
	//	ShaderFile.Open("rt");

	//	// Ȯ���ڸ� ������ ���ϸ��� �����´�.
	//	// ��Ģ : ���ϸ��� EntryPoint �̸��� ���λ��̸� ���̴��� ������ ���� ���̻簡 �޶�����.
	//	// Ex) Color.fx�� Vertex Shader ó�� �Լ��� �����ϸ� Color_VS�� EntryPoint �̸��� �ȴ�.
	//	//        Color.fx�� Pixel Shader ó�� �Լ��� �����ϸ� Color_PS�� EntryPoint �̸��� �ȴ�.
	//	std::string FileName = ShaderFile.GetFileNameWithOutExtension();

	//	// ���� �о�帰 ������ ��� ������(���ڿ�)���� �Լ���(EntryPoint)�� ã�Ƴ��� ������ ���̴��� �����Ѵ�.
	//	std::string AllCode = ShaderFile.GetString();
	//	if (std::string::npos != AllCode.find(FileName + "_VS"))
	//	{
	//		// ���ڿ��� ���̴��ڵ带 �����Ͽ� ���̴��� ����
	//		//GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Create(FileName + "_VS", AllCode);

	//		// ���ϸ�+��θ� �����Ͽ� ���̴��� ����
	//		GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Load(FileName + "_VS", ShaderFile.GetFullPath(), FileName + "_VS");
	//	}

	//	if (std::string::npos != AllCode.find(FileName + "_PS"))
	//	{
	//		// ���ڿ��� ���̴��ڵ带 �����Ͽ� ���̴��� ����
	//		//GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Create(FileName + "_PS", AllCode);

	//		// ���ϸ�+��θ� �����Ͽ� ���̴��� ����
	//		GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Load(FileName + "_PS", ShaderFile.GetFullPath(), FileName + "_PS");
	//	}
	//}

	// User Custom Shader





}

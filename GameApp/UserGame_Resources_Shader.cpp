#include "Precompile.h"
#include "UserGame_Resources_Shader.h"

void AppShaderLoad()
{
	// 셰이더 디렉터리까지 이동
	//GameEngineDirectory Dir;
	//Dir.MoveParent("DirectX");
	//Dir.MoveChild("Resources");
	//Dir.MoveChild("Shader");

	//// .fx 파일(셰이더파일)을 모두 가져온다
	//std::vector<GameEngineFile> AllShader = Dir.GetAllFile("fx");
	//for (auto& ShaderFile : AllShader)
	//{
	//	// 모든 셰이더파일에 관하여 처리

	//	// 현재 셰이더파일을 읽기전용 텍스트파일로 Open
	//	ShaderFile.Open("rt");

	//	// 확장자를 제외한 파일명을 가져온다.
	//	// 규칙 : 파일명이 EntryPoint 이름의 접두사이며 셰이더의 종류에 따라 접미사가 달라진다.
	//	// Ex) Color.fx에 Vertex Shader 처리 함수가 존재하면 Color_VS가 EntryPoint 이름이 된다.
	//	//        Color.fx에 Pixel Shader 처리 함수가 존재하면 Color_PS가 EntryPoint 이름이 된다.
	//	std::string FileName = ShaderFile.GetFileNameWithOutExtension();

	//	// 현재 읽어드린 파일의 모든 데이터(문자열)에서 함수명(EntryPoint)를 찾아내며 각각의 셰이더를 생성한다.
	//	std::string AllCode = ShaderFile.GetString();
	//	if (std::string::npos != AllCode.find(FileName + "_VS"))
	//	{
	//		// 문자열로 셰이더코드를 수신하여 셰이더를 생성
	//		//GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Create(FileName + "_VS", AllCode);

	//		// 파일명+경로를 수신하여 셰이더를 생성
	//		GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Load(FileName + "_VS", ShaderFile.GetFullPath(), FileName + "_VS");
	//	}

	//	if (std::string::npos != AllCode.find(FileName + "_PS"))
	//	{
	//		// 문자열로 셰이더코드를 수신하여 셰이더를 생성
	//		//GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Create(FileName + "_PS", AllCode);

	//		// 파일명+경로를 수신하여 셰이더를 생성
	//		GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Load(FileName + "_PS", ShaderFile.GetFullPath(), FileName + "_PS");
	//	}
	//}

	// User Custom Shader





}

#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineResourcesManager.h"
#include "GameEngineCollision.h"
#include "GameEngineBase/GameEngineDirectory.h"
#include "GameEngineBase/GameEngineFile.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineDepthStencil.h"
#include "EngineVertex.h"

void GameEngineCore::EngineResourcesLoad()
{
	// Engine용 Texture(텍스쳐 세팅을 위한 기본 텍스쳐) 로드
	GameEngineDirectory EngineTextureDir;
	EngineTextureDir.MoveParent("DirectX");
	EngineTextureDir.MoveChild("EngineResources");
	EngineTextureDir.MoveChild("Texture");
	std::vector<GameEngineFile> AllFile = EngineTextureDir.GetAllFile();
	for (size_t i = 0; i < AllFile.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
	}

	// 셰이더 디렉터리까지 이동
	GameEngineDirectory Dir;
	Dir.MoveParent("DirectX");
	Dir.MoveChild("EngineResources");
	Dir.MoveChild("Shader");

	// .fx 파일(셰이더파일)을 모두 가져온다
	std::vector<GameEngineFile> AllShader = Dir.GetAllFile("fx");
	for (auto& ShaderFile : AllShader)
	{
		// 모든 셰이더파일에 관하여 처리

		// 현재 셰이더파일을 읽기전용 텍스트파일로 Open
		ShaderFile.Open("rt");

		// 확장자를 제외한 파일명을 가져온다.
		// 규칙 : 파일명이 EntryPoint 이름의 접두사이며 셰이더의 종류에 따라 접미사가 달라진다.
		// Ex) Color.fx에 Vertex Shader 처리 함수가 존재하면 Color_VS가 EntryPoint 이름이 된다.
		//        Color.fx에 Pixel Shader 처리 함수가 존재하면 Color_PS가 EntryPoint 이름이 된다.
		std::string FileName = ShaderFile.GetFileNameWithOutExtension();

		// 현재 읽어드린 파일의 모든 데이터(문자열)에서 함수명(EntryPoint)를 찾아내며 각각의 셰이더를 생성한다.
		std::string AllCode = ShaderFile.GetString();
		if (std::string::npos != AllCode.find(FileName + "_VS"))
		{
			// 문자열로 셰이더코드를 수신하여 셰이더를 생성
			//GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Create(FileName + "_VS", AllCode);

			// 파일명+경로를 수신하여 셰이더를 생성
			GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Load(FileName + "_VS", ShaderFile.GetFullPath(), FileName + "_VS");
		}

		if (std::string::npos != AllCode.find(FileName + "_PS"))
		{
			// 문자열로 셰이더코드를 수신하여 셰이더를 생성
			//GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Create(FileName + "_PS", AllCode);

			// 파일명+경로를 수신하여 셰이더를 생성
			GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Load(FileName + "_PS", ShaderFile.GetFullPath(), FileName + "_PS");
		}
	}

	GameEngineSampler* NewRes = GameEngineSamplerManager::GetInst().Find("PointSmp");
	NewRes->Info_.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	NewRes->ReCreate();
}

void GameEngineCore::EngineResourcesCreate()
{
	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4 * 6);

		{
			RectVertex[0] = { float4({ -0.5f, 0.5f, 0.5f }) };
			RectVertex[1] = { float4({ 0.5f, 0.5f, 0.5f }) };
			RectVertex[2] = { float4({ 0.5f, -0.5f, 0.5f }) };
			RectVertex[3] = { float4({ -0.5f, -0.5f, 0.5f }) };

			RectVertex[4] = { float4::RotateXDegree(RectVertex[0].Postion, 180.0f) };
			RectVertex[5] = { float4::RotateXDegree(RectVertex[1].Postion, 180.0f) };
			RectVertex[6] = { float4::RotateXDegree(RectVertex[2].Postion, 180.0f) };
			RectVertex[7] = { float4::RotateXDegree(RectVertex[3].Postion, 180.0f) };
		}

		{
			RectVertex[8] = { float4::RotateYDegree(RectVertex[0].Postion, 90.0f) };
			RectVertex[9] = { float4::RotateYDegree(RectVertex[1].Postion, 90.0f) };
			RectVertex[10] = { float4::RotateYDegree(RectVertex[2].Postion, 90.0f) };
			RectVertex[11] = { float4::RotateYDegree(RectVertex[3].Postion, 90.0f) };

			RectVertex[12] = { float4::RotateYDegree(RectVertex[0].Postion, -90.0f) };
			RectVertex[13] = { float4::RotateYDegree(RectVertex[1].Postion, -90.0f) };
			RectVertex[14] = { float4::RotateYDegree(RectVertex[2].Postion, -90.0f) };
			RectVertex[15] = { float4::RotateYDegree(RectVertex[3].Postion, -90.0f) };
		}

		{
			RectVertex[16] = { float4::RotateXDegree(RectVertex[0].Postion, 90.0f) };
			RectVertex[17] = { float4::RotateXDegree(RectVertex[1].Postion, 90.0f) };
			RectVertex[18] = { float4::RotateXDegree(RectVertex[2].Postion, 90.0f) };
			RectVertex[19] = { float4::RotateXDegree(RectVertex[3].Postion, 90.0f) };

			RectVertex[20] = { float4::RotateXDegree(RectVertex[0].Postion, -90.0f) };
			RectVertex[21] = { float4::RotateXDegree(RectVertex[1].Postion, -90.0f) };
			RectVertex[22] = { float4::RotateXDegree(RectVertex[2].Postion, -90.0f) };
			RectVertex[23] = { float4::RotateXDegree(RectVertex[3].Postion, -90.0f) };
		}

		for (size_t i = 0; i < RectVertex.size(); i += 4)
		{
			RectVertex[i + 0].Texcoord = { 0.0f, 0.0f };
			RectVertex[i + 1].Texcoord = { 1.0f, 0.0f };
			RectVertex[i + 2].Texcoord = { 1.0f, 1.0f };
			RectVertex[i + 3].Texcoord = { 0.0f, 1.0f };
		}

		GameEngineVertexBufferManager::GetInst().Create("Box", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		for (int i = 0; i < 6; i++)
		{
			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 1);
			RectIndex.push_back(i * 4 + 2);

			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 2);
			RectIndex.push_back(i * 4 + 3);
		}

		GameEngineIndexBufferManager::GetInst().Create("Box", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);
		RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
		RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }),  { 1.0f, 0.0f } };
		RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }),  { 1.0f, 1.0f } };
		RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }),  { 0.0f, 1.0f } };

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;
		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);
		RectIndex.push_back(0);
		RectIndex.push_back(2);
		RectIndex.push_back(3);
		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(5);

		{
			// 앞면
			RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
			RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }),  { 1.0f, 0.0f } };
			RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }),  { 1.0f, 1.0f } };
			RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }),  { 0.0f, 1.0f } };
			RectVertex[4] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
		}

		GameEngineVertexBufferManager::GetInst().Create("DebugRect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);
		RectIndex.push_back(3);
		RectIndex.push_back(4);

		GameEngineIndexBufferManager::GetInst().Create("DebugRect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

		{
			// 앞면
			RectVertex[0] = { float4({ -1.0f, 1.0f, 0.0f }),float4({ 0.0f, 0.0f }) };
			RectVertex[1] = { float4({ 1.0f, 1.0f, 0.0f }), float4({ 1.0f, 0.0f }) };
			RectVertex[2] = { float4({ 1.0f, -1.0f, 0.0f }), float4({ 1.0f, 1.0f }) };
			RectVertex[3] = { float4({ -1.0f, -1.0f, 0.0f }),  float4({ 0.0f, 1.0f }) };
		}

		GameEngineVertexBufferManager::GetInst().Create("FullRect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);

		RectIndex.push_back(0);
		RectIndex.push_back(2);
		RectIndex.push_back(3);

		GameEngineIndexBufferManager::GetInst().Create("FullRect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}



	{
		D3D11_RASTERIZER_DESC Info = { D3D11_FILL_MODE::D3D11_FILL_SOLID, };
		Info.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Info.AntialiasedLineEnable = true;
		Info.MultisampleEnable = true;
		GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);

		float4 ScreenSize = GameEngineWindow::GetInst().GetSize();
		Ptr->SetViewPort(ScreenSize.x, ScreenSize.y, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	{
		D3D11_BLEND_DESC BlendInfo = { 0, };

		BlendInfo.AlphaToCoverageEnable = FALSE;
		BlendInfo.IndependentBlendEnable = FALSE;
		BlendInfo.RenderTarget[0].BlendEnable = true;
		BlendInfo.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		BlendInfo.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		BlendInfo.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		BlendInfo.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		BlendInfo.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		BlendInfo.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		BlendInfo.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

		GameEngineBlendManager::GetInst().Create("EngineAlphaBlend", BlendInfo);
	}

	{
		D3D11_DEPTH_STENCIL_DESC DepthInfo = { 0 };

		DepthInfo.DepthEnable = true;
		DepthInfo.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		DepthInfo.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		DepthInfo.StencilEnable = false;
		GameEngineDepthStencilManager::GetInst().Create("BaseDepthOn", DepthInfo);
	}

	{
		D3D11_DEPTH_STENCIL_DESC DepthInfo = { 0 };

		DepthInfo.DepthEnable = false;
		DepthInfo.StencilEnable = false;
		GameEngineDepthStencilManager::GetInst().Create("BaseDepthOff", DepthInfo);
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("DebugRect");
		Pipe->SetInputAssembler1VertexBufferSetting("DebugRect");
		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");
		Pipe->SetVertexShader("Color_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("DebugRect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Color_PS");
		Pipe->SetOutputMergerBlend("EngineAlphaBlend");
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("TargetMerge");
		Pipe->SetInputAssembler1VertexBufferSetting("FullRect");
		Pipe->SetInputAssembler2IndexBufferSetting("FullRect");
		Pipe->SetInputAssembler1InputLayOutSetting("TargetMerge_VS");
		Pipe->SetVertexShader("TargetMerge_VS");
		Pipe->SetPixelShader("TargetMerge_PS");
		Pipe->SetOutputMergerDepthStencil("BaseDepthOff");
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Color");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");
		Pipe->SetVertexShader("Color_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Color_PS");
		Pipe->SetOutputMergerBlend("EngineAlphaBlend");
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Texture");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Texture_VS");
		Pipe->SetVertexShader("Texture_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Texture_PS");
		Pipe->SetOutputMergerBlend("EngineAlphaBlend");
	}


	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("TextureUI");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Texture_VS");
		Pipe->SetVertexShader("Texture_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Texture_PS");
		Pipe->SetOutputMergerBlend("EngineAlphaBlend");
		Pipe->SetOutputMergerDepthStencil("BaseDepthOff");
	}
}

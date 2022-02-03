#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"

void UserGame::ResourcesLoad()
{
	// Game Resources Load Function

	// Sound Load
	GameEngineDirectory SoundDir;
	SoundDir.MoveParent("DirectX");
	SoundDir.MoveChild("Resources");
	SoundDir.MoveChild("Sound");

	// true 옵션을 주는경우 해당 경로의 있는 하위디렉터리를 모두 검사하여 모든 파일을 로드
	std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav", true);
	//std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav");
	for (size_t i = 0; i < AllFile.size(); ++i)
	{
		GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
	}

	// Vertex Buffer 생성
	std::vector<float4> RectVertex = std::vector<float4>(4 * 6);
	RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
	RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
	RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
	RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

	// 앞면을 x축기준 180도 회전시켜 뒷면을 생성
	RectVertex[4] = float4::RotateXDegree(RectVertex[0], 180.0f);
	RectVertex[5] = float4::RotateXDegree(RectVertex[1], 180.0f);
	RectVertex[6] = float4::RotateXDegree(RectVertex[2], 180.0f);
	RectVertex[7] = float4::RotateXDegree(RectVertex[3], 180.0f);

	// 앞면을 y축기준 90도 회전시켜 왼쪽면 생성
	RectVertex[8] = float4::RotateYDegree(RectVertex[0], 90.0f);
	RectVertex[9] = float4::RotateYDegree(RectVertex[1], 90.0f);
	RectVertex[10] = float4::RotateYDegree(RectVertex[2], 90.0f);
	RectVertex[11] = float4::RotateYDegree(RectVertex[3], 90.0f);

	// 앞면을 y축기준 -90도 회전시켜 오른쪽면 생성
	RectVertex[12] = float4::RotateYDegree(RectVertex[0], -90.0f);
	RectVertex[13] = float4::RotateYDegree(RectVertex[1], -90.0f);
	RectVertex[14] = float4::RotateYDegree(RectVertex[2], -90.0f);
	RectVertex[15] = float4::RotateYDegree(RectVertex[3], -90.0f);

	// 앞면을 x축기준 90도 회전시켜 윗면 생성
	RectVertex[16] = float4::RotateXDegree(RectVertex[0], 90.0f);
	RectVertex[17] = float4::RotateXDegree(RectVertex[1], 90.0f);
	RectVertex[18] = float4::RotateXDegree(RectVertex[2], 90.0f);
	RectVertex[19] = float4::RotateXDegree(RectVertex[3], 90.0f);

	// 앞면을 x축기준 -90도 회전시켜 아랫면 생성
	RectVertex[20] = float4::RotateXDegree(RectVertex[0], -90.0f);
	RectVertex[21] = float4::RotateXDegree(RectVertex[1], -90.0f);
	RectVertex[22] = float4::RotateXDegree(RectVertex[2], -90.0f);
	RectVertex[23] = float4::RotateXDegree(RectVertex[3], -90.0f);

	GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);

	// 인덱스 버퍼 생성
	// 각 정점을 연결시켜 정육면체를 생성하기 위하여 인덱스 버퍼 생성
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

	GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);

	// Vertex Shader 생성 및 셋팅 
	// Input Layout 생성 및 셋팅
	std::string ShaderCode =
		"\
			float4 StartVertexShader( float4 pos : POSITION, float4 pos1 : POSITION1 ) : SV_POSITION\n \
			{\n \
				return pos;\n\
			}\n\
			";

	GameEngineVertexShader* VertexShader = GameEngineVertexShaderManager::GetInst().Create("StartVertexShader", ShaderCode);

	// Vertex Shader 내부에서 처리
	// VertexShader셋팅시 자동생성하는 구조로 되어있음
	//VertexShader->AddInputLayOut("TEXCOORD", 0, 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	//VertexShader->AddInputLayOut("POSTION", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	//VertexShader->AddInputLayOut("COLOR", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);

	// Viewport 생성 및 셋팅
	GameEngineRasterizer* Rasterizer = GameEngineRasterizerManager::GetInst().Create("TestReasterizer");
	Rasterizer->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Rendering PipeList 생성
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("BoxRendering");

	// Rendering PipeLine : InputAssembler1
	// VertexBuffer, InputLayout Setting
	Pipe->SetInputAssembler1VertexBufferSetting("Rect");
	Pipe->SetInputAssembler1InputLayOutSetting("StartVertexShader");

	// Rendering PipeLine : Vertex Shader
	// Vertex Shader Setting
	Pipe->SetVertexShader("StartVertexShader");

	// Rendering PipeLine : InputAssembler2
	// Index Buffer & 면생성방법(점, 선, 삼각형, 다각형) Setting
	Pipe->SetInputAssembler2IndexBufferSetting("Rect");
	Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
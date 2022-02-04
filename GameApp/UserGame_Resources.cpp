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

	// Rasterizer의 상태 정보 생성 및 ViewPort 생성
	D3D11_RASTERIZER_DESC Info = {};
	Info.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;		// 삼각형을 렌더링할때 사용할 채우기모드 정의
																																// D3D11_FILL_MODE::D3D11_FILL_WIREFRAME : 정점을 연결하는 선을 그린다. 단, 인접 정점은 그려지지않는다.
																																// D3D11_FILL_MODE::D3D11_FILL_SOLID : 꼭짓점에 의해 형성된 삼각형을 채운다. 단, 인접 정점은 그려지지않는다.
	Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;			// 지정된 방향의 삼각형을 그리지 않겠다는 의미를 정의(DirectX는 기본적으로 시계방향을 정면, 반시계방향을 후면으로 판단)
																																// D3D11_CULL_MODE::D3D11_CULL_NONE : 방향과 관계없이 항상 모든 면을 그린다.
																																// D3D11_CULL_MODE::D3D11_CULL_FRONT : 정면을 향한 면을 그리지않는다.(정면 : 시계방향)
																																// D3D11_CULL_MODE::D3D11_CULL_BACK : 뒷면을 향한 면을 그리지않는다.(뒷면 : 반시계방향)
	Info.FrontCounterClockwise = TRUE;														// 삼각형이 전면인지 후면인지 판단 정의
																																// TRUE : 삼각형의 정점이 렌더 대상에서 반시계 방향이면 전면으로 간주되고 시계 방향이면 후면으로 간주
																																// FALSE : TRUE와 반대의 의미로 반시계방향이 후면, 시계방향을 전면으로 간주
	Info.ScissorEnable = TRUE;																			// 화면 바깥으로 나간 삼각형들을 컬링하는지 판단 정의(화면 바깥으로 나간 삼각형을 잘라내는지 판단)
																																// TRUE : 화면 외부 삼각형 모두 컬링
																																// FALSE : TRUE와 반대의 의미를 가진다.
	Info.MultisampleEnable = TRUE;																// 사변형 또는 알파라인안티앨리어싱 알고리즘을 사용할지 판단 정의
																																// (멀티샘플링 : 픽셀은 무한히 작은 크기가 아니기때문에 모니터(화면)상에서의 선(Line)을 완벽하게 표현하기는 불가능하다.     )
																																//  (                     위와같은 이유로 모니터(화면)상에 선을 렌더링할때 계단현상 또는 앨리어싱(Aliasing) 효과가 나타나게 된다.    )
																																//  (                     이러한 현상을 없애기 위하여 안티 앨리어싱(Antialiasing) 기능이 수행된다.                                                           )
																																//  (                     이 기능은 화면의 4배의 크기를 가진 후면버퍼와 깊이버퍼를 이용하여 픽셀당 한번만 계산하고                              )
																																//  (                     그 색상과 서브 픽셀들의 가시성과 포괄도를 이용하여 최종 색상을 결정한다.                                                            )
																																//  (                     단, 픽셀을 4개의 픽셀을 한개의 픽셀로 가정하고 평균색상을 구한다.                                                                        )
																																// TRUE : 안티앨리어싱(Antialiasing) 알고리즘 사용
																																// FALSE : 안티앨리어싱(Antialiasing) 알고리즘 사용안함
																																
	// 깊이 관련 Rasterizer 상태 정보
	// Depth Bias(깊이바이어스) : 3D 공간에서 동일 평면(깊이)에 있는 다각형은 각각의 z-편향을 추가하여 동일 평면이아닌것을 판단할수 있다.
	//	일반적으로 장면의 그림자를 표현하기 위한 기술로 사용된다.
	Info.DepthBias = 0;																						// 주어진 픽셀에 추가된 깊이 값
	Info.DepthBiasClamp = 0.f;																			// 픽셀의 최대 깊이 바이어스
	Info.DepthClipEnable = TRUE;																	// 거리에 따른 클리핑 활성화판단 정의 : z-클립핑 활성화판단(클립핑 : 시야로부터 사라진 삼각형을 렌더링하지않거나, 시야에 걸친 삼각형을 추려내는 작업)
																																// TRUE : 기본값으로 z-클립핑을 활성화
																																// FALSE : z-클립핑을 비활성화(단, 픽셀수준에서의 부적절한 깊이 순서가 발생할 가능성이 있다.)
	Info.SlopeScaledDepthBias = 0.f;																// 주어진 픽셀의 기울기에 대한 스칼라값

	GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
	Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);

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

	// Rendering PipeLine : Rasterizer
	// Vertex Buffer를 이용하여 생성한 면이 간섭하는 픽셀을 건져낸다.
	// 샘플링 작업을 거치지 않았기 때문에 디테일한 화면표현이 되지않으며,
	// 단순 면이 간섭하는 모든 픽셀을 찾아내는 역할을 수행한다.
	Pipe->SetRasterizer("EngineBaseRasterizer");
}
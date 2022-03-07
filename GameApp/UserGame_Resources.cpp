#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"
#include "UserGame_Resources_Shader.h"

// InGame Infomation
#include "AllSkillInfomation.h"
#include "AllMonsterInfomation.h"
#include "AllNPCInfomation.h"
#include "AllItemInfomation.h"

void UserGame::ResourcesLoad()
{
	// ======================================================= Resource Load ======================================================= // 

	// Sound Load
	GameEngineDirectory SoundDir;
	SoundDir.MoveParent("DirectX");
	SoundDir.MoveChild("Resources");
	SoundDir.MoveChild("Sound");
	std::vector<GameEngineFile> SoundAllFile = SoundDir.GetAllFile("wav", true); // true : 하위디렉터리 모두 검사
	for (size_t i = 0; i < SoundAllFile.size(); ++i)
	{
		GameEngineSoundManager::GetInst().Load(SoundAllFile[i].GetFullPath());
	}

	// Image Load
	GameEngineDirectory TextureDir;
	TextureDir.MoveParent("DirectX");
	TextureDir.MoveChild("Resources");
	TextureDir.MoveChild("Image");
	std::vector<GameEngineFile> TextureAllFile = TextureDir.GetAllFile("png", true); // true : 하위디렉터리 모두 검사
	for (size_t i = 0; i < TextureAllFile.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(TextureAllFile[i].GetFullPath());
	}

	// 셰이더 리소스 파일을 모두 읽어들여 셰이더를 생성
	AppShaderLoad();

	// 인게임 관련 모든 정보 로드
	
	// 모든 클래스 스킬 정보
	AllSkillInfomation::GetInst().CreateAllSkillInfomation();

	// 구현하려는 모든 아이템 정보
	AllItemInfomation::GetInst().CreateAllItemInfomation();

	// 구현하려는 모든 몬스터 정보
	AllMonsterInfomation::GetInst().CreateAllMonsterInfomation();

	// 구현하려는 모든 NPC 정보
	AllNPCInfomation::GetInst().CreateAllNPCInfomation();

	// ======================================================= Rectagle Rendering ======================================================= // 
	// Vertex Buffer 생성
	std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);
	RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
	RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }),  { 1.0f, 0.0f } };
	RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }),  { 1.0f, 1.0f } };
	RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }),  { 0.0f, 1.0f } };

	GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);

	// 인덱스 버퍼 생성
	// 각 정점을 연결시켜 정육면체를 생성하기 위하여 인덱스 버퍼 생성
	std::vector<UINT> RectIndex;
	RectIndex.push_back(0);
	RectIndex.push_back(1);
	RectIndex.push_back(2);
	RectIndex.push_back(0);
	RectIndex.push_back(2);
	RectIndex.push_back(3);
	GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);

	// Rasterizer의 상태 정보 생성 및 ViewPort 생성
	D3D11_RASTERIZER_DESC Info = {};
	Info.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;					// 삼각형을 렌더링할때 사용할 채우기모드 정의
																																// D3D11_FILL_MODE::D3D11_FILL_WIREFRAME : 정점을 연결하는 선을 그린다. 단, 인접 정점은 그려지지않는다.
																																// D3D11_FILL_MODE::D3D11_FILL_SOLID : 꼭짓점에 의해 형성된 삼각형을 채운다. 단, 인접 정점은 그려지지않는다.
	Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;		// 지정된 방향의 삼각형을 그리지 않겠다는 의미를 정의(DirectX는 기본적으로 시계방향을 정면, 반시계방향을 후면으로 판단)
																																// D3D11_CULL_MODE::D3D11_CULL_NONE : 방향과 관계없이 항상 모든 면을 그린다.
																																// D3D11_CULL_MODE::D3D11_CULL_FRONT : 정면을 향한 면을 그리지않는다.(정면 : 시계방향)
																																// D3D11_CULL_MODE::D3D11_CULL_BACK : 뒷면을 향한 면을 그리지않는다.(뒷면 : 반시계방향)
	Info.FrontCounterClockwise = TRUE;														// 삼각형이 전면인지 후면인지 판단 정의
																																// TRUE : 삼각형의 정점이 렌더 대상에서 반시계 방향이면 전면으로 간주되고 시계 방향이면 후면으로 간주
																																// FALSE : TRUE와 반대의 의미로 반시계방향이 후면, 시계방향을 전면으로 간주
	Info.ScissorEnable = FALSE;																			// 화면(가위-사각형) 바깥으로 나간 삼각형들을 컬링하는지 판단 정의(화면 바깥으로 나간 삼각형을 잘라내는지 판단)
																																// 가위-사각형은 기본적으로 뷰포트보다 크게 설정이 불가능하며, 아무런 가위-사각형이 생성되지않았을경우
																																// 기본 뷰포트(Viewport)가 가위-사각형(화면)으로 설정된다.
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
	Info.DepthClipEnable = FALSE;																	// 거리에 따른 클리핑 활성화판단 정의 : z-클립핑 활성화판단(클립핑 : 시야로부터 사라진 삼각형을 렌더링하지않거나, 시야에 걸친 삼각형을 추려내는 작업)
																																// TRUE : 기본값으로 z-클립핑을 활성화
																																// FALSE : z-클립핑을 비활성화(단, 픽셀수준에서의 부적절한 깊이 순서가 발생할 가능성이 있다.)
	Info.SlopeScaledDepthBias = 0.f;																// 주어진 픽셀의 기울기에 대한 스칼라값

	GameEngineRasterizer* Rasterizer = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
	Rasterizer->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Rendering PipeList 생성
	GameEngineRenderingPipeLine* RederingPipeLine = GameEngineRenderingPipeLineManager::GetInst().Create("Color");

	// Rendering PipeLine : InputAssembler1
	// VertexBuffer, InputLayout Setting
	RederingPipeLine->SetInputAssembler1VertexBufferSetting("Rect");
	RederingPipeLine->SetInputAssembler1InputLayOutSetting("Color_VS");

	// Rendering PipeLine : Vertex Shader
	// Vertex Shader Setting
	RederingPipeLine->SetVertexShader("Color_VS");

	// Rendering PipeLine : InputAssembler2
	// Index Buffer & 면생성방법(점, 선, 삼각형, 다각형) Setting
	RederingPipeLine->SetInputAssembler2IndexBufferSetting("Rect");
	RederingPipeLine->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Rendering PipeLine : Rasterizer
	// Vertex Buffer를 이용하여 생성한 면이 간섭하는 픽셀을 건져낸다.
	// 샘플링 작업을 거치지 않았기 때문에 디테일한 화면표현이 되지않으며,
	// 단순 면이 간섭하는 모든 픽셀을 찾아내는 역할을 수행한다.
	RederingPipeLine->SetRasterizer("EngineBaseRasterizer");

	// Rendering PipeLine : Pixel Shader
	RederingPipeLine->SetPixelShader("Color_PS");

	// Rendering PipeLine : OutputMerger(Blend)
	D3D11_BLEND_DESC BlendInfo = {};
	memset(&BlendInfo, 0, sizeof(BlendInfo));

	// 깊이관련
	BlendInfo.AlphaToCoverageEnable = FALSE;
	BlendInfo.IndependentBlendEnable = FALSE;

	// 블렌딩사용
	BlendInfo.RenderTarget[0].BlendEnable = true;
	BlendInfo.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// 블렌딩 공식
	// FinalColor = (SrcColor * SrcFactor) BlendOp (DestColor * DestFactor)
	// D3D11_BLEND_OP_ADD : BlendOp(+)
	// D3D11_BLEND_OP_SUBTRACT : BlendOp(-)
	// D3D11_BLEND_OP_REV_SUBTRACT : BlendOp(반전후 -)
	// D3D11_BLEND_OP_MIN : BlendOp(최소값만남김)
	// D3D11_BLEND_OP_MAX : BlendOp(최대값만남김)
	BlendInfo.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

	// 블렌딩 방식
	// D3D11_BLEND_SRC_ALPHA : (SrcColor * Src Alpha Value)로 블렌딩
	// D3D11_BLEND_INV_SRC_ALPHA : DestColor * (1 - SRC Alpha Value)로 블렌딩
	BlendInfo.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	BlendInfo.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;

	// Dx11 Version이후 블렌딩은 RGB/A로 구분하여 설정
	// D3D11_BLEND_ONE : 알파값을 1로 곱한다 => 원본알파값 그대로 유지
	BlendInfo.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	BlendInfo.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	BlendInfo.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

	// 블렌드 생성
	GameEngineBlendManager::GetInst().Create("AlphaBlend", BlendInfo);

	RederingPipeLine->SetOutputMergerBlend("AlphaBlend");

	// ======================================================= Image Rendering ======================================================= // 
	GameEngineRenderingPipeLine* TexturePipeLine = GameEngineRenderingPipeLineManager::GetInst().Create("Texture");
	TexturePipeLine->SetInputAssembler1VertexBufferSetting("Rect");
	TexturePipeLine->SetInputAssembler1InputLayOutSetting("Texture_VS");
	TexturePipeLine->SetVertexShader("Texture_VS");
	TexturePipeLine->SetInputAssembler2IndexBufferSetting("Rect");
	TexturePipeLine->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TexturePipeLine->SetRasterizer("EngineBaseRasterizer");
	TexturePipeLine->SetPixelShader("Texture_PS");
	TexturePipeLine->SetOutputMergerBlend("AlphaBlend");
}
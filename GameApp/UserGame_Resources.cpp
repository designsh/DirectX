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
	std::vector<GameEngineFile> SoundAllFile = SoundDir.GetAllFile("wav", true); // true : �������͸� ��� �˻�
	for (size_t i = 0; i < SoundAllFile.size(); ++i)
	{
		GameEngineSoundManager::GetInst().Load(SoundAllFile[i].GetFullPath());
	}

	// Image Load
	GameEngineDirectory TextureDir;
	TextureDir.MoveParent("DirectX");
	TextureDir.MoveChild("Resources");
	TextureDir.MoveChild("Image");
	std::vector<GameEngineFile> TextureAllFile = TextureDir.GetAllFile("png", true); // true : �������͸� ��� �˻�
	for (size_t i = 0; i < TextureAllFile.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(TextureAllFile[i].GetFullPath());
	}

	// ���̴� ���ҽ� ������ ��� �о�鿩 ���̴��� ����
	AppShaderLoad();

	// �ΰ��� ���� ��� ���� �ε�
	
	// ��� Ŭ���� ��ų ����
	AllSkillInfomation::GetInst().CreateAllSkillInfomation();

	// �����Ϸ��� ��� ������ ����
	AllItemInfomation::GetInst().CreateAllItemInfomation();

	// �����Ϸ��� ��� ���� ����
	AllMonsterInfomation::GetInst().CreateAllMonsterInfomation();

	// �����Ϸ��� ��� NPC ����
	AllNPCInfomation::GetInst().CreateAllNPCInfomation();

	// ======================================================= Rectagle Rendering ======================================================= // 
	// Vertex Buffer ����
	std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);
	RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
	RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }),  { 1.0f, 0.0f } };
	RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }),  { 1.0f, 1.0f } };
	RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }),  { 0.0f, 1.0f } };

	GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);

	// �ε��� ���� ����
	// �� ������ ������� ������ü�� �����ϱ� ���Ͽ� �ε��� ���� ����
	std::vector<UINT> RectIndex;
	RectIndex.push_back(0);
	RectIndex.push_back(1);
	RectIndex.push_back(2);
	RectIndex.push_back(0);
	RectIndex.push_back(2);
	RectIndex.push_back(3);
	GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);

	// Rasterizer�� ���� ���� ���� �� ViewPort ����
	D3D11_RASTERIZER_DESC Info = {};
	Info.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;					// �ﰢ���� �������Ҷ� ����� ä����� ����
																																// D3D11_FILL_MODE::D3D11_FILL_WIREFRAME : ������ �����ϴ� ���� �׸���. ��, ���� ������ �׷������ʴ´�.
																																// D3D11_FILL_MODE::D3D11_FILL_SOLID : �������� ���� ������ �ﰢ���� ä���. ��, ���� ������ �׷������ʴ´�.
	Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;		// ������ ������ �ﰢ���� �׸��� �ʰڴٴ� �ǹ̸� ����(DirectX�� �⺻������ �ð������ ����, �ݽð������ �ĸ����� �Ǵ�)
																																// D3D11_CULL_MODE::D3D11_CULL_NONE : ����� ������� �׻� ��� ���� �׸���.
																																// D3D11_CULL_MODE::D3D11_CULL_FRONT : ������ ���� ���� �׸����ʴ´�.(���� : �ð����)
																																// D3D11_CULL_MODE::D3D11_CULL_BACK : �޸��� ���� ���� �׸����ʴ´�.(�޸� : �ݽð����)
	Info.FrontCounterClockwise = TRUE;														// �ﰢ���� �������� �ĸ����� �Ǵ� ����
																																// TRUE : �ﰢ���� ������ ���� ��󿡼� �ݽð� �����̸� �������� ���ֵǰ� �ð� �����̸� �ĸ����� ����
																																// FALSE : TRUE�� �ݴ��� �ǹ̷� �ݽð������ �ĸ�, �ð������ �������� ����
	Info.ScissorEnable = FALSE;																			// ȭ��(����-�簢��) �ٱ����� ���� �ﰢ������ �ø��ϴ��� �Ǵ� ����(ȭ�� �ٱ����� ���� �ﰢ���� �߶󳻴��� �Ǵ�)
																																// ����-�簢���� �⺻������ ����Ʈ���� ũ�� ������ �Ұ����ϸ�, �ƹ��� ����-�簢���� ���������ʾ������
																																// �⺻ ����Ʈ(Viewport)�� ����-�簢��(ȭ��)���� �����ȴ�.
																																// TRUE : ȭ�� �ܺ� �ﰢ�� ��� �ø�
																																// FALSE : TRUE�� �ݴ��� �ǹ̸� ������.
	Info.MultisampleEnable = TRUE;																// �纯�� �Ǵ� ���Ķ��ξ�Ƽ�ٸ���� �˰����� ������� �Ǵ� ����
																																// (��Ƽ���ø� : �ȼ��� ������ ���� ũ�Ⱑ �ƴϱ⶧���� �����(ȭ��)�󿡼��� ��(Line)�� �Ϻ��ϰ� ǥ���ϱ�� �Ұ����ϴ�.     )
																																//  (                     ���Ͱ��� ������ �����(ȭ��)�� ���� �������Ҷ� ������� �Ǵ� �ٸ����(Aliasing) ȿ���� ��Ÿ���� �ȴ�.    )
																																//  (                     �̷��� ������ ���ֱ� ���Ͽ� ��Ƽ �ٸ����(Antialiasing) ����� ����ȴ�.                                                           )
																																//  (                     �� ����� ȭ���� 4���� ũ�⸦ ���� �ĸ���ۿ� ���̹��۸� �̿��Ͽ� �ȼ��� �ѹ��� ����ϰ�                              )
																																//  (                     �� ����� ���� �ȼ����� ���ü��� �������� �̿��Ͽ� ���� ������ �����Ѵ�.                                                            )
																																//  (                     ��, �ȼ��� 4���� �ȼ��� �Ѱ��� �ȼ��� �����ϰ� ��ջ����� ���Ѵ�.                                                                        )
																																// TRUE : ��Ƽ�ٸ����(Antialiasing) �˰��� ���
																																// FALSE : ��Ƽ�ٸ����(Antialiasing) �˰��� ������

	// ���� ���� Rasterizer ���� ����
	// Depth Bias(���̹��̾) : 3D �������� ���� ���(����)�� �ִ� �ٰ����� ������ z-������ �߰��Ͽ� ���� ����̾ƴѰ��� �Ǵ��Ҽ� �ִ�.
	//	�Ϲ������� ����� �׸��ڸ� ǥ���ϱ� ���� ����� ���ȴ�.
	Info.DepthBias = 0;																						// �־��� �ȼ��� �߰��� ���� ��
	Info.DepthBiasClamp = 0.f;																			// �ȼ��� �ִ� ���� ���̾
	Info.DepthClipEnable = FALSE;																	// �Ÿ��� ���� Ŭ���� Ȱ��ȭ�Ǵ� ���� : z-Ŭ���� Ȱ��ȭ�Ǵ�(Ŭ���� : �þ߷κ��� ����� �ﰢ���� �����������ʰų�, �þ߿� ��ģ �ﰢ���� �߷����� �۾�)
																																// TRUE : �⺻������ z-Ŭ������ Ȱ��ȭ
																																// FALSE : z-Ŭ������ ��Ȱ��ȭ(��, �ȼ����ؿ����� �������� ���� ������ �߻��� ���ɼ��� �ִ�.)
	Info.SlopeScaledDepthBias = 0.f;																// �־��� �ȼ��� ���⿡ ���� ��Į��

	GameEngineRasterizer* Rasterizer = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
	Rasterizer->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Rendering PipeList ����
	GameEngineRenderingPipeLine* RederingPipeLine = GameEngineRenderingPipeLineManager::GetInst().Create("Color");

	// Rendering PipeLine : InputAssembler1
	// VertexBuffer, InputLayout Setting
	RederingPipeLine->SetInputAssembler1VertexBufferSetting("Rect");
	RederingPipeLine->SetInputAssembler1InputLayOutSetting("Color_VS");

	// Rendering PipeLine : Vertex Shader
	// Vertex Shader Setting
	RederingPipeLine->SetVertexShader("Color_VS");

	// Rendering PipeLine : InputAssembler2
	// Index Buffer & ��������(��, ��, �ﰢ��, �ٰ���) Setting
	RederingPipeLine->SetInputAssembler2IndexBufferSetting("Rect");
	RederingPipeLine->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Rendering PipeLine : Rasterizer
	// Vertex Buffer�� �̿��Ͽ� ������ ���� �����ϴ� �ȼ��� ��������.
	// ���ø� �۾��� ��ġ�� �ʾұ� ������ �������� ȭ��ǥ���� ����������,
	// �ܼ� ���� �����ϴ� ��� �ȼ��� ã�Ƴ��� ������ �����Ѵ�.
	RederingPipeLine->SetRasterizer("EngineBaseRasterizer");

	// Rendering PipeLine : Pixel Shader
	RederingPipeLine->SetPixelShader("Color_PS");

	// Rendering PipeLine : OutputMerger(Blend)
	D3D11_BLEND_DESC BlendInfo = {};
	memset(&BlendInfo, 0, sizeof(BlendInfo));

	// ���̰���
	BlendInfo.AlphaToCoverageEnable = FALSE;
	BlendInfo.IndependentBlendEnable = FALSE;

	// �������
	BlendInfo.RenderTarget[0].BlendEnable = true;
	BlendInfo.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// ���� ����
	// FinalColor = (SrcColor * SrcFactor) BlendOp (DestColor * DestFactor)
	// D3D11_BLEND_OP_ADD : BlendOp(+)
	// D3D11_BLEND_OP_SUBTRACT : BlendOp(-)
	// D3D11_BLEND_OP_REV_SUBTRACT : BlendOp(������ -)
	// D3D11_BLEND_OP_MIN : BlendOp(�ּҰ�������)
	// D3D11_BLEND_OP_MAX : BlendOp(�ִ밪������)
	BlendInfo.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

	// ���� ���
	// D3D11_BLEND_SRC_ALPHA : (SrcColor * Src Alpha Value)�� ����
	// D3D11_BLEND_INV_SRC_ALPHA : DestColor * (1 - SRC Alpha Value)�� ����
	BlendInfo.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	BlendInfo.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;

	// Dx11 Version���� ������ RGB/A�� �����Ͽ� ����
	// D3D11_BLEND_ONE : ���İ��� 1�� ���Ѵ� => �������İ� �״�� ����
	BlendInfo.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	BlendInfo.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	BlendInfo.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

	// ���� ����
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
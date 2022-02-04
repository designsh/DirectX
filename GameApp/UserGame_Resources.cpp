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

	// true �ɼ��� �ִ°�� �ش� ����� �ִ� �������͸��� ��� �˻��Ͽ� ��� ������ �ε�
	std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav", true);
	//std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav");
	for (size_t i = 0; i < AllFile.size(); ++i)
	{
		GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
	}

	// Vertex Buffer ����
	std::vector<float4> RectVertex = std::vector<float4>(4 * 6);
	RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
	RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
	RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
	RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

	// �ո��� x����� 180�� ȸ������ �޸��� ����
	RectVertex[4] = float4::RotateXDegree(RectVertex[0], 180.0f);
	RectVertex[5] = float4::RotateXDegree(RectVertex[1], 180.0f);
	RectVertex[6] = float4::RotateXDegree(RectVertex[2], 180.0f);
	RectVertex[7] = float4::RotateXDegree(RectVertex[3], 180.0f);

	// �ո��� y����� 90�� ȸ������ ���ʸ� ����
	RectVertex[8] = float4::RotateYDegree(RectVertex[0], 90.0f);
	RectVertex[9] = float4::RotateYDegree(RectVertex[1], 90.0f);
	RectVertex[10] = float4::RotateYDegree(RectVertex[2], 90.0f);
	RectVertex[11] = float4::RotateYDegree(RectVertex[3], 90.0f);

	// �ո��� y����� -90�� ȸ������ �����ʸ� ����
	RectVertex[12] = float4::RotateYDegree(RectVertex[0], -90.0f);
	RectVertex[13] = float4::RotateYDegree(RectVertex[1], -90.0f);
	RectVertex[14] = float4::RotateYDegree(RectVertex[2], -90.0f);
	RectVertex[15] = float4::RotateYDegree(RectVertex[3], -90.0f);

	// �ո��� x����� 90�� ȸ������ ���� ����
	RectVertex[16] = float4::RotateXDegree(RectVertex[0], 90.0f);
	RectVertex[17] = float4::RotateXDegree(RectVertex[1], 90.0f);
	RectVertex[18] = float4::RotateXDegree(RectVertex[2], 90.0f);
	RectVertex[19] = float4::RotateXDegree(RectVertex[3], 90.0f);

	// �ո��� x����� -90�� ȸ������ �Ʒ��� ����
	RectVertex[20] = float4::RotateXDegree(RectVertex[0], -90.0f);
	RectVertex[21] = float4::RotateXDegree(RectVertex[1], -90.0f);
	RectVertex[22] = float4::RotateXDegree(RectVertex[2], -90.0f);
	RectVertex[23] = float4::RotateXDegree(RectVertex[3], -90.0f);

	GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);

	// �ε��� ���� ����
	// �� ������ ������� ������ü�� �����ϱ� ���Ͽ� �ε��� ���� ����
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

	// Vertex Shader ���� �� ���� 
	// Input Layout ���� �� ����
	std::string ShaderCode =
		"\
			float4 StartVertexShader( float4 pos : POSITION, float4 pos1 : POSITION1 ) : SV_POSITION\n \
			{\n \
				return pos;\n\
			}\n\
			";

	GameEngineVertexShader* VertexShader = GameEngineVertexShaderManager::GetInst().Create("StartVertexShader", ShaderCode);

	// Vertex Shader ���ο��� ó��
	// VertexShader���ý� �ڵ������ϴ� ������ �Ǿ�����
	//VertexShader->AddInputLayOut("TEXCOORD", 0, 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	//VertexShader->AddInputLayOut("POSTION", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	//VertexShader->AddInputLayOut("COLOR", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);

	// Rasterizer�� ���� ���� ���� �� ViewPort ����
	D3D11_RASTERIZER_DESC Info = {};
	Info.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;		// �ﰢ���� �������Ҷ� ����� ä����� ����
																																// D3D11_FILL_MODE::D3D11_FILL_WIREFRAME : ������ �����ϴ� ���� �׸���. ��, ���� ������ �׷������ʴ´�.
																																// D3D11_FILL_MODE::D3D11_FILL_SOLID : �������� ���� ������ �ﰢ���� ä���. ��, ���� ������ �׷������ʴ´�.
	Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;			// ������ ������ �ﰢ���� �׸��� �ʰڴٴ� �ǹ̸� ����(DirectX�� �⺻������ �ð������ ����, �ݽð������ �ĸ����� �Ǵ�)
																																// D3D11_CULL_MODE::D3D11_CULL_NONE : ����� ������� �׻� ��� ���� �׸���.
																																// D3D11_CULL_MODE::D3D11_CULL_FRONT : ������ ���� ���� �׸����ʴ´�.(���� : �ð����)
																																// D3D11_CULL_MODE::D3D11_CULL_BACK : �޸��� ���� ���� �׸����ʴ´�.(�޸� : �ݽð����)
	Info.FrontCounterClockwise = TRUE;														// �ﰢ���� �������� �ĸ����� �Ǵ� ����
																																// TRUE : �ﰢ���� ������ ���� ��󿡼� �ݽð� �����̸� �������� ���ֵǰ� �ð� �����̸� �ĸ����� ����
																																// FALSE : TRUE�� �ݴ��� �ǹ̷� �ݽð������ �ĸ�, �ð������ �������� ����
	Info.ScissorEnable = TRUE;																			// ȭ�� �ٱ����� ���� �ﰢ������ �ø��ϴ��� �Ǵ� ����(ȭ�� �ٱ����� ���� �ﰢ���� �߶󳻴��� �Ǵ�)
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
	Info.DepthClipEnable = TRUE;																	// �Ÿ��� ���� Ŭ���� Ȱ��ȭ�Ǵ� ���� : z-Ŭ���� Ȱ��ȭ�Ǵ�(Ŭ���� : �þ߷κ��� ����� �ﰢ���� �����������ʰų�, �þ߿� ��ģ �ﰢ���� �߷����� �۾�)
																																// TRUE : �⺻������ z-Ŭ������ Ȱ��ȭ
																																// FALSE : z-Ŭ������ ��Ȱ��ȭ(��, �ȼ����ؿ����� �������� ���� ������ �߻��� ���ɼ��� �ִ�.)
	Info.SlopeScaledDepthBias = 0.f;																// �־��� �ȼ��� ���⿡ ���� ��Į��

	GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
	Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Rendering PipeList ����
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("BoxRendering");

	// Rendering PipeLine : InputAssembler1
	// VertexBuffer, InputLayout Setting
	Pipe->SetInputAssembler1VertexBufferSetting("Rect");
	Pipe->SetInputAssembler1InputLayOutSetting("StartVertexShader");

	// Rendering PipeLine : Vertex Shader
	// Vertex Shader Setting
	Pipe->SetVertexShader("StartVertexShader");

	// Rendering PipeLine : InputAssembler2
	// Index Buffer & ��������(��, ��, �ﰢ��, �ٰ���) Setting
	Pipe->SetInputAssembler2IndexBufferSetting("Rect");
	Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Rendering PipeLine : Rasterizer
	// Vertex Buffer�� �̿��Ͽ� ������ ���� �����ϴ� �ȼ��� ��������.
	// ���ø� �۾��� ��ġ�� �ʾұ� ������ �������� ȭ��ǥ���� ����������,
	// �ܼ� ���� �����ϴ� ��� �ȼ��� ã�Ƴ��� ������ �����Ѵ�.
	Pipe->SetRasterizer("EngineBaseRasterizer");
}
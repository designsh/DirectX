// ���̴��� ����ϴ� ������۸� ����

// ��Ģ
// 1. ��������� ��Ī�� ������ ������, ���� ��Ī�� ����ϴ� ������۵��� ���ε������� ũ�Ⱑ �ٸ��� ���� �Ұ����ϹǷ� ũ�⸦ �����Ѵ�.
// 2. ���� ��Ī�� ����ϴ� ������۵��� ���ε������� ������ �ٸ��� ���� �Ұ����ϹǷ� ������ �����Ѵ�.
// 3. register(b0)�� ���� Bind Point�� ����Ҽ�����.
//      Ex) cbuffer A : register(b0){}; cbuffer B : register(b0) => ��� �Ұ���
// 4. 
cbuffer TransformData : register(b0)
{
    // ���� : ������������� ����(0,0,0)�� ����
    float4 vWorldTranslation;
    float4 vWorldRotation;
    float4 vWorldScaling;

    // ���� : ������ ��ü�� ����(0,0,0)�� ����
    float4 vLocalTranslation;
    float4 vLocalRotation;
    float4 vLocalScaling;

    // ��ȯ���
    float4x4 Scaling;
    float4x4 Rotation;
    float4x4 Translation;
    float4x4 Revolve;
    float4x4 Parent;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};


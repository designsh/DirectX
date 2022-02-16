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
    float4 vWorldPosition_;
    float4 vWorldRotation_;
    float4 vWorldScaling_;

    // ���� : ������ ��ü�� ����(0,0,0)�� ����
    float4 vLocalPosition_;
    float4 vLocalRotation_;
    float4 vLocalScaling_;

	// ��ȯ���
    float4x4 LocalScaling_;
    float4x4 LocalRotation_;
    float4x4 LocalPosition_;
    float4x4 LocalWorld_;

    float4x4 Parent_;
    float4x4 WorldWorld_;

    float4x4 View_;
    float4x4 Projection_;
};


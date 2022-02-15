// 셰이더가 사용하는 상수버퍼를 정의

// 규칙
// 1. 상수버퍼의 명칭은 같을수 있으나, 같은 명칭을 사용하는 상수버퍼들의 내부데이터의 크기가 다르면 구분 불가능하므로 크기를 같게한다.
// 2. 같은 명칭을 사용하는 상수버퍼들의 내부데이터의 순서가 다르면 구분 불가능하므로 순서를 같게한다.
// 3. register(b0)와 같이 Bind Point를 사용할수없다.
//      Ex) cbuffer A : register(b0){}; cbuffer B : register(b0) => 사용 불가능
// 4. 
cbuffer TransformData : register(b0)
{
    // 월드 : 월드공간에서의 원점(0,0,0)을 기준
    float4 vWorldTranslation;
    float4 vWorldRotation;
    float4 vWorldScaling;

    // 로컬 : 각각의 물체의 원점(0,0,0)을 기준
    float4 vLocalTranslation;
    float4 vLocalRotation;
    float4 vLocalScaling;

    // 변환행렬
    float4x4 Scaling;
    float4x4 Rotation;
    float4x4 Translation;
    float4x4 Revolve;
    float4x4 Parent;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};


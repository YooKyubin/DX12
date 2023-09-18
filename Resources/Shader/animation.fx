#ifndef _ANIMATION_FX_
#define _ANIMATION_FX_

#include "params.fx"
#include "utils.fx"
#include "math.fx"

struct AnimFrameParams
{
    float4 scale;
    float4 rotation;
    float4 translation;
};

StructuredBuffer<AnimFrameParams> g_bone_frame : register(t8);
StructuredBuffer<matrix> g_offset : register(t9);
RWStructuredBuffer<matrix> g_final : register(u0);

// ComputeAnimation
// g_int_0 : BoneCount
// g_int_1 : CurrentFrame
// g_int_2 : NextFrame
// g_float_0 : Ratio
[numthreads(256, 1, 1)]
void CS_Main(int3 threadIdx : SV_DispatchThreadID)
{
    if (g_int_0 <= threadIdx.x)
        return;

    int boneCount = g_int_0;
    int currentFrame = g_int_1;
    int nextFrame = g_int_2;
    float ratio = g_float_0;

    uint idx = (boneCount * currentFrame) + threadIdx.x;
    uint nextIdx = (boneCount * nextFrame) + threadIdx.x;

    float4 quaternionZero = float4(0.f, 0.f, 0.f, 1.f);

    // lerp는 ratio에 맞게 블렌딩? 해주는 함수, 쿼터니언slerp는 특수해서 따로 또 함수가 정의되어있음
    // cpu에서 사용한다면 dx library에 있음
    float4 scale = lerp(g_bone_frame[idx].scale, g_bone_frame[nextIdx].scale, ratio);
    float4 rotation = QuaternionSlerp(g_bone_frame[idx].rotation, g_bone_frame[nextIdx].rotation, ratio);
    float4 translation = lerp(g_bone_frame[idx].translation, g_bone_frame[nextIdx].translation, ratio);

    matrix matBone = MatrixAffineTransformation(scale, quaternionZero, rotation, translation);

    g_final[threadIdx.x] = mul(g_offset[threadIdx.x], matBone);
}

#endif
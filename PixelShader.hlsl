cbuffer ConstantBuffer : register(b8)
{
	float time;
}

Texture2D tex : register(t0);
Texture2D norm : register(t1);

SamplerState smp : register(s0);

struct PSInput
{
	float4 pos : SV_POSITION;
	float3 col : COLOR;
	float2 uv :TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
	float4 nm = norm.Sample(smp,input.uv);
	nm.xy *= 2;
	nm.xy -= 1;
	float4 col = tex.Sample(smp, input.uv + nm.xy * 0.25 * sin(time));
	return col;
}
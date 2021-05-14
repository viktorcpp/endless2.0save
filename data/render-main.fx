
Texture2D    txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
	matrix WVP;
}



struct VS_INPUT
{
    float4 Pos:    POSITION;
	float4 Normal: NORMAL;
    float2 Tex:    TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos:    SV_POSITION;
	float4 Normal: NORMAL;
    float2 Tex:    TEXCOORD;
};



PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
	//output.Normal = mul( float4( input.Normal, 1 ), World ).xyz;
    output.Tex = input.Tex;
    
    return output;
}



float4 PS( PS_INPUT input) : SV_Target
{
    return txDiffuse.Sample( samLinear, input.Tex );
}

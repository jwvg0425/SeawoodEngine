//=============================================================================
// Basic.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Basic effect that currently supports transformations, lighting, and texturing.
//=============================================================================

#include "LightHelper.fx"
 
cbuffer cbPerFrame
{
	DirectionalLight gDirLight[3];
	PointLight gPointLight[3];
	SpotLight gSpotLight[3];
	float3 gEyePosW;

	float  gFogStart;
	float  gFogRange;
	float4 gFogColor;
	bool   gIsFogEnable;

	int gDirLightNum;
	int gPointLightNum;
	int gSpotLightNum;
};

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldInvTranspose;
	float4x4 gWorldViewProj;
	float4x4 gTexTransform;
	Material gMaterial;
}; 

// Nonnumeric values cannot be added to a cbuffer.
Texture2D gDiffuseMap;

SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

struct VertexIn
{
	float3 PosL    : POSITION;
	float3 NormalL : NORMAL;
	float2 Tex     : TEXCOORD;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
    float3 PosW    : POSITION;
    float3 NormalW : NORMAL;
	float2 Tex     : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to world space space.
	vout.PosW    = mul(float4(vin.PosL, 1.0f), gWorld).xyz;
	vout.NormalW = mul(vin.NormalL, (float3x3)gWorldInvTranspose);
		
	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	
	// Output vertex attributes for interpolation across triangle.
	vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;

	return vout;
}
 
float4 PS(VertexOut pin, uniform bool gUseTexture, uniform bool gUseRimLight) : SV_Target
{
	// Interpolating normal can unnormalize it, so normalize it.
    pin.NormalW = normalize(pin.NormalW);

	// The toEye vector is used in lighting.
	float3 toEye = gEyePosW - pin.PosW;

	// Cache the distance to the eye from this surface point.
	float distToEye = length(toEye); 

	// Normalize.
	toEye /= distToEye;
	
    // Default to multiplicative identity.
    float4 texColor = float4(1, 1, 1, 1);

    if(gUseTexture)
	{
		// Sample texture.
		texColor = gDiffuseMap.Sample( samAnisotropic, pin.Tex );

		clip(texColor.a - 0.1f);
	}
	 
	//
	// Lighting.
	//

	// Start with a sum of zero. 
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 rim = float4(0.0f, 0.0f, 0.0f, 0.0f);

	[unroll]
	for (int i = 0; i < gDirLightNum; ++i)
	{
		float4 A, D, S, R;
		ComputeDirectionalLight(gMaterial, gDirLight[i], pin.NormalW, toEye, gUseRimLight,
			A, D, S, R);

		ambient += A;
		diffuse += D;
		spec += S;
		rim += R;
	}

	[unroll]
	for (int j = 0; j < gPointLightNum; ++j)
	{
		float4 A, D, S, R;
		ComputePointLight(gMaterial, gPointLight[j], pin.PosW, pin.NormalW, toEye, gUseRimLight,
			A, D, S, R);
		ambient += A;
		diffuse += D;
		spec += S;
		rim += R;
	}

	[unroll]
	for (int k = 0; k < gSpotLightNum; ++k)
	{
		float4 A, D, S, R;
		ComputeSpotLight(gMaterial, gSpotLight[k], pin.PosW, pin.NormalW, toEye, gUseRimLight,
			A, D, S, R);
		ambient += A;
		diffuse += D;
		spec += S;
		rim += R;
	}

	// Modulate with late add.
	float4 litColor = texColor*(ambient + diffuse) + spec + rim;

	if (gIsFogEnable)
	{
		float fogLerp = saturate((distToEye - gFogStart) / gFogRange);

		litColor = lerp(litColor, gFogColor, fogLerp);
	}

	// Common to take alpha from diffuse material and texture.
	litColor.a = gMaterial.Diffuse.a * texColor.a;

    return litColor;
}

technique11 Light
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetPixelShader( CompileShader( ps_5_0, PS(false, false) ) );
    }
}

technique11 Tex
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS(true, false)));
	}
}

technique11 Rim
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS(false, true)));
	}
}

technique11 TexRim
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS(true, true)));
	}
}
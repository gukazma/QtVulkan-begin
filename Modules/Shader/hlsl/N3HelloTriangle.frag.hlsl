struct PSInput
{
    float3 v_color : COLOR;
};

float4 main(PSInput input) : SV_Target
{
    return float4(input.v_color, 1.0);
}
struct VSInput
{
    float2 position : POSITION;
    float3 color : COLOR;
};

struct VSOutput
{
    float3 v_color : COLOR;
    float4 gl_Position : SV_POSITION;
};

VSOutput main(VSInput input)
{
    VSOutput output;
    output.v_color = input.color;
    output.gl_Position = float4(input.position, 0, 1);
    return output;
}
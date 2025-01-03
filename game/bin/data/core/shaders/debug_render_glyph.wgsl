struct VertexInput
{
    @location(0) position: vec2f,
    @location(1) color: vec3f,
    @location(2) uv: vec2f
};

struct VertexOutput 
{
    @builtin(position) position: vec4f,
    @location(1) color: vec4f,
    @location(2) uv: vec2f
};

struct GlobalUniforms
{
    projectionMatrix : mat4x4<f32>,
    viewMatrix : mat4x4<f32>,
    time : f32
};

@group(0) @binding(0) var<uniform> uGlobalUniforms: GlobalUniforms;
@group(1) @binding(0) var glyphTexture: texture_2d<f32>;
@group(1) @binding(1) var glyphSampler: sampler;

@vertex fn vertexMain(in: VertexInput) -> VertexOutput
{
    let u_screenDimensions = vec2f(1024.0, 768.0);
    let x = ((2.0 * (in.position.x - 0.5)) / u_screenDimensions.x) - 1.0;
    let y = 1.0 - ((2.0 * (in.position.y - 0.5)) / u_screenDimensions.y);

    var out: VertexOutput;
    out.position = vec4f(x, y, 0.0f, 1.0);
    out.color = vec4f(in.color, 1.0);
    out.uv = in.uv;
    return out;
}

@fragment fn fragmentMain(in: VertexOutput) -> @location(0) vec4f 
{
    return in.color * textureSample(glyphTexture, glyphSampler, in.uv).r;
}

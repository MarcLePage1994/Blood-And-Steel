attribute vec4 position;
attribute vec2 uv0;

uniform mat4 worldViewProj;

varying out vec2 UV;

void main()                    
{
	gl_Position = worldViewProj * position;
	
	UV = uv0;
}


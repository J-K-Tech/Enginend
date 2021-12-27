#version 460 core
uniform sampler2D Texture0;
uniform float brightness = 1.0;
uniform float contrast = 1.0;
uniform float saturation = 1.0;
out vec4 fragColor;
in vec2 UV;
void main()
{
	
	//vec2 UV=vec2(0.0,0.0);
	vec4 c = texture(Texture0, UV)*brightness;
	//vec4 c = vec4(1.0,1.0,1.0,1.0);
	c.r = float(int(c.r*16.0))/16.0;
	c.g = float(int(c.g*16.0))/16.0;
	c.b = float(int(c.b*16.0))/16.0;
	
	fragColor= texture(Texture0, UV);
	fragColor=vec4(c.r,c.g,c.b,1.0);
	//fragColor=vec4(UV.x,UV.y,c.b,1.0);
}

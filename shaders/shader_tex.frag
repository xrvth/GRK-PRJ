#version 430 core

uniform vec3 objectColor;
uniform vec3 lightDir;
uniform sampler2D tex;

in vec3 interpNormal;

in vec2 uv;

void main()
{
	vec3 normal = normalize(interpNormal);
	float diffuse = max(dot(normal, -lightDir), 0.0);

	vec4 TextureColour = texture2D(tex, uv);
	gl_FragColor = vec4((TextureColour * diffuse).xyz, 1.0);
}

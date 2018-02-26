#version 330 core

in vec3 Position; // eye-space
in vec2 UV;
in vec3 Normal;

uniform sampler2D Texture;
uniform vec4 Ambient;
uniform vec4 LightColor;
uniform vec3 LightPosition; // eye-space
uniform vec3 EyeDirection;
uniform float Shininess;
uniform float Strength;
uniform float ConstantAttenuation;
uniform float LinearAttenuation;
uniform float QuadraticAttenuation;

out vec4 FragColor;

void main()
{
    vec4 color = texture(Texture, UV);

    vec3 lightDirection = LightPosition - Position;
    float lightDistance = length(lightDirection);
    lightDirection /= lightDistance;

    float attenuation = 1.0 / (ConstantAttenuation + LinearAttenuation * lightDistance + QuadraticAttenuation * lightDistance * lightDistance);
    
	vec3 halfVector = normalize(lightDirection + EyeDirection);

    float diffuse = max(0.0, dot(Normal, lightDirection));
    float specular = max(0.0, dot(Normal, halfVector));
    if (diffuse == 0.0)
        specular = 0.0;
    else
        specular = pow(specular, Shininess) * Strength;

    vec3 scattered = Ambient.rgb + LightColor.rgb * diffuse * attenuation;
    vec3 reflected = LightColor.rgb * specular * attenuation;

    vec3 rgb = min(color.rgb * scattered + reflected, vec3(1.0));

    FragColor = vec4(rgb, color.a);
}
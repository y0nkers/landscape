#version 410 core

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

in vec2 texCoords;
in vec3 fragPos;

const int SHININESS = 32;
const vec3 BRIGHT_FACTOR = vec3(0.2126, 0.7152, 0.0722);
const int AMOUNT_OF_POINT_LIGHTS = 1;

struct PointLight
{
  vec3 position;
  float constant;
  float linear;
  float quadratic;
  vec3 diffuse;
  vec3 ambient;
  vec3 specular;
};

uniform sampler2D grassTex;
uniform sampler2D stoneTex;
uniform sampler2D normalMap;
uniform sampler2D heightMap;
uniform vec3 viewPos;
uniform float farPlane;
uniform int lightsAmount;
uniform PointLight lights[AMOUNT_OF_POINT_LIGHTS];

float getAttenuation(PointLight light, float dist) {
    return 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist); // Коэффициент затухания
}

vec3 calcPointLight(PointLight light, vec3 material, vec3 viewDir, vec3 normal)
{
    vec3 fragToLightDir = fragPos - light.position;
    float dist = length(fragToLightDir);
    fragToLightDir = normalize(fragToLightDir); // Направление света
    float attenuation = getAttenuation(light, dist);
    vec3 ambient = light.ambient * material;

    // diffuse
    float diffuse_coef = max(dot(fragToLightDir, normal), 0.0);
    vec3 diffuse = light.diffuse * diffuse_coef * material;

    // specular
    vec3 halfwayDir = normalize(fragToLightDir + viewDir); // посередине между направлением взгляда и направлением света
    float specular_coef = pow(max(dot(halfwayDir, normal), 0.0), SHININESS);
    vec3 specular = light.specular * specular_coef * material;
    
    return (ambient + diffuse + specular) * attenuation * material;
    //return (ambient + diffuse + specular) * attenuation;
}

vec3 blendColor(vec3 rgbA, vec3 rgbB, vec3 rgbC, float alpha) // Смешивание цветов
{
	return (rgbA * alpha) + (rgbB * alpha) + (rgbC * alpha);
}

vec3 calcFog(vec3 material) // Туман
{
    const vec3 fogColor = vec3(0.6, 0.7, 0.8);
    const float fogStart = 100;
    const float fogEnd = 175;
    float dist = length(viewPos - fragPos);
    float fogFactor = clamp(((fogEnd - dist)/(fogEnd - fogStart)), 0.125, 1.0);
    return mix(fogColor, material, fogFactor);
}

void main()
{
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 normalColor = texture(normalMap, texCoords).rgb;
    vec3 normal = vec3(normalColor.r * 2.0 - 1.0, normalColor.b, normalColor.g * 2.0 - 1.0);
    normal = normalize(normal);

    vec3 height = texture(heightMap, texCoords).rgb;

    vec3 grass1 = texture(grassTex, texCoords * 10 + 5).rgb;
    vec3 grass2 = texture(grassTex, texCoords * 15 + 20).rgb;
    vec3 grass3 = texture(grassTex, texCoords * 20 + 30).rgb;
    vec3 grass = blendColor(grass1, grass2, grass3, 0.33);

    vec3 stone1 = texture(stoneTex, texCoords * 10 + 5).rgb;
    vec3 stone2 = texture(stoneTex, texCoords * 15 + 20).rgb;
    vec3 stone3 = texture(stoneTex, texCoords * 20 + 30).rgb;
    vec3 stone = blendColor(stone1, stone2, stone3, 0.33) * vec3(2.0, 2.0, 2.0);

    vec3 material = mix(stone, grass, pow(normal.y, 5));
    material = mix(grass, material, min(fragPos.y / 0.7, 1)); // mix(x, y, a) - Линейная интерполяция между x и y с помощью a. return x * (1 - a) + y * a

    vec3 result = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < lightsAmount; ++i)
    {
      result += calcPointLight(lights[i], material, viewDir, normal);
    }

    float brightness = dot(result, BRIGHT_FACTOR);
    if (brightness > 1.0) brightColor = vec4(result, 1.0);
    else brightColor = vec4(0.0, 0.0, 0.0, 1.0);

    result = calcFog(result);
    fragColor = vec4(result, 1.0);
}

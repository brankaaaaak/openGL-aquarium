#version 330 core
out vec4 FragColor;

in vec3 chNormal;  
in vec3 chFragPos;  
in vec2 chUV;
  
uniform vec3 uLightPos; 
uniform vec3 uViewPos; 
uniform vec3 uLightColor;

uniform sampler2D uDiffMap1;
uniform vec4 uColor;        // Boja za objekte bez teksture
uniform bool uUseTexture;   // Da li koristimo teksturu ili boju

void main()
{    
    // Ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * uLightColor;
  	
    // Diffuse 
    vec3 norm = normalize(chNormal);
    vec3 lightDir = normalize(uLightPos - chFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;
    
    // Finalna boja objekta
    vec4 objectColor;
    if(uUseTexture)
        objectColor = texture(uDiffMap1, chUV);
    else
        objectColor = uColor;

    vec3 result = (ambient + diffuse) * objectColor.rgb;
    FragColor = vec4(result, objectColor.a); // Zadržavamo Alpha kanal
}
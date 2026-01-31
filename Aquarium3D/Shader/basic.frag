#version 330 core
out vec4 FragColor;

in vec3 chNormal;  
in vec3 chFragPos;  
in vec2 chUV;
  
uniform vec3 uLightPos; 
uniform vec3 uViewPos; 
uniform vec3 uLightColor;

// --- NOVO ZA SVJETLO IZ KOVCEGA ---
uniform vec3 uChestLightPos;
uniform vec3 uChestLightColor; // Boja ce biti (0,0,0) kad je zatvoren
// ----------------------------------

uniform sampler2D uDiffMap1;
uniform vec4 uColor;        
uniform bool uUseTexture;   

void main()
{    
    // Ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * uLightColor;
  	
    // Glavno svjetlo (postojece)
    vec3 norm = normalize(chNormal);
    vec3 lightDir = normalize(uLightPos - chFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;
    
    // --- NOVO: SVJETLO IZ KOVCEGA (Point Light) ---
    vec3 chestLightDir = normalize(uChestLightPos - chFragPos);
    float chestDiff = max(dot(norm, chestLightDir), 0.0);
    
    // Prigušenje (da svjetlo ne sija beskonačno daleko)
    float distance = length(uChestLightPos - chFragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));
    
    vec3 chestLightEffect = uChestLightColor * chestDiff * attenuation;
    // ----------------------------------------------

    vec4 objectColor;
    if(uUseTexture)
        objectColor = texture(uDiffMap1, chUV);
    else
        objectColor = uColor;

    // Dodajemo chestLightEffect u finalni zbir
    vec3 result = (ambient + diffuse + chestLightEffect) * objectColor.rgb;
    FragColor = vec4(result, objectColor.a); 
}
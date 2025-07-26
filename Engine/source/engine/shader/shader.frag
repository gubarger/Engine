
#version 410 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;

void main() {
    // easy light
    vec3 lightPos = vec3(10.0, 10.0, 10.0);
    vec3 lightColor = vec3(1.0);
    
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * vec3(0.8, 0.8, 0.8);
    FragColor = vec4(result, 1.0);
}

// --------------------------------=------------------------------
// @There will be a simplified version of the shader for debugging.
// --------------------------------=------------------------------

/*
#version 410 core

out vec4 FragColor;

uniform vec3 objectColor = vec3(1.0, 0.5, 0.2);

void main() {
    FragColor = vec4(objectColor, 1.0);
}
*/
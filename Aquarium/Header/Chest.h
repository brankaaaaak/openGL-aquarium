#pragma once
#include <glad/glad.h>

class Chest {
public:
    Chest();
    ~Chest();

    void Init(unsigned int* textures);  
    void Update(bool opening);           
    void Render(unsigned int shader);   

private:
    unsigned int VAO;
    unsigned int* texArray;   
    int state;                // 0-4 (zatvoren -> otvoren)
    double lastUpdateTime;

    unsigned int MakeTexturedQuad(float* data);
};

#pragma once

/** 
        -------------------------------------------------
        @This class is intended for debugging the display
        (in case the renderer does not work).
        The test part, it does not relate to the main code.
        -------------------------------------------------
*/

#include <glad/glad.h>
#include <vector>

class Cube {
public:
    Cube();
    ~Cube();

    void Draw() const;

private:
    GLuint VAO, VBO, EBO;
};
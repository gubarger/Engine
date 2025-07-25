#include <iostream>
#include "engine/begin/Application.h"

int main()
{
    try {
        Application app(1280, 720, "3D Engine");
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return -1;
    }
    return 0;
}
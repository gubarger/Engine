# Engine

My open-source 3D engine project in `C++`. It will have physics simulation and 3D scene rendering. It also saves images of scenes (for example, your created composition in the engine) or video simulations of various physical interactions. It supports embedded 2D and 3D primitives, as well as loading 2D sprites and 3D models.

`This text does not describe reality yet, this comment will be deleted after the first Release v1.0.0 is added.`

# How collect project (Developers)

The project *uses* **vcpkg** (*library manager*). *If you do not have* **vcpkg** *and dependencies* (**`glfw3, glad, imgui, imgui_impl_glfw, imgui_impl_opengl3`**), then here is the installation guide:

```sh
# download from the repository
git clone https://github.com/microsoft/vcpkg

# next, run the file
./vcpkg/bootstrap-vcpkg.sh

# for Windows
.\bootstrap-vcpkg.bat
```

After that, build the project using cmake

```sh
cmake -B build -DCMAKE_TOOLCHAIN_FILE=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

# How collect project (Regular users)

Just install it **.zip** any version of the engine from the Release. The original binary `.exe` will already be there.

`This text does not describe reality yet, this comment will be deleted after the first Release v1.0.0 is added.`

# License
MIT License `(Watch this LICENSE.txt)`

# Used Libraries
> GLFW - https://www.glfw.org/
>
> GLAD - https://glad.dav1d.de/
>
> ImGui - https://github.com/ocornut/imgui

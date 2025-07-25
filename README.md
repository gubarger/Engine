# Engine

My open-source 3D engine project in `C++`. It will have physics simulation and 3D scene rendering. It also saves images of scenes `(for example, your created composition in the engine)` or video simulations of various physical interactions. It supports embedded 2D and 3D primitives, as well as loading 2D sprites and 3D models.

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

# Screenshots
> <img width="1279" height="747" alt="{130C7FB6-FCF2-43D8-B91B-694CF74F9929}" src="https://github.com/user-attachments/assets/31b078f6-9351-4170-8c11-f18843c6bd75" />
You can hide the UI using the shift + tab key combination `(so far it just removes the entire UI, but in the future it will remove the entire UI except for the view window)`. ***But, you can also disable hotkey processing.***

# License
MIT License `(Watch this LICENSE.txt)`

# Used Libraries
> GLFW - https://www.glfw.org/
>
> GLAD - https://glad.dav1d.de/
>
> ImGui - https://github.com/ocornut/imgui

# Activity

***The project is actively being developed `(time of writing 07.26.2025 Moscow time 2:29 AM)`***

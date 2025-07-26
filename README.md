# Engine

My open-source 3D engine project in `C++`. It will have physics simulation and 3D scene rendering. It also saves images of scenes `(for example, your created composition in the engine)` or video simulations of various physical interactions. It supports embedded 2D and 3D primitives, as well as loading 2D sprites and 3D models.

# How collect project (Developers)

The project *uses* **vcpkg** (*library manager*). *If you do not have* **vcpkg** *and dependencies* (**`glfw3, glad, imgui, imgui_impl_glfw, imgui_impl_opengl3, assimp, stb_image, nlohmann-json`**), ***to find out how library data is written, go to*** **`vcpkg.io`**, then here is the installation guide:

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

- **`There is no cmake file, yet lol)`**

# How collect project (Regular users)

Just install it **.zip** any version of the engine from the Release. The original binary `.exe` will already be there.

# How to use the engine
> <img width="700" height="747" alt="{256F0127-3E14-4F27-8DE0-58355AD49677}" src="https://github.com/user-attachments/assets/df66de9f-468c-43b5-bc63-fb40f2b8d926" />
This is the main screen, there are `4 windows and the main rendering window`.

- You can hide the UI using the shift + tab key combination `(so far it just removes the entire UI, but in the future it will remove the entire UI except for the view window)`. ***But, you can also disable hotkey processing.***
#
> <img width="1273" height="743" alt="{9892054A-92CA-4E97-9439-C2A8B6D47455}" src="https://github.com/user-attachments/assets/146d6b27-315b-45ed-9afb-f8aed59131b6" />

- If you want to `place something` on the stage, you need to select the type of object **`(2D or 3D)`** ***from the catalog in the "Project" window, drag the selected object into the "Viewport" window.*** The "Viewport" is the base rendering window in which the 3D scene is displayed.
#
- In the `Inspector window`, you can configure the **`basic transformations of the object`**. ***These transformations are unique for each object, there is a Hierarchy window to select transformations for a specific object.*** In the `Hierarchy window`, you can **delete objects and switch between them.**

> <img width="800" height="746" alt="{96E0761B-EB3B-4B95-B0B8-A8B79B7805CC}" src="https://github.com/user-attachments/assets/ca740a65-d303-49ea-b1ac-377a8282436c" />

> <img width="238" height="137" alt="{198AE61F-5B08-4181-8715-12DB6B3368A7}" src="https://github.com/user-attachments/assets/1e575388-b228-48d1-b9ae-08ab5216f876" />
#
**You can also save your created scene! And besides, to learn a new...**

> <img width="363" height="146" alt="{240A0BB7-8F6E-44E4-A565-B4BCAC489716}" src="https://github.com/user-attachments/assets/083a0632-542a-4404-b736-a2c8c6a8586d" />
#
If you `select the main render window` and `hold down the right mouse button`, you can **`move around the 3D scene and look at it`**.
#
3D model output option (.obj):

> <img width="800" height="744" alt="{9885D691-76F1-434A-A0CD-E032E823B374}" src="https://github.com/user-attachments/assets/d37fde1e-a218-4c10-8b64-8b4648a21142" />

# License
MIT License `(Watch this LICENSE.txt)`

# Used Libraries
> GLFW - https://www.glfw.org/
>
> OpenGL - https://www.opengl.org/
> 
> GLAD - https://glad.dav1d.de/
>
> ImGui - https://github.com/ocornut/imgui
>
> Assimp - https://github.com/assimp/assimp
>
> stb_image - https://github.com/planetack/stb_image
>
> nlohmann - https://github.com/nlohmann/json

**These libraries are very helpful in development❤️❤️❤️.**

# Additional materials

Materials showing the operation of my 3D engine at the link: 
```sh
https://www.youtube.com/@Gubarg
```

# Activity

***The project is actively being developed `(time of writing 07.26.2025 Moscow time 2:29 AM)`***

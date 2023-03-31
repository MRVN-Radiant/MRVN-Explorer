# MRVN-Explorer

An OpenGL / ImGui respawn bsp viewer

![image](https://user-images.githubusercontent.com/64418963/229067842-74185039-3221-49e7-9d52-9bf4591b88cc.png)
![image](https://user-images.githubusercontent.com/64418963/229067977-9eac514e-3fe3-4617-8556-b19e9466e494.png)

## Compiling
### Getting dependencies on Windows
- Install [msys2](https://www.msys2.org/) and follow installation steps on their website
- Open the MingW shell
- Run:
  ```sh
  pacman -S {make,cmake}
  pacman -S mingw-w64-x86_64-{glm,glew,spdlog,glfw,cmake}
  ```

### Windows
```sh
cmake . -G "MinGW Makefiles"
cmake --build .
```

### Unzipping dlls
```sh
unzip winlibs.zip -d ./build
```

### Linux
```sh
cmake . -G "Unix Makefiles"
cmake --build .
```

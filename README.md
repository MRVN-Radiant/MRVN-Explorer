# MRVN-Explorer

An OpenGL / ImGui respawn bsp viewer

![image](https://user-images.githubusercontent.com/64418963/220383216-dcaf7e57-cd16-4ce0-a8c9-8fbaf1aa13b1.png)

## Compiling
### Getting dependencies on Windows
- Install [msys2](https://www.msys2.org/) and follow installation steps on their website
- Open the MingW shell
- Run:
  ```sh
  pacman -S  {make,cmake}
  pacman -S mingw-w64-x86_64-{glm,glew,spdlog,glfw3}
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
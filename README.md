# minimal_vulkan
Minimal Vukan HPP, GLFW, GLM cmake project.

## Build

<details>
<summary>Void Linux build dependencies (not including graphics drivers & compiler)</summary>

- Base build tools: `make cmake pkg-config`
- Libraries: `glfw-devel glm vulkan-loader-devel Vulkan-ValidationLayers`

</details>

```
cmake -B build
cmake --build build
```

## Docker

>[!WARNING]
>Current `Dockerfile` uses Void Linux & installs graphics driver packages for Radeon videocard.

Build
```
docker build -t minimal_vulkan
```

Run (for Wayland)
```
docker run -it --rm \
  --device /dev/dri:/dev/dri \
  -v $XDG_RUNTIME_DIR:$XDG_RUNTIME_DIR \
  -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
  -e WAYLAND_DISPLAY=$WAYLAND_DISPLAY \
  minimal_vulkan
```

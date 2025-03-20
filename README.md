# Khuon

**Khuon** is a **tech demo** exploring the use of **mesh shaders** for **strand-based rendering**. It serves as a proof-of-concept for leveraging the `GL_NV_mesh_shader` extension to process and render individual hair strands efficiently.

## Features

- **Mesh Shader Pipeline**: Implements `GL_NV_mesh_shader` for strand-based rendering.
- **Strand-Based Rendering**: Renders individual hair strands rather than traditional hair cards, using hair models from [Cem Yuksel's files](https://www.cemyuksel.com/research/hairmodels/).

## Requirements

- **Language**: C++ 17
- **Compiler**: `clang-cl`
- **IDE**: Visual Studio 2022
- **OpenGL**: Version 4.6
- **Extensions**: `GL_NV_mesh_shader`

## Demonstration

https://github.com/user-attachments/assets/34a4391f-543a-4362-a564-c791686b2825

## Dependencies

This demo uses the following third-party libraries:

- [cyHairFile](https://www.cemyuksel.com/cyCodeBase/) - Hair strand model and parsing library
- [gl3w](https://github.com/skaslev/gl3w) - OpenGL function loader
- [GLFW](https://www.glfw.org/) - Window and input management
- [spdlog](https://github.com/gabime/spdlog) - Logging library

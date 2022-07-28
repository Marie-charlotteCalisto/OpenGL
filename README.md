# OpenGL
Projet openGL avance

[![Watch the video]]( https://youtu.be/366bbG41iAc)
![](https://img.youtube.com/vi/366bbG41iAc/maxresdefault.jpg)

##To run and compile:
```
mkdir build; cd build
cmake ..
make
./pogla
```

## Command when running:

mouvement of camera: key arrows and mouse

augmentation of tesselation : "p"
diminution of tesseltation : "m"

augmentation of wind power : "w"
diminution of wind power : "s"


## To add model and shader pipeline:
In init\_shaders() : main.cpp

```
    std::vector<std::pair<GLenum, std::string>> shader_path = {
        {GL_VERTEX_SHADER, ROOT_DIR [PATH_VERTEX_SHADER]},
        {GL_TESS_CONTROL_SHADER, ROOT_DIR [PATH_TESSELATION_CONTROL]},
        {GL_TESS_EVALUATION_SHADER, ROOT_DIR [PATH_TESSELATION_EVAL]},
        {GL_GEOMETRY_SHADER, ROOT_DIR [PATH_GEOMETRY]},
        {GL_FRAGMENT_SHADER, ROOT_DIR [PATH_FRAGMENT]}};

    Program *shader = Program::make_program(shader_path);
    shader->use();
    //if want to set uniform:
    shader->setUniform1f([uniform]);
    shader->setUniform3f([uniform]);
    shader->setUniformMatrix4f([uniform]);


    std::vector<std::string> textures = {
            ROOT_DIR [PATH_TEXTURE],
        };

    Model object(ROOT_DIR [PATH_OBJ], [TEXTURE], shader, [SCALE], [X OFFSET], [Y OFFSET], [Z OFFSET]);
    models.push_back(object);

```


## To watch mesh geometry shader:
remove "ground" model in init\_shaders() : main.cpp
```
    models.push_back(ground);
->
    \\models.push_back(ground);
```

#include "program.hh"

std::string load(const std::string &shader_filename) {
    std::ifstream input_src_file(shader_filename, std::ios::in);
    std::string ligne;
    std::string file_content="";
    if (input_src_file.fail()) {
        std::cerr << "Fail to open " << shader_filename << "\n";
        return "";
    }
    while(getline(input_src_file, ligne)) {
        file_content = file_content + ligne + "\n";
    }
    file_content += '\0';
    input_src_file.close();
    return file_content;
}
bool check_shaders(GLuint ShaderID)
{
    GLint Result = GL_FALSE;
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
    int InfoLogLength;
    glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if ( InfoLogLength > 0 ){
        std::vector<char> ShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
        std::cerr << &ShaderErrorMessage[0] << std::endl;
        return false;
    }
    return true;
}


bool check_program(GLuint ProgramID)
{
    GLint Result = GL_FALSE;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    int InfoLogLength;
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        std::cerr << &ProgramErrorMessage[0] << std::endl;
        return false;
    }
    return true;
}


bool compile_shader(const char *ShaderCode, GLuint ShaderID)
{
    char const * SourcePointer = ShaderCode;
    glShaderSource(ShaderID, 1, &SourcePointer , NULL);
    glCompileShader(ShaderID);

    return check_shaders(ShaderID);
}

bool shaders(std::vector<std::pair<GLenum, std::string>> &shader_paths,
        GLuint ProgramID, std::vector<GLuint> &shaderID)
{
    for (std::pair<GLenum, std::string> shader : shader_paths)
    {
        GLenum type = shader.first;
        std::string path = shader.second;

        GLuint ShaderID = glCreateShader(type);

        std::string ShaderCode = load(path);
        if (ShaderCode.empty())
            return false;

        std::cout << "Compiling shader : " << path << std::endl;
        if (!compile_shader(ShaderCode.c_str(), ShaderID))
            return false;

        glAttachShader(ProgramID, ShaderID);

        shaderID.emplace_back(ShaderID);
    }
    return true;
}

Program *Program::make_program(std::vector<std::pair<GLenum, std::string>> shader_paths)
{

    GLuint ProgramID = glCreateProgram();

    std::vector<GLuint> shaderID;
    if (!shaders(shader_paths, ProgramID, shaderID))
        return nullptr;

    printf("Linking program\n");
    glLinkProgram(ProgramID);

    if(!check_program(ProgramID))
        return nullptr;

    for (GLuint ID : shaderID)
    {
        glDetachShader(ProgramID, ID);
        glDeleteShader(ID);
    }

    Program *p = new Program();
    p->id = ProgramID;

    return p;
}


char *Program::get_log()
{
    return log;
}

void Program::use()
{
    glUseProgram(id);
}

void Program::setUniform3f(const char *name, float a, float b, float c)
{
    GLuint uniID = glGetUniformLocation(id, name);
    glUniform3f(uniID, a, b, c);
}

void Program::setUniformMatrix4fv(const char *name, GLsizei count,
        GLboolean transpose, const GLfloat *value)
{
    GLuint uniID = glGetUniformLocation(id, name);
    glUniformMatrix4fv(uniID, count, transpose, value);
}

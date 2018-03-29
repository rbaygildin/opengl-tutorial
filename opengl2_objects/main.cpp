#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

GLuint vao, vbo;
GLFWwindow *wnd;
GLuint shader_programme;

using namespace std;

const char *vertex_shader =
        "#version 410\n"
                "layout (location = 0) in vec3 vp;"
                "layout (location = 1) in vec3 color;"
                "out vec3 inputColor;"
                "void main() {"
                "  gl_Position = vec4(vp, 1.0);"
                "  inputColor = color;"
                "}";

const char *fragment_shader =
        "#version 410\n"
                "out vec4 frag_colour;"
                "in vec3 inputColor;"
                "void main() {"
                "  frag_colour = vec4(inputColor, 1);"
                "}";
void update_fps_counter(GLFWwindow* window) {
    static double previous_seconds = glfwGetTime();
    static int frame_count;
    double current_seconds = glfwGetTime();
    double elapsed_seconds = current_seconds - previous_seconds;
    if (elapsed_seconds > 0.25) {
        previous_seconds = current_seconds;
        double fps = (double)frame_count / elapsed_seconds;
        char tmp[128];
        sprintf(tmp, "opengl @ fps: %.2f", fps);
        glfwSetWindowTitle(window, tmp);
        frame_count = 0;
    }
    frame_count++;
}

void resizeCallback(GLFWwindow *wnd, int w, int h) {
    glViewport(0, 0, w, h);
}

void createObjects() {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    static const GLfloat buffer[] = {
            //vertices          //colors
            -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(vbo), buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void destroyObjects() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void renderTriangle() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glVertexAttribPointer(
//            0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
//            3,                  // Размер
//            GL_FLOAT,           // Тип
//            GL_FALSE,           // Указывает, что значения не нормализованы
//            0,                  // Шаг
//            (void *) nullptr            // Смещение массива в буфере
//    );

// Вывести треугольник!
    glDrawArrays(GL_TRIANGLES, 0, 3); // Начиная с вершины 0, всего 3 вершины -> один треугольник

//    glDisableVertexAttribArray(0);
}

void render() {
    while (!glfwWindowShouldClose(wnd)) {
        update_fps_counter(wnd);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);
        glUseProgram(shader_programme);
//        auto time = static_cast<float>(glfwGetTime());
//        float greenValue = sin(time) / 2.0f + 0.5f;
//        int uniformLocation = glGetUniformLocation(shader_programme, "outColour");
//        glUniform4f(uniformLocation, 0.0f, greenValue, 0.0f, 0.0f);
        renderTriangle();

        glfwSwapBuffers(wnd);
        glFlush();
        glfwPollEvents();
    }
}

int main() {
    if (!glfwInit()) {
        cerr << "Could not to initialize GLFW context";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    cout << "GLFW context loaded successfully";
    wnd = glfwCreateWindow(640, 480, "OpenGL start", nullptr, nullptr);
    if (!wnd) {
        cerr << "Window could not created";
        glfwDestroyWindow(wnd);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    cout << "Window created successfully";
    glfwMakeContextCurrent(wnd);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GL_FALSE)
        exit(EXIT_FAILURE);
    const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte *version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
    glfwSetWindowSizeCallback(wnd, resizeCallback);
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    createObjects();
    render();
    destroyObjects();
    glfwTerminate();
    return 0;
}
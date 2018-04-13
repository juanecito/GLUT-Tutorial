
#include <iostream>

// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>

#include <GL/gl.h>

// FreeGLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>

#include <GL/glut.h>

unsigned int width = 320;
unsigned int height = 320;

GLuint program;

GLuint VBO, VAO;

float vertices[] = {
     // first triangle
     -0.9f, -0.5f, 0.0f,  // left
     -0.0f, -0.5f, 0.0f,  // right
     -0.45f, 0.5f, 0.0f,  // top
     // second triangle
      0.0f, -0.5f, 0.0f,  // left
      0.9f, -0.5f, 0.0f,  // right
      0.45f, 0.5f, 0.0f   // top
 };

inline void check_error(const std::string & file, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cerr << file << " - " << line << " - error caught = " << (char *)gluErrorString(err) << std::endl;
        std::cerr << "-----------------------------------------------------------------#" << std::endl;
    }
}

void renderScene(void)
{
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	check_error(__FILE__, __LINE__);

    glClear(GL_COLOR_BUFFER_BIT);
	check_error(__FILE__, __LINE__);

    // draw our first triangle
    glUseProgram(program);
	check_error(__FILE__, __LINE__);

	// seeing as we only have a single VAO there's no need to bind it every
	// time, but we'll do so to keep things a bit more organized
    glBindVertexArray(VAO);
	check_error(__FILE__, __LINE__);

	/* Mode glDrawArrays Specifies what kind of primitives to render.
	 * Symbolic constants GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
	 * GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP,
	 * GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY,
	 * GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.
	*/

	 // set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!
    glDrawArrays(GL_TRIANGLES, 0, 6);

	check_error(__FILE__, __LINE__);

    glBindVertexArray(0); // no need to unbind it every time
	check_error(__FILE__, __LINE__);


	glutSwapBuffers();
	check_error(__FILE__, __LINE__);
}

void create_shaders(GLuint& shaderProgram)
{
	const static std::string vertex_shader = ""
		"#version 330 core										\n"
		"layout (location = 0) in vec3 aPos;					\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\n"
		"}														\n\0";

	const static std::string fragment_shader =
		"#version 330 core										\n"
		"out vec4 FragColor;									\n"
		"void main()											\n"
		"{														\n"
		"	FragColor = vec4(0.2f, 0.0f, 0.2f, 1.0f);			\n"
		"}														\n\0";

	const char* vertexShaderSource = vertex_shader.c_str();
	GLuint vertexShader = 0;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	check_error(__FILE__, __LINE__);

	int success;
	char infoLogg[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLogg);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogg
			<< std::endl << vertex_shader << std::endl;
	}

	const char* FragmentShaderSource = fragment_shader.c_str();
	GLuint fragmentShader = 0;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	check_error(__FILE__, __LINE__);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogg);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogg
			<< std::endl << vertex_shader << std::endl;
	}

	// Shader program (link shaders)
	shaderProgram = glCreateProgram();
	check_error(__FILE__, __LINE__);

	// Attach shaders
	glAttachShader(shaderProgram, vertexShader);
	check_error(__FILE__, __LINE__);

	glAttachShader(shaderProgram, fragmentShader);
	check_error(__FILE__, __LINE__);

	glLinkProgram(shaderProgram);
	check_error(__FILE__, __LINE__);

	// Verify linkage
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogg);
		std::cout << "Error link program shaders " << infoLogg << std::endl;
	}

	// get the logs from the compile and link procedures
	GLint infologLength, charsWritten;
	char *infoLog = nullptr;

	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(vertexShader, infologLength, &charsWritten, infoLog);
		printf("\n%s\n", infoLog);
		free(infoLog);
	}
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(fragmentShader, infologLength, &charsWritten, infoLog);
		printf("\n%s\n", infoLog);
		free(infoLog);
	}
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog);
		printf("\n%s\n", infoLog);
		free(infoLog);
	}

	glDeleteShader(vertexShader);
	check_error(__FILE__, __LINE__);

	glDeleteShader(fragmentShader);
	check_error(__FILE__, __LINE__);

}

void initializeGL(GLuint& program)
{
	create_shaders(program);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

}

int main(int argc, char **argv)
{
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitContextVersion (4, 5);
	glutInitContextVersion (3, 3);
	// Profile selection, the core profile ensures no deprecated functions are used
	glutInitContextProfile (GLUT_CORE_PROFILE );

	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);

	//	Init GLEW
	// glewExperimental = GL_TRUE;
	glewExperimental = GL_FALSE;
	glewInit();
	// check if the required version is supported
	if (glewIsSupported("GL_VERSION_3_3"))
		printf("Ready for OpenGL 3.3\n");
	else {
		printf("OpenGL 3.3 not supported\n");
		return(1);
	}

	glViewport(0, 0, width, height);
	check_error(__FILE__, __LINE__);


	initializeGL(program);

	// enter GLUT event processing cycle
	glutMainLoop();
	
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

	return 0;
}

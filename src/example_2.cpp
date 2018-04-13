
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

float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << " A " << (char*)(gluErrorString(error)) << std::endl;
	}

	glutSwapBuffers();

    error = glGetError();
    if (error != GL_NO_ERROR)
    {
    	std::cout << " B " << (char*)(gluErrorString(error)) << std::endl;
    }
}

void create_shaders(GLuint& shaderProgram)
{
	const static std::string vertex_shader = ""
		"#version 330 core										\n"
		"layout (location = 0) in vec3 aPos;					\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\n"
		"}														\n";

	const static std::string fragment_shader =
		"#version 330 core										\n"
		"out vec4 FragColor;									\n"
		"void main()											\n"
		"{														\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);			\n"
		"}														\n";

	const char* vertexShaderSource = vertex_shader.c_str();
	GLuint vertexShader = 0;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
			<< std::endl << vertex_shader << std::endl;
	}

	const char* FragmentShaderSource = fragment_shader.c_str();
	GLuint fragmentShader = 0;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
			<< std::endl << vertex_shader << std::endl;
	}


	// Shader program (link shaders)
	shaderProgram = glCreateProgram();

	// Attach shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Verify linkage
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error link program shaders " << infoLog << std::endl;
	}




}

void initializeGL(GLuint& program)
{
	GLuint VBO = 0;

	// Create buffer ID
	glGenBuffers(1, &VBO);

	// Bind buffer and define GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Make copy from CPU -> GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	create_shaders(program);

	GLuint vertexLoc, texCoordLoc;

	check_error(__FILE__, __LINE__);

	// Get the locations of the attributes in the current program
	vertexLoc = glGetAttribLocation(program, "aPos");
	check_error(__FILE__, __LINE__);
	texCoordLoc = glGetAttribLocation(program, "texCoord");
	check_error(__FILE__, __LINE__);


	glEnableVertexAttribArray(vertexLoc);
	check_error(__FILE__, __LINE__);
	// Linking shaders with input data
	// Link vertex shader input parameters
	// - layout (location = 0)
	// - vec3 -> 3
	// - type float -> GL_FLOAT
	// - Normalized data (0, 1) -> GL_FALSE
	// - Stride 3 elements * 4 bytes / float -> 12
	// - offset of initial position (void*)0
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	check_error(__FILE__, __LINE__);
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
	glewExperimental = GL_TRUE;
	//glewExperimental = GL_FALSE;
	glewInit();
	// check if the required version is supported
	if (glewIsSupported("GL_VERSION_4_5"))
		printf("Ready for OpenGL 4.5\n");
	else {
		printf("OpenGL 4.5 not supported\n");
		return(1);
	}

	initializeGL(program);

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 0;
}

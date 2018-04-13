
#include <iostream>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

unsigned int width = 320;
unsigned int height = 320;

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

int main(int argc, char **argv)
{
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	// glutInitContextVersion (4, 5);
	glutInitContextVersion (3, 3);
	// Profile selection, the core profile ensures no deprecated functions are used
	glutInitContextProfile (GLUT_CORE_PROFILE );


	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 0;
}


#include <iostream>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#define n 5

unsigned int width = 100;
unsigned int height = 100;

struct S_Window
{

};


void create_window()
{


}


void renderScene(void)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);

	/*
	glScalef(0.2, 0.2, 0.2);

	glScalef(0.5, 0.5, 0.5);

	glTranslatef(-n-1, 0, 0);
	for (int i = 0; i < n; i++) {
		glRotatef(45,0,0,1);
		glutWireCube(2);
		glRotatef(-45,0,0,1);
		glTranslatef(2.82,0,0);
	}

	for (int i = 0; i < n; i++) {

		glPushMatrix();

		glTranslatef(1.414 *(- n*0.5 + i + 0.5), 0, 0);
		glRotatef(45, 0 ,0 ,1);
		glScalef(0.5, 0.5, 0.5);
		glutWireCube(2);

		glPopMatrix();

		glPushMatrix();

		glTranslatef(0, 1.414 *(- n*0.5 + i + 0.5), 0);
		glRotatef(45, 0 ,0 ,1);
		glScalef(0.5, 0.5, 0.5);
		glutWireCube(2);

		glPopMatrix();
	}
	*/

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << " A " << (char*)(gluErrorString(error)) << std::endl;
	}

	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();

	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << " B " << (char*)(gluErrorString(error)) << std::endl;
	}


	glutSwapBuffers();

    error = glGetError();
    if (error != GL_NO_ERROR)
    {
    	std::cout << " C " << (char*)(gluErrorString(error)) << std::endl;
    }
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitContextVersion (4, 5);
	// glutInitContextVersion (3, 3);
	// Profile selection, the core profile ensures no deprecated functions are used
	glutInitContextProfile (GLUT_CORE_PROFILE );


	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}

//gcc game.c -o game -lglut -lGL -lGLU

#include <stdio.h>
#include <GL/glut.h> //glut default library

GLfloat v[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
					{1,-1,1}, {-1,-1,1}, {-1,1,1}, {1,1,1}};

void cubo_colorido() {
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(v[0]); //frente
	glVertex3fv(v[1]);
	glVertex3fv(v[2]);
	glVertex3fv(v[3]);

	glColor3f(0.0f, 01.0f, 0.0f);
	glVertex3fv(v[4]); // fundos
	glVertex3fv(v[5]);
	glVertex3fv(v[6]);
	glVertex3fv(v[7]);

	glColor3f(0.0f, 1.0f, 0.5f);
	glVertex3fv(v[0]); // esq
	glVertex3fv(v[3]);
	glVertex3fv(v[6]);
	glVertex3fv(v[5]);

	glColor3f(1.0f, 1.0f, 0.5f);
	glVertex3fv(v[3]); // topo
	glVertex3fv(v[2]);
	glVertex3fv(v[7]);
	glVertex3fv(v[6]);

	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3fv(v[1]); // dir
	glVertex3fv(v[4]);
	glVertex3fv(v[7]);
	glVertex3fv(v[2]);

	glColor3f(1.0f, 0.5f, 0.5f);
	glVertex3fv(v[1]); // base
	glVertex3fv(v[0]);
	glVertex3fv(v[5]);
	glVertex3fv(v[4]);

	glEnd();
}

void display(void) {
	glMatrixMode(GL_MODELVIEW); //specify which matrix is the current matrix
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	gluLookAt(0.0, 5.0, -25.0,		0.0, 0.0, 0.0,		0.0, 1.0, 0.0);   
    
	
	const double time = glutGet(GLUT_ELAPSED_TIME) / 10.0;
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f);
		glRotatef(time, 1, 0, 0);
		glTranslatef(0, 4, 4);
		glutWireCube(2);	
	glPopMatrix();



	glPushMatrix();	
		glColor3f(1.0f, 0.0f, 0.0f);
		glRotatef(time, -1, 0, -1);
		glTranslatef(0, 0, 0);
		glutSolidCube(2);
		//cubo_colorido();
	glPopMatrix();	
	
	
	
	//glutSwapBuffers(); //when there is more than 1 buffer
	glFlush(); //force execution of GL commands in finite time
}

void gira(void) {
	glutPostRedisplay();
}


void resize(GLsizei w, GLsizei h) {
	// Evita a divisao por zero
	if (h == 0) h = 1;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45, w/h, 2, 100);

}


int main(int argc, char **argv) {
	/* set openGL parameters */ 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); //GLUT_SINGLE = sigle-buffered mode
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // defines the background color
	glutInitWindowSize(800, 600); //set default window size
	glutInitWindowPosition(10, 10); //set where the window will appear on screen
	
	glutCreateWindow("Game");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutIdleFunc(gira);
	glutMainLoop(); //the standard GLUT event loop entry point
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
}

//gcc android.c -o android -lglut -lGL -lGLU

#include <stdio.h>
#include <GL/glut.h>

GLfloat angle, fAspect;
	
	

void capisula (void) {
	
	GLUquadric* quad = gluNewQuadric(); //tipo primitivo pra desenhar quadrics

	glPushMatrix();
		gluSphere(quad, 2, 64, 64);
		glTranslatef(0, 0, -5);		
		glColor3f(0.0f, 0.9f, 0.0f);
		gluCylinder(quad, 2, 2, 5, 64, 64);
		gluSphere(quad, 2, 64, 64);
	glPopMatrix();	
}


// Fun��o callback chamada para fazer o desenho
void Desenha(void) {
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	const double time = glutGet(GLUT_ELAPSED_TIME) / 10.0;
	
	//glRotatef(2, 0, 1, 0);
	glPushMatrix();
		glTranslatef(-4, 0, 0);
		capisula();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0, 0);
		capisula();
	glPopMatrix();
		
	glPushMatrix();
		glTranslatef(4, 0, 0);
		capisula();
	glPopMatrix();
	
	
	glutSwapBuffers();
}


void redisplay(void) {
	glutPostRedisplay();
}

// Inicializa par�metros de rendering
void Inicializa(void) {
	GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat luzDifusa[4] = { 0.5,0.5,0.5,1.0 };	   // "cor"
	GLfloat luzEspecular[4] = { 0.7,0.7,0.7, 1.0 };// "brilho"
	GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };
//
	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 10;

	// Especifica que a cor de fundo da janela ser� preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a reflet�ncia do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz);

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT1);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	angle = 45;
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void) {
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva
	gluPerspective(angle, fAspect, 0.4, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi��o do observador e do alvo
	//gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);
	gluLookAt(0, 5, 20, 0, 0, 0, 0, 1, 0);
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	// Para previnir uma divis�o por zero
	if (h == 0) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Fun��o callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Programa Principal
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 350);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	Inicializa();
	glutIdleFunc(redisplay);
	glutMainLoop();
}

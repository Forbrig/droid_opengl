//g++ android.cpp -o android -lglut -lGL -lGLU

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

GLfloat angle, fAspect;

GLdouble p[3] = { 0,0,0 };
const double pi = 3.1415926;

// Fun??o Esfera: aproxima??o usando quadrilateros
// E as formulas:
// x(theta,phi) = r seno(phi) coseno(theta)
// y(theta,phi) = r seno(phi) seno(theta)
// z(theta,phi) = r coseno(phi)
void esfera(GLdouble *centro, GLdouble radius, GLfloat num) {
	GLdouble c, c2, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	GLdouble phi, theta, phi1, theta1, phi2, theta2;
	GLdouble senphi1, cosphi1, senphi2, cosphi2,
	         sentheta1, costheta1, sentheta2, costheta2,
	         passo;

    GLfloat cor[5][3] = { {0.5, 0.15, 0.8}, {1,0,0}, {1,0.75, 0.15}, {0.3, 1, 0.6}, {0.15,0.65,0.3}};

	glVertex3d(centro[0], centro[1] + radius, centro[2]);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	c = pi / 180;
	passo = 180 / num * c;
	glBegin(GL_TRIANGLES);
	phi1 = 0;
	senphi1 = sin(phi1);
	cosphi1 = cos(phi1);
	int i,j,k=0;
	for (i=0; i < num /2; i++) {
		phi2 = phi1 + passo;
		senphi2 = sin(phi2);
		cosphi2 = cos(phi2);
		theta1 = 0;
		sentheta1 = sin(theta1);
		costheta1 = cos(theta1);
		for (j=0; j < 2 * num; j++) {
			theta2 = theta1 + passo;
			sentheta2 = sin(theta2);
			costheta2 = cos(theta2);
			x1 = centro[0] + radius * senphi1 * costheta1;
			y1 = centro[1] + radius * senphi1 * sentheta1;
			z1 = centro[2] + radius * cosphi1;
			glNormal3d(x1, y1, z1);
			glVertex3d(x1, y1, z1);
			x2 = centro[0] + radius * senphi2 * costheta1;
			y2 = centro[1] + radius * senphi2 * sentheta1;
			z2 = centro[2] + radius * cosphi2;
			glNormal3d(x2, y2, z2);
			glVertex3d(x2, y2, z2);
			x3 = centro[0] + radius * senphi2 * costheta2;
			y3 = centro[1] + radius * senphi2 * sentheta2;
			z3 = centro[2] + radius * cosphi2;
			glNormal3d(x3, y3, z3);
			glVertex3d(x3, y3, z3);
			
			glNormal3d(x1, y1, z1);
			glVertex3d(x1, y1, z1);
			
			glNormal3d(x3, y3, z3);
			glVertex3d(x3, y3, z3);
			x4 = centro[0] + radius * senphi1 * costheta2;
			y4 = centro[1] + radius * senphi1 * sentheta2;
			z4 = centro[2] + radius * cosphi1;
			glNormal3d(x4, y4, z4);
			glVertex3d(x4, y4, z4);
			theta1 = theta2;
			sentheta1 = sentheta2;
			costheta1 = costheta2;
		}
		phi1 = phi2;
		senphi1 = senphi2;
		cosphi1 = cosphi2;
	}
	glEnd();
}


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
	
	GLUquadric* quad = gluNewQuadric(); //tipo primitivo pra desenhar quadrics

	glRotatef(2, 1, 0, 0);

	glPushMatrix();
		glPushMatrix();
			glTranslatef(0, 0, 0.8);
			
			//olho 1
			glPushMatrix();
				glColor3f(0.0f, 0.0f, 0.9f);
				glRotatef(90, 0, 1, 0);
				glTranslatef(-4, 2, -4);
				glutSolidSphere(0.5, 25, 25);
			glPopMatrix();
			
			//olho 1
			glPushMatrix();
				glColor3f(0.0f, 0.0f, 0.9f);
				glRotatef(90, 0, 1, 0);
				glTranslatef(-3, 3.5, 4);
				glutSolidSphere(0.5, 25, 25);
			glPopMatrix();
			
			
			
			glColor3f(0.0f, 0.9f, 0.0f);
			//Antena 1
			glPushMatrix();
				glRotatef(45, 0, 1, 0);
				glTranslatef(1	, 0, 6 + (7*0.4));
				glScalef(0.1, 0.1, 0.4);
				capisula();
			glPopMatrix();
			
			//Antena 2
			glPushMatrix();
				glRotatef(-45, 0, 1, 0);
				glTranslatef(-1, 0, 6 + (7*0.4));
				glScalef(0.1, 0.1, 0.4);
				capisula();
			glPopMatrix();
			
			//cabeca	
			glPushMatrix();
				glPushMatrix();
					glRotatef(180, 0, 1, 0);
					gluDisk(quad,  0,  6,  64,  64);
				glPopMatrix();
				
				esfera(p, 6, 64);
			glPopMatrix();
		glPopMatrix();
		
		
		//desenhar o torso na mão pra nao perder a beleza
		glPushMatrix();
			glScalef(3, 3, 3);
			
			gluDisk(quad,  0,  2,  64,  64); //fechando o torso
			//tronco	
			glPushMatrix();	
				glTranslatef(0, 0, -5);	// coloca o tronco pra z -5	
				glColor3f(0.0f, 0.9f, 0.0f);
				gluCylinder(quad, 2, 2, 5, 64, 64);
				glPushMatrix(); //bundinha
					glScalef(1, 1, 0.4);
					gluSphere(quad, 2, 64, 64);
				glPopMatrix();		
			glPopMatrix();
		glPopMatrix();

		//braco direito
		glPushMatrix();
			glTranslatef(-9, 0, -2);
			capisula();
		glPopMatrix();
			
		//braco esquerdo	
		glPushMatrix();
			glTranslatef(9, 0, -2);
			capisula();
		glPopMatrix();
		
		//perna direita
		glPushMatrix();
			glTranslatef(3, 0, -15);
			capisula();
		glPopMatrix();
		
		//perna esquerda
		glPushMatrix();
			glTranslatef(-3, 0, -15);
			capisula();
		glPopMatrix();
	
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
	
	glEnable(GL_NORMALIZE);
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
	gluLookAt(0, 100, 0, 0, 0, 0, 0, 0, 1);
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

#include "stdafx.h"

#include <cmath>

#ifdef __APPLE__

#include <GLUT/glut.h>

#else

#include <GL/glut.h>

#endif

// Poczatkowy rozmiar i pozycja prostokta

GLfloat x_1 = 100.0f;

GLfloat y_1 = 100.0f;

GLsizei rsize = 50;



// Rozmiar kroku (liczba pikseli) w osi x i y

GLfloat xstep = 3.0f;

GLfloat ystep = 3.0f;

// Dane zmieniajcych się rozmiarów okna

GLfloat windowWidth;

GLfloat windowHeight;

///////////////////////////////////////////////////////////

// Wywoływana w celu przerysowania sceny

void RenderScene(void) {

	// Wyczyszczenie okna aktualnym kolorem czyszczacym

	glClear(GL_COLOR_BUFFER_BIT);



	// Aktualny kolor rysujacy - czerwony

	// R G B

	glColor3f(1.0f, 0.0f, 0.0f);



	// Narysowanie prostokata wypełnionego aktualnym kolorem

	int amount = 8;

	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(x_1, y_1);

	for (int i = 0; i <= amount; i++)

	{

		glVertex2f(

			(x_1 + (10.0 * cos(i * 2 * 3.14f / amount)) * 5),

			(y_1 + (10.0 * sin(i * 2 * 3.14f / amount)) * 5)

		);

	}

	glEnd();

	glFlush();

	glutSwapBuffers();

}

///////////////////////////////////////////////////////////

// Wywoływana przez bibliotek GLUT w czasie, gdy okno nie

// jest przesuwane ani nie jest zmieniana jego wielkoœć

void TimerFunction(int value) {

	// Odwrócenie kierunku, jeżeli osišgnięto lewš lub prawš krawędŸ

	if (x_1 > windowWidth - rsize || x_1 + (10.0 * cos(3 * 2 * 3.14f / 8)) * 8 < 0)

		xstep = -xstep;



	// Odwrócenie kierunku, jeżeli osišgnięto dolnš lub górnš krawędŸ

	if (y_1 > windowHeight - rsize || y_1 - rsize < 0)

		ystep = -ystep;





	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno

	// zmniejszyło swoj wielkoœć w czasie, gdy kwadrat odbijał się od

	// krawędzi, co mogłoby spowodować, że znalazł by się poza

	// przestrzeniš ograniczajcš.

	if (x_1 > windowWidth - rsize)

		x_1 = windowWidth - rsize - 1;



	if (y_1 > windowHeight - rsize)

		y_1 = windowHeight - rsize - 1;



	// Wykonanie przesunięcia kwadratu

	x_1 += xstep;

	y_1 += ystep;



	// Ponowne rysowanie sceny z nowymi współrzędnymi

	glutPostRedisplay();

	glutTimerFunc(33, TimerFunction, 1);

}

///////////////////////////////////////////////////////////

// Konfigurowanie stanu renderowania

void SetupRC(void) {

	// Ustalenie niebieskiego koloru czyszczšcego

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

}

///////////////////////////////////////////////////////////

// Wywoływana przez bibliotek GLUT przy każdej zmianie wielkoœci okna

void ChangeSize(GLsizei w, GLsizei h) {

	// Zabezpieczenie przed dzieleniem przez zero

	if (h == 0)

		h = 1;



	// Ustalenie wielkoœci widoku zgodnego z rozmiarami okna

	glViewport(0, 0, w, h);



	// Ustalenie układu współrzędnych

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();



	// Keep the square square, this time, save calculated

	// width and height for later use

	if (w <= h)

	{

		windowHeight = 250.0f*h / w;

		windowWidth = 250.0f;

	}

	else

	{

		windowWidth = 250.0f*w / h;

		windowHeight = 250.0f;

	}



	// Ustanowienie przestrzeni ograniczajšcej (lewo, prawo, dół, góra, blisko, daleko)

	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);



	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

}

///////////////////////////////////////////////////////////

// Główny punkt wejœcia programu

void main(int argc, char* argv[]) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(800, 600);

	glutCreateWindow("Bounce");

	glutDisplayFunc(RenderScene);

	glutReshapeFunc(ChangeSize);

	glutTimerFunc(33, TimerFunction, 1);

	SetupRC();

	glutMainLoop();

}
//////////////////////////////////////////////////////////////////////////////// 
// Name - Khushi Chaudhary
// Scene - Tea-Shop
// 
// Interaction:
// Press the arrow keys to cycle through the objects.
// Press x, X, y, Y, z, Z to turn the objects.
// 
// References - 
// Sumant Guha
//////////////////////////////////////////////////////////////////////////////// 

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> 

// Globals.
static int objID = 1; // Object ID.

static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate objects.
//static char* objName; // Pointer to object name.

// Routine to draw a stroke character string.

void writeStrokeString(void* font, char* string)
{
	char* c;

	for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

// Routine to write object name.
void writeObjectName()
{
	glPushMatrix();
	glTranslatef(-4.5, 10.0, -20.0);
	glScalef(0.01, 0.01, 0.01);
	//writeStrokeString(GLUT_STROKE_ROMAN, objName);
	glPopMatrix();
}

// Drawing routine.

void drawlamps()
{	

	//Making Lamp one
	glRotatef(90, 3.0, 0, 0);
	glRotatef(180, 0, 3.0, 0);
	
	glTranslatef(3, -2.5, -5);
	glutWireCone(0.1, 8.0, 10, 30);

	glTranslatef(0, 0, 8);
	glutWireSphere(0.5,10,10);
	
	//Making Lamp two

	glTranslatef(-5, -5, -8);
	glutWireCone(0.1, 8.0, 10, 30);

	glTranslatef(0, 0, 8);
	glutWireSphere(0.5, 10, 10);
}

void drawHouse()
{
		// Draw objects.

		glutWireCube(10.0);
		//objName = "Wire Cube";

		glRotatef(90, 3.0, 0,0);
		glRotatef(180, 0, 3.0, 0);
		glTranslatef(0, 0, 5);
		glutWireCone(10.0, 8.0, 10, 30);
		//objName = "Wire Cone";

		glutWireCube(5.0);

		glTranslatef(0, 7.5, -7.5);
		glutWireCube(5.0);
		//objName = "Wire Cube";

		glRotatef(90, 3.0, 0,0);
		glTranslatef(0,5.0,0);
		glutWireTeapot(3.0);
		//objName = "Wire Teapot";

		glRotatef(90, 0, 3.0, 0);
		glTranslatef(-7.5, -2.5, 5);
		glutWireTorus(1, 2, 3, 190);
		//objName = "Wire Torus"

		glTranslatef(0, 0, -10);
		glutWireTorus(1, 2, 3, 190);
		//objName = "Wire Torus"

}

void drawTrees()
{

	// Draw Tree One
	glRotatef(35.26, 0, 3.0, 0);
	glTranslatef(15, -2.5, 8);
	glScalef(3.0, 3.0, 3.0);
	glutWireTetrahedron();

	glScalef(1.0, 1.0, 1.0);
	glTranslatef(0, 2, 0);
	glutWireDodecahedron();
	//objName = "Wire Dodecahedron";

	glScalef(1.0, 1.0, 1.0);
	//glutWireOctahedron();
	//objName = "Wire Octahedron";

	// Draw Tree two
	glTranslatef(-5, -2, 4);
	//glScalef(3.0, 3.0, 3.0);
	glutWireTetrahedron();

	glTranslatef(0, 2, 0);
	glutWireDodecahedron();

}
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Position the objects for viewing.
	gluLookAt(30.0, 25.0, 20.0, 0.0, 0.0, 0.0, 0,1,0);

	glLineWidth(2.0); // Thicken the wireframes.

					  // Commands to turn the objects.
	glPushMatrix();
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 1.0, 0.0, 0.0);

	// Draw objects.
		

	drawHouse();
	drawTrees();
	drawlamps();

		 
		//glScalef(5.0, 5.0, 5.0);
		//glutWireOctahedron();
		//objName = "Wire Octahedron";

		 
		//glScalef(5.0, 5.0, 5.0);
		//glutWireIcosahedron();
		//objName = "Wire Icosahedron";
		 
		 
	glPopMatrix();

	// Write label after disabling lighting.
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.0, 0.0);
	writeObjectName();
	glEnable(GL_LIGHTING);

	glutSwapBuffers();
}



// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

// Initialization routine.
void setup(void)
{
	// Material property vectors.
	float matSpec[] = { 0.0, 1.0, 1.0, 1.0 };
	float matShine[] = { 50.0 };
	float matAmbAndDif[] = { 0.0, 0.1, 1.0, 1.0 };

	// Light property vectors.
	float lightAmb[] = { 0.0, 0.1, 1.0, 1.0 };
	float lightDifAndSpec[] = { 0.0, 0.1, 1.0, 1.0 };
	float lightPos[] = { 0.0, 7.0, 3.0, 0.0 };
	float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

	// Material properties of the objects.
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matAmbAndDif);

	// Light0 properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// Poperties of the ambient light.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

	glEnable(GL_LIGHTING); // Enable lighting calculations.
	glEnable(GL_LIGHT0); // Enable particular light source.
	//glEnable(GL_DEPTH_TEST); // Enable depth testing.
	glEnable(GL_NORMALIZE); // Enable automatic normalization of normals.

	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle < 0.0) Xangle += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 0.0) Yangle += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 0.0) Zangle += 360.0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_DOWN)
	{
		if (objID > 1) objID--;
		else objID = 18;
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (objID > 1) objID--;
		else objID = 18;
	}
	if (key == GLUT_KEY_UP)
	{
		if (objID < 18) objID++;
		else objID = 1;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (objID < 18) objID++;
		else objID = 1;
	}

	Xangle = Yangle = Zangle = 0.0;
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the arrow keys to cycle through the objects." << std::endl
		<< "Press x, X, y, Y, z, Z to turn the objects." << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("glutObjects.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

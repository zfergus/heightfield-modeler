/*
 * GL3DWindow.h
 * Created by Zachary Ferguson
 * Header file for the GL3DWindow class, a class for creating an openGL Window 
 * and displaying 3d geometry
 */

#include "GL3DWindow.h"

/* Constructor for a GL3DWindow that takes the int aspects, a char* */
/* for the window label, and a Node3D for the root.                 */
GL3DWindow::GL3DWindow(int x, int y, int w, int h, const char* label, Mesh* 
	mesh,  bool drawEdges, bool drawFaces) : Fl_Gl_Window(x, y, w, h, label)
{
	this->mesh = NULL;
	this->setMesh(mesh);
	
	this->cam = new Camera(15, 0, 45, 0);

	this->drawEdges = drawEdges;
	this->drawFaces = drawFaces;

	this->selectedIndecies = NULL;
}
		
/* Destructor for this GL3DWindow, deletes the root and camera. */
GL3DWindow::~GL3DWindow()
{
	delete this->cam;
	delete this->mesh;
	delete this->selectedIndecies;
}

/* Sets this GL3DWindows Mesh to the given mesh. */
void GL3DWindow::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
	if(this->selectedIndecies)
	{
		delete this->selectedIndecies;		
	}
	this->selectedIndecies = NULL;
}

/* Sets whether or not to draw the edges of the mash. */
void GL3DWindow::setDrawEdges(bool drawEdges)
{
	this->drawEdges = drawEdges;
}

/* Sets whether or not to draw the faces of the mesh. */
void GL3DWindow::setDrawFaces(bool drawFaces)
{
	this->drawFaces = drawFaces;
}

/* Set the selected index of the mesh vertex. */
const std::vector<unsigned int>* GL3DWindow::selectMeshIndex(unsigned int row, 
	unsigned int col)
{
	assert(row < this->mesh->getRows() && col < this->mesh->getCols());
	
	if(this->selectedIndecies)
	{
		delete this->selectedIndecies;
	}
	
	this->selectedIndecies = new std::vector<unsigned int>();
	this->selectedIndecies->push_back(row);
	this->selectedIndecies->push_back(col);

	this->redraw();

	return this->selectedIndecies;
}

/* Set the selected index of the mesh vertex. */
const std::vector<unsigned int>* GL3DWindow::selectMeshIndex(
	std::vector<unsigned int>* indecies)
{
	if(indecies)
	{
		assert(indecies->size() == 2);
	}
	
	if(this->selectedIndecies)
	{
		delete this->selectedIndecies;	
		this->selectedIndecies = NULL;	
	}
	
	this->selectedIndecies = indecies;

	this->redraw();

	return this->selectedIndecies;
}

/* Get the selected index of the mesh vertex. */
const std::vector<unsigned int>* GL3DWindow::getSelectedMeshIndex() const
{
	return this->selectedIndecies;
}

/* Callback function for aligning the camera. */
void GL3DWindow::cameraAlignCB(Fl_Widget* w, void* data)
{
	GL3DWindow* gl3DWin = (GL3DWindow*)data;
	CameraControlButton* button = (CameraControlButton*)w;

	switch(button->getCameraPosition())
	{
		/* Front */
		case FRONT:
			delete gl3DWin->cam;
			gl3DWin->cam = new Camera(15, 0, 0, 0);
			break;
		/* Right */
		case RIGHT:
			delete gl3DWin->cam;
			gl3DWin->cam = new Camera(15, 90, 0, 0);
			break;
		/* Left */
		case LEFT:
			delete gl3DWin->cam;
			gl3DWin->cam = new Camera(15, -90, 0, 0);
			break;
		/* Back */
		case BACK:
			delete gl3DWin->cam;
			gl3DWin->cam = new Camera(15, 180, 0, 0);
			break;
		/* Above */
		case ABOVE:
			delete gl3DWin->cam;
			gl3DWin->cam = new Camera(15, 0, 90, 0);
			break;
	}

	gl3DWin->redraw();
}

/* Method in FL_GL_Window class for initializing the window. */
/* Initialize the required OpenGL transforms.                */
void GL3DWindow::init()
{
	/* Maps to Screen. */
	glViewport(0, 0, this->w(), this->h());
	
	/* Set the projection matrix. */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* gluPerspective(fovy, aspect, zNear, zFar) */
	gluPerspective(60, 1, 0.1, 100);
	
	/* Set the transformation matrix. */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

/* Method in FL_GL_Window class for drawing the window. */
/* Draws the 3D geometry out to the screen.             */
void GL3DWindow::draw()
{
	if (!valid())
	{
		init();
		valid(1);
	}
	glLoadIdentity();
	//glClearColor(0.067f, 0.067f, 0.067f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	vec4 eye = this->cam->getEye();
	vec4 up  = this->cam->getUp();
	/* Look at the center */
	gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, up[0], up[1], up[2]);

	/* X-axis */
	glColor3f(GREEN);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-100, 0, 0);
		glVertex3f( 100, 0, 0);
	glEnd();

	/* Y-axis */
	glColor3f(BLUE);
	glBegin(GL_LINE_LOOP);
		glVertex3f(0, -100, 0);
		glVertex3f(0,  100, 0);
	glEnd();

	/* Z-axis */
	glColor3f(RED);
	glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, -100);
		glVertex3f(0, 0, 100);
	glEnd();

	/* Draw out the selection box. */
	if(this->selectedIndecies)
	{
		vec4 v = this->mesh->getVertex(selectedIndecies->at(0),
			selectedIndecies->at(1));
		float x = v[0]; 
		float y = v[1];
		float z = v[2];

		/* Draw a square around the slected vertex. */
		glColor3f(ORANGE);
		glBegin(GL_LINE_LOOP);
			glVertex3f(x-0.5f, y, z-0.5f);
			glVertex3f(x-0.5f, y, z+0.5f);
			glVertex3f(x+0.5f, y, z+0.5f);
			glVertex3f(x+0.5f, y, z-0.5f);
		glEnd();
		//glBegin(GL_LINE_LOOP);
		//	glVertex3f(x, y+0.5f, z+0.5f);
		//	glVertex3f(x, y-0.5f, z+0.5f);
		//	glVertex3f(x, y-0.5f, z-0.5f);
		//	glVertex3f(x, y+0.5f, z-0.5f);
		//glEnd();
		//glBegin(GL_LINE_LOOP);
		//	glVertex3f(x-0.5f, y+0.5f, z);
		//	glVertex3f(x-0.5f, y-0.5f, z);
		//	glVertex3f(x+0.5f, y-0.5f, z);
		//	glVertex3f(x+0.5f, y+0.5f, z);
		//glEnd();
	}

	this->mesh->draw(this->drawEdges, this->drawFaces);
}
		
/* Method in FL_GL_Window class for handling FLTK events. */
/* Moves the camera around according to key presses.      */
int GL3DWindow::handle(int event)
{
	/* If key held down. */
	if (event == FL_KEYDOWN)
	{
		this->handleKeys();
	}

	return Fl_Gl_Window::handle(event);
}

/* Handles the key press event for this GL3DWindow. */
void GL3DWindow::handleKeys()
{
	/* Switch on the key being pressed. */
	switch(Fl::event_key())
	{
		/* Rotate Up */
		case 'w':
			this->cam->increasePhi(DELTAANGLE);
			break;
		/* Rotate Left */
		case 'a':
			this->cam->increaseTheta(-DELTAANGLE);
			break;
		/* Rotate Down */
		case 's':
			this->cam->increasePhi(-DELTAANGLE);
			break;
		/* Rotate Right */
		case 'd':
			this->cam->increaseTheta(DELTAANGLE);
			break;
		/* Roll Counter-clockwise */
		case 'e':
			this->cam->increaseRoll(-DELTAANGLE);
			break;
		/* Roll Clockwise */
		case 'q':
			this->cam->increaseRoll(DELTAANGLE);
			break;
		/* Decrease Radius */
		case SHIFTKEY:
			this->cam->increaseRad(-DELTARADIUS);
			break;
		/* Increase Radius */
		case CTRLKEY:
			this->cam->increaseRad(DELTARADIUS);
			break;
		//default:
		//	std::cout << Fl::event_key() << std::endl;
	}
	this->redraw();
}

/* In the event of a FL_PUSH, this method can be used to get a ray from the */
/* event x and y into the world.                                            */
ray GL3DWindow::getRayFromPush() const
{
	vec3 eye = this->cam->getEye();
	vec3 camView = -1*eye;
	float camDist = camView.length();
	vec3 up = this->cam->getUp();
	float theta = 60;
	float phi = 60;

	/* Step 1: Compute the horizontal screen vector, H, at the point E. */
	vec3 camH = camView%up;
	vec3 horizontal = (camH*camDist*tan(theta))/(camH.length());
	/* Step 2: Compute the vertical screen vector, V, at the point E. */
	vec3 camV = camH % camView;
	vec3 vertical = ((camV)*camDist*tan(phi))/(camV.length());
	/* Step 3: Compute the midpoint of the screen, M. */
	vec3 midpoint = eye + camView;
	/* Step 4: Compute P, the point in world 2D coordinates that the user */
	/* points at, given the point in Normalized Device Coordinates,       */
	/* (sx, sy), where 0 <= sx <= 1 and 0 <= sy <= 1.                     */
	float sx = ((float)(Fl::event_x()-this->x()) / this->w());
	float sy = 1 - ((float)(Fl::event_y()-this->y()) / this->h());
	vec4 selected = 2*(midpoint + (2 * sx - 1)*horizontal + (2 * sy - 1)*
		vertical);
	/* Step 5: Compute the ray equation, R. */
	return ray(eye, selected);
}
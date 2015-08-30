/*
 * GL3DWindow.h
 * Created by Zachary Ferguson
 * Header file for the GL3DWindow class, a class for creating an openGL Window 
 * and displaying 3d geometry
 */

#ifndef GL3DWINDOW_H
#define GL3DWINDOW_H

/* Include necessary types */
#include <FL/Fl.H>
#include <Fl/Fl_Gl_Window.h>
#include <GL/glu.h>
#include "ray.h"
#include "Mesh.h"
#include "Camera.h"
#include "CameraControlButton.h"

#define DELTARADIUS 1
#define DELTAANGLE 5
#define SHIFTKEY 65505
#define CTRLKEY 65507

/* Child class of FL_GL_Window */
class GL3DWindow : public Fl_Gl_Window
{
	private:
		
		/* Pointer to the camera in the 3D space. */
		Camera* cam;

		/* 3D Mesh to draw out to the screen. */
		Mesh* mesh;

		/* Booleans for if the elements should be drawn. */
		bool drawEdges, drawFaces;

		/* Method in FL_GL_Window class for initializing the window. */
		/* Initialize the required OpenGL transforms.                */
		void init();		
		
		/* Method in FL_GL_Window class for drawing the window. */
		/* Draws the 3D geometry out to the screen.             */
		void draw();

		/* Handles the key press event for this GL3DWindow. */
		void handleKeys();

		std::vector<unsigned int>* selectedIndecies;

	public:

		/* Constructor for a GL3DWindow that takes the int aspects, a char* */
		/* for the window label, and a Node3D for the root.                 */
		GL3DWindow(int x, int y, int w, int h, const char* label, 
			Mesh* mesh, bool drawEdges, bool drawFaces);
		
		/* Destructor for this GL3DWindow, deletes the root and camera. */
		virtual ~GL3DWindow();

		/* Sets this GL3DWindows Mesh to the given mesh. */   
		void setMesh(Mesh* mesh);

		/* Sets whether or not to draw the edges of the mash. */
		void setDrawEdges(bool drawEdges);
		/* Sets whether or not to draw the faces of the mesh. */
		void setDrawFaces(bool drawFaces);

		/* Set the selected index of the mesh vertex. */
		const std::vector<unsigned int>* selectMeshIndex(unsigned int row, 
			unsigned int col);
		/* Set the selected index of the mesh vertex. */
		const std::vector<unsigned int>* selectMeshIndex(
			std::vector<unsigned int>* indecies);
		/* Get the selected index of the mesh vertex. */
		const std::vector<unsigned int>* getSelectedMeshIndex() const;

		/* Callback function for aligning the camera. */
		static void cameraAlignCB(Fl_Widget* w, void* data);
		/* Callback function for selecting a vertex in the mesh. */
		static void selectIndexCB(Fl_Widget* w, void* data);


		/* Method in FL_GL_Window class for handling FLTK events. */
		/* Moves the camera around according to key presses.      */
		int handle(int event);

		/* In the event of a FL_PUSH, this method can be used to get a ray */
		/* from the event x and y into the world.                          */
		ray getRayFromPush() const;
};

#endif
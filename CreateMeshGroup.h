/*
 * CreateMeshGroup.h
 * Created by Zachary Ferguson
 * Header for the CreateMeshGroup class, a child class of the Fl_Group class
 * for getting the properties of a new mesh.
 */

#ifndef CREATEMESHGROUP_H
#define CREATEMESHGROUP_H

#define _CRT_SECURE_NO_WARNINGS

#include <FL/Fl_Group.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Color_Chooser.H>
#include "Color.h"

class CreateMeshGroup : public Fl_Group
{
	private:
	
		/* Spinners for the values of the new mesh. */
		Fl_Spinner* rows;
		Fl_Spinner* cols;
		Fl_Spinner* width;
		Fl_Spinner* depth;

		/* Color chooser for the color of the new mesh. */
		//Fl_Color_Chooser* color;

		/* Button to generate a new mesh. */
		Fl_Button* generateB;

	public:
		
		/* Constructor for creating a new CreateMesh_Widget.                */
		/* Requires the x,y coordinates of the new CreateMesh_Widget.       */
		/* Also requires the starting values for the rows, cols, width, and */
		/* depth spinners.                                                  */
		CreateMeshGroup(int x, int y, int rows, int cols, float width, float
			depth);

		/* Destructor for this CreateMesh_Widget. */
		virtual ~CreateMeshGroup();

		/* Sets the callback function to cb with an argument of p. */
		void callback(Fl_Callback* cb, void *p);

		/* Accessor methods */
		int getRowsValue();
		int getColsValue();
		float getWidthValue();
		float getDepthValue();
		//Color* getColorValue();
};

#endif
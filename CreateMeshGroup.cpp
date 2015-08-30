/*
 * CreateMeshGroup.h
 * Created by Zachary Ferguson
 * Source file for the CreateMeshGroup class, a child class of the Fl_Group 
 * class for getting the properties of a new mesh.
 */

#include "CreateMeshGroup.h"

/* Constructor for creating a new CreateMesh_Widget.                      */
/* Requires the x,y coordinates of the new CreateMesh_Widget.             */
/* Also requires the starting values for the rows, cols, width, and depth */
/* spinners.                                                              */
CreateMeshGroup::CreateMeshGroup(int x, int y, int rows, int cols, float width,
	float depth) : Fl_Group(x, y, 220, 230)
{
	Fl_Group* settings = new Fl_Group(x, y, 110, 170, "New Mesh\nSettings");
    settings->box(FL_ENGRAVED_FRAME);
	settings->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));

	this->rows = new Fl_Spinner(x+51, y+45, 52, 24, "Rows:");
    this->rows->maximum(99);
    this->rows->value(rows);
	
	this->cols = new Fl_Spinner(x+51, y+75, 52, 24, "Cols:");
    this->cols->maximum(99);
    this->cols->value(cols);

	this->width = new Fl_Spinner(x+51, y+105, 52, 24, "Width:");
	this->width->type(1);
	this->width->minimum(0.5);
	this->width->maximum(99);
	this->width->step(0.5);
	this->width->value(width);

	this->depth = new Fl_Spinner(x+51, y+135, 52, 24, "Depth:");
	this->depth->type(1);
	this->depth->minimum(0.5);
	this->depth->maximum(99);
	this->depth->step(0.5);
	this->depth->value(depth);

	//this->color = new Fl_Color_Chooser(x+10, y+85, 192, 100);
	//this->color->rgb(BLUE);

	settings->end();

	this->generateB = new Fl_Button(x, y+175, 110, 24, "Generate Mesh");

	this->end();
}

/* Destructor for this CreateMesh_Widget. */
CreateMeshGroup::~CreateMeshGroup()
{
	delete this->rows;
	delete this->cols;
	delete this->width;
	delete this->depth;
	//delete this->color;
	delete this->generateB;
}

/* Sets the callback function to cb with an argument of p. */
void CreateMeshGroup::callback(Fl_Callback* cb, void *p)
{
	this->generateB->callback(cb, p);
}

/********************/
/* Accessor methods */
/********************/

int CreateMeshGroup::getRowsValue()
{
	return (int)(this->rows->value());
}

int CreateMeshGroup::getColsValue()
{
	return (int)(this->cols->value());
}

float CreateMeshGroup::getWidthValue()
{
	return (float)(this->width->value());
}

float CreateMeshGroup::getDepthValue()
{
	return (float)(this->depth->value());
}

//Color* CreateMeshGroup::getColorValue()
//{
//	return new Color((float)this->color->r(), (float)this->color->g(), 
//		(float)this->color->b());
//}
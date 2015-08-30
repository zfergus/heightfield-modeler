/*
 * ViewModeGroup.cpp
 * Created by Zachary Ferguson
 * Source file for the ViewModeGroup class, a child class of the Fl_Group class
 * for getting the viewing mode.
 */

#include "ViewModeGroup.h"

/* Constructor for creating a new CreateMesh_Widget.          */
/* Requires the x,y coordinates of the new CreateMesh_Widget. */
ViewModeGroup::ViewModeGroup(int x, int y) : Fl_Group(x, y, 110, 115, 
	"Viewing Modes")
{
	/* Group for how to draw the mesh. */
	this->box(FL_ENGRAVED_FRAME);
    this->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
	
	/* Display wire frame button. */
	this->wireframeB = new Fl_Round_Button(x+10, y+20, 89, 24, "Wireframe");
	this->wireframeB->type(102);
    this->wireframeB->down_box(FL_ROUND_DOWN_BOX);
	
	/* Display solid button. */
	this->solidB = new Fl_Round_Button(x+10, y+50, 89, 24, "Solid");
    this->solidB->type(102);
    this->solidB->down_box(FL_ROUND_DOWN_BOX);
    
	/* Display both button. */
	this->bothB = new Fl_Round_Button(x+10, y+80, 89, 24, "Both");
	this->bothB->value(1);
	this->bothB->type(102);
    this->bothB->down_box(FL_ROUND_DOWN_BOX);

	this->end();
}

/* Destructor for this CreateMesh_Widget. */
ViewModeGroup::~ViewModeGroup()
{
	/* Delete the child buttons. */
	delete this->wireframeB;
	delete this->solidB;
	delete this->bothB;
}

/* Sets the callback function to cb with an argument of p. */
void ViewModeGroup::callback(Fl_Callback* cb, void *p)
{
	/* Set the callbacks of the children. */
	this->wireframeB->callback(cb, p);
	this->solidB->callback(cb, p);
	this->bothB->callback(cb, p);
}

/* Get the viewing mode. Returns a ViewingMode enum value. */
ViewingMode ViewModeGroup::getViewMode()
{
	if(this->wireframeB->value())
	{
		return WIREFRAME;
	}
	else if(this->solidB->value())
	{
		return SOLID;
	}
	return BOTH;
}

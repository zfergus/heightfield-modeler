/*
 * CameraControlGroup.h
 * Created by Zachary Ferguson
 * Header for the CameraControlGroup class, a child class of the Fl_Group class
 * for setting the camera to a preset position.
 */

#include "CameraControlGroup.h"

/* Constructor for creating a new CameraControlGroup.          */
/* Requires the x,y coordinates of the new CameraControlGroup. */
CameraControlGroup::CameraControlGroup(int x, int y) : Fl_Group(x, y, 180, 115,
	"Camera Aligns")
{
	this->box(FL_ENGRAVED_FRAME);
	this->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
  
	this->rightB = new CameraControlButton(x+120, y+55, 48, 24, "Right", 
		RIGHT);

	this->frontB = new CameraControlButton( x+65, y+85, 48, 24, "Front", 
		FRONT);
  
	this->leftB  = new CameraControlButton( x+10, y+55, 48, 24,  "Left", 
		LEFT);
  
	this->backB  = new CameraControlButton( x+65, y+25, 48, 24,  "Back",
		BACK);
  
	this->aboveB = new CameraControlButton( x+65, y+55, 48, 24, "Above", 
		ABOVE);

	this->end();
}

/* Destructor for this CameraControlGroup. */
CameraControlGroup::~CameraControlGroup()
{
	delete this->rightB;
	delete this->leftB;
	delete this->frontB;
	delete this->backB;
	delete this->aboveB;
}

/* Sets the callback function to cb with an argument of p. */
void CameraControlGroup::callback(Fl_Callback* cb, void *p)
{
	this->rightB->callback(cb, p);
	this->leftB->callback(cb, p);
	this->frontB->callback(cb, p);
	this->backB->callback(cb, p);
	this->aboveB->callback(cb, p);
}
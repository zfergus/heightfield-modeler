/*
 * CameraControlButton.cpp
 * Created by Zachary Ferguson
 * Source file for the CameraControlButton class, a child class of the 
 * Fl_Button class for setting the camera to a preset position.
 */

#include "CameraControlButton.h"

/* Constructor for creating a new CameraControlGroup.          */
/* Requires the x,y coordinates of the new CameraControlGroup. */
CameraControlButton::CameraControlButton(int x, int y, int h, int w, 
	const char* label, CameraPosition position) : Fl_Button(x, y, h, w, label)
{
	this->position = position;
}

/* Destructor for this CameraControlGroup. */
CameraControlButton::~CameraControlButton(){}

/* Sets the current camera position to the given one. */
void CameraControlButton::setCameraPosition(CameraPosition position)
{	
	this->position = position;
}

/* Returns the current camera position for this CameraControlButton. */
CameraPosition CameraControlButton::getCameraPosition()
{
	return this->position;
}
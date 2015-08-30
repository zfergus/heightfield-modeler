/*
 * CameraControlButton.h
 * Created by Zachary Ferguson
 * Header for the CameraControlButton class, a child class of the Fl_Button 
 * class for setting the camera to a preset position.
 */

#ifndef CAMERACONTROLBUTTON_H
#define CAMERACONTROLBUTTON_H

#include <FL/Fl_Button.h>

enum CameraPosition { RIGHT, LEFT, FRONT, BACK, ABOVE, BELOW };

class CameraControlButton : public Fl_Button
{
	private:
	
		/* This CameraControlButton's viewing position value. */
		CameraPosition position;

	public:
		
		/* Constructor for creating a new CameraControlGroup.          */
		/* Requires the x,y coordinates of the new CameraControlGroup. */
		CameraControlButton(int x, int y, int h, int w, const char* label, 
			CameraPosition position);

		/* Destructor for this CameraControlGroup. */
		virtual ~CameraControlButton();

		/* Sets the current camera position to the given one. */
		void setCameraPosition(CameraPosition position);

		/* Returns the current camera position for this CameraControlButton. */
		CameraPosition getCameraPosition();
};

#endif
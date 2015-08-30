/*
 * CameraControlGroup.h
 * Created by Zachary Ferguson
 * Header for the CameraControlGroup class, a child class of the Fl_Group class
 * for setting the camera to a preset position.
 */

#ifndef CAMERACONTROLGROUP_H
#define CAMERACONTROLGROUP_H

#include <FL/Fl_Group.H>
#include "CameraControlButton.h"

class CameraControlGroup : public Fl_Group
{
	private:
	
		/* Fl_Buttons for the different preset camera positions. */
		CameraControlButton* rightB;
		CameraControlButton* leftB;
		CameraControlButton* frontB;
		CameraControlButton* backB;
		CameraControlButton* aboveB;

	public:
		
		/* Constructor for creating a new CameraControlGroup.          */
		/* Requires the x,y coordinates of the new CameraControlGroup. */
		CameraControlGroup(int x, int y);

		/* Destructor for this CameraControlGroup. */
		virtual ~CameraControlGroup();

		/* Sets the callback function to cb with an argument of p. */
		void callback(Fl_Callback* cb, void *p);
};

#endif
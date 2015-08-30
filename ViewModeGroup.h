/*
 * ViewModeGroup.h
 * Created by Zachary Ferguson
 * Header for the ViewModeGroup class, a child class of the Fl_Group class
 * for getting the viewing mode.
 */

#ifndef VIEWMODEGROUP_H
#define VIEWMODEGROUP_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.h>

enum ViewingMode { WIREFRAME, SOLID, BOTH };

class ViewModeGroup : public Fl_Group
{
	private:
	
		/* Fl_Round_Buttons for the different view options. */
		Fl_Round_Button* wireframeB;
		Fl_Round_Button* solidB;
		Fl_Round_Button* bothB;

	public:
		
		/* Constructor for creating a new ViewModeGroup.          */
		/* Requires the x,y coordinates of the new ViewModeGroup. */
		ViewModeGroup(int x, int y);

		/* Destructor for this ViewModeGroup. */
		virtual ~ViewModeGroup();

		/* Sets the callback function to cb with an argument of p. */
		void callback(Fl_Callback* cb, void *p);

		/* Get the viewing mode. Returns a ViewingMode enum value. */
		ViewingMode getViewMode();
};

#endif
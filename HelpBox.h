/*
 * HelpBox.h
 * Created by Zachary Ferguson
 * Header for the HelpBox class, a sub-class of the Fl_Window class for 
 * displaying help information.
 */

#ifndef HELPBOX_H
#define HELPBOX_H

#include <fstream>
#include <sstream>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Return_Button.H>

class HelpBox : public Fl_Window
{
	private:
		
		Fl_Text_Display *helpText;

	public:
		
		/* Requaires the new windows x, y coords and width and height. Also */
		/* requires the filename of the help file. Optionally requires a    */
		/* window label.                                                    */
		HelpBox(int x, int y, int w, int h, const char* helpFilename, 
			const char* label = NULL);
		
		/* Deconstructor. */
		~HelpBox();
};

#endif
/*
 * HeightEditorGroup.h
 * Created by Zachary Ferguson
 * Header for the HeightEditorGroup class, a child class of the Fl_Group class
 * for selecting vertices and setting the height of a height field.
 */

#ifndef HEIGHTEDITORGROUP_H
#define HEIGHTEDITORGROUP_H

#define _CRT_SECURE_NO_WARNINGS

#include <cfloat>
#include <FL/Fl_Group.H>
#include <FL/Fl_Spinner.h>
#include <FL/Fl_Value_Slider.h>

class HeightEditorGroup : public Fl_Group
{
	private:
	
		/* Fl_Buttons for the different preset camera positions. */
		Fl_Value_Slider* heightSlider;
		Fl_Spinner* rowSpinner;
		Fl_Spinner* colSpinner;

	public:
		
		/* Constructor for creating a new HeightEditorGroup.                 */
		/* Requires the x,y coordinates of the new HeightEditorGroup, as     */
		/* well as the number of rows and cols for the spinners' max values. */
		HeightEditorGroup(int x, int y, unsigned int rows, unsigned int cols);

		/* Destructor for this CameraControlGroup. */
		virtual ~HeightEditorGroup();

		/* Sets the callback function for the spinners to cb with an */
		/* argument of p.                                            */
		void indexCallback(Fl_Callback* cb, void *p);
		/* Sets the callback function for the height slider to cb with an */
		/* argument of p.                                                 */
		void heightCallback(Fl_Callback* cb, void *p);

		/* Accessor Methods */
		const unsigned int getRow() const;
		const unsigned int getCol() const;
		const float getHeight() const;

		/* Set the values for the spinners */
		void setRow(const unsigned int row);
		void setCol(const unsigned int col);
		void setHeight(const float height);
		/* Set the max values for the spinners */
		void setRows(const unsigned int rows);
		void setCols(const unsigned int cols);
};

#endif
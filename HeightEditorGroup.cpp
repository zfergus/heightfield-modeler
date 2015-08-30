/*
 * HeightEditorGroup.cpp
 * Created by Zachary Ferguson
 * Source file for the HeightEditorGroup class, a child class of the Fl_Group
 * class for selecting vertices and setting the height of a height field.
 */

#include "HeightEditorGroup.h"

/* Constructor for creating a new HeightEditorGroup.                         */
/* Requires the x,y coordinates of the new HeightEditorGroup, as well as the */
/* number of rows and cols for the spinners' max values.                     */
HeightEditorGroup::HeightEditorGroup(int x, int y, unsigned int rows, 
	unsigned int cols) : Fl_Group(x, y, 290, 80, "Edit Vertex")
{
	this->box(FL_ENGRAVED_FRAME);
	this->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));

	/* Create height slider */
	this->heightSlider = new Fl_Value_Slider(x+85, y+50, 198, 24, "Height");
	this->heightSlider->type(1);
	this->heightSlider->box(FL_BORDER_BOX);
	this->heightSlider->minimum(-25);
	this->heightSlider->maximum(25);
	this->heightSlider->step(0.1);
	this->heightSlider->align(Fl_Align(FL_ALIGN_TOP));
	
	/* Create row spinner */
	this->rowSpinner = new Fl_Spinner(x+30, y+20, 48, 24, "Row");
	this->rowSpinner->minimum(0);
	this->rowSpinner->maximum(rows-1);
	this->rowSpinner->value(0);
	this->rowSpinner->align(Fl_Align(FL_ALIGN_TOP));
	
	/* Create column spinner */
	this->colSpinner = new Fl_Spinner(x+30, y+50, 48, 24, "Col");
	this->colSpinner->minimum(0);
	this->colSpinner->maximum(cols-1);
	this->colSpinner->value(0);

	this->end();
}

/* Destructor for this CameraControlGroup. */
HeightEditorGroup::~HeightEditorGroup()
{
	delete this->heightSlider;
	delete this->rowSpinner;
	delete this->colSpinner;
}

/* Sets the callback function for the spinners to cb with an argument of p. */
void HeightEditorGroup::indexCallback(Fl_Callback* cb, void *p)
{
	this->rowSpinner->callback(cb, p);
	this->colSpinner->callback(cb, p);
}

/* Sets the callback function for the height slider to cb with an argument */
/* of p.                                                                   */
void HeightEditorGroup::heightCallback(Fl_Callback* cb, void *p)
{
	this->heightSlider->callback(cb, p);
}

/* Accessor Methods */

const unsigned int HeightEditorGroup::getRow() const
{
	return (int)this->rowSpinner->value();
}

const unsigned int HeightEditorGroup::getCol() const
{
	return (int)this->colSpinner->value();
}

const float HeightEditorGroup::getHeight() const
{
	return (float)this->heightSlider->value();
}

/* Set the values for the spinners */

void HeightEditorGroup::setRow(const unsigned int row)
{
	this->rowSpinner->value(row);
}

void HeightEditorGroup::setCol(const unsigned int col)
{
	this->colSpinner->value(col);
}

void HeightEditorGroup::setHeight(const float height)
{
	this->heightSlider->value(height);
}

/* Set the max values for the spinners */

void HeightEditorGroup::setRows(const unsigned int rows)
{
	this->rowSpinner->maximum(rows-1);
}

void HeightEditorGroup::setCols(const unsigned int cols)
{
	this->colSpinner->maximum(cols-1);
}
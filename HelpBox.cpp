/*
 * HelpBox.cpp
 * Created by Zachary Ferguson
 * Source file for the HelpBox class, a sub-class of the Fl_Window class for 
 * displaying help information.
 */

#include "HelpBox.h"

/* Requaires the new windows x, y coords and width and height. Also */
/* requires the filename of the help file. Optionally requires a    */
/* window label.                                                    */
HelpBox::HelpBox(int x, int y, int w, int h, const char* helpFilename, 
	const char* label) : Fl_Window(x, y, w, h, label)
{
	this->helpText = new Fl_Text_Display(10, 10, w-20, h-20);
	this->helpText->textfont(4);
	/* Attempt to read in the help text. */
	std::ifstream helpFile(helpFilename);
	if(helpFile)
	{
		std::string line;
		std::stringstream helpStr;
		while(std::getline(helpFile, line))
		{
			helpStr << line << std::endl;
		}
		//std::cout << helpStr.str().c_str() << std::endl;

		Fl_Text_Buffer *buff = new Fl_Text_Buffer();
		this->helpText->buffer(buff);
		buff->text(helpStr.str().c_str()); 

		helpFile.close();
	}

	this->end();
}

/* Deconstructor. */
HelpBox::~HelpBox()
{
	delete this->helpText;
}
/*
 * Color.cpp
 * Created by Zachary Ferguson
 * Source file for the definitions of the Color class.
 */

#include "Color.h"

/* Constructor that takes a red, green, and blue value. */
Color::Color(float red, float green, float blue)
{
	/* Sets the color to the one given. */
	this->setColor(red, green, blue);
}
		
/* Deconstructor */
Color::~Color(){}
		
/* Set the colors or a specific color. */
void Color::setColor(float red, float green, float blue)
{
	/* Check that the color values are valid */
	this->setRed(red);
	this->setGreen(green);
	this->setBlue(blue);
}

void Color::setRed(float red)
{
	/* Check that the color value given is valid */
	assert(red >= 0.0 && red <= 1.0);
	this->red = red;
}

void Color::setGreen(float green)
{
	/* Check that the color value given is valid */
	assert(green >= 0.0 && green <= 1.0);
	this->green = green;
}

void Color::setBlue(float blue)
{
	/* Check that the color value given is valid */
	assert(blue >= 0.0 && blue <= 1.0);
	this->blue = blue;
}

/* Get all the colors as a vector or just a single color as a float. */
const std::vector<float> Color::getColor() const
{
	return{ this->getRed(), this->getGreen(), this->getBlue() };
}

const float Color::getRed() const
{
	return this->red;
}

const float Color::getGreen() const
{
	return this->green;
}

const float Color::getBlue() const
{
	return this->blue;
}

/* Convert this color to a string representation of the format "r g b". */
std::string Color::toString() const
{
	/* Makes the string representation of the vector. */
	std::stringstream strStream;
	/* set the precision to 4 */
	strStream.precision(4);

	strStream << this->red << " " << this->green << " " << this->blue;

	return strStream.str();
}
/*
 * Face.h
 * Created by Zachary Ferguson
 * Header file for the Color class, a simple class that stores a RGB value.
 */

#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include <sstream>
#include <assert.h>

/* Primary Colors */
#define RED 1, 0, 0
#define YELLOW 1, 1, 0
#define BLUE 0, 0, 1
/* Secondary Colors */
#define ORANGE 1, 0.4f, 0
#define GREEN 0, 1, 0
#define PURPLE 0.5, 0, 0.5
/* Gray Scale */
#define BLACK 0, 0, 0
#define DARK_GREY 0.25f, 0.25f, 0.25f
#define GREY 0.5, 0.5, 0.5
#define LIGHT_GREY 0.75f, 0.75f, 0.75f
#define WHITE 1.0, 1.0, 1.0

class Color
{
	private:
		
		float red, green, blue;
	
	public:
	
		/* Constructor that takes a red, green, and blue value. */
		Color(float red, float green, float blue);
		
		/* Deconstructor */
		virtual ~Color();
		
		/* Set the colors or a specific color. */
		void setColor(float red, float green, float blue);
		void setRed(float red);
		void setGreen(float green);
		void setBlue(float blue);

		/* Get all the colors as a vector or just a single color as a float. */
		const std::vector<float> getColor() const;
		const float getRed() const;
		const float getGreen() const;
		const float getBlue() const;

		/* Convert this color to a string representation of the format */
		/* "r g b".                                                    */
		std::string toString() const;
};

#endif
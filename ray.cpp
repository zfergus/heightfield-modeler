/*
 * ray.cpp
 * Created by Zachary Ferguson
 * Source file for the ray class that represents a ray in 3D space.
 */

#include "ray.h"

/* Creates a new ray with the given camera eye and point selected. */
ray::ray(vec4 eye, vec4 pointSelected)
{
	this->eye = eye;
	this->pointSelected = pointSelected;
}

/* Gets the rays position at the given t. */
vec4 ray::value(float t)
{
	vec4 dif = this->pointSelected - this->eye;
	return (this->eye + (t*(dif)) / (dif.length()));
}

/* Returns the point of origin for this vector. */
vec4 ray::origin()
{
	return this->pointSelected;
}
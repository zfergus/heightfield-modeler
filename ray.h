/*
 * ray.h
 * Created by Zachary Ferguson
 * Header for the ray class that represents a ray in 3D space.
 */

#ifndef RAY_H
#define RAY_H

#include "vec4.h"

class ray
{
	private:
		
		vec4 eye;
		vec4 pointSelected;

	public:
		
		/* Creates a new ray with the given camera eye and point selected. */
		ray(vec4 eye, vec4 pointSelected);
		
		/* Gets the rays position at the given t. */
		vec4 value(float t);

		/* Returns the point of origin for this vector. */
		vec4 origin();
};

#endif
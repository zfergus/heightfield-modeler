/*
 * vec4.h
 * Created by Zachary Ferguson
 * Header file for the vec4 class, a 4 dimensional vector.
 */

#ifndef VEC4_H
#define VEC4_H

#include <sstream>  /* Used to create a string representation.     */
#include <string>   /* Used for the return of the toString mathod. */
#include "vec3.h"   /* Include 3D vector for type conversion.      */

class vec3;

class vec4
{
	private:
	
		float data[4];

	public:

		/****************/
		/* Constructors */
		/****************/
		/* Defaults all value to 0. */
		vec4();

		/* Converts vec3 to vec4 with t = 0. */
		vec4(vec3 v);

		/* Set the values of this vector to the given floats. */
		vec4(float x, float y, float z, float t);
	
		/*********************/
		/* Getters & Setters */
		/*********************/
		/* Returns the value at index. */
		float operator[](unsigned int index) const;
	
		/* Returns a reference to the value at index. */
		float& operator[](unsigned int index);

		/**********************/
		/* Display the Vector */
		/**********************/
		/* Prints the vector to standard output in a nice format. */
		void print();
		/* Returns a string representation of this vector. */
		std::string toString();

		/*********************/
		/* Vector Operations */
		/*********************/
		/* Returns the geometric length of the vector. */
		float length() const;
		
		/** Friend Functions **/
		
		/* Checks if v1 == v2 */
		friend bool operator==(const vec4& v1, const vec4& v2);
	
		/* Checks if v1 != v2 */
		friend bool operator!=(const vec4& v1, const vec4& v2);
	
		/* Vector Addition (v1 + v2) */
		friend vec4 operator+ (const vec4& v1, const vec4& v2);
	
		/* Vector Subtraction (v1 - v2) */
		friend vec4 operator- (const vec4& v1, const vec4& v2);
	
		/* Scalar Multiplication (v * c) */
		friend vec4 operator* (const vec4& v, float c);	
	
		/* Scalar Multiplication (c * v) */
		friend vec4 operator* (float c, const vec4& v);
	
		/* Scalar Division (v/c) */
		friend vec4 operator/ (const vec4& v, float c);
	
		/* Dot Product (v1 * v2) */
		friend float operator* (const vec4& v1, const vec4& v2);
	
		/* Cross Product (v1 % v2)          */
		/* No such operation on 4D vectors. */
		//friend vec4 operator% (const vec4& v1, const vec4& v2);
};

#endif
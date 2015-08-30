/*
 * amt4.h
 * Created by Zachary Ferguson
 * Header file for the mat4 class, a 4x4 matrix.
 */
 
#ifndef MAT4_H
#define MAT4_H

#include "vec4.h" /* Used to store vec4's in the mat4.  */
#include "mat3.h" /* Used to convert to 3x3.            */
#include <cmath>  /* Need to get float trig. functions. */

class mat4
{
	private:
		
		vec4 data[4];
	
	public:
		
		/****************/
		/* Constructors */
		/****************/
		/* Default Constructor.            */
		/* Initialize to matrix of all 0s. */
		mat4();

		/* Initializes matrix with each vector representing a row in the */
		/* matrix.                                                       */
		mat4(const vec4& row1, const vec4& row2, const vec4& row3, 
			const vec4& row4);
		
		/***********************/
		/* Static Initializers */
		/***********************/
	
		/* Creates a 4-D homogeneous rotation matrix.                   */
		/* Takes an angle in degrees and outputs a 4x4 rotation matrix. */
		static mat4 rotation3D(float angle, const vec3& axisOfRotation);
		
		/* Takes an x, y, and z displacement and outputs a 4x4 translation */
		/* matrix.                                                         */
		static mat4 translation3D(float x, float y, float z);
		
		/* Takes an x, y, and z scale and outputs a 4x4 scale matrix. */
		static mat4 scale3D(float x, float y, float z);
		
		/* Generates a 4x4 identity matrix. */
		static mat4 identity();	
		
		/*********************/
		/* Getters & Setters */
		/*********************/	
		/* Returns the values of the row at the index */
		vec4 operator[](unsigned int index) const;
		
		/* Returns a reference to the row at the index */
		vec4& operator[](unsigned int index);
		
		/* Returns a column of the matrix */
		vec4 getColumn(unsigned int index) const;

		/**********************/
		/* Display the Matrix */
		/**********************/
		/* Prints the matrix to standard output in a nice format */
		void print();
		/* Returns a string representation of this vector. */		
		std::string toString();
		
		/*********************/
		/* Matrix Operations */
		/*********************/	
		/* Returns the transpose of the matrix (v_ij == v_ji) */
		mat4 transpose() const;

		/** Friend Functions **/

		/* Checks if m1 == m2 */
		friend bool operator==(const mat4& m1, const mat4& m2);
		
		/* Checks if m1 != m2 */
		friend bool operator!=(const mat4& m1, const mat4& m2);
		
		/* Matrix addition (m1 + m2) */
		friend mat4 operator+ (const mat4& m1, const mat4& m2);
		
		/* Matrix subtraction (m1 - m2) */
		friend mat4 operator- (const mat4& m1, const mat4& m2);
		
		/* Scalar multiplication (m * c) */
		friend mat4 operator* (const mat4& m,  float c);
		
		/* Scalar multiplication (c * m) */
		friend mat4 operator* (float c, const mat4& m);
		
		/* Scalar division (m / c) */
		friend mat4 operator/ (const mat4& m,  float c);
		
		/* Matrix multiplication (m1 * m2) */
		friend mat4 operator* (const mat4& m1, const mat4& m2);
		
		/* Matrix/vector multiplication (m * v)           */
		/* Assume v is a column vector (ie. a 4x1 matrix) */
		friend vec4 operator* (const mat4& m,  const vec4& v);
		
		/* Vector/matrix multiplication (v * m)        */
		/* Assume v is a row vector (ie. a 1x4 matrix) */
		friend vec4 operator* (const vec4& v,  const mat4& m);
};

#endif
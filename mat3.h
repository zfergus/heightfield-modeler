/*
 *  mat3.h
 */
 
#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"   /* Used to store vec3's in the mat3.           */

#define PI 3.1415926535897 /* Math constant for angle conversions. */

class mat3
{
	private:

		vec3 data[3];
	
	public:
	
		/****************/
		/* Constructors */
		/****************/
		/* Default Constructor.  Initialize to matrix of all 0s. */
		mat3();

		/* Initializes matrix with each vector representing a row in the */ 
		/* matrix.                                                       */
		mat3(const vec3& row1, const vec3& row2, const vec3& row3);
		
		/***********************/
		/* Static Initializers */
		/***********************/
		/* Creates a 3-D rotation matrix.                               */
		/* Takes an angle in degrees and outputs a 3x3 rotation matrix. */
		static mat3 rotation2D(float angle);
	
		/* Takes an x and y displacement and outputs a 3x3 translation */
		/* matrix.                                                     */
		static mat3 translation2D(float x, float y);
	
		/* Takes an x and y scale and outputs a 3x3 scale matrix. */
		static mat3 scale2D(float x, float y);
	
		/* Generates a 3x3 identity matrix */
		static mat3 identity();	
		
		/*********************/
		/* Getters & Setters */
		/*********************/		
		/* Returns the values of the row at the index. */
		vec3 operator[](unsigned int index) const;
	
		/* Returns a reference to the row at the index. */
		vec3& operator[](unsigned int index);
	
		/* Returns a column of the matrix. */
		vec3 getColumn(unsigned int index) const;

		/**********************/
		/* Display the Matrix */
		/**********************/

		/* Prints the matrix to standard output in a nice format. */
		void print();

		/*********************/
		/* Matrix Operations */
		/*********************/		
		/* Returns the transpose of the matrix (v_ij == v_ji). */
		mat3 transpose() const;

		/** Friend Functions **/
		
		/* Checks if m1 == m2. */
 		friend bool operator==(const mat3& m1, const mat3& m2);
	
		/* Checks if m1 != m2. */
		friend bool operator!=(const mat3& m1, const mat3& m2);
	
		/* Matrix addition (m1 + m2). */
		friend mat3 operator+ (const mat3& m1, const mat3& m2);
	
		/* Matrix subtraction (m1 - m2). */
		friend mat3 operator- (const mat3& m1, const mat3& m2);
	
		/* Scalar multiplication (m * c). */
		friend mat3 operator* (const mat3& m,  float c);
	
		/* Scalar multiplication (c * m). */
		friend mat3 operator* (float c, const mat3& m);
	
		/* Scalar division (m / c). */
		friend mat3 operator/ (const mat3& m,  float c);
	
		/* Matrix multiplication (m1 * m2). */
		friend mat3 operator* (const mat3& m1, const mat3& m2);
	
		 /* Matrix/vector multiplication (m * v).           */
		 /* Assume v is a column vector (ie. a 3x1 matrix). */
		friend vec3 operator* (const mat3& m,  const vec3& v);
	
		 /* Vector/matrix multiplication (v * m).       */
		 /*Assume v is a row vector (ie. a 1x3 matrix). */
		friend vec3 operator* (const vec3& v,  const mat3& m);
};

#endif
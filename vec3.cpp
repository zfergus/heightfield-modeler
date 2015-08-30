/*
 * vec3.cpp
 * Created by Zachary Ferguson
 * Last Edited: 1/28/2015
 * Definition for 3D Vector Class.
 */

#include "vec3.h"   /* Class and function prototypes.                     */



/* Constructor for the 3 dimensional zero vector.          */
/* Creates a vector with zeros for x, y, and z components. */
vec3::vec3() : vec3(0.0, 0.0, 0.0){}

/* Converts the given vec4 to a vec3. */
vec3::vec3(vec4 v4) : vec3(v4[0], v4[1], v4[2]){}

/* Constructor to create a 3-dimensional vector with the given parameters. */
/* Takes three floating point numbers in the order x, y, and z.            */
vec3::vec3(float x, float y, float z)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
}
/* Indexing operator that returns the value at the index.    */
/* 0 for x, 1 for y, and 2 for the z value.                  */
/* If the given index is out of bounds an error is asserted. */
float vec3::operator[](unsigned int index) const
{
	/* Check index is in bounds */
	assert(index >= 0 && index < 3);
	/* Return the component corresponding to the given index */
	return (this->data)[index];
}

/* Indexing operator that returns a reference to the value at index. */
/* 0 for x, 1 for y, and 2 for the z value.                          */
/* If the given index is out of bounds an error is asserted.         */
float& vec3::operator[](unsigned int index)
{
	/* Check index is in bounds */
	assert(index >= 0 && index < 3);
	/* Return the component corresponding to the given index */
	return (this->data)[index];
}

/* Print out this vector in a neat fashion. */
/* Ex) [x, y, z]                            */
void vec3::print()
{
	/* set the precision to 4 */
	std::cout.precision(6);
	/* Print out the vector */
	std::cout << "[" << (*this)[0] << ", " \
		             << (*this)[1] << ", " \
		             << (*this)[2] << "]";
}

/* Calculates the magnitude of this vector.          */
/* Returns a float for the magnitude of this vector. */
float vec3::length() const
{
	/* Calculate the squares of the components */
	float xSq = (*this)[0] * (*this)[0];
	float ySq = (*this)[1] * (*this)[1];
	float zSq = (*this)[2] * (*this)[2];

	/* Return the magnitude */
	return sqrt(xSq + ySq + zSq);
}

/* Determines if the given two vectors are equal.  */
/* Returns a boolean for if the vectors are equal. */
bool operator==(const vec3& v1, const vec3& v2)
{
	/* Compare components */
	return (abs(v1[0] - v2[0]) < EPSILON) && \
		   (abs(v1[1] - v2[1]) < EPSILON) && \
		   (abs(v1[2] - v2[2]) < EPSILON);
}

/* Determines if the given two vectors are not equal.  */
/* Returns a boolean for if the vectors are not equal. */
bool operator!=(const vec3& v1, const vec3& v2)
{
	/* Return if they are not equal */
	return !(v1 == v2);
}

/* Operator for adding two vectors together. */
/* Must give two vectors to be added.         */
/* Returns there sum.                        */
vec3 operator+(const vec3& v1, const vec3& v2)
{
	/* Sum up the components */
	float sumX = v1[0] + v2[0];
	float sumY = v1[1] + v2[1];
	float sumZ = v1[2] + v2[2];
	/* Create the new vector */
	vec3 vSum = vec3(sumX, sumY, sumZ);
	return vSum;
}

/* Operator for subtracting two vectors together.   */
/* Must give two vectors to be subtracted.           */
/* Returns there difference.                        */
vec3 operator-(const vec3& v1, const vec3& v2)
{
	/* Add -v2 to v1 */
	vec3 vDelta = v1 + (-1 * v2);
	/* Return new vector */
	return vDelta;
}

/* Operator for scalar multiplication.                  */
/* Must give a vector and a float scalar in that order. */
vec3 operator* (const vec3& v, float c)
{
	/* Multiply the components by c */
	float scaledX = v[0] * c;
	float scaledY = v[1] * c;
	float scaledZ = v[2] * c;
	
	/* Return the vector with the new components calculated */
	return vec3(scaledX, scaledY, scaledZ);
}

/* Operator for scalar multiplication.                  */
/* Must give a float scalar and a vector in that order. */
vec3 operator* (float c, const vec3& v)
{
	/* Multiply v times c */
	return v * c;
}

/* Operator for scalar division of the given vector.  */
vec3 operator/ (const vec3& v, float c)
{
	/* Make sure the constant to be divided by is not zero */
	assert(c != 0);
	/* Multiply v * the reciprocal of c */
	return v * (1/c);
}

/* Operator for computing the Dot Product (Inner Product) between two       */
/* vectors. Returns a float for the inner product of the two given vectors. */
float operator* (const vec3& v1, const vec3& v2)
{
	/* Calculate the Dot Product */
	float innerProduct = (v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]);
	return innerProduct;
}

/* Operator for computing the Cross Product between two vectors. */
/* Returns a new vector that is orthogonal to the given vectors. */
vec3 operator% (const vec3& v1, const vec3& v2)
{
	/* Compute the x, y, and z components of the cross product */
	float xComponent = v1[1] * v2[2] - v1[2] * v2[1];
	float yComponent = (v1[0] * v2[2] - v1[2] * v2[0]) * -1;
	float zComponent = v1[0] * v2[1] - v1[1] * v2[0];

	/* Return the new orthogonal vector */
	return vec3(xComponent, yComponent, zComponent);
}
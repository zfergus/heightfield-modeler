/*
 * vec4.cpp
 * Created by Zachary Ferguson
 * Source file for the vec4 class, a 4 dimensional vector.
 */

#include "vec4.h"   /* Class and function prototypes. */

/****************/
/* Constructors */
/****************/

/* Constructor for the 4 dimensional zero vector.             */
/* Creates a vector with zeros for x, y, z, and t components. */
vec4::vec4() : vec4(0.0, 0.0, 0.0, 0.0){}

/* Converts vec3 to vec4 with t = 0. */
vec4::vec4(vec3 v3) : vec4(v3[0], v3[1], v3[2], 0){}

/* Constructor to create a 4-dimensional vector with the given parameters. */
/* Takes three floating point numbers in the order x, y, z, and t.         */
vec4::vec4(float x, float y, float z, float t)
{
	(this->data)[0] = x;
	(this->data)[1] = y;
	(this->data)[2] = z;
	(this->data)[3] = t;
}

/*********************/
/* Getters & Setters */
/*********************/

/* Indexing operator that returns the value at the index.    */
/* 0 for x, 1 for y, 2 for z, and 3 for the t value.         */
/* If the given index is out of bounds an error is asserted. */
float vec4::operator[](unsigned int index) const
{
	/* Check index is in bounds */
	assert(index < 4);
	/* Return the component corresponding to the given index */
	return (this->data)[index];
}

/* Indexing operator that returns a reference to the value at index. */
/* 0 for x, 1 for y, 2 for z, and 3 for the t value.                 */
/* If the given index is out of bounds an error is asserted.         */
float& vec4::operator[](unsigned int index)
{
	/* Check index is in bounds */
	assert(index < 4);
	/* Return the component corresponding to the given index */
	return (this->data)[index];
}

/**********************/
/* Display the Vector */
/**********************/

/* Print out this vector in a neat fashion. */
/* Ex) [x, y, z, t]                         */
void vec4::print()
{
	
	/* set the precision to 4 */
	std::cout.precision(6);
	std::cout << this->toString();

}

/* Returns a string representation of this vector. */
/* Ex) [x, y, z, t]                                */
std::string vec4::toString()
{
	/* Makes the string representation of the vector. */
	std::stringstream stream;
	/* set the precision to 4 */
	stream.precision(4);

	stream << "[" << (*this)[0] << ", " << (*this)[1] << ", " << (*this)[2] <<
		", " << (*this)[3] << "]";

	return stream.str();
}

/*********************/
/* Vector Operations */
/*********************/

/* Calculates the magnitude of this vector.          */
/* Returns a float for the magnitude of this vector. */
float vec4::length() const
{
	/* Calculate the squares of the components */
	float xSq = (*this)[0] * (*this)[0];
	float ySq = (*this)[1] * (*this)[1];
	float zSq = (*this)[2] * (*this)[2];
	float tSq = (*this)[3] * (*this)[3];
	/* Return the magnitude */
	return sqrt(xSq + ySq + zSq + tSq);
}

/* Determines if the given two vectors are equal.  */
/* Returns a boolean for if the vectors are equal. */
bool operator==(const vec4& v1, const vec4& v2)
{
	/* Compare components */
	return (abs(v1[0] - v2[0]) < EPSILON) && \
		   (abs(v1[1] - v2[1]) < EPSILON) && \
		   (abs(v1[2] - v2[2]) < EPSILON) && \
		   (abs(v1[3] - v2[3]) < EPSILON);
}

/* Determines if the given two vectors are not equal.  */
/* Returns a boolean for if the vectors are not equal. */
bool operator!=(const vec4& v1, const vec4& v2)
{
	/* Return if they are not equal */
	return !(v1 == v2);
}

/* Operator for adding two vectors together. */
/* Must give two vectors to be added.        */
/* Returns there sum.                        */
vec4 operator+(const vec4& v1, const vec4& v2)
{
	/* Sum up the components */
	float sumX = v1[0] + v2[0];
	float sumY = v1[1] + v2[1];
	float sumZ = v1[2] + v2[2];
	float sumT = v1[3] + v2[3];
	/* Create the new vector */
	vec4 vSum = vec4(sumX, sumY, sumZ, sumT);
	return vSum;
}

/* Operator for subtracting two vectors together.   */
/* Must give two vectors to be subtracted.          */
/* Returns there difference.                        */
vec4 operator-(const vec4& v1, const vec4& v2)
{
	/* Add -v2 to v1 */
	vec4 vDelta = v1 + (-1 * v2);
	/* Return new vector */
	return vDelta;
}

/* Operator for scalar multiplication.                  */
/* Must give a vector and a float scalar in that order. */
vec4 operator* (const vec4& v, float c)
{
	/* Multiply the components by c */
	float scaledX = v[0] * c;
	float scaledY = v[1] * c;
	float scaledZ = v[2] * c;
	float scaledT = v[3] * c;
	
	/* Return the vector with the new components calculated */
	return vec4(scaledX, scaledY, scaledZ, scaledT);
}

/* Operator for scalar multiplication.                  */
/* Must give a float scalar and a vector in that order. */
vec4 operator* (float c, const vec4& v)
{
	/* Multiply v times c */
	return v * c;
}

/* Operator for scalar division of the given vector.  */
vec4 operator/ (const vec4& v, float c)
{
	/* Make sure the constant to be divided by is not zero */
	assert(c != 0);
	/* Multiply v * the reciprocal of c */
	return v * (1/c);
}

/* Operator for computing the Dot Product (Inner Product) between two       */
/* vectors. Returns a float for the inner product of the two given vectors. */
float operator* (const vec4& v1, const vec4& v2)
{
	/* Calculate the Dot Product */
	float innerProduct = (v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]) +
		(v1[3] * v2[3]);
	return innerProduct;
}
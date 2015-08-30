/*
 * mat4.cpp
 * Created by Zachary Ferguson
 * Definition for 4X4 Matrix Class containing 4 vec4's as Rows.
 */

#include "mat4.h"   /* Class and function prototypes. */

/****************/
/* Constructors */
/****************/

/* Creates a matrix of all zeros. */
mat4::mat4() : mat4(vec4(), vec4(), vec4(), vec4()){}

/* Constructs a matrix from the given three vectors. */
/* The vectors become the rows of the matrix.        */
mat4::mat4(const vec4& row1, const vec4& row2, const vec4& row3, 
	const vec4& row4)
{
	data[0] = row1;
	data[1] = row2;
	data[2] = row3;
	data[3] = row4;
}

/***********************/
/* Static Initializers */
/***********************/

/* Given a angle in degrees for rotation and the axis, starting at the */
/* origin, to rotate about. Returns a rotation matrix.                 */
mat4 mat4::rotation3D(float angle, const vec3& axisOfRotation)
{
	/* Convert angle to radians. */
	float theta = (float)((PI*angle)/180.0);
	
	/* Calculate sine and cosine values */
	float co = cos(theta);
	float si = sin(theta);
	float t = 1.0f - co;
	
	/* Calculate the axis' length and the direction cosines. */
	float axisLen = axisOfRotation.length();
	float a = (axisOfRotation/axisLen)[0];
	float b = (axisOfRotation/axisLen)[1];
	float c = (axisOfRotation/axisLen)[2];
	
	/* Create the rotation matrix. */
	vec4 row1 = vec4(t * a * a + co, t * a * b - si * c, t * a * c + si * b,
		0.0);
	vec4 row2 = vec4(t * a * b + si * c, t * b * b + co, t * b * c - si * a,
		0.0);
	vec4 row3 = vec4(t * a * c - si * b, t * b * c + si * a, t * c * c + co,
		0.0);
	vec4 row4 = vec4(0, 0, 0, 1);
	
	return mat4(row1, row2, row3, row4);
}

/* Given a x and y translation value returns a translation matrix. */
mat4 mat4::translation3D(float x, float y, float z)
{
	/* Create the Translation matrix */
	return mat4(vec4(1, 0, 0, x),
				vec4(0, 1, 0, y),
				vec4(0, 0, 1, z),
				vec4(0, 0, 0, 1));
}

/* Given a x and y scaling float value returns a scaling matrix. */
mat4 mat4::scale3D(float x, float y, float z)
{
	/* Create the Scale matrix */
	return mat4(vec4(x, 0, 0, 0),
				vec4(0, y, 0, 0),
				vec4(0, 0, z, 0),
				vec4(0, 0, 0, 1));
}

/* Returns the 3x3 Identity Matrix */
mat4 mat4::identity()
{
	/* Create the Identity matrix */
	return mat4(vec4(1, 0, 0, 0),
				vec4(0, 1, 0, 0),
				vec4(0, 0, 1, 0),
				vec4(0, 0, 0, 1));
}

/* Returns the ith row in this matrix. */
vec4 mat4::operator[](unsigned int index) const
{
	/* Check index is in bounds */
	assert(index < 4);
	/* Return the row corresponding to the given index */
	return data[index];
}

/* Returns a reference to the ith row in this matrix. */
vec4& mat4::operator[](unsigned int index)
{
	/* Check index is in bounds */
	assert(index < 4);
	/* Return the row corresponding to the given index */
	return data[index];
}

/* Returns the column of this matrix corresponding to the given index. */
vec4 mat4::getColumn(unsigned int index) const
{
	/* Check column is in bounds */
	assert(index < 4);
	/* Create and return the column */
	return vec4(data[0][index], data[1][index], data[2][index], data[3][index]);
}

/**********************/
/* Display the Matrix */
/**********************/

/* Nicely prints out this matrix. */
void mat4::print()
{
	/* Print out the matrix */
	std::cout << this->toString();
}

/* Returns a string representation of this vector. */		
std::string mat4::toString()
{
	std::stringstream stream;
	stream << "[" << data[0].toString() << std::endl 
	       << " " << data[1].toString() << std::endl
		   << " " << data[2].toString() << std::endl
		   << " " << data[3].toString() << "]";
	return stream.str();
}

/* Returns the transpose of this matrix (x_ij == x_ji). */
mat4 mat4::transpose() const
{
	/* Make a new matrix with rows equal to the columns of this matrix */
	return mat4(this->getColumn(0), this->getColumn(1), this->getColumn(2),
				this->getColumn(3));
}

/* Returns a boolean for if the matrices are equal to each other. */
bool operator==(const mat4& m1, const mat4& m2)
{
	/* Compare vectors */
	return m1[0] == m2[0] && 
		   m1[1] == m2[1] &&
		   m1[2] == m2[2] &&
		   m1[3] == m2[3];
}

/* Returns a boolean for if the matrices are not equal to each other. */
bool operator!=(const mat4& m1, const mat4& m2)
{
	/* Return if they are not equal. */
	return !(m1 == m2);
}

/* Return the sum of the given matrices. */
mat4 operator+ (const mat4& m1, const mat4& m2)
{
	/* Sum up the rows */
	vec4 row1 = m1[0] + m2[0];
	vec4 row2 = m1[1] + m2[1];
	vec4 row3 = m1[2] + m2[2];
	vec4 row4 = m1[3] + m2[3];
	
	/* Return a new matrix of the sum of the vectors */
	return mat4(row1, row2, row3, row4);
}

/* Return the difference between the given matrices. */
mat4 operator- (const mat4& m1, const mat4& m2)
{
	/* Return the difference of the matrices */
	return m1 + (-1 * m2);
}

/* Multiplies the given constant by the given matrix.          */
/* Must give a mat4 and a float for to multiply in that order. */
/* Returns the new matrix after the multiplication.            */
mat4 operator* (const mat4& m, float c)
{
	/* multiply c by the up the rows */
	vec4 row1 = c * m[0];
	vec4 row2 = c * m[1];
	vec4 row3 = c * m[2];
	vec4 row4 = c * m[3];

	/* Return a new matrix of the new vectors */
	return mat4(row1, row2, row3, row4);
}

/* Multiplies the given constant by the given matrix.      */
/* Must give a float and a mat4 to multiply in that order. */
/* Returns the new matrix after the multiplication.        */
mat4 operator* (float c, const mat4& m)
{
	return m * c;
}

/* Divides given matrix entries by the given constant.     */
/* Must give a float and a mat4 to multiply in that order. */
/* Returns the new matrix after the division.              */
mat4 operator/ (const mat4& m, float c)
{
	/* Check that c is not zero */
	assert(c != 0);
	/* Divide the matrix by c */
	return m * (1/c);
}

/* Multiply the given two 3x3 matrices and return the new matrix. */
mat4 operator* (const mat4& m1, const mat4& m2)
{
	mat4 product = mat4();
	
	/* Multiply the rows of m1 times the columns of m2. */
	for(int r = 0; r < 4; r++)
	{
		for(int c = 0; c < 4; c++)
		{
			product[r][c] = m1[r] * m2.getColumn(c);
		}
	}
	
	return product;
}

/* Multiply the given 3x3 matrices and vec4 and return the new matrix. */
/* Must give a mat4 for the matrix and a vec4 for the vector in that   */
/* order.                                                              */
vec4 operator* (const mat4& m, const vec4& v)
{
	vec4 product = vec4();
	
	/* Multiply the rows of m by the vector to get the products components. */
	for(int i = 0; i < 4; i++)
	{
		product[i] = m[i] * v;
	}

	/* Return the new product vector*/
	return product;
}

/* Multiply the given 3x3 matrices and vec4 and return the new matrix. */
/* Must give a vec4 for the vector and a mat4 for the matrix in that   */
/* order.                                                              */
vec4 operator* (const vec4& v, const mat4& m)
{
	vec4 product = vec4();
	
	/* Multiply the rows of m by the vector to get the products components. */
	for(int i = 0; i < 4; i++)
	{
		product[i] = m.getColumn(i) * v;
	}

	/* Return the new product vector*/
	return product;
}
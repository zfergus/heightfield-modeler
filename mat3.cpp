/*
 * mat3.cpp
 * Created by Zachary Ferguson
 * Last Edited: 1/31/2015
 * Definition for 3X3 Matrix Class containing 3 vec3's as Rows.
 */

#include "mat3.h"   /* Class and function prototypes.              */

/* Creates a matrix of all zeros. */
mat3::mat3()
{
	for (int i = 0; i < 3; i++)
	{
		data[i] = vec3();
	}
}

/* Constructs a matrix from the given three vectors. */
/* The vectors become the rows of the matrix.        */
mat3::mat3(const vec3& row1, const vec3& row2, const vec3& row3)
{
	data[0] = row1;
	data[1] = row2;
	data[2] = row3;
}

/* Returns the ith row in this matrix. */
vec3 mat3::operator[](unsigned int index) const
{
	/* Check index is in bounds */
	assert(index >= 0 && index < 3);
	/* Return the row corresponding to the given index */
	return data[index];
}

/* Returns a reference to the ith row in this matrix. */
vec3& mat3::operator[](unsigned int index)
{
	/* Check index is in bounds */
	assert(index >= 0 && index < 3);
	/* Return the row corresponding to the given index */
	return data[index];
}

/* Returns the column of this matrix corresponding to the given index. */
vec3 mat3::getColumn(unsigned int index) const
{
	/* Check column is in bounds */
	assert(index >= 0 && index < 3);
	/* Create and return the column */
	return vec3(data[0][index], data[1][index], data[2][index]);
}

/* Nicely prints out this matrix. */
void mat3::print()
{
	/* Print out the matrix */
	std::cout << "["; 
	data[0].print();
	std::cout << std::endl << " ";
	data[1].print();
	std::cout << std::endl << " ";
	data[2].print();
	std::cout << "]";
}

/* Returns the transpose of this matrix (x_ij == x_ji). */
mat3 mat3::transpose() const
{
	/* Make a new matrix with rows equal to the columns of this matrix */
	return mat3(this->getColumn(0), this->getColumn(1), this->getColumn(2));
}

/* Given a angle in degrees for rotation returns a rotation matrix. */
mat3 mat3::rotation2D(float angle)
{
	/* Convert to radians and create the rotation matrix */
	return mat3(vec3((float)cos((PI*angle) / 180), (float)(-1 * sin((PI*angle)/
			180)), 0),
		vec3((float)sin((PI*angle) / 180), (float)cos((PI*angle) / 180), 0),
		vec3(0, 0, 1));
}

/* Given a x and y translation value returns a translation matrix. */
mat3 mat3::translation2D(float x, float y)
{
	/* Create the Translation matrix */
	return mat3(vec3(1, 0, x),
				vec3(0, 1, y),
				vec3(0, 0, 1));
}

/* Given a x and y scaling float value returns a scaling matrix. */
mat3 mat3::scale2D(float x, float y)
{
	/* Create the Scale matrix */
	return mat3(vec3(x, 0, 0),
				vec3(0, y, 0),
				vec3(0, 0, 1));
}

/* Returns the 3x3 Identity Matrix */
mat3 mat3::identity()
{
	/* Create the Identity matrix */
	return mat3(vec3(1, 0, 0),
				vec3(0, 1, 0),
				vec3(0, 0, 1));
}

/* Returns a boolean for if the matrices are equal to each other. */
bool operator==(const mat3& m1, const mat3& m2)
{
	/* Compair vectors */
	return m1[0] == m2[0] && 
		   m1[1] == m2[1] &&
		   m1[2] == m2[2];
}

/* Returns a boolean for if the matrices are not equal to each other. */
bool operator!=(const mat3& m1, const mat3& m2)
{
	/* Return if they are not equal. */
	return !(m1 == m2);
}

/* Return the sum of the given matrices. */
mat3 operator+ (const mat3& m1, const mat3& m2)
{
	/* Sum up the rows */
	vec3 row1 = m1[0] + m2[0];
	vec3 row2 = m1[1] + m2[1];
	vec3 row3 = m1[2] + m2[2];
	
	/* Return a new matrix of the sum of the vectors */
	return mat3(row1,
				row2,
				row3);
}

/* Return the difference between the given matrices. */
mat3 operator- (const mat3& m1, const mat3& m2)
{
	/* Return the difference of the matrices */
	return m1 + (-1 * m2);
}

/* Multiplies the given constant by the given matrix.          */
/* Must give a mat3 and a float for to multiply in that order. */
/* Returns the new matrix after the multiplication.            */
mat3 operator* (const mat3& m, float c)
{
	/* multiply c by the up the rows */
	vec3 row1 = c * m[0];
	vec3 row2 = c * m[1];
	vec3 row3 = c * m[2];

	/* Return a new matrix of the new vectors */
	return mat3(row1,
				row2,
				row3);
}

/* Multiplies the given constant by the given matrix.      */
/* Must give a float and a mat3 to multiply in that order. */
/* Returns the new matrix after the multiplication.        */
mat3 operator* (float c, const mat3& m)
{
	return m * c;
}

/* Divides given matrix entries by the given constant.     */
/* Must give a float and a mat3 to multiply in that order. */
/* Returns the new matrix after the division.              */
mat3 operator/ (const mat3& m, float c)
{
	/* Check that c is not zero */
	assert(c != 0);
	/* Divide the matrix by c */
	return m * (1/c);
}

/* Multiply the given two 3x3 matrices and return the new matrix. */
mat3 operator* (const mat3& m1, const mat3& m2)
{
	/* Multiply first row by the columns of m2 */
	vec3 row1 = vec3(m1[0] * m2.getColumn(0), 
					 m1[0] * m2.getColumn(1), 
					 m1[0] * m2.getColumn(2));
	/* Multiply second row by the columns of m2 */
	vec3 row2 = vec3(m1[1] * m2.getColumn(0),
					 m1[1] * m2.getColumn(1),
					 m1[1] * m2.getColumn(2));
	/* Multiply third row by the columns of m2 */
	vec3 row3 = vec3(m1[2] * m2.getColumn(0),
					 m1[2] * m2.getColumn(1),
					 m1[2] * m2.getColumn(2));

	/* Return a new matrix of the new vectors */
	return mat3(row1,
				row2,
				row3);
}

/* Multiply the given 3x3 matrices and vec3 and return the new matrix. */
/* Must give a mat3 for the matrix and a vec3 for the vector in that   */
/* order.                                                              */
vec3 operator* (const mat3& m, const vec3& v)
{
	/* Multiply row one by the vector to get the new x component */
	float x = m[0] * v;
	/* Multiply row two by the vector to get the new y component */
	float y = m[1] * v;
	/* Multiply row three by the vector to get the new z component */
	float z = m[2] * v;

	/* Return a new vector with the new components */
	return vec3(x, y, z);
}

/* Multiply the given 3x3 matrices and vec3 and return the new matrix. */
/* Must give a vec3 for the vector and a mat3 for the matrix in that   */
/* order.                                                              */
vec3 operator* (const vec3& v, const mat3& m)
{
	/* Multiply column one by the vector to get the new x component */
	float x = m.getColumn(0) * v;
	/* Multiply column two by the vector to get the new y component */
	float y = m.getColumn(1) * v;
	/* Multiply column three by the vector to get the new z component */
	float z = m.getColumn(2) * v;

	/* Return a new vector with the new components */
	return vec3(x, y, z);
}
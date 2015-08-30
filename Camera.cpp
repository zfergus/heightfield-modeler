/*
 * Camera.cpp
 * Created by Zachary Ferguson
 * Source file for the Camera class, a class for representing a camera in 3D 
 * space.
 */

#include "Camera.h"

/* Camera constructor that takes the initial radius, the XZ-plane angle in */
/* degrees, and the XY-plane angle in degrees.                             */
Camera::Camera(float rho, float theta, float phi, float roll)
{
	/* Create the up vector as a +Y vector. */
	this->up  = vec4(0, 1, 0, 1);
	/* Put the cameras eye in the Z direction. */
	this->eye = vec4(0, 0, rho, 1);
	/* Vector orthogonal to the eye and up. */
	this->right = vec4(vec3(this->eye) % vec3(this->up));
	this->right = this->right / this->right.length();

	/* Calculate the initial rotation of the eye and up vectors. */
	this->rotation = mat4::rotation3D(theta, vec3(this->up)) *
					 mat4::rotation3D(phi, vec3(this->right)) * 
					 mat4::rotation3D(roll, vec3(this->eye));
}
		
/* Deconstructor */
Camera::~Camera(){ return; }

/* Increase the XZ-plane angle. Note a negative value will decrease it. */
void Camera::increaseTheta(float inc)
{
	/* Change the rotation matrix by multiply the old rotation times the */
	/* incrementation. Use the +Y for the axis of rotation.              */
	this->rotation = this->rotation * mat4::rotation3D(inc, vec3(this->up));
}

/* Increase the XY-plane angle. Note a negative value will decrease it. */
void Camera::increasePhi(float inc)
{
	/* Change the rotation matrix by multiply the old rotation times the */
	/* incrementation. Use the -X for the axis of rotation.              */
	this->rotation = this->rotation * mat4::rotation3D(inc, vec3(this->right));
}

/* Increase the roll angle. Note a negative value will decrease it. */
void Camera::increaseRoll(float inc)
{
	/* Change the rotation matrix by multiply the old rotation times the */
	/* incrementation. Use the eye vector for the axis of rotation.      */
	this->rotation = this->rotation * mat4::rotation3D(inc, vec3(this->eye));
}
		
/* Increase the radius to move the eye closer or further away. Note a */
/* negative value will decrease the radius.                           */
void Camera::increaseRad(float inc)
{
	/* Increase the Z value of the eye vector. */
	(this->eye)[2] += inc;
}
		
/* Returns a vec4 for the up vector. */
const vec4 Camera::getUp() const
{
	/* Rotate the up vector then return it. */
	return this->rotation * this->up;
}

/* Returns a vec4 for the current eye position. */
const vec4 Camera::getEye() const
{
	/* Rotate the eye vector then return it. */
	return this->rotation * this->eye;
}

/* Returns the transformation matrix on the camera. */
const mat4 Camera::getRotationMatrix() const
{
	/* Rotate the rotation matrix of this camera. */
	return this->rotation;
}
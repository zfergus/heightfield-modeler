/*
 * Camera.h
 * Created by Zachary Ferguson
 * Header file for the Camera class, a class for representing a camera in 3D 
 * space.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "mat4.h"

class Camera
{
	private:
		
		/* The current rotation matrix. */
		mat4 rotation;
		
		/* The current up vector. */
		vec4 up;
		
		/* The current camera position. */
		vec4 eye;

		/* Vector orthogonal to the eye and up. */
		vec4 right;
	
	public:
	
		/* Camera constructor that takes the initial radius, the xz-plane */
		/* angle, and the xy-plane angle.                                 */
		Camera(float rho, float theta, float phi, float roll); 
		
		/* Deconstructor */
		virtual ~Camera();

		/* Increase the xz-plane angle. Note a negative value will decrease */
		/* it.                                                              */
		void increaseTheta(float inc);

		/* Increase the xy-plane angle. Note a negative value will decrease */
		/* it.                                                              */
		void increasePhi(float inc);
		
		/* Increase the roll angle. Note a negative value will decrease */
		/* it.                                                          */
		void increaseRoll(float inc);

		/* Increase the radius. Note a negative value will decrease the */
		/* radius.                                                      */
		void increaseRad(float inc);
		
		/* Returns a vec4 for the up vector. */
		const vec4 getUp() const;

		/* Returns a vec4 for the current eye position. */
		const vec4 getEye() const;
		
		/* Returns the transformation matrix on the camera. */
		const mat4 getRotationMatrix() const;
};

#endif
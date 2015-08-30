/*
 * main.cpp
 * Created by Zachary Ferguson
 * Main file for constructing a 3D World with a camera and spinning cude.
 */

#include "MeshModeler.h"

/* Constructs a 3D World with a camera and spinning cude. */
int main(int argc, char* const argv[])
{
	MeshModeler* meshModeler = new MeshModeler(450, 150, 900, 600, 
		"Mesh Modeler");
	meshModeler->show();
	return Fl::run();
}
/*
 * Mesh.h
 * Created by Zachary Ferguson
 * Header file for the Mesh class that represents a Mesh in 3D space.
 */

#ifndef MESH_H
#define MESH_H

#include "vec4.h"
#include "ray.h"
#include "Color.h"
#include <FL/Gl.H>

#define SELECTION_RADIUS 0.5

class Mesh
{
	private:
		
		/* Vector of vertices. */
		std::vector<std::vector<vec4>*>* vertices;
		/* The color of this face. */
		const Color* color;
		/* Height of the snow caps. Any vertex above this height is drawn */
		/* white.                                                         */
		float snowCapHeight;

		/* Width and depth of this mesh. */
		float width, depth;
	
		/* Set the color of for gl based on the given height and the snow */
		/* cap height. Color white if above snow height, default color    */
		/* otherwise.                                                     */
		void colorVertices(const float y) const;

	public:
		
		/* Constructor for creating a new mesh.                             */
		/* Must send a unsigned int for the number of rows and cols of the  */
		/* mesh. Also requires the width and depth of the mesh in 3D space. */
		/* Lastly requires the color of the mesh.                           */
		Mesh(const unsigned int rows, const unsigned int cols, 
			 const float width, const float depth, 
			 const Color* color, const float snowCapHeight = 100);
		
		/* Deletes this Face */
		virtual ~Mesh();
	
		/* Returns the number of rows in the mesh. */
		const unsigned int getRows() const;
		
		/* Returns the number of rows in the mesh. */
		const unsigned int getCols() const;		
		
		/* Returns the width of this mesh. */
		const float getWidth() const;
		/* Returns the depth of this mesh. */
		const float getDepth() const; 

		/* Deletes the old color and sets it to the given new one. */
		void setColor(const Color* newColor);

		/* Returns a constant pointer to the color of this face. */
		const Color* getColor() const;

		/* Sets the height of a vertex at the given row and column number. */
		void setHeight(const unsigned int row, const unsigned int col,
			const float height);

		/* Sets the vertex at the given row and column number with the new */
		/* vec4.                                                           */
		void setVertex(const unsigned int row, const unsigned int col,
			vec4 newVertex);

		/* Returns the vertex at the given row and column number. */
		const vec4 getVertex(unsigned int row, unsigned int col) const;

		/* Set the current snow cap height. */
		void setSnowCapHeight(const float height);

		/* Get the current snow cap height. */
		const float getSnowCapHeight() const;

		/* Returns the indecies of the userRay's selected vertex. Returns */
		/* NULL if no vertex selected.                                    */
		std::vector<unsigned int>* selectVertex(ray userRay);

		/* Copies this mesh into a larger mesh and fractalizes it. */
		Mesh* fractalize() const;

		/* Copies this mesh into a larger mesh and subdivides it using the */
		/* Catmull-Clark Subdivision Algorithm.                            */
		Mesh* smooth() const;

		/* Draws this mesh out to 3D space. */
		void draw(bool displayEdges, bool displayFaces) const;
};

#endif
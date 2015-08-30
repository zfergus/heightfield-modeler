/*
 * Mesh.cpp
 * Created by Zachary Ferguson
 * Source file for the Mesh class that represents a Mesh in 3D space.
 */

#include "Mesh.h"

/* Constructor for creating a new mesh.                                   */
/* Must send a unsigned int for the number of rows and cols of the  mesh. */
/* Also requires the width and depth of the mesh in 3D space. Lastly      */
/* requires the color of the mesh.                                        */
Mesh::Mesh(const unsigned int rows, const unsigned int cols, const float width,
	const float depth, const Color* color, const float snowCapHeight)
{
	/* Check that the width and depth are non-negative. */
	assert(depth > 0 && width > 0);

	/* Create new vector for the rows. */
	this->vertices = new std::vector<std::vector<vec4>*>();
	
	/* Fill the rows with columns. */
	float range = (width / rows + depth / cols)/2;
	for (unsigned int r = 0; r <= rows; r++)
	{
		std::vector<vec4>* row = new std::vector<vec4>();
		float z = depth * (r/(rows*1.0f)) - (depth / 2.0f);
		for (unsigned int c = 0; c <= cols; c++)
		{
			float x =  width * (c/(cols*1.0f)) - ((width) / 2.0f);
			float y = (((float)rand()/(float)RAND_MAX) * range) - (range/2.0f);
			//float y = ((float)rand()/(float)RAND_MAX) * .5f - .25f;
			//float y = (x*x+z*z)/5;
			//float y = 0;
			row->push_back(vec4(x, y, z, 0.0));
		}
		this->vertices->push_back(row);
	}

	/* Set the instance variables. */
	this->color = color;

	this->snowCapHeight = snowCapHeight;

	this->width = width;
	this->depth = depth;
}
		
/* Deletes this Face */
Mesh::~Mesh()
{
	for (unsigned int r = 0; r < this->vertices->size(); r++)
	{
		this->vertices->at(r)->clear();
	}
	this->vertices->clear();
	delete this->vertices;
}

/* Returns the number of rows in the mesh. */
const unsigned int Mesh::getRows() const
{
	return this->vertices->size();
}
		
/* Returns the number of rows in the mesh. */
const unsigned int Mesh::getCols() const
{
	return this->vertices->at(0)->size();
}
		
/* Returns the width of this mesh. */
const float Mesh::getWidth() const
{
	return this->width;
}

/* Returns the depth of this mesh. */
const float Mesh::getDepth() const
{
	return this->depth;
}

/* Deletes the old color and sets it to the given new one. */
void Mesh::setColor(const Color* newColor)
{
	this->color = newColor;
}

/* Returns a constant pointer to the color of this face. */
const Color* Mesh::getColor() const
{
	return this->color;
}

/* Sets the height of a vertex at the given row and column number. */
void Mesh::setHeight(const unsigned int row, const unsigned int col, 
	const float height)
{
	/* Check the row and col are in bounds. */
	assert(row < this->getRows() && col < this->getCols());

	/* Set the height. */
	this->vertices->at(row)->at(col)[1] = height;
}

/* Sets the vertex at the given row and column number with the new vec4. */
void Mesh::setVertex(const unsigned int row, const unsigned int col, 
	vec4 newVertex)
{
	/* Check the row and col are in bounds. */
	assert(row < this->getRows() && col < this->getCols());
	this->vertices->at(row)->at(col) = newVertex;
}

/* Returns the vertex at the given row and column number. */
const vec4 Mesh::getVertex(unsigned int row, unsigned int col) const
{
	/* Check the row and col are in bounds. */
	assert(row < this->getRows() && col < this->getCols());
	
	return this->vertices->at(row)->at(col);
}

/* Set the current snow cap height. */
void Mesh::setSnowCapHeight(const float height)
{
	this->snowCapHeight = height;
}

/* Get the current snow cap height. */
const float Mesh::getSnowCapHeight() const
{
	return this->snowCapHeight;
}

/* Returns the indecies of the userRay's selected vertex. Returns NULL if no */
/* vertex selected.                                                          */
std::vector<unsigned int>* Mesh::selectVertex(ray userRay)
{
	/* Step 6: For each vertex, v, in the mesh, compute the distance from v */
	/* to the ray, R, computed in step 5. If the distance is less than or   */
	/* equal to r, then select that vertex.                                 */
	vec4 rayDirection = userRay.value(1) - userRay.value(0);
	rayDirection = rayDirection / rayDirection.length();

	float closestDistance = FLT_MAX;
	std::vector<unsigned int>* closestIndecies = NULL;

	for (unsigned int r = 0; r < this->getRows(); r++)
	{
		for (unsigned int c = 0; c < this->getCols(); c++)
		{
			vec4 v = this->vertices->at(r)->at(c);
			float distance = (rayDirection % (v - userRay.origin())).length();
			if(distance <= SELECTION_RADIUS && distance < closestDistance)
			{
				closestIndecies = new std::vector<unsigned int>();
				closestIndecies->push_back(r);
				closestIndecies->push_back(c);
				closestDistance = distance;
			}
		}
	}

	return closestIndecies;
}

/* Copies this mesh into a larger mesh and fractalizes it. */
Mesh* Mesh::fractalize() const
{
	//////////////////////////
	// Calculate the range. //
	//////////////////////////
	vec4 v1 = this->getVertex(0, 0);
	vec4 v2 = this->getVertex(0, 1);
	float deltaX = v2[0] - v1[0];
	//float deltaY = v2[1] - v1[1];
	float deltaZ = v2[2] - v1[2];

	float range = sqrt(deltaX*deltaX + deltaZ*deltaZ);

	////////////////////////
	// Create a new mesh. //
	////////////////////////

	/* Create a new larger mesh. */
	Mesh* newMesh = new Mesh((this->getRows()*2)-2, (this->getCols()*2)-2,
		this->getWidth(), this->getDepth(), this->color, this->snowCapHeight);

	//////////////////////////////////////
	// Copy over the original vertices. //
	//////////////////////////////////////

	/* Copy over the original values of the Mesh to the new mesh's even */
	/* indecies. Run time complexity of O((r*c)/4).                     */
	for (unsigned int newRow = 0, originalRow = 0; newRow < newMesh->getRows();
		 newRow+=2, originalRow++)
	{
		for (unsigned int newCol = 0, originalCol = 0; newCol < newMesh->
			 getCols(); newCol+=2, originalCol++)
		{
			newMesh->setVertex(newRow, newCol, 
				this->getVertex(originalRow, originalCol));
		}
	}

	//////////////////////////////////////////////////////////////
	// Add new averaged vertices between the original vertices, //
	// and change their heights by a random delta.              //
	//////////////////////////////////////////////////////////////

	/* Create new vectors that are averages of the original mesh's vectors. */
	/* Run time complexity of O((r*c)/4).                                   */
	for (unsigned int r = 0; r < newMesh->getRows(); r+=2)
	{
		for (unsigned int c = 1; c < newMesh->getCols(); c+=2)
		{
			vec4 prev = newMesh->getVertex(r, c - 1);
			vec4 next = newMesh->getVertex(r, c + 1);
			float delta = ((float)rand()/(float)RAND_MAX)*range-(range/2.0f);
			newMesh->setVertex(r, c, vec4((prev[0]+next[0])/2.0f,
				(prev[1]+next[1])/2.0f+ delta, (prev[2]+next[2])/2.0f, 1.0));
		}
	}

	/* Create new rows that are average of the above and below column */ 
	/* values. Run time complexity of O((r*c)/2).                     */
	for (unsigned int r = 1; r < newMesh->getRows(); r+=2)
	{
		for (unsigned int c = 0; c < newMesh->getCols(); c++)
		{
			vec4 prev = newMesh->getVertex(r-1, c);
			vec4 next = newMesh->getVertex(r+1, c);
			float delta = ((float)rand()/(float)RAND_MAX)*range-(range/2.0f);
			newMesh->setVertex(r, c, vec4((prev[0]+next[0])/2.0f,
				(prev[1]+next[1])/2.0f+ delta, (prev[2]+next[2])/2.0f, 1.0));
		}
	}

	return newMesh;
}

Mesh* Mesh::smooth() const
{
	////////////////////////
	// Create a new mesh. //
	////////////////////////

	/* Create a new larger mesh. */
	Mesh* newMesh = new Mesh((this->getRows()*2)-2, (this->getCols()*2)-2,
		this->getWidth(), this->getDepth(), this->color, this->snowCapHeight);

	//////////////////////////////////////
	// Copy over the original vertices. //
	//////////////////////////////////////

	/* Copy over the original values of the Mesh to the new mesh's even */
	/* indecies. Run time complexity of O((r*c)/4).                     */
	for (unsigned int newRow = 0, originalRow = 0; newRow < newMesh->getRows();
		 newRow+=2, originalRow++)
	{
		for (unsigned int newCol = 0, originalCol = 0; newCol < newMesh->
			 getCols(); newCol+=2, originalCol++)
		{
			newMesh->setVertex(newRow, newCol, 
				this->getVertex(originalRow, originalCol));
		}
	}

	/////////////////////////////////////////////////////
	// Create new vertices at the center of each face. //
	/////////////////////////////////////////////////////
	
	/* Average the vertices of the face to make a centered face vertex. */
	for (unsigned int r = 1; r < newMesh->getRows(); r+=2)
	{
		for (unsigned int c = 1; c < newMesh->getCols(); c+=2)
		{
			/* Determine the face's vertices. */
			vec4 avgVec;
			
			/* Sum up the connected vertices. */
			avgVec =          newMesh->getVertex(r - 1, c - 1);
			avgVec = avgVec + newMesh->getVertex(r + 1, c - 1);
			avgVec = avgVec + newMesh->getVertex(r + 1, c + 1);
			avgVec = avgVec + newMesh->getVertex(r - 1, c + 1);
			/* Average the sum. */
			avgVec = avgVec / 4.0f;
			
			newMesh->setVertex(r, c, avgVec);
		}
	}

	//////////////////////////////////////////////////////////////
	// For each edge in the mesh, create a new edge midpoint    //
	// vertex that is the average of the adjacent edge vertices //
	// and the adjacent face vertices.                          //
	//////////////////////////////////////////////////////////////

	/* Iterate through even rows creating edge vertices. */
	for (unsigned int r = 0; r < newMesh->getRows(); r+=2)
	{
		for (unsigned int c = 1; c < newMesh->getCols(); c+=2)
		{
			float n = 2.0f;
			vec4 avgVec; 

			/* Sum up the connected vertices. */
			avgVec =          newMesh->getVertex(r, c - 1);
			avgVec = avgVec + newMesh->getVertex(r, c + 1);
			
			/* Sum up the connected face vertices. */
			if(r > 0)
			{
				avgVec = avgVec + newMesh->getVertex(r-1, c);
				n++;
			}
			if(r < newMesh->getRows()-1)
			{
				avgVec = avgVec + newMesh->getVertex(r+1, c);
				n++;
			}

			/* Average the sum. */
			avgVec = avgVec / n;

			newMesh->setVertex(r, c, avgVec);
		}
	}


	/* Iterate through odd rows creating edge vertices. */
	for (unsigned int r = 1; r < newMesh->getRows(); r+=2)
	{
		for (unsigned int c = 0; c < newMesh->getCols(); c+=2)
		{
			float n = 2.0f;
			vec4 avgVec;

			/* Sum up the connected vertices. */
			avgVec =		  newMesh->getVertex(r - 1, c);
			avgVec = avgVec + newMesh->getVertex(r + 1, c);

			/* Sum up the connected faces. */
			if(c > 0)
			{
				avgVec = avgVec + newMesh->getVertex(r, c - 1);
				n++;
			}
			if(c < newMesh->getCols()-1)
			{
				avgVec = avgVec + newMesh->getVertex(r, c + 1);
				n++;
			}

			avgVec = avgVec / n;

			newMesh->setVertex(r, c, avgVec);
		}
	}
	
	///////////////////////////////////////////////////////////////////
	// Update the original vertices to be an weighted average of the //
	// surrounding face centres, edge midpoints, and vertex.         //
	///////////////////////////////////////////////////////////////////
	for (unsigned int r = 0, origR = 0; r < newMesh->getRows(); r += 2, 
		origR++)
	{
		for (unsigned int c = 0, origC = 0; c < newMesh->getRows(); c += 2, 
			origC++)
		{
			/* Sum up faces the vertex is part of. */
			vec4 faceAvg = vec4(0, 0, 0, 0);
			float f = 0;
			if(r > 0 && c > 0)
			{
				faceAvg = faceAvg + newMesh->getVertex(r - 1, c - 1);
				f++;
			}
			if(r > 0 && c < newMesh->getCols()-1)
			{
				faceAvg = faceAvg + newMesh->getVertex(r - 1, c + 1);
				f++;
			}
			if(r < newMesh->getRows()-1 && c > 0)
			{
				faceAvg = faceAvg + newMesh->getVertex(r + 1, c - 1);
				f++;
			}
			if(r < newMesh->getRows()-1 && c < newMesh->getCols()-1)
			{
				faceAvg = faceAvg + newMesh->getVertex(r + 1, c + 1);
				f++;
			}
			/* Average */
			faceAvg = faceAvg / f;

			/* Sum up all of the edge midpoints connected to the vertex. */
			vec4 edgeAvg = vec4(0, 0, 0, 0);
			float valence = 0.0;
			/* Up Edge */
			if(r > 0)
			{
				vec4 edgeMid = (this->getVertex(origR, origC) +
					this->getVertex(origR - 1, origC)) / 2.0f;
				edgeAvg = edgeAvg + edgeMid;
				valence++;
			}
			/* Down Edge */
			if(r < newMesh->getRows()-1)
			{
				vec4 edgeMid = (this->getVertex(origR, origC) +
					this->getVertex(origR + 1, origC)) / 2.0f;
				edgeAvg = edgeAvg + edgeMid;
				valence++;
			}
			/* Left Edge */
			if(c > 0)
			{
				vec4 edgeMid = (this->getVertex(origR, origC) +
					this->getVertex(origR, origC - 1)) / 2.0f;
				edgeAvg = edgeAvg + edgeMid;
				valence++;
			}
			/* Right Edge */
			if(c < newMesh->getCols()-1)
			{
				vec4 edgeMid = (this->getVertex(origR, origC) +
					this->getVertex(origR, origC + 1)) / 2.0f;
				edgeAvg = edgeAvg + edgeMid;
				valence++;
			}
			/* Average */
			edgeAvg = edgeAvg / valence;

			/* Move the vertex. */
			vec4 origV = newMesh->getVertex(r, c);

			/* Update the vertex. */
			valence += f;
			vec4 newVertex = (faceAvg + (2 * edgeAvg) + (valence-3)*origV) / 
				valence;
			newMesh->setVertex(r, c, newVertex);
		}
	}

	return newMesh;
}

/* Draws this mesh out to 3D space. */
void Mesh::draw(bool displayEdges, bool displayFaces) const
{
	/* Draw the vertices */
	for (unsigned int r = 0; r < this->vertices->size()-1; r++)
	{
		for (unsigned int c = 0; c < this->vertices->at(0)->size()-1; c++)
		{
			std::vector<vec4>* row1 = this->vertices->at(r);
			std::vector<vec4>* row2 = this->vertices->at(r + 1);
			
			/* If the edges are choosen to be displayed. */
			if(displayEdges)
			{
				glColor3f(WHITE);

				/* Draw triangle one */
				glBegin(GL_LINE_LOOP);
					glVertex3f(row1->at(c)[0], row1->at(c)[1], row1->at(c)[2]);
					glVertex3f(row2->at(c+1)[0], row2->at(c+1)[1], 
						row2->at(c+1)[2]);
					glVertex3f(row2->at(c)[0], row2->at(c)[1], row2->at(c)[2]);
				glEnd();

				/* Draw triangle two */
				glBegin(GL_LINE_LOOP);
					glVertex3f(row1->at(c)[0], row1->at(c)[1], row1->at(c)[2]);
					glVertex3f(row1->at(c+1)[0], row1->at(c+1)[1], 
						row1->at(c+1)[2]);
					glVertex3f(row2->at(c+1)[0], row2->at(c+1)[1], 
						row2->at(c+1)[2]);
				glEnd();
			}

			if(displayFaces)
			{
				//glColor3f(this->color->getRed(), this->color->getGreen(), 
				//	this->color->getBlue());

				/* Draw triangle one */
				glBegin(GL_POLYGON);
					/* Vertex 1 */
					this->colorVertices(row1->at(c)[1]);
					glVertex3f(row1->at(c)[0], row1->at(c)[1], row1->at(c)[2]);

					/* Vertex 2 */
					this->colorVertices(row2->at(c+1)[1]);
					glVertex3f(row2->at(c+1)[0], row2->at(c+1)[1], 
						row2->at(c+1)[2]);

					/* Vertex 3 */
					this->colorVertices(row2->at(c)[1]);
					glVertex3f(row2->at(c)[0], row2->at(c)[1], row2->at(c)[2]);
				glEnd();

				/* Draw triangle two */
				glBegin(GL_POLYGON);
					/* Vertex 1 */
					this->colorVertices(row1->at(c)[1]);
					glVertex3f(row1->at(c)[0], row1->at(c)[1], row1->at(c)[2]);

					/* Vertex 2 */
					this->colorVertices(row1->at(c+1)[1]);
					glVertex3f(row1->at(c+1)[0], row1->at(c+1)[1], 
						row1->at(c+1)[2]);

					/* Vertex 3 */
					this->colorVertices(row2->at(c+1)[1]);
					glVertex3f(row2->at(c+1)[0], row2->at(c+1)[1], 
						row2->at(c+1)[2]);
				glEnd();
			}
		}
	}
}

/* Set the color of for gl based on the given height and the snow */
/* cap height. Color white if above snow height, default color    */
/* otherwise.                                                     */
void Mesh::colorVertices(const float y) const
{
	/* Color white if above snow height. */
	if(y >= this->snowCapHeight)
	{
		glColor3f(WHITE);
	}
	/* Default color otherwise. */
	else
	{
		glColor3f(this->color->getRed(), this->color->
			getGreen(), this->color->getBlue());
	}
}
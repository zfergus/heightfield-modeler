/*
 * MeshModeler.cpp
 * Created by Zachary Ferguson
 * Source for the MeshModeler class, a class that puts a GUI around the 
 * GL3DWindow.
 */

#include "MeshModeler.h"

/* Constructor for creating a new MeshModeler.                               */
/* Requires the x,y coordinates and the width and height of the window. Also */
/* requires a char* for the label.                                           */
MeshModeler::MeshModeler(int x, int y, int w, int h, const char* label) :
	Fl_Window(x, y, w, h, label)
{
	/* Create the starting mesh. */
	this->mesh = new Mesh(4, 4, 10, 10, new Color(BLUE), 1.5);

	/* Create the GL3DWindow to display the mesh in. */
	this->gl3DWin = new GL3DWindow(0, 0, h, h, "3D Modeler", this->mesh, true, 
		true);

	Fl_Menu_Bar* menu = new Fl_Menu_Bar(h, 0, w-h, 24, "Mesh Modeler");
	menu->box(FL_BORDER_BOX);
	menu->down_box(FL_BORDER_BOX);
	menu->add("File/Save", 0, MeshModeler::saveCB, this);
	menu->add("File/Exit", 0, MeshModeler::exitCB, this);
	menu->add("Help/How To Use", 0, MeshModeler::helpCB, this);
	menu->add("Help/About", 0, MeshModeler::aboutCB, this);

	/* Create the color chooser. */
	this->colorChooser = new Fl_Color_Chooser(h+5, menu->h() + 6, 175, 100);
	this->colorChooser->rgb(BLUE);
	this->colorChooser->callback(MeshModeler::colorCB, this);
	
	/* Create the create mesh group. */
	this->newMesh = new CreateMeshGroup(this->colorChooser->x() + 
		this->colorChooser->w()+5, this->colorChooser->y(), 
		this->mesh->getRows()-1, this->mesh->getCols()-1, 
		this->mesh->getWidth(), this->mesh->getDepth());
	this->newMesh->callback(MeshModeler::newMeshCB, this);

	/* Range of the randomize. */
	this->randomizeSlider = makeHorizSlider(this->colorChooser->x(), 
		this->colorChooser->y() + this->colorChooser->h() + 17, 
		this->colorChooser->w(), 24, "Randomize Range", 0, 50, 4.0, 0.1);

	/* Create a randomize button. */
	this->randomizeB = new Fl_Button(this->randomizeSlider->x(), 
		this->randomizeSlider->y() + this->randomizeSlider->h() + 5, 
		this->randomizeSlider->w(), 24,"Randomize Heights");
	this->randomizeB->callback(MeshModeler::randomizeCB, this);

	/* Create a flatten button. */
	this->flattenB = new Fl_Button(this->randomizeB->x(), 
		this->randomizeB->y() + this->randomizeB->h() + 5, 
		this->randomizeB->w(), 24, "Flatten Mesh");
	this->flattenB->callback(MeshModeler::flattenCB, this);

	/* Create the height editing group. */
	this->heightEditor = new HeightEditorGroup(this->flattenB->x(),
		this->flattenB->y() + this->flattenB->h() + 10, this->mesh->getRows(),
		this->mesh->getCols());
	this->heightEditor->indexCallback(MeshModeler::selectIndexCB, this);
	this->heightEditor->heightCallback(MeshModeler::changeHeightCB, this);
	this->selectedIndecies = NULL;

	/* Slider for changing the snow cap height. */
	this->snowHeightSlider = makeHorizSlider(this->heightEditor->x(), 
		this->heightEditor->y() + this->heightEditor->h() + 25, 
		this->heightEditor->w(), 24, "Snow Cap Height", -26, 26, 
		this->mesh->getSnowCapHeight(), 0.1);
	this->snowHeightSlider->callback(MeshModeler::changeSnowHeightCB, this);
	
	/* Slider for the number of fractilization iterations. */
	this->fractalizeSlider = makeHorizSlider(this->snowHeightSlider->x(), 
		this->snowHeightSlider->y() + this->snowHeightSlider->h() + 25, 
		this->snowHeightSlider->w()/2, 24, "Fractalize Iterations", 0, 5);
	/* Button for fractalizing the mesh. */
	this->fractalizeB = new Fl_Button(this->fractalizeSlider->x() + 
		this->fractalizeSlider->w() + 5, this->fractalizeSlider->y(), 
		this->fractalizeSlider->w(), 24, "Fractalize Mesh");
	this->fractalizeB->callback(MeshModeler::fractalizeCB, this);

	/* Slider for the number of fractilization iterations. */
	this->smoothSlider = makeHorizSlider(this->fractalizeSlider->x(), 
		this->fractalizeSlider->y() + this->fractalizeSlider->h() + 25, 
		this->fractalizeSlider->w(), 24, "Smooth Iterations", 0, 5);
	/* Button for fractalizing the mesh. */
	this->smoothB = new Fl_Button(this->smoothSlider->x() + 
		this->smoothSlider->w() + 5, this->smoothSlider->y(), 
		this->smoothSlider->w(), 24, "Smooth Mesh");
	this->smoothB->callback(MeshModeler::smoothCB, this);

	/* Create the view mode group. */
	this->viewMode = new ViewModeGroup(w-297, h-117);
	this->viewMode->callback(MeshModeler::viewModeCB, this);

	/* Create the camera control group. */
	this->cameraControls = new CameraControlGroup(w-183, h-117);
	this->cameraControls->callback(GL3DWindow::cameraAlignCB, this->gl3DWin);

	/* Sets this mesh modeler as the Fl focus. */
	Fl::focus(this);
}

/* Makes a horizontal slider with the given specs. */
Fl_Value_Slider* makeHorizSlider(int x, int y, int w, int h, const char* label,
	float min, float max,  double value, double step)
{
	Fl_Value_Slider* slider = new Fl_Value_Slider(x, y, w, h, label);
	
	slider->value(value);
	slider->type(1);
	slider->box(FL_BORDER_BOX);
	slider->minimum(min);
	slider->maximum(max);
	slider->step(step);
	slider->align(Fl_Align(FL_ALIGN_TOP));

	return slider;
}

/* Destructor for this MeshModeler. */
MeshModeler::~MeshModeler()
{
	/* Delete GL3DWindow and mesh. */
	delete this->gl3DWin;
	/* Delete the vector of selected indecies. */
	delete this->selectedIndecies;
	/* Delete the widgets. */
	delete this->newMesh;
	delete this->colorChooser;
	delete this->flattenB;
	delete this->viewMode;
	delete this->cameraControls;
	delete this->heightEditor;
	delete this->snowHeightSlider;
	delete this->fractalizeSlider;
	delete this->fractalizeB;
	delete this->smoothSlider;
	delete this->smoothB;
	delete this->helpBox;
}

/**********************/
/* Callback Functions */
/**********************/

/* Creates a new mesh for the GL3DWindow. */
void MeshModeler::newMeshCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;

	/* Delete the old mesh. */
	delete modeler->mesh;

	/* Get the new mesh's property. */
	int rows = modeler->newMesh->getRowsValue();
	int cols = modeler->newMesh->getColsValue();
	float width = modeler->newMesh->getWidthValue();
	float depth = modeler->newMesh->getDepthValue();
	Color* color = new Color((float)modeler->colorChooser->r(), 
		(float)modeler->colorChooser->g(), (float)modeler->colorChooser->b());
	float snowCapHeight = (float)modeler->snowHeightSlider->value();

	/* Create the new mesh. */
	modeler->mesh = new Mesh(rows, cols, width, depth, color, snowCapHeight);

	/* Set the mesh of the gl3DWin. */
	modeler->gl3DWin->setMesh(modeler->mesh);

	/* Set the height editor's values. */
	modeler->heightEditor->setRow(0);
	modeler->heightEditor->setCol(0);
	modeler->heightEditor->setRows(modeler->mesh->getRows());
	modeler->heightEditor->setCols(modeler->mesh->getCols());
	MeshModeler::selectIndexCB(NULL, modeler);
	
	/* Redraw the gl3DWin. */
	modeler->gl3DWin->redraw();
	modeler->redraw();
}

/* Changes the current mesh's color. */
void MeshModeler::colorCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;

	Color* color = new Color((float)modeler->colorChooser->r(), 
		(float)modeler->colorChooser->g(), (float)modeler->colorChooser->b());

	modeler->mesh->setColor(color);

	modeler->gl3DWin->redraw();
}

/* Callbacks for setting if the elements should be drawn. */
void MeshModeler::viewModeCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;
	
	switch(modeler->viewMode->getViewMode())
	{
		/* If draw wireframe is selected. */
		case WIREFRAME:
			modeler->gl3DWin->setDrawEdges(true);
			modeler->gl3DWin->setDrawFaces(false);
			break;
		/* If draw solid is selected. */
		case SOLID:
			modeler->gl3DWin->setDrawEdges(false);
			modeler->gl3DWin->setDrawFaces(true);
			break;
		/* If draw both is selected. */
		case BOTH:
			modeler->gl3DWin->setDrawEdges(true);
			modeler->gl3DWin->setDrawFaces(true);
			break;
	}

	modeler->gl3DWin->redraw();
}

/* Callback function for selecting a vertex in the mesh. */
void MeshModeler::selectIndexCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;
	modeler->selectedIndecies = modeler->gl3DWin->selectMeshIndex(modeler->
		heightEditor->getRow(), modeler->heightEditor->getCol());
	modeler->updateHeightSlider();
}

/* Callback for the height slider. */
void MeshModeler::changeHeightCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;
	if(modeler->selectedIndecies)
	{
		unsigned int row = modeler->selectedIndecies->at(0);
		unsigned int col = modeler->selectedIndecies->at(1);
		float height = modeler->heightEditor->getHeight();
		modeler->mesh->setHeight(row, col, height);
		modeler->gl3DWin->redraw();
	}
}

/* Callback for the snow cap height slider. */
void MeshModeler::changeSnowHeightCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;
	modeler->mesh->setSnowCapHeight((float)modeler->snowHeightSlider->value());
	modeler->gl3DWin->redraw();
}

/* Callback function for fractalizing the mesh of the data. */
void MeshModeler::fractalizeCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;

	for (int i = 0; i < modeler->fractalizeSlider->value(); i++)
	{
		Mesh* newMesh = modeler->mesh->fractalize();
		delete modeler->mesh;
		modeler->mesh = newMesh;
	}
	modeler->gl3DWin->setMesh(modeler->mesh);

	/* Set the height editor's values. */
	modeler->heightEditor->setRow(0);
	modeler->heightEditor->setCol(0);
	modeler->heightEditor->setRows(modeler->mesh->getRows());
	modeler->heightEditor->setCols(modeler->mesh->getCols());
	MeshModeler::selectIndexCB(NULL, modeler);

	modeler->gl3DWin->redraw();
}

/* Callback function for fractalizing the mesh of the data. */
void MeshModeler::smoothCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;

	for (int i = 0; i < modeler->smoothSlider->value(); i++)
	{
		Mesh* newMesh = modeler->mesh->smooth();
		delete modeler->mesh;
		modeler->mesh = newMesh;
	}
	modeler->gl3DWin->setMesh(modeler->mesh);

	/* Set the height editor's values. */
	modeler->heightEditor->setRow(0);
	modeler->heightEditor->setCol(0);
	modeler->heightEditor->setRows(modeler->mesh->getRows());
	modeler->heightEditor->setCols(modeler->mesh->getCols());
	MeshModeler::selectIndexCB(NULL, modeler);

	modeler->gl3DWin->redraw();
}

/* Callback function for randomizing the mesh's heights. */
void MeshModeler::randomizeCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;

	float range = (float)(modeler->randomizeSlider->value());

	/* Set all vertices' heights to zero. */
	for (unsigned int r = 0; r < modeler->mesh->getRows(); r++)
	{
		for (unsigned int c = 0; c < modeler->mesh->getCols(); c++)
		{
			modeler->mesh->setHeight(r, c, 
				(((float)rand()/(float)RAND_MAX) * range) - (range/2.0f));
		}
	}

	/* Update the height editors value. */
	if(modeler->selectedIndecies)
	{
		modeler->heightEditor->setHeight((modeler->mesh->getVertex(
			modeler->selectedIndecies->at(0), 
			modeler->selectedIndecies->at(1)))[1]);
	}
	else
	{
		modeler->heightEditor->setHeight(0);
	}

	modeler->gl3DWin->redraw();
}

/* Callback function for flattening the mesh. */
void MeshModeler::flattenCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;

	/* Set all vertices' heights to zero. */
	for (unsigned int r = 0; r < modeler->mesh->getRows(); r++)
	{
		for (unsigned int c = 0; c < modeler->mesh->getCols(); c++)
		{
			modeler->mesh->setHeight(r, c, 0);
		}
	}

	/* Update the height editors value. */
	modeler->heightEditor->setHeight(0);

	modeler->gl3DWin->redraw();
}

/* Save the current mesh in the mesh modeler, data, to and obj file. */
void MeshModeler::saveCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;
	modeler->deactivate();
	const char* filename = fl_file_chooser("Save Mesh", "*",  "NewMesh.obj",  
		0);

	if(!filename)
	{
		modeler->activate();
		return;
	}

	std::cout << "Saving to " << filename << std::endl;

	const char* mtlFilename = strcat(extractFilename(filename), ".mtl");
	//std::cout << extractFilename(filename) << std::endl;
	std::ofstream outFile(mtlFilename, std::ios::out);
	if(!(outFile.is_open()))
	{
		std::cout << "Unable to save to " << mtlFilename << std::endl;
		modeler->activate();
		return;
	}

	/* Write out the materal file. */
	outFile << "newmtl snow"	<< std::endl
			<< "illum 4"		<< std::endl
			<< "Kd 1.0 1.0 1.0" << std::endl
			<< "Ka 0.0 0.0 0.0" << std::endl
			<< "Tf 1.0 1.0 1.0" << std::endl
			<< "Ni 1.00"		<< std::endl
			<< std::endl
			<< "newmtl color"	<< std::endl
			<< "illum 4"		<< std::endl
			<< "Kd "
				<< modeler->mesh->getColor()->toString()
				<< std::endl
			<< "Ka 0.0 0.0 0.0" << std::endl
			<< "Tf 1.0 1.0 1.0" << std::endl
			<< "Ni 1.00"		<< std::endl;

	outFile.close();

	/* Save the mesh to an OBJ file. */
	outFile = std::ofstream(filename, std::ios::out);
	if(!(outFile.is_open()))
	{
		std::cout << "Unable to save to " << filename << std::endl;
		modeler->activate();
		return;
	}
	
	/* Write out the header. */
	outFile << "########################################################" 
			<< std::endl << "#"<< std::endl;
	outFile << "# Created with Mesh Modeler(Copyright Zachary Ferguson)"
		<< std::endl;
	outFile << "#" << std::endl 
			<< "########################################################" 
			<< std::endl;
	outFile << "#" << std::endl
			<< "# Vertices: " << 
				(modeler->mesh->getRows() * modeler->mesh->getCols())
			<< std::endl
			<< "# Faces: "    <<
			2 * (modeler->mesh->getRows()-1) * (modeler->mesh->getCols()-1)
			<< std::endl
			<< "#" << std::endl 
			<< "########################################################" 
			<< std::endl;
		
	const char* mtlName = extractName(mtlFilename);
	outFile << "mtllib " << mtlName << std::endl;

	/* Write out the vertices of the mesh. */
	for (unsigned int r = 0; r < modeler->mesh->getRows(); r++)
	{
		for (unsigned int c = 0; c < modeler->mesh->getCols(); c++)
		{
			vec4 vertex = modeler->mesh->getVertex(r, c);
			outFile << "v " << vertex[0] << " " << vertex[1] << " "
				<< vertex[2] << std::endl;
				
			//float height = modeler->mesh->getSnowCapHeight();
			///* Write out the color of the vertex. */
			//if(vertex[1] >= height)
			//{
			//	outFile << " 1.0 1.0 1.0" << std::endl;
			//}
			//else
			//{
			//	outFile << " " << modeler->mesh->getColor()->toString() 
			//			<< std::endl;
			//}
		}
	}
		
	/* Write out the faces of the mesh. */
	float snowHeight = modeler->mesh->getSnowCapHeight();
	for (unsigned int r = 1; r < modeler->mesh->getRows(); r++)
	{
		for (unsigned int c = 1; c < modeler->mesh->getCols(); c++)
		{
			int v1 = (r-1) * modeler->mesh->getCols() + c;
			int v2 = v1 + 1;
			int v3 = v1 + modeler->mesh->getCols();
			int v4 = v3 + 1;

			/* Write out the color of the vertex. */
			vec4 vertex = modeler->mesh->getVertex(r-1, c-1);
			outFile << ((vertex[1] >= snowHeight) ? ("usemtl snow") : 
				("usemtl color")) << std::endl;
			outFile << "f " << v1 << " " << v4 << " " << v2 << std::endl;
			outFile << "f " << v1 << " " << v3 << " " << v4 << std::endl;
		}
	}

	outFile.close();

	modeler->activate();
}

/* Extracts the filename with out the extension of the given char*. */
char* extractFilename(const char* filename)
{
	char* extractedName = new char[strlen(filename)];
	strcpy(extractedName, filename);

	for (int i = strlen(filename) - 1; i >= 0; i--)
	{
		if(extractedName[i] == '.')
		{
			extractedName[i] = 0;
			break;
		}
	}

	return extractedName;
}

/* Extracts the filename, without the path, of the given char*. */
const char* extractName(const char* filename)
{
	for (int i = strlen(filename) - 1; i >= 0; i--)
	{
		if(filename[i] == '/')
		{
			char* extractedName = new char[strlen(&(filename[i+1]))];
			strcpy(extractedName, &(filename[i + 1]));
			return extractedName;
		}
	}

	return filename;
}

/* Exit the mesh modeler. */
void MeshModeler::exitCB(Fl_Widget* w, void* data)
{
	delete data;
	exit(0);
}

/* Display the Help window. */
void MeshModeler::helpCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;
	if (modeler->helpBox)
		delete modeler->helpBox;
	modeler->helpBox = new HelpBox(modeler->x(), modeler->y(), 720, 350, 
		"help.txt", "Help");
	modeler->helpBox->show();
}

/* Display the About window. */
void MeshModeler::aboutCB(Fl_Widget* w, void* data)
{
	MeshModeler* modeler = (MeshModeler*)data;
	if (modeler->aboutBox)
		delete modeler->aboutBox;
	modeler->aboutBox = new HelpBox(modeler->x(), modeler->y(), 720, 350, 
		"about.txt", "About");
	modeler->aboutBox->show();
}

/********************/
/* Update Functions */
/********************/

/* Update the height slider's value. */
void MeshModeler::updateHeightSlider()
{
	if(this->selectedIndecies)
	{
		float y = (this->mesh->getVertex(this->selectedIndecies->at(0),
			this->selectedIndecies->at(1)))[1];
		this->heightEditor->setHeight(y);
	}
}

/* Update the index spinners' values. */
void MeshModeler::updateIndexSpinners()
{
	if(this->selectedIndecies)
	{
		this->heightEditor->setRow(this->selectedIndecies->at(0));
		this->heightEditor->setCol(this->selectedIndecies->at(1));
	}
}

/********************/
/* Handle Functions */
/********************/

/* Method in FL_GL_Window class for handling FLTK events. */
/* Moves the camera around according to key presses.      */
int MeshModeler::handle(int event)
{
	/* MeshModeler does not handle draging. */
	/* Prevent stack overflow exception.    */
	if(event == FL_DRAG)
	{
		return 0;
	}
	
	if (event == FL_FOCUS)
	{
		return 1;
	}

	/* If mouse clicked. */
	if(event == FL_PUSH && Fl::event_x() <= this->gl3DWin->w() && 
		Fl::event_y() <= this->gl3DWin->h())
	{
		Fl::focus(this->gl3DWin);
		this->handlePush();
		return 1;
	}

	/* Handle the event with the gl3DWin and then the Fl_Window. */
	return this->gl3DWin->handle(event) || Fl_Window::handle(event);
}

/* Handle the mouse clicks on the GL3DWindow. */
void MeshModeler::handlePush()
{
	ray userRay = this->gl3DWin->getRayFromPush();

	/* Check for the vertices that the ray passes through, within a radius */
	/* of r from the vertex.                                               */
	this->selectedIndecies = this->gl3DWin->selectMeshIndex(this->mesh->
		selectVertex(userRay));

	/* Update the height editor. */
	this->updateHeightSlider();
	this->updateIndexSpinners();

	this->gl3DWin->redraw();
}
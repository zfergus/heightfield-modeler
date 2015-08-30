/*
 * MeshModeler.h
 * Created by Zachary Ferguson
 * Header for the MeshModeler class, a class that puts a GUI around the 
 * GL3DWindow.
 */

#ifndef MESHMODELER_H
#define MESHMODELER_H

#define _CRT_SECURE_NO_WARNINGS

#include <FL/Fl_Window.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_ask.H>
#include "CreateMeshGroup.h"
#include "ViewModeGroup.h"
#include "CameraControlGroup.h"
#include "HeightEditorGroup.h"
#include "HelpBox.h"
#include "GL3DWindow.h"

class MeshModeler : public Fl_Window
{
	private:
	
		/* GL3DWindow for drawing out the mesh. */
		GL3DWindow* gl3DWin;

		/* 3D Mesh to draw out to the screen. */
		Mesh* mesh;

		/* Selected row and col of the mesh. */
		const std::vector<unsigned int>* selectedIndecies;

		/* Group for the new mesh's properties. */
		CreateMeshGroup* newMesh;
		/* Color chooser for the mesh's color */
		Fl_Color_Chooser* colorChooser;
		/* Button for randomizing the mesh. */
		Fl_Button* randomizeB;
		/* Range of the randomize. */
		Fl_Value_Slider* randomizeSlider;
		/* Button for flattening the mesh. */
		Fl_Button* flattenB;
		/* Group for the view mode selection. */
		ViewModeGroup* viewMode;
		/* Group for the camera controls. */
		CameraControlGroup* cameraControls;
		/* Group for the height editing controls. */
		HeightEditorGroup* heightEditor;
		/* Slider for changing the snow cap height. */
		Fl_Value_Slider* snowHeightSlider;
		/* Slider for the number of fractilization iterations. */
		Fl_Value_Slider* fractalizeSlider;
		/* Button to fractalize the mesh. */
		Fl_Button* fractalizeB;
		/* Slider for the number of smoothing iterations. */
		Fl_Value_Slider* smoothSlider;
		/* Button to smooth the mesh. */
		Fl_Button* smoothB;
		/* Window for displaying help info. */
		HelpBox* helpBox;
		/* Window for displaying help info. */
		HelpBox* aboutBox;
		
		/* Creates a new mesh for the GL3DWindow. */
		static void newMeshCB(Fl_Widget* w, void* data);
		/* Changes the current mesh's color. */
		static void colorCB(Fl_Widget* w, void* data);
		/* Callbacks for setting if the elements should be drawn. */
		static void viewModeCB(Fl_Widget* w, void* data);
		/* Callback function for selecting a vertex in the mesh. */
		static void selectIndexCB(Fl_Widget* w, void* data);
		/* Callback for the height slider. */
		static void changeHeightCB(Fl_Widget* w, void* data);
		/* Callback for the snow cap height slider. */
		static void changeSnowHeightCB(Fl_Widget* w, void* data);
		/* Callback function for fractalizing the mesh. */
		static void fractalizeCB(Fl_Widget* w, void* data);
		/* Callback function for smoothing the mesh. */
		static void smoothCB(Fl_Widget* w, void* data);
		/* Callback function for randomizing the mesh's heights. */
		static void randomizeCB(Fl_Widget* w, void* data);
		/* Callback function for flattening the mesh. */
		static void flattenCB(Fl_Widget* w, void* data);
		/* Save the current mesh in the mesh modeler, data, to and obj file. */
		static void saveCB(Fl_Widget* w, void* data);
		/* Exit the mesh modeler. */
		static void exitCB(Fl_Widget* w, void* data);
		/* Displays a help window for the mesh modeler. */
		static void helpCB(Fl_Widget* w, void* data);
		/* Display the About window. */
		static void aboutCB(Fl_Widget* w, void* data);
		
		/* Update the height sliders value. */
		void updateHeightSlider();
		/* Update the index spinners' values. */
		void updateIndexSpinners();
		
		/* Handle the mouse clicks on the GL3DWindow. */
		void handlePush();

	public:
		
		/* Constructor for creating a new MeshModeler.                  */
		/* Requires the x,y coordinates and the width and height of the */
		/* window. Also requires a char* for the label.                 */
		MeshModeler(int x, int y, int w, int h, const char* label);

		/* Destructor for this MeshModeler. */
		virtual ~MeshModeler();

		/* Method in FL_GL_Window class for handling FLTK events. */
		/* Moves the camera around according to key presses.      */
		int handle(int event);
};

/* Makes a horizontal slider with the given specs. */
Fl_Value_Slider* makeHorizSlider(int x, int y, int w, int h, const char* label,
	float min, float max, double value = 1.0, double step = 1.0);

/* Extracts the filename, without the extension, of the given char*. */
char* extractFilename(const char* filename);

/* Extracts the filename, without the path, of the given char*. */
const char* extractName(const char* filename);

#endif
#pragma once

#include "meshLoader/mesh.h"
#include "maths/matrix.h"
#include <string>

#include "graph/scenegraph.cpp"
#define _USE_MATH_DEFINES
#include <math.h>


namespace cgj {

	struct scene {

		static void createTangramSceneGraph(scenegraph* current_scenegraph);
		static void createSkyboxSceneGraph(scenegraph* current_scenegraph);
		static void createWaterSceneGraph(scenegraph* current_scenegraph);
		static void createIslandSceneGraph(scenegraph* current_scenegraph);
		static void createSceneGraph(scenegraph* current_scenegraph, float win_rx, float win_ry);
		static void update(scenegraph* current_scenegraph, float time_elapsed);

		static void KeyPressed(int key, scenegraph* current_scenegraph);
		static void KeyReleased(int key, scenegraph* current_scenegraph);


	};
}
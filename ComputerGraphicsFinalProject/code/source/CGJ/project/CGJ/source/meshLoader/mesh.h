#pragma once

#include "../util/filereader.h"
#include "../maths/matrix.h"
#include <iostream>
//#include <list>
#include <vector>

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2
#include <GL/glew.h>

namespace cgj {
		typedef struct {
			GLfloat x, y, z;
		} Vertex;

		typedef struct {
			GLfloat u, v;
		} Texcoord;

		typedef struct {
			GLfloat nx, ny, nz;
		} Normal;



		struct mesh {
			GLuint vao_id;

			vec4 color;

			bool TexcoordsLoaded, NormalsLoaded;

			std::vector <Vertex> Vertices, vertexData;
			std::vector <Texcoord> Texcoords, texcoordData;
			std::vector <Normal> Normals, normalData;

			std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;

			mesh() {}

			void parseVertex(std::stringstream& sin);
			void parseTexcoord(std::stringstream& sin);
			void parseNormal(std::stringstream& sin);
			void parseFace(std::stringstream& sin);

			void parseLine(std::stringstream& sin);

			void loadMeshData(std::string& filename);

			void processMeshData();
			void freeMeshData();


			void create_mesh();
			void destroy_mesh_data();
			//const void createMesh(std::string& filename);

			//mesh();

			mesh(std::string& filename);

			void draw();
		};
}
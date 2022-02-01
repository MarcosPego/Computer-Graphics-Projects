
#include "mesh.h"
#include <iostream>

using namespace cgj::util;

namespace cgj {
	
	void mesh::parseVertex(std::stringstream& sin)
	{
		Vertex v;
		sin >> v.x >> v.y >> v.z;
		vertexData.push_back(v);
	}

	void mesh::parseTexcoord(std::stringstream& sin)
	{
		Texcoord t;
		sin >> t.u >> t.v;
		texcoordData.push_back(t);
	}

	void mesh::parseNormal(std::stringstream& sin)
	{
		Normal n;
		sin >> n.nx >> n.ny >> n.nz;
		normalData.push_back(n);
	}

	void mesh::parseFace(std::stringstream& sin)
	{
		std::string token;
		if (normalData.empty() && texcoordData.empty())
		{
			for (int i = 0; i < 3; i++)
			{
				sin >> token;
				vertexIdx.push_back(std::stoi(token));
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				std::getline(sin, token, '/');
				if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
				std::getline(sin, token, '/');
				if (token.size() > 0) texcoordIdx.push_back(std::stoi(token));
				std::getline(sin, token, ' ');
				if (token.size() > 0) normalIdx.push_back(std::stoi(token));
			}
		}
	}

	void mesh::parseLine(std::stringstream& sin)
	{
		std::string s;
		sin >> s;
		if (s.compare("v") == 0) parseVertex(sin);
		else if (s.compare("vt") == 0) parseTexcoord(sin);
		else if (s.compare("vn") == 0) parseNormal(sin);
		else if (s.compare("f") == 0) parseFace(sin);
	}

	void mesh::loadMeshData(std::string& filename)
	{
		std::ifstream ifile(filename);
		std::string line;
		while (std::getline(ifile, line)) {
			std::stringstream sline(line);
			parseLine(sline);
		}
		TexcoordsLoaded = (texcoordIdx.size() > 0);
		NormalsLoaded = (normalIdx.size() > 0);
	}

	void mesh::processMeshData()
	{
		for (unsigned int i = 0; i < vertexIdx.size(); i++) {
			unsigned int vi = vertexIdx[i];
			Vertex v = vertexData[vi - 1];
			Vertices.push_back(v);
			if (TexcoordsLoaded) {
				unsigned int ti = texcoordIdx[i];
				Texcoord t = texcoordData[ti - 1];
				Texcoords.push_back(t);
			}
			if (NormalsLoaded) {
				unsigned int ni = normalIdx[i];
				Normal n = normalData[ni - 1];
				Normals.push_back(n);
			}	
		}
	}

	void mesh::freeMeshData()
	{
		vertexData.clear();
		texcoordData.clear();
		normalData.clear();
		vertexIdx.clear();
		texcoordIdx.clear();
		normalIdx.clear();
	}

	mesh::mesh(std::string& filename)
	{
		loadMeshData(filename);
		processMeshData();
		freeMeshData();
	}


	void mesh::create_mesh()
	{
		GLuint VboVertices, VboTexcoords, VboNormals;

		glGenVertexArrays(1, &vao_id);
		glBindVertexArray(vao_id);
		{
			glGenBuffers(1, &VboVertices);
			glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
			glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

			if (TexcoordsLoaded)
			{
				glGenBuffers(1, &VboTexcoords);
				glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
				glBufferData(GL_ARRAY_BUFFER, Texcoords.size() * sizeof(Texcoord), &Texcoords[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(TEXCOORDS);
				glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Texcoord), 0);
			}
			if (NormalsLoaded)
			{
				glGenBuffers(1, &VboNormals);
				glBindBuffer(GL_ARRAY_BUFFER, VboNormals);
				glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(Normal), &Normals[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(NORMALS);
				glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Normal), 0);
			}
		}
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &VboVertices);
		glDeleteBuffers(1, &VboTexcoords);
		glDeleteBuffers(1, &VboNormals);
	}

	void mesh::destroy_mesh_data() {
		glBindVertexArray(vao_id);
		glDisableVertexAttribArray(VERTICES);
		glDisableVertexAttribArray(TEXCOORDS);
		glDisableVertexAttribArray(NORMALS);
		glDeleteVertexArrays(1, &vao_id);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void mesh::draw() {
		glBindVertexArray(vao_id);

		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Vertices.size());

		glBindVertexArray(0);
	}
}
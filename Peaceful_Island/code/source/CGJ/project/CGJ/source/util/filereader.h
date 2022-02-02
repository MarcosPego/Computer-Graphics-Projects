#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <iterator>

namespace cgj {
	namespace util {
		struct filereader {
			static std::string read_shader_file(const char* shader_file);
			static std::list<std::string*> read_obj_file(const char* obj_file);
		};
	}



	/*std::string read_file(const char* filepath) {
		
		FILE* file = fopen(filepath, "rt");
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;

		
		//return "ola";
	}*/
}
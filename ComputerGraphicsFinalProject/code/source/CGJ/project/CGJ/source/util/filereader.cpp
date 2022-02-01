#include "filereader.h"


namespace cgj {
	namespace util {
		std::string filereader::read_shader_file(const char* shader_file)
		{
			// no feedback is provided for stream errors / exceptions.
			std::ifstream file(shader_file);
			if (!file) std::cerr << "Could not open file" << std::endl; ;

			file.ignore(std::numeric_limits<std::streamsize>::max());
			auto size = file.gcount();

			if (size > 0x10000) // 64KiB sanity check for shaders:
				return std::string();

			file.clear();
			file.seekg(0, std::ios_base::beg);

			std::stringstream sstr;
			sstr << file.rdbuf();
			file.close();

			return sstr.str();
		}

		std::list<std::string *> filereader::read_obj_file(const char* obj_file)
		{	
			std::list<std::string*> coord;

			std::ifstream file(obj_file);
			if (!file) std::cerr << "Could not open file" << std::endl; ;
			char buf[256];

			while (!file.eof())
			{
				file.getline(buf, 256);
				coord.push_back(new std::string(buf));
			}
			
			return coord;
		}
	}
}
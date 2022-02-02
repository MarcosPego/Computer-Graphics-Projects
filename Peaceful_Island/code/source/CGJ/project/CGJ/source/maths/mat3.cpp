#include "matrix.h"
#include <math.h>

namespace cgj {

	mat3::mat3() : data{ 0,0,0,0,0,0,0,0,0 } {
	}

	mat3::mat3(const float k) : data{ k,k,k,k,k,k,k,k,k } {
	}

	mat3::mat3(const float m0, const float m1, const float m2,
		const float m3, const float m4, const float m5,
		const float m6, const float m7, const float m8)
		: data{ m0 , m1 , m2, m3, m4 , m5 , m6, m7, m8} {
	}




	//Column major constructor
	mat3::mat3(const mat3& m) : data{
			m.data[0] , m.data[1] , m.data[2],
			m.data[3] , m.data[4] , m.data[5],
			m.data[6] , m.data[7] , m.data[8]
	} {
	}

	mat3::mat3(const mat4& m) : data{
			m.data[0] , m.data[1] , m.data[2],
			m.data[4] , m.data[5] , m.data[6],
			m.data[8] , m.data[9] , m.data[10]
	} {
	}


	void mat3::clean() {
		for (int i = 0; i < this->array_size; i++) {
			if (fabs(this->data[i]) < EPSILON) this->data[i] = 0.0f;
		}
	}

	mat3& mat3::operator - (const mat3& m) {
		for (int i = 0; i < m.array_size; i++) {
			this->data[i] = -m.data[i];
		}
		return(*this);
	}


	mat3 adjugate(const mat3& m) {
		mat3 new_matrix = mat3();
		new_matrix.data[0] =   m.data[4] * m.data[8] - m.data[5] * m.data[7];
		new_matrix.data[1] = -(m.data[3] * m.data[8] - m.data[5] * m.data[6]);
		new_matrix.data[2] =   m.data[3] * m.data[7] - m.data[4] * m.data[6];
		
		new_matrix.data[3] = -(m.data[1] * m.data[8] - m.data[2] * m.data[7]);
		new_matrix.data[4] = m.data[0] * m.data[8] - m.data[2] * m.data[6];
		new_matrix.data[5] = -(m.data[0] * m.data[7] - m.data[1] * m.data[6]);

		new_matrix.data[6] = m.data[1] * m.data[5] - m.data[2] * m.data[4];
		new_matrix.data[7] = -(m.data[0] * m.data[5] - m.data[2] * m.data[3]);
		new_matrix.data[8] = m.data[0] * m.data[4] - m.data[1] * m.data[3];

		return transpose(new_matrix);
	}

	float mat3::determiant() const {
		return this->data[0] * this->data[4] * this->data[8] + 
			this->data[3] * this->data[7] * this->data[2] +
			this->data[6] * this->data[1] * this->data[5] -
			this->data[6] * this->data[4] * this->data[2] - 
			this->data[3] * this->data[1] * this->data[8] -
			this->data[0] * this->data[7] * this->data[5];
	}

	mat3 transpose(const mat3& m) {
		mat3 new_matrix = mat3();
		for (int line = 0; line < 3; line++) {
			for (int col = 0; col < 3; col++) {
				new_matrix.data[line + col * 3] = m.data[line * 3 + col];
			}
		}
		return new_matrix;
	}

	mat3 inverse(const mat3& m) {
		mat3 new_matrix = mat3();
		mat3 adjugate_m = adjugate(m);
		for (int i = 0; i < m.array_size; i++) {
			new_matrix.data[i] = 1 / m.determiant() * adjugate_m.data[i];
		}
		return new_matrix;
	}

	mat3& mat3::operator+= (const mat3& m) {
		for (int i = 0; i < m.array_size; i++) {
			this->data[i] += m.data[i];
		}
		return(*this);
	};

	mat3& mat3::operator-= (const mat3& m) {
		for (int i = 0; i < m.array_size; i++) {
			this->data[i] -= m.data[i];
		}
		return(*this);
	};

	mat3& mat3::operator*= (const mat3& m) {
		mat3 new_matrix = mat3();
		new_matrix += (*this);
		//line
		for (int line = 0; line < 3; line++) {
			//col
			for (int col = 0; col < 3; col++) {
				//this->data[line + col * 3] = this->data[col] * m.data[line * 3] + this->data[col+3] * m.data[line * 3 + 1] + this->data[col + 6] * m.data[line * 3 + 2];
				new_matrix.data[line + col * 3] = this->data[line] * m.data[col * 3] + this->data[line + 3] * m.data[col * 3 + 1] + this->data[line + 6] * m.data[col * 3 + 2];
				
			}
		}
		for (int i = 0; i < new_matrix.array_size; i++) {
			this->data[i] = new_matrix.data[i];
		}

		return(*this);
	};


	const mat3 operator + (const mat3& m0, const mat3& m1) {

		mat3 new_matrix = mat3();
		new_matrix += m0;
		new_matrix += m1;

		return new_matrix;
	};

	const mat3 operator - (const mat3& m0, const mat3& m1) {
		mat3 new_matrix = mat3();
		new_matrix += m0;
		new_matrix -= m1;

		return new_matrix;
	};

	const mat3 operator * (const mat3& m0, const mat3& m1) {
		mat3 new_matrix = mat3();
		new_matrix += m0;
		new_matrix *= m1;

		return new_matrix;
	};

	const mat3 operator * (const mat3& m, const float k) {
		mat3 new_matrix = mat3();
		for (int i = 0; i < m.array_size; i++) {
			new_matrix.data[i] = m.data[i] * k;
		}
		return new_matrix;
	};

	const mat3 operator * (const float k, const mat3& m) {
		mat3 new_matrix = mat3();
		for (int i = 0; i < m.array_size; i++) {
			new_matrix.data[i] = m.data[i] * k;
		}
		return new_matrix;
	};

	const vec3 operator * (const mat3& m, const vec3& v) {
		vec3 new_vector = vec3();
		new_vector.x = v.x * m.data[0] + v.y * m.data[2] + v.z * m.data[6];
		new_vector.y = v.x * m.data[1] + v.y * m.data[4] + v.z * m.data[7];
		new_vector.z = v.x * m.data[2] + v.y * m.data[5] + v.z * m.data[8];

		return new_vector;
	};

	const bool operator == (const mat3& m0, const mat3& m1) {
		for (int i = 0; i < m0.array_size; i++) {
			if (fabs(m0.data[i] - m1.data[i]) > EPSILON)
			{
				return false;
			}
				
		}
		return true;
	}

	const bool operator != (const mat3& m0, const mat3& m1) {
		for (int i = 0; i < m0.array_size; i++) {
			if (fabs(m0.data[i] - m1.data[i]) > EPSILON)
			{
				return true;
			}
		}
		return false;
	}

	std::ostream& operator << (std::ostream& os, const mat3& m) {
		os << "{ " << m.data[0] << ", " << m.data[3] << ", " << m.data[6]
			<< "\n  \0" << m.data[1] << ", " << m.data[4] << ", " << m.data[7]
			<< "\n  \0" << m.data[2] << ", " << m.data[5] << ", " << m.data[8] << " }";
		return os;
	}

	std::istream& operator >> (std::istream& is, mat3& m) {
		for (int i = 0; i < m.array_size; i++) {
			is >> m.data[i];
		}
		return is;
	};
}
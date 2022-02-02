#include "matrix.h"


namespace cgj {


	mat2::mat2() : data{ 0,0,0,0 } {
	}

	mat2::mat2(const float k) : data{ k , k , k, k } {
	}
	mat2::mat2(const float m0, const float m1,
		const float m2, const float m3) 
		: data{ m0 , m1 , m2, m3 } {
	}

	void mat2::clean(){
		for (int i = 0; i < this->array_size; i++) {
			if (fabs(this->data[i]) < EPSILON) this->data[i] = 0.0f;
		}
	}

	//Column major constructor
	mat2::mat2(const mat2& m) 
		: data{ m.data[0] , m.data[1] , m.data[2], m.data[3] } {
	}

	mat2& mat2::operator - (const mat2& m) {
		for (int i = 0; i < m.array_size; i++) {
			this->data[i] = -m.data[i];
		}
		return(*this);
	}

	float mat2::determiant() const {
		return this->data[0] * this->data[3] - this->data[2] * this->data[1];
	}

	mat2 adjugate(const mat2& m) {
		mat2 new_matrix = mat2();
		new_matrix.data[0] = m.data[3];
		new_matrix.data[1] = -m.data[1];
		new_matrix.data[2] = -m.data[2];
		new_matrix.data[3] = m.data[0];
		return new_matrix;
	}

	mat2 transpose(const mat2& m) {
		mat2 new_matrix = mat2();
		for (int line = 0; line < 2; line++) {
			for (int col = 0; col < 2; col++) {
				new_matrix.data[line + col* 2] = m.data[line * 2 + col];
			}
		}
		return new_matrix;
	}

	mat2 inverse(const mat2& m) {
		mat2 new_matrix = mat2();
		mat2 adjugate_m = adjugate(m);
		for (int i = 0; i < m.array_size; i++) {
			new_matrix.data[i] = 1 / m.determiant() * adjugate_m.data[i];
		}
		return new_matrix;
	}

	mat2& mat2::operator+= (const mat2& m) {
		for (int i = 0; i < m.array_size; i++) {
			this->data[i] += m.data[i];
		}
		return(*this);
	};

	mat2& mat2::operator-= (const mat2& m) {
		for (int i = 0; i < m.array_size; i++) {
			this->data[i] -= m.data[i];
		}
		return(*this);
	};

	mat2& mat2::operator*= (const mat2& m) {
		mat2 new_matrix = mat2();
		new_matrix += (*this);
		//line
		for (int line = 0; line < 2; line++) {
			//col
			
			for (int col = 0; col < 2; col++) {
				//this->data[line + col * 2] = this->data[col] * m.data[line * 2] + this->data[col + 2] * m.data[line * 2 + 1];
				new_matrix.data[line + col * 2] = this->data[line] * m.data[col * 2] + this->data[line + 2] * m.data[col * 2 + 1];
			}
		}
		for (int i = 0; i < new_matrix.array_size; i++) {
			this->data[i] = new_matrix.data[i];
		}
		return(*this);
	};

	const mat2 operator + (const mat2& m0, const mat2& m1) {
		
		mat2 new_matrix = mat2();
		new_matrix += m0;
		new_matrix += m1;

		return new_matrix;
	};

	const mat2 operator - (const mat2& m0, const mat2& m1) {
		mat2 new_matrix = mat2();
		new_matrix += m0;
		new_matrix -= m1;

		return new_matrix;
	};

	const mat2 operator * (const mat2& m0, const mat2& m1) {
		mat2 new_matrix = mat2();
		new_matrix += m0;
		new_matrix *= m1;

		return new_matrix;
	};

	const mat2 operator * (const mat2& m, const float k) {
		mat2 new_matrix = mat2();
		for (int i = 0; i < m.array_size; i++) {
			new_matrix.data[i] = m.data[i] * k;
		}
		return new_matrix;
	};

	const mat2 operator * (const float k, const mat2& m) {
		mat2 new_matrix = mat2();
		for (int i = 0; i < m.array_size; i++) {
			new_matrix.data[i] = m.data[i] * k;
		}
		return new_matrix;
	};

	const vec2 operator * (const mat2& m, const vec2& v) {
		vec2 new_vector = vec2();
		new_vector.x = v.x * m.data[0] + v.y * m.data[2];
		new_vector.y = v.x * m.data[1] + v.y * m.data[3];

		return new_vector;
	};

	const bool operator == (const mat2& m0, const mat2& m1) {
		for (int i = 0; i < m0.array_size; i++) {
			if (fabs(m0.data[i] - m1.data[i]) > EPSILON)
			{
				return false;
			}
		}
		return true;
	}

	const bool operator != (const mat2& m0, const mat2& m1) {
		for (int i = 0; i < m0.array_size; i++) {
			if (fabs(m0.data[i] - m1.data[i]) > EPSILON)
			{
				return true;
			}
		}
		return false;
	}

	std::ostream& operator << (std::ostream& os, const mat2& m) {
		os << "{ " << m.data[0] << ", " << m.data[2] 
			<< "\n  \0" << m.data[1] << ", " << m.data[3] << " }";
		return os;
	}
	

	std::istream& operator >> (std::istream& is, mat2& m) {
		for (int i = 0; i < m.array_size; i++) {
			is >> m.data[i];
		}
		return is;
	};

}

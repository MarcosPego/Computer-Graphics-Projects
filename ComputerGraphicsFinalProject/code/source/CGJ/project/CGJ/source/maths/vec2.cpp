#include "vector.h"


namespace cgj {

	vec2::vec2() {
		this->x = 0;
		this->y = 0;
	};

	vec2::vec2(const float same_value) {
		this->x = same_value;
		this->y = same_value;
	};

	vec2::vec2(const float x, const float y) {
		this->x = x;
		this->y = y;
	};

	vec2::vec2(const vec2& vec2) {
		this->x = vec2.x;
		this->y = vec2.y;
	};

	vec2::vec2(const vec3& vec3){
		this->x = vec3.x / vec3.z;
		this->y = vec3.y / vec3.z;
	}


	const float  vec2::quadrance() const {
		return this->x * this->x + this->y * this->y;
	};

	const float vec2::length() const {
		return sqrt(this->quadrance());
	};

	const vec2 operator - (const vec2& v) {
		vec2 new_vector = vec2();
		new_vector.x = v.x == 0 ? v.x : -v.x;
		new_vector.y = v.y == 0 ? v.y : -v.y;
		
		return new_vector;
	};

	/*const vec2 vec2::operator - () const {
		vec2 new_vector = vec2();
		new_vector.x = this->x == 0 ? this->x : -this->x;
		new_vector.y = this->y == 0 ? this->y : -this->y;
		return new_vector;
	};*/

	vec2& vec2::operator+= (const vec2& v) {
		this->x += v.x;
		this->y += v.y;
		return(*this);
	};

	vec2& vec2::operator-= (const vec2& v) {
		this->x -= v.x;
		this->y -= v.y;
		return(*this);
	};

	vec2& vec2::operator*= (const vec2& v) {
		this->x *= v.x;
		this->y *= v.y;
		return(*this);
	};

	const vec2 operator+ (const vec2& v1, const vec2& v2) {
		vec2 new_vector = vec2();
		new_vector += v1;
		new_vector += v2;

		return new_vector;
	};

	const vec2 operator- (const vec2& v1, const vec2& v2) {
		vec2 new_vector = vec2();
		new_vector += v1;
		new_vector -= v2;

		return new_vector;
	};

	const vec2 operator * (const float k, const vec2& v) {
		vec2 new_vector = vec2();
		new_vector.x = v.x * k;
		new_vector.y = v.y * k;

		return new_vector;
	};

	const vec2 operator * (const vec2& v, const float k) {
		vec2 new_vector = vec2();
		new_vector.x = v.x * k;
		new_vector.y = v.y * k;

		return new_vector;
	};

	const vec2 operator / (const float k, const vec2& v) {
		vec2 new_vector = vec2();
		new_vector.x = v.x / k;
		new_vector.y = v.y / k;

		return new_vector;
	};

	const vec2 operator / (const vec2& v, const float k) {
		vec2 new_vector = vec2();
		new_vector.x = v.x / k;
		new_vector.y = v.y / k;

		return new_vector;
	};

	const float dot(const vec2& v1, const vec2& v2) {
		return v1.x*v2.x + v1.y*v2.y;
	};


	const vec2 normalize(const vec2& v) {
		return v / v.length();
	};

	const bool operator == (const vec2& v1, const vec2& v2) {
		return fabs(v1.x - v2.x) < EPSILON && fabs(v1.y - v2.y) < EPSILON;
	};
	
	const bool operator !=  (const vec2& v1, const vec2& v2) {
		return fabs(v1.x - v2.x) > EPSILON || fabs(v1.y - v2.y) > EPSILON;
	};

	std::ostream& operator << (std::ostream& os, const vec2& v) {
		os << "(" << v.x << "," << v.y <<  ")";
		return os;
	}; 

	std::istream& operator >> (std::istream& is, vec2& v) {
		is >> v.x;
		is >> v.y;
		return is;
	};
};
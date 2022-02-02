#include "vector.h"

namespace cgj {
	vec3::vec3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	};

	vec3::vec3(const float same_value) {
		this->x = same_value;
		this->y = same_value;
		this->z = same_value;
	};

	vec3::vec3(const float x, const float y) {
		this->x = x;
		this->y = y;
		this->z = 0;
	};

	vec3::vec3(const float x, const float y, const float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};

	vec3::vec3(const vec2& vec2) {
		this->x = vec2.x;
		this->y = vec2.y;
		this->z = 0;
	};

	vec3::vec3(const vec3& vec3) {
		this->x = vec3.x;
		this->y = vec3.y;
		this->z = vec3.z;
	};

	vec3::vec3(const vec4& vec4) {
		this->x = vec4.x / vec4.w;
		this->y = vec4.y / vec4.w;
		this->z = vec4.z / vec4.w;
	};

	const float  vec3::quadrance() const {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	};

	const float vec3::length() const {
		return sqrt(this->quadrance());
	};

	const vec3 operator - (const vec3& v) {
		vec3 new_vector = vec3();
		new_vector.x = v.x == 0 ? v.x : -v.x;
		new_vector.y = v.y == 0 ? v.y : -v.y;
		new_vector.z = v.z == 0 ? v.z : -v.z;
		return new_vector;
	};

	/*const vec3 vec3::operator - () const {
		vec3 new_vector = vec3();
		new_vector.x = this->x == 0 ? this->x : -this->x;
		new_vector.y = this->y == 0 ? this->y : -this->y;
		new_vector.z = this->z == 0 ? this->z : -this->z;
		return new_vector;
	};*/

	vec3& vec3::operator+= (const vec3& v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return(*this);
	};

	vec3& vec3::operator-= (const vec3& v) {
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return(*this);
	};

	vec3& vec3::operator*= (const vec3& v) {
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
		return(*this);
	};


	const vec3 operator+ (const vec3& v1, const vec3& v2) {
		vec3 new_vector = vec3();
		new_vector += v1;
		new_vector += v2;

		return new_vector;
	};

	const vec3 operator- (const vec3& v1, const vec3& v2) {
		vec3 new_vector = vec3();
		new_vector += v1;
		new_vector -= v2;

		return new_vector;
	};

	const vec3 operator * (const float k, const vec3& v) {
		vec3 new_vector = vec3();
		new_vector.x = v.x * k;
		new_vector.y = v.y * k;
		new_vector.z = v.z * k;

		return new_vector;
	};

	const vec3 operator * (const vec3& v, const float k) {
		vec3 new_vector = vec3();
		new_vector.x = v.x * k;
		new_vector.y = v.y * k;
		new_vector.z = v.z * k;

		return new_vector;
	};

	const vec3 operator / (const float k, const vec3& v) {
		vec3 new_vector = vec3();
		new_vector.x = v.x / k;
		new_vector.y = v.y / k;
		new_vector.z = v.z / k;

		return new_vector;
	};

	const vec3 operator / (const vec3& v, const float k) {
		vec3 new_vector = vec3();
		new_vector.x = v.x / k;
		new_vector.y = v.y / k;
		new_vector.z = v.z / k;

		return new_vector;
	};

	const float dot(const vec3& v1, const vec3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	};

	const vec3 cross(const vec3& v1, const vec3& v2) {
		vec3 new_vector = vec3();
		new_vector.x = v1.y* v2.z  - v1.z* v2.y;
		new_vector.y = v1.z * v2.x - v1.x * v2.z;
		new_vector.z = v1.x * v2.y - v1.y * v2.x;
		
		return new_vector;
	};

	const vec3 normalize(const vec3& v) {
		return v / v.length();
	};



	const bool operator == (const vec3& v1, const vec3& v2) {
		return fabs(v1.x - v2.x) < EPSILON && fabs(v1.y - v2.y) < EPSILON && fabs(v1.z - v2.z) < EPSILON;
	};

	const bool operator !=  (const vec3& v1, const vec3& v2) {
		return fabs(v1.x - v2.x) > EPSILON || fabs(v1.y - v2.y) > EPSILON || fabs(v1.z - v2.z) > EPSILON;
	};

	std::ostream& operator << (std::ostream& os, const vec3& v) {
		os << "(" << v.x << "," << v.y << "," << v.z << ")";
		return os;
	};

	std::istream& operator >> (std::istream& is, vec3& v) {
		is >> v.x;
		is >> v.y;
		is >> v.z;
		return is;
	};
};
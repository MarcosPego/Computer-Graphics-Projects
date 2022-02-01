#pragma once
#include <iostream>

namespace cgj {
	static float EPSILON = 0.00001f;
	struct vec4;
	struct vec3;

	struct vec2 {
		float x, y;


		vec2();
		vec2(const float same_value);
		vec2(const float x, const float y);
		vec2(const vec2& vec2);
		vec2(const vec3& vec3);
		//float* data();
		//void clean();
		const float quadrance() const;
		const float length() const;
		friend const vec2 operator - (const vec2& v);
		//const vec2 operator - () const;
		vec2& operator += (const vec2& v);
		vec2& operator -= (const vec2& v);
		vec2& operator *= (const vec2& v);
		friend const vec2 normalize(const vec2& v);
		friend const vec2 operator + (const vec2& v1, const vec2& v2);
		friend const vec2 operator - (const vec2& v1, const vec2& v2);
		friend const vec2 operator * (const float k, const vec2& v);
		friend const vec2 operator * (const vec2& v, const float k);
		friend const vec2 operator / (const float k, const vec2& v);
		friend const vec2 operator / (const vec2& v, const float k);
		friend const float dot(const vec2& v1, const vec2& v2);
		friend const bool operator == (const vec2& v1, const vec2& v2);
		friend const bool operator !=  (const vec2& v1, const vec2& v2);
		friend std::ostream& operator << (std::ostream& os, const vec2& v);
		friend std::istream& operator >> (std::istream& is, vec2& v);
	};

	struct vec3 {
		float x, y, z;

		vec3();
		vec3(const float same_value);
		vec3(const float x, const float y);
		vec3(const float x, const float y, const float z);
		vec3(const vec2& vec2);
		vec3(const vec3& vec3);
		vec3(const vec4& vec4);

		//float* data();
		//void clean();
		const float quadrance() const;
		const float length() const;
		friend const vec3 operator - (const vec3& v);
		//const vec3 operator - () const;
		vec3& operator += (const vec3& v);
		vec3& operator -= (const vec3& v);
		vec3& operator *= (const vec3& v);
		friend const vec3 normalize(const vec3& v);
		friend const vec3 operator + (const vec3& v1, const vec3& v2);
		friend const vec3 operator - (const vec3& v1, const vec3& v2);
		friend const vec3 operator * (const float k, const vec3& v);
		friend const vec3 operator * (const vec3& v, const float k);
		friend const vec3 operator / (const float k, const vec3& v);
		friend const vec3 operator / (const vec3& v, const float k);
		friend const float dot(const vec3& v1, const vec3& v2);
		friend const vec3 cross(const vec3& v1, const vec3& v2);
		friend const bool operator == (const vec3& v1, const vec3& v2);
		friend const bool operator !=  (const vec3& v1, const vec3& v2);
		friend std::ostream& operator << (std::ostream& os, const vec3& v);
		friend std::istream& operator >> (std::istream& is, vec3& v);
	};

	struct vec4 {
		float x, y, z, w;


		vec4();
		vec4(const float same_value);
		vec4(const float x, const float y, const float z);
		vec4(const float x, const float y, const float z, const float w);
		vec4(const vec2& v);
		vec4(const vec3& v);
		vec4(const vec4& v);
		//float* data();
		//void clean();

		const float quadrance() const;
		const float length() const;
		friend const vec4 operator - (const vec4& v);
		//const vec4 operator - () const;
		vec4& operator += (const vec4& v);
		vec4& operator -= (const vec4& v);
		vec4& operator *= (const vec4& v);
		friend const vec4 normalize(const vec4& v);
		friend const vec4 operator + (const vec4& v1, const vec4& v2);
		friend const vec4 operator - (const vec4& v1, const vec4& v2);
		friend const vec4 operator * (const float k, const vec4& v);
		friend const vec4 operator * (const vec4& v, const float k);
		friend const vec4 operator / (const float k, const vec4& v);
		friend const vec4 operator / (const vec4& v, const float k);
		friend const float dot(const vec4& v1, const vec4& v2);

		friend const bool operator == (const vec4& v1, const vec4& v2);
		friend const bool operator !=  (const vec4& v1, const vec4& v2);
		friend std::ostream& operator << (std::ostream& os, const vec4& v);
		friend std::istream& operator >> (std::istream& is, vec4& v);
	};
};
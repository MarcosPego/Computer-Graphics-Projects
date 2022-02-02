#pragma once
#include <iostream>
#include "vector.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace cgj {
	//Matrixes are used in Column major
	//static float EPSILON = 0.00001f;
	struct mat4;


	struct mat2 {
		GLfloat data[4];
		float array_size = (sizeof(data) / sizeof(*data));

		mat2();
		mat2(const float k);
		mat2(const float m0, const float m1, 
			const float m2, const float m3);

		//Column major constructor
		mat2(const mat2& m);
		void clean();
		float determiant() const;
		
		mat2& operator - (const mat2& m);
		friend mat2 adjugate(const mat2& m);
		friend mat2 transpose(const mat2& m);
		friend mat2 inverse(const mat2& m);
		mat2& operator += (const mat2& m);
		mat2& operator -= (const mat2& m);
		mat2& operator *= (const mat2& m);
		friend const mat2 operator + (const mat2& m0, const mat2& m1);
		friend const mat2 operator - (const mat2& m0, const mat2& m1);
		friend const mat2 operator * (const mat2& m, const float k);
		friend const mat2 operator * (const float k, const mat2& m);
		friend const vec2 operator * (const mat2& m, const vec2& v);
		friend const mat2 operator * (const mat2& m0, const mat2& m1);

		friend const bool operator == (const mat2& m0, const mat2& m1);
		friend const bool operator != (const mat2& m0, const mat2& m1);
		friend std::istream& operator >> (std::istream& is, mat2& m);
		friend std::ostream& operator << (std::ostream& os, const mat2& m);
	};

	struct mat3 {
		GLfloat data[9];
		float array_size = (sizeof(data) / sizeof(*data));

		mat3();
		mat3(const float k);
		mat3(const float m0, const float m1, const float m2, 
			const float m3,  const float m4, const float m5, 
			const float m6, const float m7, const float m8);

		//Column major constructor
		mat3(const mat3& m);
		mat3(const mat4& m);

		void clean();
		float determiant() const;
		mat3& operator - (const mat3& m);
		friend mat3 adjugate(const mat3& m);
		friend mat3 transpose(const mat3& m);
		friend mat3 inverse(const mat3& m);
		mat3& operator += (const mat3& m);
		mat3& operator -= (const mat3& m);
		mat3& operator *= (const mat3& m);
		friend const mat3 operator + (const mat3& m0, const mat3& m1);
		friend const mat3 operator - (const mat3& m0, const mat3& m1);
		friend const mat3 operator * (const mat3& m, const float k);
		friend const mat3 operator * (const float k, const mat3& m);
		friend const vec3 operator * (const mat3& m, const vec3& v);
		friend const mat3 operator * (const mat3& m0, const mat3& m1);

		friend const bool operator == (const mat3& m0, const mat3& m1);
		friend const bool operator != (const mat3& m0, const mat3& m1);
		friend std::istream& operator >> (std::istream& is, mat3& m);
		friend std::ostream& operator << (std::ostream& os, const mat3& m);

	};

	struct mat4 {
		GLfloat data[16];
		float array_size = (sizeof(data) / sizeof(*data));

		mat4();
		mat4(const float k);
		mat4(const float m0, const float m1, const float m2, const float m3, 
			const float m4, const float m5, const float m6, const float m7, 
			const float m8, const float m9, const float m10, const float m11, 
			const float m12, const float m13, const float m14, const float m15);

		//Column major constructor
		mat4(const mat3& m);
		mat4(const mat4& m);
		void clean();
		mat4& operator - (const mat4& m);

		friend mat4 transpose(const mat4& m);
		friend mat4 inverse(const mat4& m);
		mat4& operator += (const mat4& m);
		mat4& operator -= (const mat4& m);
		mat4& operator *= (const mat4& m);
		friend const mat4 operator + (const mat4& m0, const mat4& m1);
		friend const mat4 operator - (const mat4& m0, const mat4& m1);
		friend const mat4 operator * (const mat4& m, const float k);
		friend const mat4 operator * (const float k, const mat4& m);
		friend const vec4 operator * (const mat4& m, const vec4& v);
		friend const mat4 operator * (const mat4& m0, const mat4& m1);

		friend const bool operator == (const mat4& m0, const mat4& m1);
		friend const bool operator != (const mat4& m0, const mat4& m1);
		friend std::istream& operator >> (std::istream& is, mat4& m);;
		friend std::ostream& operator << (std::ostream& os, const mat4& m);

		
	};

	struct MatrixFactory {
		static const mat2 createZeroMat2();
		static const mat2 createIdentityMat2();
		static const mat2 createScaleMat2(const vec2& v);
		static const mat2 createRotationMat2(const float angle);

		static const mat3 createZeroMat3();
		static const mat3 createIdentityMat3();
		static const mat3 createDualMat3(const vec3& v);
		static const mat3 createScaleMat3(const vec3& v);
		static const mat3 createRotationMat3(const float angle, const vec3& axis);
		static const mat3 createMat3FromMat4(const mat4& axis);

		static const mat3 createRandomBet9Mat3();

		static const mat4 createZeroMat4();
		static const mat4 createIdentityMat4();
		static const mat4 createScaleMat4(const vec3& v);
		static const mat4 createRotationMat4(const float angle, const vec3& axis);
		static const mat4 createTranslationMat4( const vec3& vector);
		static const mat4 createMat4FromMat3(const mat3& m3);

		static const mat4 createRotation2DMat4(const float angle);


		static const mat4 createViewMat4(const vec3& eye, const vec3& center, const vec3& up);
		static const mat4 createOrtoMat4(const float left, const float right, const float bottom, const float top, const float near, const float far);
		static const mat4 createPerspectiveMat4(const float fovy, const float aspect, const float nearZ, const float farZ);

		static const mat4 createModelMatrix(vec3 scale, float angle, vec3 position, vec3 parent_position, float parent_angle);

		static const mat4 createReflectionMatrix(vec4 plane_vec);
		static const mat4 createNEGY();
	};
};
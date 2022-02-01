#pragma once

#include "../maths/quaternions.h"
#include "../maths/matrix.h"
#include <GL/glew.h>

namespace cgj {
	namespace graphics {
		struct camera {

			camera(const mat4& viewMatrix, const float left, const float right, const float bottom, const float top, const float near, const float far);
			camera(const mat4& viewMatrix, const float fovy, const float aspect, const float nearZ, const float farZ);
			camera(const mat4& viewMatrix, const mat4& projMatrix);
			camera(const vec3& eye, const vec3& center, const vec3& up, const mat4& projMatrix);

			std::string currentProjectionMatrix;
			mat4 viewMatrix;
			mat4 projectionMatrix;
			mat4 viewProjectionMatrix;

			vec3 c_eye;
			vec3 viewDirection;
			vec3 c_up;

			float x = 0;
			float y = 0;
			qtrn quaternion = qtrn();
			mat4 toRotateX = MatrixFactory::createIdentityMat4();
			mat4 toRotateY = MatrixFactory::createIdentityMat4();
			mat4 toRotate = MatrixFactory::createIdentityMat4();
			
			mat4 toTranslate = MatrixFactory::createIdentityMat4();
			mat4 toZoom = MatrixFactory::createIdentityMat4();

			std::string checkCurrentProjectionMatrix();
			
			void rotateX(const vec3& axis, const float angle);
			void rotateY(const vec3& axis, const float angle);
			void quaternionRotate(const float x, const float y);
			void quaternionRotate(const float y);
			void quaternionRotate(qtrn quaternion);
			void rotate();
			void translate(const vec3& direction);

			void zoom(const float zoom);

			void updateViewMatrix();
			void updateRotationLockViewMatrix();
		};
	}
}
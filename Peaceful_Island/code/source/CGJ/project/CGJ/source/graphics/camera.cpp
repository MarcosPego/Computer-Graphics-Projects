#include "camera.h"

namespace cgj {
	namespace graphics {
		camera::camera(const mat4& viewMatrix, const float left, const float right, const float bottom, const float top, const float near, const float far)
			: viewMatrix(viewMatrix), projectionMatrix(MatrixFactory::createOrtoMat4(left, right, bottom, top, near, far)) {
			currentProjectionMatrix = "Ortho";
		}

		camera::camera(const mat4& viewMatrix, const float fovy, const float aspect, const float nearZ, const float farZ)
			: viewMatrix(viewMatrix) , projectionMatrix(MatrixFactory::createPerspectiveMat4(fovy, aspect, nearZ, farZ)) {
			currentProjectionMatrix = "Perspective";
		}

		camera::camera(const mat4& viewMatrix, const mat4& projMatrix)
			: viewMatrix(viewMatrix), projectionMatrix(projMatrix) {
				currentProjectionMatrix = "Unknown";
		}

		camera::camera(const vec3& eye, const vec3& center, const vec3& up, const mat4& projMatrix)
			: viewMatrix(MatrixFactory::createViewMat4(eye, center, up)), projectionMatrix(projMatrix) {
			currentProjectionMatrix = "Unknown";
			c_eye = eye;
			viewDirection = center - eye;
			c_up = up;

		}

		std::string camera::checkCurrentProjectionMatrix() {
			return currentProjectionMatrix;
		}
		
		//MatrixFactory::createRotationMat4(const float angle, const vec3& axis)
		//MatrixFactory::createTranslationMat4(const vec3& vector)


		void camera::translate(const vec3& direction) {
			toTranslate = MatrixFactory::createTranslationMat4(direction);
		}

		void camera::rotateX(const vec3& axis, const float angle) {
			toRotateX = MatrixFactory::createRotationMat4(angle, axis) * toRotateX;
		}

		void camera::rotateY(const vec3& axis, const float angle) {
			toRotateY = MatrixFactory::createRotationMat4(angle, axis) * toRotateY;
		}

		void camera::quaternionRotate(const float x, const float y) {
			quaternion = qtrn::qFromAngleAxis(x, vec4(0, 1, 0, 1))*
				qtrn::qFromAngleAxis(y, vec4(1, 0, 0, 1))*
				quaternion;
			qGLMatrix(quaternion, toRotate);
		}

		void camera::quaternionRotate(const float y) {
			quaternion = qtrn::qFromAngleAxis(y, vec4(1, 0, 0, 1)) * quaternion;
			qGLMatrix(quaternion, toRotate);
		}

		void camera::quaternionRotate(qtrn quaternion) {
			qGLMatrix(quaternion, toRotate);
		}

		void camera::rotate() {
			toRotate = toRotateY * toRotateX;
		}

		void camera::zoom(const float zoom) {
			vec3 zoom_vec = vec3(0, 0, zoom);
			toZoom = MatrixFactory::createTranslationMat4(zoom_vec) * toZoom;
		}

		void camera::updateViewMatrix() {
			viewMatrix = toTranslate* toRotate * viewMatrix;
			toRotateX = MatrixFactory::createIdentityMat4();
			toRotateY = MatrixFactory::createIdentityMat4();
			toTranslate = MatrixFactory::createIdentityMat4();
		}

		void camera::updateRotationLockViewMatrix() {
			viewMatrix = toZoom * toTranslate * toRotate;
		}
	}
}
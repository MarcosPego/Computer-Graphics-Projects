#pragma once

#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913
#define EPSILON (float)1.0e-5


namespace cgj {
	struct qtrn {
		float t, x, y, z;
		
		qtrn();
		qtrn(const float same_value);
		qtrn(const float t, const float x, const float y, const float z);
		qtrn(const qtrn& q);



		qtrn& operator += (const qtrn& q);
		qtrn& operator -= (const qtrn& q);
		qtrn& operator *= (const qtrn& q);

		friend const qtrn operator + (const qtrn& q1, const qtrn& q2);
		friend const qtrn operator - (const qtrn& q1, const qtrn& q2);
		friend const qtrn operator * (const float k, const qtrn& q);
		friend const qtrn operator * (const qtrn& q, const float k);
		friend const qtrn operator * (const qtrn& q1, const qtrn& q2);
		friend const qtrn operator / (const qtrn& q, const float k);

		friend const bool operator == (const qtrn& q1, const qtrn& q2);
		friend const bool operator !=  (const qtrn& q1, const qtrn& q2);
		friend std::ostream& operator << (std::ostream& os, const qtrn& q);
		friend std::istream& operator >> (std::istream& is, qtrn& q);




		//const float qThreshold = (float)1.0e-5;

		static const qtrn qFromAngleAxis(float theta, vec4 axis);
		static const void qToAngleAxis(const qtrn& q, float& theta, vec4& axis);

		friend const void qClean(qtrn& q);
		friend const float qQuadrance(const qtrn& q);
		friend const float qNorm(const qtrn& q);
		friend const qtrn qNormalize(const qtrn& q);
		friend const qtrn qConjugate(const qtrn& q);
		friend const qtrn qInverse(const qtrn& q);
		friend const qtrn qAdd(const qtrn& q0, const qtrn& q1);
		friend const qtrn qMultiply(const qtrn& q, const float s);
		friend const qtrn qMultiply(const qtrn& q0, const qtrn& q1);
		friend const void qGLMatrix(const qtrn& q, mat4& matrix);
		friend const qtrn qLerp(const qtrn& q0, const qtrn& q1, float k);
		friend const qtrn qSlerp(const qtrn& q0, const qtrn& q1, float k);
		friend const bool qEqual(const qtrn& q0, const qtrn& q1);
		friend const void qPrint(const std::string& s, const qtrn& q);
		friend const void qPrintAngleAxis(const std::string& s, const qtrn& q);

	};
}
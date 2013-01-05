////////////////////////////////////////////////////////////////////////////////
/**
 * \file    CTangible.h
 * \author  Hua Fei Yu 0951402
 * \date    October 18, 2011
 * \brief   Any physical object in 3D space
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef CTANGIBLE_H
#define CTANGIBLE_H

// Headers
#include "math/Matrix3x3.h"

class CTangible
{
	public:
		CTangible() : pitch(0.f), yaw(0.f), roll(0.f), vel(0.f), pos(Vec3f(0.f,0.f, 0.f)) {}

		float 			pitch;
		Matrix3x3		mat_pitch;

		float 			yaw;
		Matrix3x3		mat_yaw;

		float 			roll;
		Matrix3x3		mat_roll;

		Vec3f 			forward;
		Vec3f 			right;
		Vec3f 			up;

		float 			vel;
		Vec3f 			pos;

};



#endif // CTANGIBLE_H

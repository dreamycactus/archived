////////////////////////////////////////////////////////////////////////////////
/**
 * \file    CCamera.h
 * \author  Hua Fei Yu 0951402
 * \date    Nov 6, 2011
 * \brief  	Camera class, adapted from http://www.dhpoware.com
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef CCAMERA_H
#define CCAMERA_H

#include "dcmath.h"

class CCamera
{
    public:
        enum CameraBehavior
        {
            CAMERA_BEHAVIOR_FIRST_PERSON,
            CAMERA_BEHAVIOR_FLIGHT
        };

                        CCamera();
        virtual         ~CCamera();

        void            lookAt(const Vec3f& target);
        void            lookAt(const Vec3f& eye, const Vec3f& target, const Vec3f& up);
        void            move(float dx, float dy, float dz);
        void            perspective(float fovx, float aspect, float znear, float zfar);
        void            rotate(float heading_degree, float pitch_degree, float roll_degree);
        void            updatePos(const Vec3f& direction, float elapsed_time);

        // Getters
        const Vec3f&    getAccel() const;
        const Vec3f&    getCurrentVel() const;
        const Vec3f&    getPos() const;
        const Matrix4&  getProjectionMatrix() const;
        const Vec3f&    getVel() const;
        const Vec3f&    getViewDirection() const;
        const Matrix4&  getViewMatrix() const;
        const Vec3f&    getXAxis() const;
        const Vec3f&    getYAxis() const;
        const Vec3f&    getZAxis() const;

        // Setters
        void            setAccel(float x, float y, float z);
        void            setAccel(const Vec3f& accel);
        void            setBehavior(CameraBehavior b);
        void            setCurrentVel(float x, float y, float z);
        void            setCurrentVel(const Vec3f& vel);
        void            setPos(float x, float y, float z);
        void            setPos(const Vec3f& position);
        void            setVel(float x, float y, float z);
        void            setVel(const Vec3f& vel);

    protected:
        void            rotateAll(float heading_degree, float pitch_degree, float roll_degree);
        void            rotateFirstPerson(float heading_degree, float pitch_degree);
        void            rotateFlight(float heading_degree, float pitch_degree, float roll_degree);
        void            updateVelocity(const Vec3f& direction, float elapsed_time);
        void            updateViewMatrix(bool orthogonalize);

        static const float DEFAULT_FOVX;
        static const float DEFAULT_ZFAR;
        static const float DEFAULT_ZNEAR;
        static const Vec3f WORLD_XAXIS;
        static const Vec3f WORLD_YAXIS;
        static const Vec3f WORLD_ZAXIS;

        CameraBehavior behavior_;
        float fovx_;
        float znear_;
        float zfar_;
        float aspect_ratio_;
        float accum_pitch_;
        Vec3f eye_;
        Vec3f x_axis_;
        Vec3f y_axis_;
        Vec3f z_axis_;
        Vec3f view_dir_;
        Vec3f accel_;
        Vec3f current_vel_;
        Vec3f vel_;
        Matrix4 view_matrix_;
        Matrix4 proj_matrix_;
};

// Inline Implementations

inline const Vec3f& CCamera::getAccel() const
{ return accel_; }

inline const Vec3f& CCamera::getCurrentVel() const
{ return current_vel_; }

inline const Vec3f& CCamera::getPos() const
{ return eye_; }

inline const Matrix4& CCamera::getProjectionMatrix() const
{ return proj_matrix_; }

inline const Vec3f& CCamera::getVel() const
{ return vel_; }

inline const Vec3f& CCamera::getViewDirection() const
{ return view_dir_; }

inline const Matrix4& CCamera::getViewMatrix() const
{ return view_matrix_; }

inline const Vec3f& CCamera::getXAxis() const
{ return x_axis_; }

inline const Vec3f& CCamera::getYAxis() const
{ return y_axis_; }

inline const Vec3f& CCamera::getZAxis() const
{ return z_axis_; }

#endif // CCAMERA_H

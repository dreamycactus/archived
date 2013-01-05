#include "camera/CCamera.h"

#include <cmath>

const float CCamera::DEFAULT_FOVX = 90.0f;
const float CCamera::DEFAULT_ZFAR = 1000.0f;
const float CCamera::DEFAULT_ZNEAR = 0.1f;
const Vec3f CCamera::WORLD_XAXIS(1.0f, 0.0f, 0.0f);
const Vec3f CCamera::WORLD_YAXIS(0.0f, 1.0f, 0.0f);
const Vec3f CCamera::WORLD_ZAXIS(0.0f, 0.0f, 1.0f);

CCamera::CCamera() :
    behavior_(CAMERA_BEHAVIOR_FLIGHT),
    fovx_(DEFAULT_FOVX),
    znear_(DEFAULT_ZNEAR),
    zfar_(DEFAULT_ZFAR),
    aspect_ratio_(0.0f),
    accum_pitch_(0.0f)
{
    eye_.set(0.0f, 0.0f, 0.0f);
    x_axis_.set(1.0f, 0.0f, 0.0f);
    y_axis_.set(0.0f, 1.0f, 0.0f);
    z_axis_.set(0.0f, 0.0f, 1.0f);
    view_dir_.set(0.0f, 0.0f, -1.0f);

    accel_.set(0.0f, 0.0f, 0.0f);
    current_vel_.set(0.0f, 0.0f, 0.0f);
    vel_.set(0.0f, 0.0f, 0.0f);

    view_matrix_.identity();
    proj_matrix_.identity();

}

CCamera::~CCamera()
{
    //dtor
}

void CCamera::lookAt(const Vec3f& target)
{
    lookAt(eye_, target, y_axis_);
}

void CCamera::lookAt(const Vec3f& eye, const Vec3f& target, const Vec3f& up)
{
    eye_ = eye;

    z_axis_ = eye - target;
    z_axis_.normalize();

    view_dir_ = -z_axis_;

    x_axis_ = up ^ z_axis_;
    x_axis_.normalize();

    y_axis_ = z_axis_ ^ x_axis_;
    y_axis_.normalize();

    view_matrix_[0][0] = x_axis_.x;
    view_matrix_[1][0] = x_axis_.y;
    view_matrix_[2][0] = x_axis_.z;
    view_matrix_[3][0] = -(x_axis_ * eye);

    view_matrix_[0][1] = y_axis_.x;
    view_matrix_[1][1] = y_axis_.y;
    view_matrix_[2][1] = y_axis_.z;
    view_matrix_[3][1] = -(y_axis_ * eye);

    view_matrix_[0][2] = z_axis_.x;
    view_matrix_[1][2] = z_axis_.y;
    view_matrix_[2][2] = z_axis_.z;
    view_matrix_[3][2] = -(z_axis_ * eye);

    accum_pitch_ = dcMath::radiansToDegrees(-asinf(view_matrix_[1][2]));
}
void CCamera::move(float dx, float dy, float dz)
{
    Vec3f eye = eye_;
    Vec3f forwards;

    if (behavior_ == CAMERA_BEHAVIOR_FIRST_PERSON)
    {
        forwards = WORLD_YAXIS ^ x_axis_;
        forwards.normalize();
    }
    else
    {
        forwards = view_dir_;
    }


    eye += x_axis_ * dx;
    eye += WORLD_YAXIS * dy;
    eye += forwards * dz;

    setPos(eye);
}

void CCamera::perspective(float fovx, float aspect, float znear, float zfar)
{
    float e = 1.0f / tanf(dcMath::degreesToRadians(fovx) / 2.0f);
    float aspect_inv = 1.0f / aspect;
    float fovy = 2.0f * atanf(aspect_inv / e);
    float x_scale = 1.0f / tanf(0.5f * fovy);
    float y_scale = x_scale / aspect_inv;

    proj_matrix_[0][0] = x_scale;
    proj_matrix_[0][1] = 0.0f;
    proj_matrix_[0][2] = 0.0f;
    proj_matrix_[0][3] = 0.0f;

    proj_matrix_[1][0] = 0.0f;
    proj_matrix_[1][1] = y_scale;
    proj_matrix_[1][2] = 0.0f;
    proj_matrix_[1][3] = 0.0f;

    proj_matrix_[2][0] = 0.0f;
    proj_matrix_[2][1] = 0.0f;
    proj_matrix_[2][2] = (zfar + znear) / (znear - zfar);
    proj_matrix_[2][3] = -1.0f;

    proj_matrix_[3][0] = 0.0f;
    proj_matrix_[3][1] = 0.0f;
    proj_matrix_[3][2] = (2.0f * zfar * znear) / (znear - zfar);
    proj_matrix_[3][3] = 0.0f;

    fovx_               = fovx;
    aspect_ratio_       = aspect;
    znear_              = znear;
    zfar_               = zfar;
}
void CCamera::rotate(float heading_degree, float pitch_degree, float roll_degree)
{
    if (behavior_ == CAMERA_BEHAVIOR_FIRST_PERSON)
        { rotateFirstPerson(heading_degree, pitch_degree); }
    else
        { rotateFlight(heading_degree, pitch_degree, roll_degree); }

    updateViewMatrix(true);
}

void CCamera::rotateFirstPerson(float heading_degree, float pitch_degree)
{
    accum_pitch_ += pitch_degree;

    if (accum_pitch_ > 90.0f)
    {
        pitch_degree = 90.0f - (accum_pitch_ - pitch_degree);
        accum_pitch_ = 90.0f;
    }

    if (accum_pitch_ < -90.0f)
    {
        pitch_degree = -90.0f - (accum_pitch_ - pitch_degree);
        accum_pitch_ = -90.0f;
    }

    Matrix4 rot_mtx;


    // Rotate camera's existing x and z axes about the world y axis.
    if (heading_degree != 0.0f)
    {
        rot_mtx.rotate(WORLD_YAXIS, heading_degree);
        x_axis_ = x_axis_ * rot_mtx;
        z_axis_ = z_axis_ * rot_mtx;
    }

    // Rotate camera's existing y and z axes about its existing x axis.
    if (pitch_degree != 0.0f)
    {
        rot_mtx.rotate(x_axis_, pitch_degree);
        y_axis_ = y_axis_ * rot_mtx;
        z_axis_ = z_axis_ * rot_mtx;
    }
}

void CCamera::rotateFlight(float heading_degree, float pitch_degree, float roll_degree)
{
    accum_pitch_ += pitch_degree;

    if (accum_pitch_ > 90.0f)
    {
        pitch_degree = 90.0f - (accum_pitch_ - pitch_degree);
        accum_pitch_ = 90.0f;
    }

    if (accum_pitch_ < -90.0f)
    {
        pitch_degree = -90.0f - (accum_pitch_ - pitch_degree);
        accum_pitch_ = -90.0f;
    }

    Matrix4 rot_mtx;


    // Rotate camera's existing x and z axes about the world y axis.
    if (heading_degree != 0.0f)
    {
        rot_mtx.rotate(WORLD_YAXIS, heading_degree);
        x_axis_ = x_axis_ * rot_mtx;
        z_axis_ = z_axis_ * rot_mtx;
    }

    // Rotate camera's existing y and z axes about its existing x axis.
    if (pitch_degree != 0.0f)
    {
        rot_mtx.rotate(x_axis_, pitch_degree);
        y_axis_ = y_axis_ * rot_mtx;
        z_axis_ = z_axis_ * rot_mtx;
    }

    if (roll_degree != 0.0f)
    {
        rot_mtx.rotate(z_axis_, roll_degree);
        x_axis_ = x_axis_ * rot_mtx;
        y_axis_ = y_axis_ * rot_mtx;
    }
}


void CCamera::setAccel(float x, float y, float z)
{
    accel_.set(x, y, z);
}

void CCamera::setAccel(const Vec3f& acceleration)
{
    accel_ = acceleration;
}
void CCamera::setBehavior(CameraBehavior b)
{
    if (behavior_ == CAMERA_BEHAVIOR_FLIGHT && b == CAMERA_BEHAVIOR_FIRST_PERSON)
    {
        // Moving from flight-simulator mode to first-person.
        // Need to ignore camera roll, but retain existing pitch and heading.

        lookAt(eye_, eye_ - z_axis_, WORLD_YAXIS);
    }

    behavior_ = b;
}
void CCamera::setCurrentVel(float x, float y, float z)
{
    current_vel_.set(x, y, z);
}

void CCamera::setCurrentVel(const Vec3f& current_v)
{
    current_vel_ = current_v;
}

void CCamera::setPos(float x, float y, float z)
{
    eye_.set(x, y, z);
    updateViewMatrix(false);
}

void CCamera::setPos(const Vec3f& position)
{
    eye_ = position;
    updateViewMatrix(false);
}

void CCamera::setVel(float x, float y, float z)
{
    vel_.set(x, y, z);
}

void CCamera::setVel(const Vec3f& velocity)
{
    vel_ = velocity;
}

void CCamera::updatePos(const Vec3f& direction, float elapsed_time)
{
    if (current_vel_.lengthSquared() != 0.0f)
    {
        Vec3f displacement = (current_vel_ * elapsed_time) +
            (0.5f * accel_ * elapsed_time * elapsed_time);
        if (direction.x == 0.0f && dcMath::closeTof(current_vel_.x, 0.0f))
            displacement.x = 0.0f;
        if (direction.y == 0.0f && dcMath::closeTof(current_vel_.y, 0.0f))
            displacement.y = 0.0f;
        if (direction.z == 0.0f && dcMath::closeTof(current_vel_.z, 0.0f))
            displacement.z = 0.0f;

        move(displacement.x, displacement.y, displacement.z);
    }

    updateVelocity(direction, elapsed_time);
}

void CCamera::updateVelocity(const Vec3f& direction, float elapsed_time)
{
        if (direction.x != 0.0f)
    {
        // Camera is moving along the x axis.
        // Linearly accelerate up to the camera's max speed.

        current_vel_.x += direction.x * accel_.x * elapsed_time;

        if (current_vel_.x > vel_.x)
            current_vel_.x = vel_.x;
        else if (current_vel_.x < -vel_.x)
            current_vel_.x = -vel_.x;
    }
    else
    {
        // Camera is no longer moving along the x axis.
        // Linearly decelerate back to stationary state.

        if (current_vel_.x > 0.0f)
        {
            if ((current_vel_.x -= accel_.x * elapsed_time) < 0.0f)
                current_vel_.x = 0.0f;
        }
        else
        {
            if ((current_vel_.x += accel_.x * elapsed_time) > 0.0f)
                current_vel_.x = 0.0f;
        }
    }

    if (direction.y != 0.0f)
    {
        // Camera is moving along the y axis.
        // Linearly accelerate up to the camera's max speed.

        current_vel_.y += direction.y * accel_.y * elapsed_time;

        if (current_vel_.y > vel_.y)
            current_vel_.y = vel_.y;
        else if (current_vel_.y < -vel_.y)
            current_vel_.y = -vel_.y;
    }
    else
    {
        // Camera is no longer moving along the y axis.
        // Linearly decelerate back to stationary state.

        if (current_vel_.y > 0.0f)
        {
            if ((current_vel_.y -= accel_.y * elapsed_time) < 0.0f)
                current_vel_.y = 0.0f;
        }
        else
        {
            if ((current_vel_.y += accel_.y * elapsed_time) > 0.0f)
                current_vel_.y = 0.0f;
        }
    }

    if (direction.z != 0.0f)
    {
        // Camera is moving along the z axis.
        // Linearly accelerate up to the camera's max speed.

        current_vel_.z += direction.z * accel_.z * elapsed_time;

        if (current_vel_.z > vel_.z)
            current_vel_.z = vel_.z;
        else if (current_vel_.z < -vel_.z)
            current_vel_.z = -vel_.z;
    }
    else
    {
        // Camera is no longer moving along the z axis.
        // Linearly decelerate back to stationary state.

        if (current_vel_.z > 0.0f)
        {
            if ((current_vel_.z -= accel_.z * elapsed_time) < 0.0f)
                current_vel_.z = 0.0f;
        }
        else
        {
            if ((current_vel_.z += accel_.z * elapsed_time) > 0.0f)
                current_vel_.z = 0.0f;
        }
    }
}




void CCamera::updateViewMatrix(bool orthogonalize)
{
    if (orthogonalize)
    {
        // Regenerate the camera's local axes to orthogonalize them.

        z_axis_.normalize();

        y_axis_ = z_axis_ ^ x_axis_;
        y_axis_.normalize();

        x_axis_ = y_axis_ ^ z_axis_;
        x_axis_.normalize();

        view_dir_ = -z_axis_;
    }

    // Reconstruct the view matrix.

    view_matrix_[0][0] = x_axis_.x;
    view_matrix_[1][0] = x_axis_.y;
    view_matrix_[2][0] = x_axis_.z;
    view_matrix_[3][0] = -(x_axis_* eye_);

    view_matrix_[0][1] = y_axis_.x;
    view_matrix_[1][1] = y_axis_.y;
    view_matrix_[2][1] = y_axis_.z;
    view_matrix_[3][1] = -(y_axis_ * eye_);

    view_matrix_[0][2] = z_axis_.x;
    view_matrix_[1][2] = z_axis_.y;
    view_matrix_[2][2] = z_axis_.z;
    view_matrix_[3][2] = -(z_axis_ * eye_);

    view_matrix_[0][3] = 0.0f;
    view_matrix_[1][3] = 0.0f;
    view_matrix_[2][3] = 0.0f;
    view_matrix_[3][3] = 1.0f;
}

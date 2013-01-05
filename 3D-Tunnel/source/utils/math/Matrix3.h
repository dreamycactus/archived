////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for 3x3 matrices.
 *	\file		Matrix3.h
 *	\author		Hua Fei Yu 0951402
 *	\date		October 18, 2011.
 *  \brief      Code adapted from Pierre Terdiman's (my hero) IceMatrix3
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef MATRIX3_H
#define MATRIX3_H

// Headers
#include "stdinc.h"
#include "memory_macros.h"
#include "helper.h"
#include "vec3.h"
class Matrix3
{
    public:
    // Members
                float           m[3][3];

    // Methods
    //! Default ctor
    inline          Matrix3() {}
    //! 9 Element ctor
    inline          Matrix3(float m00, float m01, float m02,
                              float m10, float m11, float m12,
                              float m20, float m21, float m22)
                    {
                        m[0][0] = m00;	m[0][1] = m01;	m[0][2] = m02;
                        m[1][0] = m10;	m[1][1] = m11;	m[1][2] = m12;
                        m[2][0] = m20;	m[2][1] = m21;	m[2][2] = m22;
                    }
    //! Copy ctor
    inline          Matrix3(const Matrix3& mat)
                    {
                        CopyMemory(m, &mat.m, 9*sizeof(float));
                    }
    //! Dtor
    inline          ~Matrix3() {}

    //! Copy matrix
    inline void     copy(const Matrix3& src)
                    {
                        CopyMemory(m, &src.m, 9*sizeof(float));
                    }
    //! Set values
    inline void     set(float m00, float m01, float m02,
                        float m10, float m11, float m12,
                        float m20, float m21, float m22)
                    {
                        m[0][0] = m00;	m[0][1] = m01;	m[0][2] = m02;
                        m[1][0] = m10;	m[1][1] = m11;	m[1][2] = m12;
                        m[2][0] = m20;	m[2][1] = m21;	m[2][2] = m22;
                    }
    //! Returns row
    inline void         getRow(int r, Vec3f& v) const
                        {
                            v.x = m[r][0];
                            v.y = m[r][1];
                            v.z = m[r][2];
                        }
    //! Returns row
    inline const Vec3f  getRow(int r) const
                        {
                            return Vec3f(m[r][0], m[r][1], m[r][2]);
                        }
    //! Set row values
    inline void			setRow(int r, const Vec3f& v)
                        {
                            m[r][0] = v.x;
                            m[r][1] = v.y;
                            m[r][2] = v.z;
                        }
    //! Returns column
    inline void         getCol(int c, Vec3f& v) const
                        {
                            v.x = m[0][c];
                            v.y = m[1][c];
                            v.z = m[2][c];
                        }
    //! Returns column
    inline const Vec3f getCol(int c) const
                        {
                            return Vec3f(m[0][c], m[1][c], m[2][c]);
                        }
    //! Sets column values
    inline void			setCol(int c, const Vec3f& v)
                        {
                            m[0][c] = v.x;
                            m[1][c] = v.y;
                            m[2][c] = v.z;

                        }
    //! Returns trace, sum of main diagonal elements
    inline float        trace() const { return m[0][0]+m[1][1]+m[2][2]; }

    //! Sets all values to 0
    inline void			zero()        { ZeroMemory(&m, sizeof(m));	}

    //! Sets to identity
    inline void         identity()
                        {
                            zero();
                            m[1][1] = m[2][2] = m[3][3] = 1.f;
                        }
    //! Check matrix validity
    inline bool			isValid() const
                        {
                            for(uint j=0; j<3; j++)
                            {
                                for(uint i=0; i<3; i++)
                                {
                                    if(!isValidFloat(m[j][i]))	return false;
                                }
                            }
                            return true;
                        }

    //! Makes a skew-symmetric matrix (a.k.a. Star(*) Matrix)
    //!	[  0.0  -a.z   a.y ]
    //!	[  a.z   0.0  -a.x ]
    //!	[ -a.y   a.x   0.0 ]
    //! This is also called a "cross matrix" since for any vectors A and B,
    //! A^B = Skew(A) * B = - B * Skew(A);
    inline void			skewSymmetric(const Vec3f& a)
                        {
                            m[0][0] = 0.0f;
                            m[0][1] = -a.z;
                            m[0][2] = a.y;

                            m[1][0] = a.z;
                            m[1][1] = 0.0f;
                            m[1][2] = -a.x;

                            m[2][0] = -a.y;
                            m[2][1] = a.x;
                            m[2][2] = 0.0f;
                        }

    //! Negates the matrix
    inline void			neg()
                        {
                            m[0][0] = -m[0][0];	m[0][1] = -m[0][1];	m[0][2] = -m[0][2];
                            m[1][0] = -m[1][0];	m[1][1] = -m[1][1];	m[1][2] = -m[1][2];
                            m[2][0] = -m[2][0];	m[2][1] = -m[2][1];	m[2][2] = -m[2][2];
                        }

    //! Add another matrix
    inline void			add(const Matrix3& mat)
                        {
                            m[0][0] += mat.m[0][0];	m[0][1] += mat.m[0][1];	m[0][2] += mat.m[0][2];
                            m[1][0] += mat.m[1][0];	m[1][1] += mat.m[1][1];	m[1][2] += mat.m[1][2];
                            m[2][0] += mat.m[2][0];	m[2][1] += mat.m[2][1];	m[2][2] += mat.m[2][2];
                        }

    //! Sub another matrix
    inline void			sub(const Matrix3& mat)
                        {
                            m[0][0] -= mat.m[0][0];	m[0][1]	-= mat.m[0][1];	m[0][2] -= mat.m[0][2];
                            m[1][0] -= mat.m[1][0];	m[1][1] -= mat.m[1][1];	m[1][2] -= mat.m[1][2];
                            m[2][0] -= mat.m[2][0];	m[2][1] -= mat.m[2][1];	m[2][2] -= mat.m[2][2];
                        }
    //! Mac
    //! Add by matrix and another matrix scaled...
    inline void			mac(const Matrix3& a, const Matrix3& b, float s)
                        {
                            m[0][0] = a.m[0][0] + b.m[0][0] * s;
                            m[0][1] = a.m[0][1] + b.m[0][1] * s;
                            m[0][2] = a.m[0][2] + b.m[0][2] * s;

                            m[1][0] = a.m[1][0] + b.m[1][0] * s;
                            m[1][1] = a.m[1][1] + b.m[1][1] * s;
                            m[1][2] = a.m[1][2] + b.m[1][2] * s;

                            m[2][0] = a.m[2][0] + b.m[2][0] * s;
                            m[2][1] = a.m[2][1] + b.m[2][1] * s;
                            m[2][2] = a.m[2][2] + b.m[2][2] * s;
                        }
    //! Mac
    //! Add a scaled matrix to this one
    inline  void		mac(const Matrix3& a, float s)
                        {
                            m[0][0] += a.m[0][0]*s; m[0][1] += a.m[0][1]*s;	m[0][2] += a.m[0][2]*s;
                            m[1][0] += a.m[1][0]*s; m[1][1] += a.m[1][1]*s;	m[1][2] += a.m[1][2]*s;
                            m[2][0] += a.m[2][0]*s; m[2][1] += a.m[2][1]*s;	m[2][2] += a.m[2][2]*s;
                        }
    //! this = a * b
    inline  void	    mult(const Matrix3& a, const Matrix3& b)
                        {
                            m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0];
                            m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1];
                            m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2];
                            m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0];
                            m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1];
                            m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2];
                            m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0];
                            m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1];
                            m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2];
                        }

    //! this = transpose(a) * b
    inline  void		multAtB(const Matrix3& a, const Matrix3& b)
                        {
                            m[0][0] = a.m[0][0] * b.m[0][0] + a.m[1][0] * b.m[1][0] + a.m[2][0] * b.m[2][0];
                            m[0][1] = a.m[0][0] * b.m[0][1] + a.m[1][0] * b.m[1][1] + a.m[2][0] * b.m[2][1];
                            m[0][2] = a.m[0][0] * b.m[0][2] + a.m[1][0] * b.m[1][2] + a.m[2][0] * b.m[2][2];
                            m[1][0] = a.m[0][1] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[2][1] * b.m[2][0];
                            m[1][1] = a.m[0][1] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[2][1] * b.m[2][1];
                            m[1][2] = a.m[0][1] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[2][1] * b.m[2][2];
                            m[2][0] = a.m[0][2] * b.m[0][0] + a.m[1][2] * b.m[1][0] + a.m[2][2] * b.m[2][0];
                            m[2][1] = a.m[0][2] * b.m[0][1] + a.m[1][2] * b.m[1][1] + a.m[2][2] * b.m[2][1];
                            m[2][2] = a.m[0][2] * b.m[0][2] + a.m[1][2] * b.m[1][2] + a.m[2][2] * b.m[2][2];
                        }

    //! this = a * transpose(b)
    inline  void		multABt(const Matrix3& a, const Matrix3& b)
                        {
                            m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[0][1] + a.m[0][2] * b.m[0][2];
                            m[0][1] = a.m[0][0] * b.m[1][0] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[1][2];
                            m[0][2] = a.m[0][0] * b.m[2][0] + a.m[0][1] * b.m[2][1] + a.m[0][2] * b.m[2][2];
                            m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[0][1] + a.m[1][2] * b.m[0][2];
                            m[1][1] = a.m[1][0] * b.m[1][0] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[1][2];
                            m[1][2] = a.m[1][0] * b.m[2][0] + a.m[1][1] * b.m[2][1] + a.m[1][2] * b.m[2][2];
                            m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[0][1] + a.m[2][2] * b.m[0][2];
                            m[2][1] = a.m[2][0] * b.m[1][0] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[1][2];
                            m[2][2] = a.m[2][0] * b.m[2][0] + a.m[2][1] * b.m[2][1] + a.m[2][2] * b.m[2][2];
                        }
    //! Makes a rotation matrix mapping vector "from" to vector "to".
            Matrix3&	fromTo(const Vec3f& from, const Vec3f& to);

    //! Set a rotation matrix around the X axis.
    //!		 1		0		0
    //!	RX = 0		cx		sx
    //!		 0		-sx		cx
            void		rotX(float angle)
                        {
                            m[0][0] = 1.0f; m[0][1] = 0.0f;                  m[0][2] = 0.0f;
                            m[1][0] = 0.0f; m[1][1] = cos(DEGTORAD(angle));  m[1][2] = sin(DEGTORAD(angle));
                            m[2][0] = 0.0f; m[2][1] = -sin(DEGTORAD(angle)); m[2][2] = cos(DEGTORAD(angle));
                        }

    //! Set a rotation matrix around the Y axis.
    //!		 cy		0		-sy
    //!	RY = 0		1		0
    //!		 sy		0		cy
            void		rotY(float angle);

    //! Set a rotation matrix around the Z axis.
    //!		 cz		sz		0
    //!	RZ = -sz	cz		0
    //!		 0		0		1
            void		rotZ(float angle);

    //!			cy		sx.sy		-sy.cx
    //!	RY.RX	0		cx			sx
    //!			sy		-sx.cy		cx.cy
            void		rotYX(float y, float x);

    //! Make a rotation matrix about an arbitrary axis
            Matrix3&  rot(float angle, const Vec3f& axis);

    //! Transpose the matrix. // wtf amazing.
            void		transpose()
                        {
                            IR(m[1][0]) ^= IR(m[0][1]);	IR(m[0][1]) ^= IR(m[1][0]);	IR(m[1][0]) ^= IR(m[0][1]);
                            IR(m[2][0]) ^= IR(m[0][2]);	IR(m[0][2]) ^= IR(m[2][0]);	IR(m[2][0]) ^= IR(m[0][2]);
                        }
    //! this = Transpose(a)
            void		transpose(const Matrix3& a)
                        {
                            m[0][0] = a.m[0][0];	m[0][1] = a.m[1][0];	m[0][2] = a.m[2][0];
                            m[1][0] = a.m[0][1];	m[1][1] = a.m[1][1];	m[1][2] = a.m[2][1];
                            m[2][0] = a.m[0][2];	m[2][1] = a.m[1][2];	m[2][2] = a.m[2][2];
                        }
    //! Compute the determinant of the matrix. We use the rule of Sarrus.
            float		determinant() const
                        {
                            return (m[0][0]*m[1][1]*m[2][2] + m[0][1]*m[1][2]*m[2][0] + m[0][2]*m[1][0]*m[2][1])
                                -  (m[2][0]*m[1][1]*m[0][2] + m[2][1]*m[1][2]*m[0][0] + m[2][2]*m[1][0]*m[0][1]);
                        }
    //! Invert the matrix. Determinant must be different from zero, else matrix can't be inverted.
            Matrix3&  invert()
                        {
                            float det = determinant();	// Must be !=0
                            float one_over_det = 1.0f / det;

                            Matrix3 temp;
                            temp.m[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]) * one_over_det;
                            temp.m[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * one_over_det;
                            temp.m[2][0] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]) * one_over_det;
                            temp.m[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * one_over_det;
                            temp.m[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]) * one_over_det;
                            temp.m[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * one_over_det;
                            temp.m[0][2] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]) * one_over_det;
                            temp.m[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * one_over_det;
                            temp.m[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]) * one_over_det;

                            *this = temp;

                            return	*this;
                        }
            Matrix3&  normalize();

    //! this = exp(a)
            Matrix3&	exp(const Matrix3& a);

//            void FromQuat(const Quat &q);
//            void FromQuatL2(const Quat &q, float l2);

    // Arithmetic Operators. I LOOOVE OVERLOADING
    //! Operator for Matrix3 Plus = Matrix3 + Matrix3;
    inline	Matrix3		operator+(const Matrix3& mat)	const
                            {
                                return Matrix3(
                                m[0][0] + mat.m[0][0],	m[0][1] + mat.m[0][1],	m[0][2] + mat.m[0][2],
                                m[1][0] + mat.m[1][0],	m[1][1] + mat.m[1][1],	m[1][2] + mat.m[1][2],
                                m[2][0] + mat.m[2][0],	m[2][1] + mat.m[2][1],	m[2][2] + mat.m[2][2]);
                            }

    //! Operator for Matrix3 Minus = Matrix3 - Matrix3;
    inline	Matrix3		operator-(const Matrix3& mat)	const
                            {
                                return Matrix3(
                                m[0][0] - mat.m[0][0],	m[0][1] - mat.m[0][1],	m[0][2] - mat.m[0][2],
                                m[1][0] - mat.m[1][0],	m[1][1] - mat.m[1][1],	m[1][2] - mat.m[1][2],
                                m[2][0] - mat.m[2][0],	m[2][1] - mat.m[2][1],	m[2][2] - mat.m[2][2]);
                            }

    //! Operator for Matrix3 Mul = Matrix3 * Matrix3;
    inline	Matrix3		operator*(const Matrix3& mat)	const
                            {
                                return Matrix3(
                                m[0][0]*mat.m[0][0] + m[0][1]*mat.m[1][0] + m[0][2]*mat.m[2][0],
                                m[0][0]*mat.m[0][1] + m[0][1]*mat.m[1][1] + m[0][2]*mat.m[2][1],
                                m[0][0]*mat.m[0][2] + m[0][1]*mat.m[1][2] + m[0][2]*mat.m[2][2],

                                m[1][0]*mat.m[0][0] + m[1][1]*mat.m[1][0] + m[1][2]*mat.m[2][0],
                                m[1][0]*mat.m[0][1] + m[1][1]*mat.m[1][1] + m[1][2]*mat.m[2][1],
                                m[1][0]*mat.m[0][2] + m[1][1]*mat.m[1][2] + m[1][2]*mat.m[2][2],

                                m[2][0]*mat.m[0][0] + m[2][1]*mat.m[1][0] + m[2][2]*mat.m[2][0],
                                m[2][0]*mat.m[0][1] + m[2][1]*mat.m[1][1] + m[2][2]*mat.m[2][1],
                                m[2][0]*mat.m[0][2] + m[2][1]*mat.m[1][2] + m[2][2]*mat.m[2][2]);
                            }
    //! Operator for Point Mul = Matrix3 * Point;
//    inline	Vec3f		    operator*(const Vec3f& v) const
//                            {
//                                return Vec3f(getRow(0)|v, getRow(1)|v, getRow(2)|v);
//                            }


    //! Operator for Matrix3 Mul = Matrix3 * float;
    inline	Matrix3		operator*(float s)				const
                            {
                                return Matrix3(
                                m[0][0]*s,	m[0][1]*s,	m[0][2]*s,
                                m[1][0]*s,	m[1][1]*s,	m[1][2]*s,
                                m[2][0]*s,	m[2][1]*s,	m[2][2]*s);
                            }

    //! Operator for Matrix3 Mul = float * Matrix3;
    inline	friend Matrix3 operator*(float s, const Matrix3& mat)
                            {
                                return Matrix3(
                                s*mat.m[0][0],	s*mat.m[0][1],	s*mat.m[0][2],
                                s*mat.m[1][0],	s*mat.m[1][1],	s*mat.m[1][2],
                                s*mat.m[2][0],	s*mat.m[2][1],	s*mat.m[2][2]);
                            }

    //! Operator for Matrix3 Div = Matrix3 / float;
    inline	Matrix3		operator/(float s)				const
                            {
                                if (s)	s = 1.0f / s;
                                return Matrix3(
                                m[0][0]*s,	m[0][1]*s,	m[0][2]*s,
                                m[1][0]*s,	m[1][1]*s,	m[1][2]*s,
                                m[2][0]*s,	m[2][1]*s,	m[2][2]*s);
                            }

    //! Operator for Matrix3 Div = float / Matrix3;
    inline	friend Matrix3 operator/(float s, const Matrix3& mat)
                            {
                                return Matrix3(
                                s/mat.m[0][0],	s/mat.m[0][1],	s/mat.m[0][2],
                                s/mat.m[1][0],	s/mat.m[1][1],	s/mat.m[1][2],
                                s/mat.m[2][0],	s/mat.m[2][1],	s/mat.m[2][2]);
                            }

    //! Operator for Matrix3 += Matrix3
    inline	Matrix3&		operator+=(const Matrix3& mat)
                            {
                                m[0][0] += mat.m[0][0];		m[0][1] += mat.m[0][1];		m[0][2] += mat.m[0][2];
                                m[1][0] += mat.m[1][0];		m[1][1] += mat.m[1][1];		m[1][2] += mat.m[1][2];
                                m[2][0] += mat.m[2][0];		m[2][1] += mat.m[2][1];		m[2][2] += mat.m[2][2];
                                return	*this;
                            }

    //! Operator for Matrix3 -= Matrix3
    inline	Matrix3&		operator-=(const Matrix3& mat)
                            {
                                m[0][0] -= mat.m[0][0];		m[0][1] -= mat.m[0][1];		m[0][2] -= mat.m[0][2];
                                m[1][0] -= mat.m[1][0];		m[1][1] -= mat.m[1][1];		m[1][2] -= mat.m[1][2];
                                m[2][0] -= mat.m[2][0];		m[2][1] -= mat.m[2][1];		m[2][2] -= mat.m[2][2];
                                return	*this;
                            }

    //! Operator for Matrix3 *= Matrix3
    inline	Matrix3&		operator*=(const Matrix3& mat)
                            {
                                Vec3f temp_row;

                                getRow(0, temp_row);
                                m[0][0] = temp_row.x*mat.m[0][0] + temp_row.y*mat.m[1][0] + temp_row.z*mat.m[2][0];
                                m[0][1] = temp_row.x*mat.m[0][1] + temp_row.y*mat.m[1][1] + temp_row.z*mat.m[2][1];
                                m[0][2] = temp_row.x*mat.m[0][2] + temp_row.y*mat.m[1][2] + temp_row.z*mat.m[2][2];

                                getRow(1, temp_row);
                                m[1][0] = temp_row.x*mat.m[0][0] + temp_row.y*mat.m[1][0] + temp_row.z*mat.m[2][0];
                                m[1][1] = temp_row.x*mat.m[0][1] + temp_row.y*mat.m[1][1] + temp_row.z*mat.m[2][1];
                                m[1][2] = temp_row.x*mat.m[0][2] + temp_row.y*mat.m[1][2] + temp_row.z*mat.m[2][2];

                                getRow(2, temp_row);
                                m[2][0] = temp_row.x*mat.m[0][0] + temp_row.y*mat.m[1][0] + temp_row.z*mat.m[2][0];
                                m[2][1] = temp_row.x*mat.m[0][1] + temp_row.y*mat.m[1][1] + temp_row.z*mat.m[2][1];
                                m[2][2] = temp_row.x*mat.m[0][2] + temp_row.y*mat.m[1][2] + temp_row.z*mat.m[2][2];
                                return	*this;
                            }

    //! Operator for Matrix3 *= float
    inline	Matrix3&		operator*=(float s)
                            {
                                m[0][0] *= s;	m[0][1] *= s;	m[0][2] *= s;
                                m[1][0] *= s;	m[1][1] *= s;	m[1][2] *= s;
                                m[2][0] *= s;	m[2][1] *= s;	m[2][2] *= s;
                                return	*this;
                            }

    //! Operator for Matrix3 /= float
    inline	Matrix3&		operator/=(float s)
                            {
                                if (s)	s = 1.0f / s;
                                m[0][0] *= s;	m[0][1] *= s;	m[0][2] *= s;
                                m[1][0] *= s;	m[1][1] *= s;	m[1][2] *= s;
                                m[2][0] *= s;	m[2][1] *= s;	m[2][2] *= s;
                                return	*this;
                            }

       //inline      void setScale(const Vec3f p)

};

#endif // MATRIX3_H

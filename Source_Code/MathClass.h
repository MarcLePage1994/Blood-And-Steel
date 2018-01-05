#pragma once
#include <iostream>
using namespace std;

const float PI = 3.141592654f;
const float DegreesToRadians = PI / 180.0f;
const float RadiansToDegrees = 180.0f / PI;


//3D vectors
class Vec3f
{
public:
	Vec3f();
	Vec3f(float x, float y, float z);

	Vec3f operator+ (const Vec3f &other);
	Vec3f operator- (const Vec3f &other);
	Vec3f operator* (const Vec3f &other);
	Vec3f operator* (float scale);
	/*Vec3f operator/ (Vec3f &other);*/

	//access vector's individual elements
	float operator[](int index) const;
	float &operator[](int index);

	Vec3f operator+= (const Vec3f &other);
	//Vec3f operator-= (Vec3f &other);
	Vec3f operator*= (const Vec3f &other);
	Vec3f operator*= (float scale);
	bool operator == (const Vec3f &other);
	bool operator != (const Vec3f &other);
	bool operator <= (const Vec3f &other);

	float magnitude();
	Vec3f normalize();
	Vec3f square();
	float dot(const Vec3f &other);	//dot product
	Vec3f cross(const Vec3f &other);	//cross product
	Vec3f dirVec(const Vec3f &other);		//direction of a vector between two points
	
	//matrix multyplyed by a vector
	Vec3f matrixMult(Vec3f &row1, Vec3f &row2, Vec3f &row3);

	Vec3f applyYRotation(float &theta);

	Vec3f negate(); //finds the inverse of the vector

//private:
	float v[3];
};

ostream &operator<<(ostream &os, const Vec3f &v);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//4D vectors
class Vec4f
{
public:
	Vec4f();
	Vec4f(float x, float y, float z, float w);
	Vec4f(Vec3f vec, float w);

	Vec4f operator+ (const Vec4f &other);
	Vec4f operator- (const Vec4f &other);
	Vec4f operator* (const Vec4f &other);
	Vec4f operator* (float scale);

	//access vector's individual elements
	float operator[](int index) const;
	float &operator[](int index);

	Vec4f operator+= (const Vec4f &other);
	//Vec3f operator-= (Vec3f &other);
	Vec4f operator*= (const Vec4f &other);
	Vec4f operator*= (float scale);
	bool operator == (const Vec4f &other);
	bool operator != (const Vec4f &other);

	float magnitude();
	Vec4f normalize();
	Vec4f square();
	float dot(const Vec4f &other);	//dot product
	Vec4f cross(const Vec4f &other);	//cross product
	Vec4f dirVec(const Vec4f &other);		//direction of a vector between two points

	Vec4f negate(); //finds the inverse of the vector

//private:
	float v[4];
};

ostream &operator<<(ostream &os, const Vec4f &v);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//3D matrices
class Mat3f
{
public:
	Mat3f();
	Mat3f(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
	Mat3f(Vec3f Vrow1, Vec3f Vrow2, Vec3f Vrow3);
	//~Mat3f();

	Mat3f operator+ (const Mat3f &other);
	Mat3f operator* (const Mat3f &other);
	Mat3f operator* (float scale);
	Vec3f operator* (const Vec3f &other);
	
	//Mat3f operator+= (Mat3f &other);
	//Mat3f operator*= (Mat3f &other);
	//Mat3f operator*= (float scale);
	//Vec3f operator*= (Vec3f &other);

	Mat3f square();
	Mat3f transpose(); 

	//union; this means that all of these variables are accessing the same memory location and i can determine how i want my data to be represented
	union
	{
		float m[9];
		struct
		{
			Vec3f row1;
			Vec3f row2;
			Vec3f row3;
		};
	};
};

//ostream& operator<<(ostream& os, const Mat3f& Mat3f);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//4D matrices
class Mat4f
{
public:
	Mat4f();
	Mat4f(float matrix[16]);
	Mat4f(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
	Mat4f(Vec4f Vrow1, Vec4f Vrow2, Vec4f Vrow3, Vec4f Vrow4);
	//~Mat3f();

	Mat4f operator+ (const Mat4f &other);
	Mat4f operator* (const Mat4f &other);
	Mat4f operator* (const Mat4f &other) const;
	Mat4f operator* (const float scale);
	Vec4f operator* (const Vec4f &other);
	
	//Mat4f operator+= (Mat4f &other);
	//Mat4f operator*= (Mat4f &other);
	//Mat4f operator*= (float scale);
	//Vec3f operator*= (Vec3f &other);

	Mat4f square();
	Mat4f transpose(); 

	//union; this means that all of these variables are accessing the same memory location and i can determine how i want my data to be represented
	union
	{
		float m[16];
		float a[4][4];
		struct
		{
			Vec4f row1;
			Vec4f row2;
			Vec4f row3;
			Vec4f row4;
		};
	};
};

//ostream& operator<<(ostream& os, const Mat4f& Mat4f);

//------------------------------------------------------------------------------------------------------------------------------------------------>

//creates a 4D translation matrix
inline Mat4f Translate(float x, float y, float z)
{
	return Mat4f(Vec4f(1.0f, 0.0f, 0.0f, x), Vec4f(0.0f, 1.0f, 0.0f, y), Vec4f(0.0f, 0.0f, 1.0f, z), Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
}

inline Mat4f Translate(const Vec3f &v)
{
	return Translate(v[0], v[1], v[2]);
}

inline Mat4f Translate(const Vec4f &v)
{
	return Translate(v[0], v[1], v[2]);
}

//------------------------------------------------------------------------------------------------------------------------------------------------>

//creates a 4D scaling matrix
inline Mat4f Scale(float x, float y, float z)
{
	return Mat4f(Vec4f(x, 0.0f, 0.0f, 0.0f), Vec4f(0.0f, y, 0.0f, 0.0f), Vec4f(0.0f, 0.0f, z, 0.0f), Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
}

inline Mat4f Scale(const Vec3f &v)
{
	return Scale(v[0], v[1], v[2]);
}

inline Mat4f Scale(const Vec4f &v)
{
	return Scale(v[0], v[1], v[2]);
}
//------------------------------------------------------------------------------------------------------------------------------------------------>
//return an identiy matrix
inline Mat4f Identity()
{
	return Mat4f(1.0f, 0.0f, 0.0f, 0.0f,
				 0.0f, 1.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 1.0f, 0.0f,
				 0.0f, 0.0f, .0f, 1.0f); 
}

//------------------------------------------------------------------------------------------------------------------------------------------------>

////creates a 4D rotation matrix on the x-axis
inline Mat4f RotateX(const float angle)
{
	float radians = DegreesToRadians * angle;
	return Mat4f(Vec4f(1.0f, 0.0f, 0.0f, 0.0f), Vec4f(0.0f, cosf(radians), -sinf(radians), 0.0f), Vec4f(0.0f, sinf(radians), cosf(radians), 0.0f), Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
}

////creates a 4D rotation matrix on the y-axis
inline Mat4f RotateY(const float angle)
{
	float radians = DegreesToRadians * angle;
	return Mat4f(Vec4f(cosf(radians), 0.0f, sinf(radians), 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 0.0f), Vec4f(-sinf(radians), 0.0f, cosf(radians), 0.0f), Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
}

////creates a 4D rotation matrix on the z-axis
inline Mat4f RotateZ(const float angle)
{
	float radians = DegreesToRadians * angle;
	return Mat4f(Vec4f(cosf(radians), -sinf(radians), 0.0f, 0.0f), Vec4f(sinf(radians), cos(radians), 0.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 0.0f), Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
}

//------------------------------------------------------------------------------------------------------------------------------------------------>
// homogeneous transform
inline Mat4f makeTransform(const Mat4f &r, const Vec3f &t)
{
	/*return Mat4f(r.row1[0], r.row1[1], r.row1[2], t[0],
				 r.row2[0], r.row2[1], r.row2[2], t[1],
				 r.row3[0], r.row3[1], r.row3[2], t[2],
				 0.0f,		0.0f,	   0.0f,	  1.0f);*/
	return Mat4f(Vec4f(r.row1[0], r.row1[1], r.row1[2], t[0]),
				 Vec4f(r.row2[0], r.row2[1], r.row2[2], t[1]),
				 Vec4f(r.row3[0], r.row3[1], r.row3[2], t[2]),
				 Vec4f(0.0f,	  0.0f,		 0.0f,		1.0f));
}

// homogeneous transform transform with scale
inline Mat4f makeTransform(const Mat4f &r, const Mat4f &s, const Vec3f &t)
{
	return makeTransform( r * s, t );
}

//creates a inverse matrix of a transformation matrix that does not have a scale factor applied to it
inline Mat4f transformInverseNoScale(const Mat4f &m)
{
	//extract rotation component of matrix and transpose it
	Mat4f r = Mat4f(Vec4f(m.row1[0], m.row1[1], m.row1[2], 0.0f), 
					Vec4f(m.row2[0], m.row2[1], m.row2[2], 0.0f), 
					Vec4f(m.row3[0], m.row3[1], m.row3[2], 0.0f), 
					Vec4f(0.0f, 0.0f, 0.0f, 1.0f)).transpose();
	
	//extract translation component of matrix and negate it
	//Mat4f t = Mat4f(1.0f, 0.0f, 0.0f, m.row1[3] * -1.0f,
	//				0.0f, 1.0f, 0.0f, m.row2[3] * -1.0f,
	//				0.0f, 0.0f, 1.0f, m.row3[3] * -1.0f,
	//				0.0f, 0.0f, 0.0f, 1.0f);
	Mat4f t = Mat4f(Vec4f(1.0f, 0.0f, 0.0f, m.row1[3] * -1.0f),
					Vec4f(0.0f, 1.0f, 0.0f, m.row2[3] * -1.0f),
					Vec4f(0.0f, 0.0f, 1.0f, m.row3[3] * -1.0f),
					Vec4f(0.0f, 0.0f, 0.0f, 1.0f));

	//return r * t; 
	return makeTransform(r, Vec3f(t.row1[3], t.row2[3], t.row3[3])); 
}

//inline float determinant(Mat4f m)
//{
//	float det = (m.row1[0] * m.row2[1] * m.row3[2] * m.row4[3]) + (m.row1[0] * m.row2[2] * m.row3[3] * m.row4[1]) + (m.row1[0] * m.row2[3] * m.row3[1] * m.row4[2]) +
//				(m.row1[1] * m.row2[0] * m.row3[3] * m.row4[2]) + (m.row1[1] * m.row2[2] * m.row3[0] * m.row4[3]) + (m.row1[1] * m.row2[3] * m.row3[2] * m.row4[0]) +
//				(m.row1[2] * m.row2[0] * m.row3[1] * m.row4[3]) + (m.row1[2] * m.row2[1] * m.row3[3] * m.row4[0]) + (m.row1[2] * m.row2[3] * m.row3[0] * m.row4[1]) + 
//				(m.row1[3] * m.row2[0] * m.row3[2] * m.row4[1]) + (m.row1[3] * m.row2[1] * m.row3[0] * m.row4[2]) + (m.row1[3] * m.row2[2] * m.row3[1] * m.row4[0]) -
//				(m.row1[0] * m.row2[1] * m.row3[3] * m.row4[2]) - (m.row1[0] * m.row2[2] * m.row3[1] * m.row4[3]) - (m.row1[0] * m.row2[3] * m.row3[2] * m.row4[1]) - 
//				(m.row1[1] * m.row2[0] * m.row3[2] * m.row4[3]) - (m.row1[1] * m.row2[2] * m.row3[3] * m.row4[0]) - (m.row1[1] * m.row2[3] * m.row3[0] * m.row4[2]) -
//				(m.row1[2] * m.row2[0] * m.row3[3] * m.row4[1]) - (m.row1[2] * m.row2[1] * m.row3[0] * m.row4[3]) - (m.row1[2] * m.row2[3] * m.row3[1] * m.row4[0]) -
//				(m.row1[3] * m.row2[0] * m.row3[1] * m.row4[2]) - (m.row1[3] * m.row2[1] * m.row3[2] * m.row4[0]) - (m.row1[3] * m.row2[2] * m.row3[0] * m.row4[1]); 
//
//	//determinant cannot equal to 0 
//	if(det == 0)
//	{
//		return 1;
//	}
//
//	return det; 
//}
//
//inline Mat4f inverse(Mat4f m)
//{
//	Mat4f inverseM;
//
//	inverseM.row1[0] = (m.row2[1] * m.row3[2] * m.row4[3]) + (m.row2[2] * m.row3[3] * m.row4[1]) + (m.row2[3] * m.row3[1] * m.row4[2]) - (m.row2[1] * m.row3[3] * m.row4[2]) - (m.row2[2] * m.row3[1] * m.row4[3]) - (m.row2[3] * m.row3[2] * m.row4[1]);
//	inverseM.row1[1] = (m.row1[1] * m.row3[3] * m.row4[2]) + (m.row1[2] * m.row3[1] * m.row4[3]) + (m.row1[3] * m.row3[2] * m.row4[1]) - (m.row1[1] * m.row3[2] * m.row4[3]) - (m.row1[2] * m.row3[3] * m.row4[1]) - (m.row1[3] * m.row3[1] * m.row4[2]);
//	inverseM.row1[2] = (m.row1[1] * m.row2[2] * m.row4[3]) + (m.row1[2] * m.row2[3] * m.row4[1]) + (m.row1[3] * m.row2[1] * m.row4[2]) - (m.row1[1] * m.row2[3] * m.row4[2]) - (m.row1[2] * m.row2[1] * m.row4[3]) - (m.row1[3] * m.row2[2] * m.row4[1]);
//	inverseM.row1[3] = (m.row1[1] * m.row2[3] * m.row3[2]) + (m.row1[2] * m.row2[1] * m.row3[3]) + (m.row1[3] * m.row2[2] * m.row3[1]) - (m.row1[1] * m.row2[2] * m.row3[3]) - (m.row1[2] * m.row2[3] * m.row3[1]) - (m.row1[3] * m.row2[1] * m.row3[2]);
//
//	inverseM.row2[0] = (m.row2[0] * m.row3[3] * m.row4[2]) + (m.row2[2] * m.row3[0] * m.row4[3]) + (m.row2[3] * m.row3[2] * m.row4[0]) - (m.row2[0] * m.row3[2] * m.row4[3]) - (m.row2[2] * m.row3[3] * m.row4[0]) - (m.row2[3] * m.row3[0] * m.row4[2]);
//	inverseM.row2[1] = (m.row1[0] * m.row3[2] * m.row4[3]) + (m.row1[2] * m.row3[3] * m.row4[0]) + (m.row1[3] * m.row3[0] * m.row4[2]) - (m.row1[0] * m.row3[3] * m.row4[2]) - (m.row1[2] * m.row3[0] * m.row4[3]) - (m.row1[3] * m.row3[2] * m.row4[0]);
//	inverseM.row2[2] = (m.row1[0] * m.row2[3] * m.row4[2]) + (m.row1[2] * m.row2[0] * m.row4[3]) + (m.row1[3] * m.row2[2] * m.row4[0]) - (m.row1[0] * m.row2[2] * m.row4[3]) - (m.row1[2] * m.row2[3] * m.row4[0]) - (m.row1[3] * m.row2[0] * m.row4[2]);
//	inverseM.row2[3] = (m.row1[0] * m.row2[2] * m.row3[3]) + (m.row1[2] * m.row2[3] * m.row3[0]) + (m.row1[3] * m.row2[0] * m.row3[2]) - (m.row1[0] * m.row2[3] * m.row3[2]) - (m.row1[2] * m.row2[0] * m.row3[3]) - (m.row1[3] * m.row2[2] * m.row3[0]);
//
//	inverseM.row3[0] = (m.row2[0] * m.row3[1] * m.row4[3]) + (m.row2[1] * m.row3[3] * m.row4[0]) + (m.row2[3] * m.row3[0] * m.row4[1]) - (m.row2[0] * m.row3[3] * m.row4[1]) - (m.row2[1] * m.row3[0] * m.row4[3]) - (m.row2[3] * m.row3[1] * m.row4[0]);
//	inverseM.row3[1] = (m.row1[0] * m.row3[3] * m.row4[1]) + (m.row1[1] * m.row3[0] * m.row4[3]) + (m.row1[3] * m.row3[1] * m.row4[0]) - (m.row1[0] * m.row3[1] * m.row4[3]) - (m.row1[1] * m.row3[3] * m.row4[0]) - (m.row1[3] * m.row3[0] * m.row4[1]);
//	inverseM.row3[2] = (m.row1[0] * m.row2[1] * m.row4[3]) + (m.row1[1] * m.row2[3] * m.row4[0]) + (m.row1[3] * m.row2[0] * m.row4[1]) - (m.row1[0] * m.row2[3] * m.row4[1]) - (m.row1[1] * m.row2[0] * m.row4[3]) - (m.row1[3] * m.row2[1] * m.row4[0]);
//	inverseM.row3[3] = (m.row1[0] * m.row2[3] * m.row3[1]) + (m.row1[1] * m.row2[0] * m.row3[3]) + (m.row1[3] * m.row2[1] * m.row3[0]) - (m.row1[0] * m.row2[1] * m.row3[3]) - (m.row1[1] * m.row2[3] * m.row3[0]) - (m.row1[3] * m.row2[0] * m.row3[1]);
//
//	inverseM.row4[0] = (m.row2[0] * m.row3[2] * m.row4[1]) + (m.row2[1] * m.row3[0] * m.row4[2]) + (m.row2[2] * m.row3[1] * m.row4[0]) - (m.row2[0] * m.row3[1] * m.row4[2]) - (m.row2[1] * m.row3[2] * m.row4[0]) - (m.row2[2] * m.row3[0] * m.row4[1]);
//	inverseM.row4[1] = (m.row1[0] * m.row3[1] * m.row4[2]) + (m.row1[1] * m.row3[2] * m.row4[0]) + (m.row1[2] * m.row3[0] * m.row4[1]) - (m.row1[0] * m.row3[2] * m.row4[1]) - (m.row1[1] * m.row3[0] * m.row4[2]) - (m.row1[2] * m.row3[1] * m.row4[0]);
//	inverseM.row4[2] = (m.row1[0] * m.row2[2] * m.row4[1]) + (m.row1[1] * m.row2[0] * m.row4[2]) + (m.row1[2] * m.row2[1] * m.row4[0]) - (m.row1[0] * m.row2[1] * m.row4[2]) - (m.row1[1] * m.row2[2] * m.row4[0]) - (m.row1[2] * m.row2[0] * m.row4[1]);
//	inverseM.row4[3] = (m.row1[0] * m.row2[1] * m.row3[2]) + (m.row1[1] * m.row2[2] * m.row3[0]) + (m.row1[2] * m.row2[0] * m.row3[1]) - (m.row1[0] * m.row2[2] * m.row3[1]) - (m.row1[1] * m.row2[0] * m.row3[2]) - (m.row1[2] * m.row2[1] * m.row3[0]);
//
//	float det = determinant(inverseM);
//
//	return inverseM * (1.0f/det); 
//}

//------------------------------------------------------------------------------------------------------------------------------------------------>

//creates a 4D perspective matrix
/*
fovy: is the field of view angle on the yz-plane ranging from 0 to 180 degrees
aspect: is the aspect ratio (window width/ window height)
zNear and zFar: is the distance from the near clipping plane to the far clipping plane
which starts from the viewport and travels down the z-axis. 
*/
inline Mat4f Perspective(float fovyDegrees, float aspectRatio, float zNear, float zFar)
{
	float top = tanf((fovyDegrees * DegreesToRadians) * 0.5f) * zNear;
	float right = top * aspectRatio;

	return Mat4f(Vec4f(zNear/right, 0.0f, 0.0f, 0.0f), 
				Vec4f(0.0f, zNear/top, 0.0f, 0.0f), 
				Vec4f(0.0f, 0.0f, -(zFar + zNear) / (zFar - zNear), -1.0f), 
				Vec4f(0.0f, 0.0f, (-2.0f * zFar * zNear) / (zFar - zNear), 0.0f));
}

inline Mat4f inversePerspective(float fovyDegrees, float aspectRatio, float zNear, float zFar)
{
	float top = tanf((fovyDegrees * DegreesToRadians) * 0.5f) * zNear;
	float right = top * aspectRatio;

	return Mat4f(Vec4f(right/zNear, 0.0f, 0.0f, 0.0f), 
				Vec4f(0.0f, top/zNear, 0.0f, 0.0f), 
				Vec4f(0.0f, 0.0f, 0.0f, (zFar - zNear) / (-2.0f * zFar * zNear)), 
				Vec4f(0.0f, 0.0f, -1.0f, (zFar + zNear) / (2.0f * zFar * zNear)));
}

//viewing Transformation matrix generation
//inline Mat4f LookAt(Vec4f &eye, Vec4f &at, Vec4f &yAxis)
//{
//	//frenet frame
//	Vec4f dir = (eye - at).normalize();		
//	Vec4f right = (yAxis.cross(dir)).normalize();
//	Vec4f up = (dir.cross(right)).normalize();
//	
//	Vec4f temp = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
//
//	//return Mat4f(right, up, dir, temp) * Translate(eye * -1.0f);
//
//	return Mat4f(right[0], up[0], dir[0], temp[0],
//				 right[1], up[1], dir[1], temp[1],
//				 right[2], up[2], dir[2], temp[2],
//				 right[3], up[3], dir[3], temp[3]) * Translate(eye * -1.0f);
//}

// compute a transform (obj-to-world) using a 'look-at' utility
// this can be used for anything, not just a camera!
inline Mat4f LookAt(Vec4f eye, Vec4f at, Vec4f yAxis)
{
	//	
	//	YOU SHOULD REMEMBER THIS FROM LAST TERM: 
	//	"FRENET FRAME"
	//
	//				c1 = j = Up
	//						o
	//						|	
	//						|  . (Dir)
	//						| .
	//						|.
	//	c3 = E = position	X----------o  c0 = i = Right
	//					   /
	//					  /
	//					 o
	//	c2 = k = -(Direction)
	//	

	//frenet frame
	Vec4f dir = (eye - at).normalize();		
	Vec4f right = (yAxis.cross(dir)).normalize();
	Vec4f up = (dir.cross(right)).normalize();
	
	Vec4f temp = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);

	return Mat4f(right[0], up[0], dir[0], temp[0],
				 right[1], up[1], dir[1], temp[1],
				 right[2], up[2], dir[2], temp[2],
				 right[3], up[3], dir[3], temp[3]) * Translate(eye * -1.0f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//quaternions
class Quat
{
public:
	Quat();
	Quat(float _w, Vec3f &other);
	Quat(float w, float x, float y, float z);

	Vec3f toVector ();	//for this to work properly, the quaternion must be a pure quaternion
	Quat conjugate();

	Quat operator* (Quat &other);
	Quat operator* (float scale);
	Quat operator+ (Quat &other);
	float operator[](int index) const;
	float &operator[](int index);

	float dot(Quat &other);	//dot product
	Quat normalize();

	Vec3f XYZ;	//vector
	float w;	//scaler

};

inline Quat rotationQuat(float degrees, Vec3f &axis)
{
	float radians = degrees * DegreesToRadians;
	return Quat(cosf(radians / 2), axis.normalize() * (sinf(radians / 2)));
}

ostream& operator<<(ostream& os, const Quat& Quat);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//for physics calculations

class physics
{
public:
	physics();
	~physics();

	Vec3f spring(float k, float length, Vec3f direction);

	Vec3f acceleration(Vec3f force, float m);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//for animation
//LERP
template <typename lerpClass>
inline lerpClass LERP(lerpClass v0, lerpClass v1, float t)
{
	/*if (v0 == v1)
	{
		return v0;
	}*/

	return (v0*(1.0f-t)) + (v1*t);
}

inline Quat SLERP(Quat q0, Quat q1, float dt)
{
	float angle = acosf(q0.dot(q1));

	//return (q0 * (1-dt))  + (q1 * dt);

	Quat temp1 = q0 * (sinf((1-dt)*angle)/sinf(angle));
	Quat temp2 = q1 * (sinf(dt * angle)/sinf(angle));

	return (temp1 + temp2);
}

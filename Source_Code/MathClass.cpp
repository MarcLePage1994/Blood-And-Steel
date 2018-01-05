#include "MathClass.h"

Vec3f::Vec3f()
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}

Vec3f::Vec3f(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vec3f Vec3f::negate() //mathclass.cpp
{
	return Vec3f(-v[0], -v[1], -v[2]);
}

Vec3f Vec3f::operator+ (const Vec3f &other)
{
	return Vec3f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Vec3f Vec3f::operator- (const Vec3f &other)
{
	return Vec3f(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Vec3f Vec3f::operator* (const Vec3f &other)
{
	return Vec3f(v[0] * other.v[0], v[1] * other.v[1], v[2] * other.v[2]);
}

Vec3f Vec3f::operator* (float scale)
{
	return Vec3f(v[0] * scale, v[1] * scale, v[2] * scale);
}

//Vec3f Vec3f::operator/ (Vec3f &other)
//{
//	return Vec3f(v[0] / other.v[0], v[1] / other.v[1], v[2] / other.v[2]);
//}

float Vec3f::operator[](int index) const
{
	return v[index];
}

float &Vec3f::operator[](int index)
{
	return v[index];
}

Vec3f Vec3f::operator+= (const Vec3f &other)
{
	return Vec3f(v[0] += other.v[0], v[1] += other.v[1], v[2] += other.v[2]); 
}

Vec3f Vec3f::operator*= (const Vec3f &other)
{
	return Vec3f(v[0] *= other.v[0], v[1] *= other.v[1], v[2] *= other.v[2]);
}

Vec3f Vec3f::operator*= (float scale)
{
	return Vec3f(v[0] *= scale, v[1] *= scale, v[2] *= scale);
}

bool Vec3f::operator== (const Vec3f &other)
{
	if(v[0] == other.v[0] && v[1] == other.v[1] && v[2] == other.v[2])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Vec3f::operator!= (const Vec3f &other)
{
	if(v[0] == other.v[0] && v[1] == other.v[1] && v[2] == other.v[2])
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Vec3f::operator<= (const Vec3f &other)
{
	if(v[0] <= other.v[0] && v[1] <= other.v[1] && v[2] <= other.v[2])
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Vec3f::magnitude()
{
	return sqrtf((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
}

Vec3f Vec3f::normalize()
{
	float mag = sqrtf((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
	return Vec3f(v[0] * (1.0f/mag), v[1] * (1.0f/mag), v[2] * (1.0f/mag));
}

Vec3f Vec3f::square()
{
	return Vec3f((v[0] * v[0]), (v[1] * v[1]), (v[2] * v[2]));
}

float Vec3f::dot(const Vec3f &other)
{
	return (v[0] * other.v[0]) + (v[1] * other.v[1]) + (v[2] * other.v[2]);
}

Vec3f Vec3f::cross(const Vec3f &other)
{
	return Vec3f((v[1] * other.v[2]) - (other.v[1] * v[2]), (v[2] * other.v[0]) - (other.v[2] * v[0]), (v[0] * other.v[1]) - (other.v[0] * v[1]));
}

Vec3f Vec3f::dirVec(const Vec3f &other)
{
	Vec3f combined = Vec3f(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
	return combined.normalize();
}

Vec3f Vec3f::matrixMult(Vec3f &row1, Vec3f &row2, Vec3f &row3)
{
	return Vec3f((v[0] * row1.v[0]) + (v[1] * row1.v[1]) + (v[2] * row1.v[2]), (v[0] * row2.v[0]) + (v[1] * row2.v[1]) + (v[2] * row2.v[2]), (v[0] * row3.v[0]) + (v[1] * row3.v[1]) + (v[2] * row3.v[2]));
}

Vec3f Vec3f::applyYRotation(float &theta)
{
	float radsToDegrees = theta * DegreesToRadians;

	//is this giving me a value in radians?! YES IT IS. GOTTA FIX THAT
	Vec3f YMatrixRow1(cos(radsToDegrees), 0, sin(radsToDegrees));
	Vec3f YMatrixRow2(0.f, 1.f, 0.f);
	Vec3f YMatrixRow3(-sin(radsToDegrees), 0, cos(radsToDegrees));

	return this->matrixMult(YMatrixRow1,YMatrixRow2,YMatrixRow3);
}

ostream& operator<<(ostream& os, const Vec3f &v)
{
	cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << endl;
	return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vec4f::Vec4f()
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 1.0f;
}

Vec4f::Vec4f(float x, float y, float z, float w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

Vec4f::Vec4f(Vec3f vec, float w)
{
	v[0] = vec[0];
	v[1] = vec[1];
	v[2] = vec[2];
	v[3] = w;
}

Vec4f Vec4f::negate() //mathclass.cpp
{
	return Vec4f(-v[0], -v[1], -v[2], -v[3]);
}

Vec4f Vec4f::operator+ (const Vec4f &other)
{
	return Vec4f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2], v[3] + other.v[3]);
}

Vec4f Vec4f::operator- (const Vec4f &other)
{
	return Vec4f(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2], v[3] - other.v[3]);
}

Vec4f Vec4f::operator* (const Vec4f &other)
{
	return Vec4f(v[0] * other.v[0], v[1] * other.v[1], v[2] * other.v[2], v[3] * other.v[3]);
}

Vec4f Vec4f::operator* (float scale)
{
	return Vec4f(v[0] * scale, v[1] * scale, v[2] * scale, v[3] * scale);
}

float Vec4f::operator[](int index) const
{
	return v[index];
}

float &Vec4f::operator[](int index)
{
	return v[index];
}

Vec4f Vec4f::operator+= (const Vec4f &other)
{
	return Vec4f(v[0] += other.v[0], v[1] += other.v[1], v[2] += other.v[2], v[3] += other.v[3]); 
}

Vec4f Vec4f::operator*= (const Vec4f &other)
{
	return Vec4f(v[0] *= other.v[0], v[1] *= other.v[1], v[2] *= other.v[2], v[3] *= other.v[3]);
}

Vec4f Vec4f::operator*= (float scale)
{
	return Vec4f(v[0] *= scale, v[1] *= scale, v[2] *= scale, v[3] *= scale);
}

bool Vec4f::operator== (const Vec4f &other)
{
	if(v[0] == other.v[0] && v[1] == other.v[1] && v[2] == other.v[2] && v[3] == other.v[3])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Vec4f::operator!= (const Vec4f &other)
{
	if(v[0] == other.v[0] && v[1] == other.v[1] && v[2] == other.v[2] && v[3] == other.v[3])
	{
		return false;
	}
	else
	{
		return true;
	}
}

float Vec4f::magnitude()
{
	return sqrtf((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]) + (v[3] * v[3]));
}

Vec4f Vec4f::normalize()
{
	float mag = sqrtf((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]) + (v[3] * v[3]));
	return Vec4f(v[0] * (1.0f/mag), v[1] * (1.0f/mag), v[2] * (1.0f/mag), v[3] * (1.0f/mag));
}

Vec4f Vec4f::square()
{
	return Vec4f((v[0] * v[0]), (v[1] * v[1]), (v[2] * v[2]), (v[3] * v[3]));
}

float Vec4f::dot(const Vec4f &other)
{
	return (v[0] * other.v[0]) + (v[1] * other.v[1]) + (v[2] * other.v[2]) + (v[3] * other.v[3]);
}

Vec4f Vec4f::cross(const Vec4f &other)
{
	return Vec4f((v[1] * other.v[2]) - (other.v[1] * v[2]), (v[2] * other.v[0]) - (other.v[2] * v[0]), (v[0] * other.v[1]) - (other.v[0] * v[1]), 1.0f);
}

Vec4f Vec4f::dirVec(const Vec4f &other)
{
	Vec4f combined = Vec4f(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2], v[3] - other.v[3]);
	return combined.normalize();
}

ostream& operator<<(ostream& os, const Vec4f &v)
{
	cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")" << endl;
	return os;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//identity matrix
Mat3f::Mat3f()
{
	row1[0] = 1.0f;
	row1[1] = 0.0f;
	row1[2] = 0.0f;
	row2[0] = 0.0f;
	row2[1] = 1.0f;
	row2[2] = 0.0f;
	row3[0] = 0.0f;
	row3[1] = 0.0f;
	row3[2] = 1.0f;

}

Mat3f::Mat3f(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
{
	row1[0] = m00;
	row1[1] = m01;
	row1[2] = m02;
	row2[0] = m10;
	row2[1] = m11;
	row2[2] = m12;
	row3[0] = m20;
	row3[1] = m21;
	row3[2] = m22;

	m[0] = m00;
	m[1] = m01;
	m[2] = m02;
	m[3] = m10;
	m[4] = m11;
	m[5] = m12;
	m[6] = m20;
	m[7] = m21;
	m[8] = m22;
}

Mat3f::Mat3f(Vec3f Vrow1, Vec3f Vrow2, Vec3f Vrow3)
{
	row1[0] = Vrow1[0];
	row1[1] = Vrow1[1];
	row1[2] = Vrow1[2];
	row2[0] = Vrow2[0];
	row2[1] = Vrow2[1];
	row2[2] = Vrow2[2];
	row3[0] = Vrow3[0];
	row3[1] = Vrow3[1];
	row3[2] = Vrow3[2];
}

Mat3f Mat3f::operator+ (const Mat3f &other)
{
	return Mat3f(row1[0] + other.row1[0], row1[1] + other.row1[1], row1[2] + other.row1[2], row2[0] + other.row2[0], row2[1] + other.row2[1], row2[2] + other.row2[2], row3[0] + other.row3[0], row3[1] + other.row3[1], row3[2] + other.row3[2]);
}

Mat3f Mat3f::operator* (const Mat3f &other)
{
	return Mat3f((row1[0] * other.row1[0]) + (row1[1] * other.row2[0]) + (row1[2] * other.row3[0]), (row1[0] * other.row1[1]) + (row1[1] * other.row2[1]) + (row1[2] * other.row3[1]), (row1[0] * other.row1[2]) + (row1[1] * other.row2[2]) + (row1[2] * other.row3[2]),	//first row
				 (row2[0] * other.row1[0]) + (row2[1] * other.row2[0]) + (row2[2] * other.row3[0]), (row2[0] * other.row1[1]) + (row2[1] * other.row2[1]) + (row2[2] * other.row3[1]), (row2[0] * other.row1[2]) + (row2[1] * other.row2[2]) + (row2[2] * other.row3[2]),		//second row
				 (row3[0] * other.row1[0]) + (row3[1] * other.row2[0]) + (row3[2] * other.row3[0]), (row3[0] * other.row1[1]) + (row3[1] * other.row2[1]) + (row3[2] * other.row3[1]), (row3[0] * other.row1[2]) + (row3[1] * other.row2[2]) + (row3[2] * other.row3[2]));	//third row
}

Mat3f Mat3f::operator* (float scale)
{
	return Mat3f(row1 * scale, row2 * scale, row3 * scale);
}

Vec3f Mat3f::operator*(const Vec3f &other)
{
	return Vec3f ((row1[0] * other.v[0]) + (row1[1] * other.v[1]) + (row1[2] * other.v[2]),	//x-axis
				  (row2[0] * other.v[0]) + (row2[1] * other.v[1]) + (row2[2] * other.v[2]),  //y-axis
				  (row3[0] * other.v[0]) + (row3[1] * other.v[1]) + (row3[2] * other.v[2]));	//z-axis

}

Mat3f Mat3f::transpose()
{
	return Mat3f(row1[0], row2[0], row3[0],
				 row1[1], row2[1], row3[1],
				 row1[2], row2[2], row3[2]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//identity matrix
//Mat4f::Mat4f()
//{
//	row1[0] = 1.0f;
//	row1[1] = 0.0f;
//	row1[2] = 0.0f;
//	row1[3] = 0.0f;
//	row2[0] = 0.0f;
//	row2[1] = 1.0f;
//	row2[2] = 0.0f;
//	row2[3] = 0.0f;
//	row3[0] = 0.0f;
//	row3[1] = 0.0f;
//	row3[2] = 1.0f;
//	row3[3] = 0.0f;
//	row4[0] = 0.0f;
//	row4[1] = 0.0f;
//	row4[2] = 0.0f;
//	row4[3] = 1.0f;
//
//	m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
//	m[4] = 0.0f; m[5] = 1.0f; m[6] = 0.0f; m[7] = 0.0f;
//	m[8] = 0.0f; m[9] = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
//	m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
//
//	a[0][0] = 1.0f; a[0][1] = 0.0f; a[0][2] = 0.0f; a[0][3]= 0.0f;
//	a[1][0] = 0.0f; a[1][1] = 1.0f; a[1][2] = 0.0f; a[1][3]= 0.0f;
//	a[2][0] = 0.0f; a[2][1] = 0.0f; a[2][2] = 1.0f; a[2][3]= 0.0f;
//	a[3][0] = 0.0f; a[3][1] = 0.0f; a[3][2] = 0.0f; a[3][3]= 1.0f;
//}

Mat4f::Mat4f()
{
	row1[0] = 0.0f;
	row1[1] = 0.0f;
	row1[2] = 0.0f;
	row1[3] = 0.0f;
	row2[0] = 0.0f;
	row2[1] = 0.0f;
	row2[2] = 0.0f;
	row2[3] = 0.0f;
	row3[0] = 0.0f;
	row3[1] = 0.0f;
	row3[2] = 0.0f;
	row3[3] = 0.0f;
	row4[0] = 0.0f;
	row4[1] = 0.0f;
	row4[2] = 0.0f;
	row4[3] = 0.0f;

	m[0] = 0.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
	m[4] = 0.0f; m[5] = 0.0f; m[6] = 0.0f; m[7] = 0.0f;
	m[8] = 0.0f; m[9] = 0.0f; m[10] = 0.0f; m[11] = 0.0f;
	m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 0.0f;

	a[0][0] = 0.0f; a[0][1] = 0.0f; a[0][2] = 0.0f; a[0][3]= 0.0f;
	a[1][0] = 0.0f; a[1][1] = 0.0f; a[1][2] = 0.0f; a[1][3]= 0.0f;
	a[2][0] = 0.0f; a[2][1] = 0.0f; a[2][2] = 0.0f; a[2][3]= 0.0f;
	a[3][0] = 0.0f; a[3][1] = 0.0f; a[3][2] = 0.0f; a[3][3]= 0.0f;
}

Mat4f::Mat4f(float matrix[16])
{
	row1[0] = matrix[0]; row1[1] = matrix[1]; row1[2] = matrix[2]; row1[3] = matrix[3];
	row2[0] = matrix[4]; row2[1] = matrix[5]; row2[2] = matrix[6]; row2[3] = matrix[7];
	row3[0] = matrix[8]; row3[1] = matrix[9]; row3[2] = matrix[10]; row3[3] = matrix[11];
	row4[0]	= matrix[12]; row4[1] = matrix[13]; row4[2] = matrix[14]; row4[3] = matrix[15];

	m[0] = matrix[0]; m[1] = matrix[1]; m[2] = matrix[2]; m[3] = matrix[3];
	m[4] = matrix[4]; m[5] = matrix[5]; m[6] = matrix[6]; m[7] = matrix[7];
	m[8] = matrix[8]; m[9] = matrix[9]; m[10] = matrix[10]; m[11] = matrix[11];
	m[12] = matrix[12]; m[13] = matrix[13]; m[14] = matrix[14]; m[15] = matrix[15];

	a[0][0] = matrix[0]; a[0][1] = matrix[1]; a[0][2] =  matrix[2]; a[0][3]= matrix[3];
	a[1][0] = matrix[4]; a[1][1] = matrix[5]; a[1][2] =  matrix[6]; a[1][3]= matrix[7];
	a[2][0] = matrix[8]; a[2][1] = matrix[9]; a[2][2] = matrix[10]; a[2][3]= matrix[11];
	a[3][0] = matrix[12]; a[3][1] = matrix[13]; a[3][2] = matrix[14]; a[3][3]= matrix[15];
}


Mat4f::Mat4f(float m00, float m01, float m02, float m03, 
			 float m10, float m11, float m12, float m13, 
			 float m20, float m21, float m22, float m23, 
			 float m30, float m31, float m32, float m33)
{
	row1[0] = m00; row1[1] = m01; row1[2] = m02; row1[3] = m03;
	row2[0] = m10; row2[1] = m11; row2[2] = m12; row2[3] = m13;
	row3[0] = m20; row3[1] = m21; row3[2] = m22; row3[3] = m23;
	row4[0]	= m30; row4[1] = m31; row4[2] = m32; row4[3] = m33;

	m[0] = m00; m[1] = m01; m[2] = m02;m[3] = m03;
	m[4] = m10; m[5] = m11; m[6] = m12;m[7] = m13;
	m[8] = m20; m[9] = m21; m[10] = m22; m[11] = m23;
	m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;

	a[0][0] = m00; a[0][1] = m01; a[0][2] = m02; a[0][3]= m03;
	a[1][0] = m10; a[1][1] = m11; a[1][2] = m12; a[1][3]= m13;
	a[2][0] = m20; a[2][1] = m21; a[2][2] = m22; a[2][3]= m23;
	a[3][0] = m30; a[3][1] = m31; a[3][2] = m32; a[3][3]= m33;
}


Mat4f::Mat4f(Vec4f Vrow1, Vec4f Vrow2, Vec4f Vrow3, Vec4f Vrow4)
{
	row1[0] = Vrow1[0];
	row1[1] = Vrow1[1];
	row1[2] = Vrow1[2];
	row1[3] = Vrow1[3];

	row2[0] = Vrow2[0];
	row2[1] = Vrow2[1];
	row2[2] = Vrow2[2];
	row2[3] = Vrow2[3];

	row3[0] = Vrow3[0];
	row3[1] = Vrow3[1];
	row3[2] = Vrow3[2];
	row3[3] = Vrow3[3];

	row4[0] = Vrow4[0];
	row4[1] = Vrow4[1];
	row4[2] = Vrow4[2];
	row4[3] = Vrow4[3];

	m[0] = row1[0]; m[1] = row1[1]; m[2] = row1[2]; m[3] = row1[3];
	m[4] = row2[0]; m[5] = row2[1]; m[6] = row2[2]; m[7] = row2[3];
	m[8] = row3[0]; m[9] = row3[1]; m[10] = row3[2]; m[11] = row3[3];
	m[12] = row4[0]; m[13] = row4[1]; m[14] = row4[2]; m[15] = row4[3];

	a[0][0] = row1[0]; a[0][1] = row1[1]; a[0][2] = row1[2]; a[0][3]= row1[3];
	a[1][0] = row2[0]; a[1][1] = row2[1]; a[1][2] = row2[2]; a[1][3]= row2[3];
	a[2][0] = row3[0]; a[2][1] = row3[1]; a[2][2] = row3[2]; a[2][3]= row3[3];
	a[3][0] = row4[0]; a[3][1] = row4[1]; a[3][2] = row4[2]; a[3][3]= row4[3];
}

Mat4f Mat4f::operator+ (const Mat4f &other)
{
	return Mat4f(row1[0] + other.row1[0], row1[1] + other.row1[1], row1[2] + other.row1[2], row1[3] + other.row1[3], row2[0] + other.row2[0], row2[1] + other.row2[1], row2[2] + other.row2[2], row2[3] + other.row2[3], row3[0] + other.row3[0], row3[1] + other.row3[1], row3[2] + other.row3[2], row3[3] + other.row3[3], row4[0] + other.row4[0], row4[1] + other.row4[1], row4[2] + other.row4[2], row4[3] + other.row4[3]);
}

Mat4f Mat4f::operator* (const Mat4f &other) const  
{
	Mat4f temp = Mat4f();
	for(int row = 0; row < 4; row++)
	{
		for(int col1 = 0; col1 < 4; col1++)
		{
			for(int col2 = 0; col2 < 4; col2++)
			{
				temp.a[row][col1] += a[row][col2] * other.a[col2][col1]; 
			}
		}
	}

	return Mat4f(temp.a[0][0], temp.a[0][1], temp.a[0][2], temp.a[0][3],
				 temp.a[1][0], temp.a[1][1], temp.a[1][2], temp.a[1][3],
				 temp.a[2][0], temp.a[2][1], temp.a[2][2], temp.a[2][3],
				 temp.a[3][0], temp.a[3][1], temp.a[3][2], temp.a[3][3]); 

}

Mat4f Mat4f::operator* (const Mat4f &other)
{
	Mat4f temp = Mat4f();
	for(int row = 0; row < 4; row++)
	{
		for(int col1 = 0; col1 < 4; col1++)
		{
			for(int col2 = 0; col2 < 4; col2++)
			{
				temp.a[row][col1] += a[row][col2] * other.a[col2][col1]; 
			}
		}
	}

	return Mat4f(temp.a[0][0], temp.a[0][1], temp.a[0][2], temp.a[0][3],
				 temp.a[1][0], temp.a[1][1], temp.a[1][2], temp.a[1][3],
				 temp.a[2][0], temp.a[2][1], temp.a[2][2], temp.a[2][3],
				 temp.a[3][0], temp.a[3][1], temp.a[3][2], temp.a[3][3]); 

	//return Mat4f((row1[0] * other.row1[0]) + (row1[1] * other.row2[0]) + (row1[2] * other.row3[0]) + (row1[3] * other.row4[0]), (row1[0] * other.row1[1]) + (row1[1] * other.row2[1]) + (row1[2] * other.row3[1]) + (row1[3] * other.row4[1]), (row1[0] * other.row1[2]) + (row1[1] * other.row2[2]) + (row1[2] * other.row3[2]) + (row1[3] * other.row4[2]), (row1[0] * other.row1[3]) + (row1[1] * other.row2[3]) + (row1[2] * other.row3[3]) + (row1[3] * other.row4[3]),	//first row
	//			 (row2[0] * other.row1[0]) + (row2[1] * other.row2[0]) + (row2[2] * other.row3[0]) + (row2[3] * other.row4[0]), (row2[0] * other.row1[1]) + (row2[1] * other.row2[1]) + (row2[2] * other.row3[1]) + (row2[3] * other.row4[1]), (row2[0] * other.row1[2]) + (row2[1] * other.row2[2]) + (row2[2] * other.row3[2]) + (row2[3] * other.row4[2]), (row2[0] * other.row1[3]) + (row2[1] * other.row2[3]) + (row2[2] * other.row3[3]) + (row2[3] * other.row4[3]),		//second row
	//			 (row3[0] * other.row1[0]) + (row3[1] * other.row2[0]) + (row3[2] * other.row3[0]) + (row3[3] * other.row4[0]), (row3[0] * other.row1[1]) + (row3[1] * other.row2[1]) + (row3[2] * other.row3[1]) + (row3[3] * other.row4[1]), (row3[0] * other.row1[2]) + (row3[1] * other.row2[2]) + (row3[2] * other.row3[2]) + (row3[3] * other.row4[2]), (row3[0] * other.row1[3]) + (row3[1] * other.row2[3]) + (row3[2] * other.row3[3]) + (row3[3] * other.row4[3]),		//third row
	//			 (row4[0] * other.row1[0]) + (row4[1] * other.row2[0]) + (row4[2] * other.row3[0]) + (row4[3] * other.row4[0]), (row4[0] * other.row1[1]) + (row4[1] * other.row2[1]) + (row4[2] * other.row3[1]) + (row4[3] * other.row4[1]), (row4[0] * other.row1[2]) + (row4[1] * other.row2[2]) + (row4[2] * other.row3[2]) + (row4[3] * other.row4[2]), (row4[0] * other.row1[3]) + (row4[1] * other.row2[3]) + (row4[2] * other.row3[3]) + (row4[3] * other.row4[3]));	//fourth row
}

Mat4f Mat4f::operator* (const float scale)
{
	return Mat4f(row1 * scale, row2 * scale, row3 * scale, row4 * scale);
}

Vec4f Mat4f::operator*(const Vec4f &other)
{
	return Vec4f ((row1[0] * other.v[0]) + (row1[1] * other.v[1]) + (row1[2] * other.v[2]) + (row1[3] * other.v[3]),	//x-axis
				  (row2[0] * other.v[0]) + (row2[1] * other.v[1]) + (row2[2] * other.v[2]) + (row2[3] * other.v[3]), //y-axis
				  (row3[0] * other.v[0]) + (row3[1] * other.v[1]) + (row3[2] * other.v[2]) + (row3[3] * other.v[3]),	//z-axis
				  (row4[0] * other.v[0]) + (row4[1] * other.v[1]) + (row4[2] * other.v[2]) + (row4[3] * other.v[3]));	//w-axis

}

Mat4f Mat4f::transpose()
{
	return Mat4f(row1[0], row2[0], row3[0], row4[0],
				 row1[1], row2[1], row3[1], row4[1],
				 row1[2], row2[2], row3[2], row4[2],
				 row1[3], row2[3], row3[3], row4[3]); 
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Quaternions

Quat::Quat()
{
	w = 0.0f;
	XYZ = Vec3f(0.0f, 0.0f, 0.0f);
}

Quat::Quat(float _w, Vec3f &other)
{
	w = _w;
	XYZ = other;
}

Quat::Quat(float _w, float x, float y, float z)
{
	w = _w;
	XYZ = Vec3f(x, y, z);
}

/*Quat rotationQuat(float degrees, Vec3f &axis)
{
	float radians = degrees * (3.141592654 / 180.0f);
	return Quat(cosf(radians / 2), axis.normalize() * (sinf(radians / 2)));
}
*/
Quat Quat::conjugate()
{
	return Quat(w, XYZ * -1);
}

Quat Quat::operator*(Quat &other)
{
	return Quat((w * other.w) - XYZ.dot(other.XYZ), (other.XYZ * w) + (XYZ * other.w) + (XYZ.cross(other.XYZ)));
}

Quat Quat::operator*(float scale)
{
	return Quat(w * scale, XYZ[0] * scale, XYZ[1] * scale, XYZ[2] * scale);
}

Quat Quat::operator+(Quat &other)
{
	return Quat(w + other.w, XYZ[0] + other.XYZ[0], XYZ[1] + other.XYZ[1], XYZ[2] + other.XYZ[2]);
}

Vec3f Quat::toVector()
{
	return Vec3f(XYZ);
}

float Quat::operator[](int index) const
{
	if(index == 0)
	{
		return w;
	}

	else
	{
		return XYZ[index - 1];
	}

}

float &Quat::operator[](int index) 
{
	if(index == 0)
	{
		return w;
	}

	else
	{
		return XYZ[index - 1];
	}

}

float Quat::dot(Quat &other)
{
	return (w * other.w) + (XYZ[0] * other.XYZ[0]) + (XYZ[1] * other.XYZ[1]) + (XYZ[2] * other.XYZ[2]);
}

Quat Quat::normalize()
{
	float mag = sqrtf((w * w) + (XYZ[0] * XYZ[0]) + (XYZ[1] * XYZ[1]) + (XYZ[2] * XYZ[2]));
	return Quat(w * (1.0f/mag), XYZ[0] * (1.0f/mag), XYZ[1] * (1.0f/mag), XYZ[2] * (1.0f/mag));

}

ostream &operator<<(ostream &os, const Quat &q)
{
	cout << "< " << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3] << ">" << endl;
	return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

physics::physics()
{
}

physics::~physics()
{
}

//hooke's law
Vec3f physics::spring(float k, float length, Vec3f direction)
{
	return  direction * ((-1 * k) * (direction.magnitude()) - (length));
}

Vec3f physics::acceleration(Vec3f force, float mass)
{
	return force * (1.0f/mass);
}


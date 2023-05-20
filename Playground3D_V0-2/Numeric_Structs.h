#pragma once

#include "Playground3D_V0-2.h"

using namespace std;

struct Vector2DM {
	double x = 0, y = 0;

	Vector2DM() { }

	Vector2DM(double x_, double y_) {
		x = x_;
		y = y_;
	}

	// substitute for constructor but it takes magnitude and angle(radians) as params
	inline static Vector2DM ConstrVA(double val, double ang) {
		return Vector2DM(val * cos(ang), val * sin(ang));
	}

	inline static Vector2DM* ConstrVA_New(double val, double ang) {
		return new Vector2DM(val * cos(ang), val * sin(ang));
	}

	// try avoiding spamming it, expansive sqrt() inside
	inline double Magnitude() {
		return sqrt(x * x + y * y);
	}

	// in case you needed to square the mag. for example in grav. force formula Fg = GMm/[r^2]
	inline double MagnitudeSqr() {
		return x * x + y * y;
	}

	inline void ComplexMult(const Vector2DM& boi) {
		this->x = this->x * boi.x - this->y * boi.y;
		this->y = this->x * boi.y + this->y * boi.x;
	}

	// ret ref for less copying
	inline static Vector2DM& ComplexMultS(Vector2DM first, const Vector2DM& second) {
		first.ComplexMult(second);
		return first;
	}
	
	void Normalize() {
		double meh = this->Magnitude();
		this->x /= meh;
		this->y /= meh;
	}
	
};


#pragma region Vector2DM Operators

Vector2DM operator -(Vector2DM one) {
	one.x = -one.x;
	one.y = -one.y;
	return one;
}

Vector2DM operator +(Vector2DM one, Vector2DM& two) {
	one.x += two.x;
	one.y += two.y;
	return one;
}

Vector2DM operator -(Vector2DM one, Vector2DM& two) {
	one.x -= two.x;
	one.y -= two.y;
	return one;
}

Vector2DM operator *(Vector2DM one, double two) {
	one.x *= two;
	one.y *= two;
	return one;
}

Vector2DM operator /(Vector2DM one, double two) {
	one.x /= two;
	one.y /= two;
	return one;
}

#pragma endregion

struct Vector3DM {
	double x = 0, y = 0, z = 0;

	Vector3DM() { }

	Vector3DM(double x_, double y_, double z_) {
		x = x_;
		y = y_;
		z = z_;
	}

	Vector3DM(Vector2DM& two) {
		x = two.x;
		y = two.y;
		z = 0;
	}

	// try avoiding spamming it, expansive sqrt() inside
	inline double Magnitude() {
		return sqrt(x * x + y * y + z * z);
	}

	// in case you needed to square the mag. for example in grav. force formula Fg = GMm/[r^2]
	inline double MagnitudeSqr() {
		return x * x + y * y + z * z;
	}
	
	inline double Dot(const Vector3DM& two) {
		return this->x * two.x + this->y * two.y + this->z * two.z;
	}

	inline static double DotS(Vector3DM one, const Vector3DM& two) {
		return one.Dot(two);
	}

	inline void Cross(const Vector3DM& two) {
		this->x = this->y * two.z - this->z * two.y;
		this->y = this->z * two.x - this->x * two.z;
		this->z = this->x * two.y - this->y * two.x;
	}

	inline static Vector3DM CrossS(Vector3DM one, const Vector3DM& two) {
		one.Cross(two);
		return one;
	}
	
	void Normalize() {
	double meh = this->Magnitude();
		this->x /= meh;
		this->y /= meh;
		this->z /= meh;
	}
};

#pragma region Vector3DM Operators

Vector3DM operator -(Vector3DM one) {
	one.x = -one.x;
	one.y = -one.y;
	one.z = -one.z;
	return one;
}

Vector3DM operator +(Vector3DM one, Vector3DM& two) {
	one.x += two.x;
	one.y += two.y;
	one.z += two.z;
	return one;
}

Vector3DM operator -(Vector3DM one, Vector3DM& two) {
	one.x -= two.x;
	one.y -= two.y;
	one.z -= two.z;
	return one;
}

Vector3DM operator *(Vector3DM one, double two) {
	one.x *= two;
	one.y *= two;
	one.z *= two;
	return one;
}

Vector3DM operator /(Vector3DM one, double two) {
	one.x /= two;
	one.y /= two;
	one.z /= two;
	return one;
}

#pragma endregion

struct QuaternionM {
	double r = 0;
	Vector3DM vectorPart;

	QuaternionM() {}

	QuaternionM(double r_, double a, double b, double c) {
		r = r_;
		vectorPart = Vector3DM(a, b, c);
	}

	QuaternionM(double r_, const Vector3DM& two) {
		r = r_;
		vectorPart = two;
	}

	inline static QuaternionM& AngleAxis_Quat(double angle, const Vector3DM& axis) {
		QuaternionM quat = QuaternionM(cos(angle), axis);
		quat.vectorPart.Normalize();
		quat.vectorPart = quat.vectorPart * sin(angle);
		return quat;
	}
};

#pragma once
#include <math.h>

class Vector2_ {
private:
public:
	float x;
	float y;

	Vector2() {
		this->x = 0;
		this->y = 0;
	}

	Vector2(float _x, float _y) {
		x = _x;
		y = _y;
	}

	explicit Vector2(const Vector2& b) : x(b.x), y(b.y){

	}

	~Vector2() {}

	float Lenght() {
		return sqrt(x*x + y*y);
	}

	float LenghtSquared() {
		return (x * x + y * y);
	}

	static float DotProduct(const Vector2& a, const Vector2& b) {
		return a.x * b.x + a.y + b.y;
	}

	Vector2 CrossProduct(Vector2 a, Vector2 b) {
		//Implementar?
	}

	Vector2& Normalized() {
		float l = Lenght();
		Vector2 normal(0,0);
		if (l != 0) {
			normal.x = this->x / l;
			normal.y = this->y / l;
		}
		return normal;
	}

	Vector2& operator =(const Vector2& b) {
		if (this != &b) {
			this->x = b.x;
			this->y = b.y;
		}
		return (*this);
	}

	Vector2& operator + (const Vector2& b) {
		Vector2 tmp(*this);
		tmp += b;
		return tmp;
	}

	Vector2& operator += (const Vector2& b) {
		this->x = this->x + b.x;
		this->y = this->y + b.y;
		return (*this);
	}

	Vector2& operator - (const Vector2 b) {
		
		this->x = this->x - b.x;
		this->y = this->y - b.y;
		return (*this);
	}

	Vector2& operator -= (const Vector2 b) {
		this->x = this->x - b.x;
		this->y = this->y - b.y;
		return (*this);
	}

	Vector2& operator * (const Vector2 b) {
		Vector2 v;
		v.x = this->x * b.x;
		v.y = this->y * b.y;
		return v;
	}

	Vector2& operator * (int j) {
		this->x = this->x * j;
		this->y = this->y * j;
	}

	Vector2& operator * (float j) {
		this->x = this->x * j;
		this->y = this->y * j;
	}
};

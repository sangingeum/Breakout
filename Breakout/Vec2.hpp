#pragma once
class Vec2 {
public:
    float x = 0;
    float y = 0;
    Vec2();
    Vec2(float xin, float yin);
    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(const Vec2& rhs) const;
    Vec2 operator*(float rhs) const;
    Vec2 operator/(const Vec2& rhs) const;
    Vec2 operator/(float rhs) const;
    Vec2& operator+=(const Vec2& rhs);
    Vec2& operator-=(const Vec2& rhs);
    Vec2& operator-=(float rhs);
    Vec2& add(const Vec2& rhs);
    Vec2& scale(float s);
    Vec2& rotate(float degree);
    Vec2& normalize();
    Vec2& resize(float length);
    Vec2& decreaseUntilZero(float diff);
    float dist(const Vec2& v) const;
    Vec2 delta(const Vec2& v) const;
    float length() const;
    void set(float xin, float yin);
    void negate();

};
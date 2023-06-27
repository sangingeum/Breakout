#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2() {}
Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {}

Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(this->x + rhs.x, this->y + rhs.y);
}
Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(this->x - rhs.x, this->y - rhs.y);
}
Vec2 Vec2::operator*(const Vec2& rhs) const {
    return Vec2(this->x * rhs.x, this->y * rhs.y);
}
Vec2 Vec2::operator*(float rhs) const {
    return Vec2(this->x * rhs, this->y * rhs);
}
Vec2 Vec2::operator/(const Vec2& rhs) const {
    return Vec2(this->x / rhs.x, this->y / rhs.y);
}
Vec2 Vec2::operator/(float rhs) const {
    return Vec2(this->x / rhs, this->y / rhs);
}
Vec2& Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}
Vec2& Vec2::operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}
Vec2& Vec2::operator-=(float rhs) {
    x -= rhs;
    y -= rhs;
    return *this;
}
Vec2& Vec2::add(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}
Vec2& Vec2::scale(float s) {
    x *= s;
    y *= s;
    return *this;
}
Vec2& Vec2::rotate(float degree) {
    // TODO
    return *this;
}
Vec2& Vec2::normalize(){
    float len = length();
    x /= len;
    y /= len;
    return *this;
}
Vec2& Vec2::resize(float length) {
    normalize();
    scale(length);
    return *this;
}

Vec2& Vec2::decreaseUntilZero(float diff) {
    x -= (std::signbit(x) ? -1.0f : 1.0f) * std::max(abs(x) - diff, 0.f);
    y -= (std::signbit(y) ? -1.0f : 1.0f) * std::max(abs(y) - diff, 0.f);
    return *this;
}

float Vec2::dist(const Vec2& v) const {
    return sqrtf(powf(x - v.x, 2) + powf(y - v.y, 2));
}
Vec2 Vec2::delta(const Vec2& v) const {
    return Vec2({abs(this->x - v.x), abs(this->y - v.y)});
}

float Vec2::length() const {
    return sqrtf(powf(x, 2) + powf(y, 2));
}
void Vec2::set(float xin, float yin) {
    x = xin;
    y = yin;
}

void Vec2::negate() {
    x = -x;
    y = -y;
}
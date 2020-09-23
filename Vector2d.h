#pragma once
#include <iostream>

template<typename T> struct Vector2d
{
    Vector2d() = default;

    Vector2d(T first, T second) : x{first}, y{second}
    {

    }

    T operator + (const Vector2d<T>& substract)
    {
        return Vector2d<T>{x + substract.x, y + substract.y};
    }

    T operator - (const Vector2d<T>& substract)
    {
        return Vector2d<T>{x + substract.x, y + substract.y};
    }

    T& operator += (const Vector2d<T>& substract)
    {
        x += substract.x;
        y += substract.y;
        return *this;
    }

    T& operator -= (const Vector2d<T>& substract)
    {
        x -= substract.x;
        y -= substract.y;
        return *this;
    }

    T& operator - ()
    {
        x = -x;
        y = -y;
        return *this;
    }

    T x;
    T y;
};

template<typename T> std::ostream& operator << (std::ostream& out, const Vector2d<T>& vect)
{
    return out<<vect.x<<" "<<vect.y<<" ";
}
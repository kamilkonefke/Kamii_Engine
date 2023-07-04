#ifndef Vector2D_hpp
#define Vector2D_hpp

#include <iostream>
#include <stdio.h>

class Vector2D
{
    public:
        float x;
        float y;

        Vector2D()
        {
            x = 0.0f;
            y = 0.0f;
        }

        Vector2D(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        // Add, Subtract, Multiply, Divide
        Vector2D& Add(const Vector2D& vector)
        {
            this->x += vector.x;
            this->y += vector.y;

            return *this;
        }

        Vector2D& Subtract(const Vector2D& vector)
        {
            this->x -= vector.x;
            this->y -= vector.y;

            return *this;
        }

        Vector2D& Multiply(const Vector2D& vector)
        {
            this->x *= vector.x;
            this->y *= vector.y;

            return *this;
        }

        Vector2D& Divide(const Vector2D& vector)
        {
            this->x /= vector.x;
            this->y /= vector.y;

            return *this;
        }

        // Operators +, -, *, /
        friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
        {
            return v1.Add(v2);
        }

        friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
        {
            return v1.Subtract(v2);
        }

        friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
        {
            return v1.Multiply(v2);
        }

        friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
        {
            return v1.Divide(v2);
        }

        // Operators +=, -=, *=, /=
        Vector2D& operator+=(Vector2D& vector)
        {
            return this->Add(vector);
        }

        Vector2D& operator-=(Vector2D& vector)
        {
            return this->Subtract(vector);
        }

        Vector2D& operator*=(Vector2D& vector)
        {
            return this->Multiply(vector);
        }

        Vector2D& operator/=(Vector2D& vector)
        {
            return this->Divide(vector);
        }
};

#endif
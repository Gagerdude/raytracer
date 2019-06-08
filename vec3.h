#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <random>

class vec3{
    public:
        // constructors
        vec3();
        vec3(double v1);
        vec3(double v1, double v2, double v3);

        // copy constructor / assignment
        vec3(const vec3& vec);
        vec3& operator=(const vec3& vec);

        // operator overloads
        vec3 operator-() const;

        double operator[](int index) const;
        double& operator[](int index);

        vec3 operator+(const vec3& rhs) const;
        vec3 operator-(const vec3& rhs) const;
        vec3 operator*(const vec3& rhs) const;
        vec3 operator/(const vec3& rhs) const;
        
        vec3 operator*(double rhs) const;
        vec3 operator/(double rhs) const;

        vec3& operator+=(const vec3& rhs);
        vec3& operator-=(const vec3& rhs);
        vec3& operator*=(const vec3& rhs);
        vec3& operator/=(const vec3& rhs);

        vec3& operator*=(double rhs);
        vec3& operator/=(double rhs);

        // member accessors
        double x() const;
        double y() const;
        double z() const;
        double r() const;
        double g() const;
        double b() const;

        // utility methods
        double length() const;
        double length_squared() const;

        vec3& normalize();
        vec3 normalized() const;

        static vec3 random();

    private:
        double m_array[3];

        static std::mt19937 rng;
};

vec3 operator*(double lhs, const vec3& rhs);

std::ostream& operator<<(std::ostream& strm, const vec3& rhs);

double dot(const vec3& lhs, const vec3& rhs);
vec3 cross(const vec3& lhs, const vec3& rhs);
vec3 reflect(const vec3& vec, const vec3& normal);
bool refract(const vec3& vec, const vec3& normal, double refractive_index, vec3& refracted);

#endif
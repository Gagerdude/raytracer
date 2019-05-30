#ifndef VEC3_H
#define VEC3_H

class vec3{
    public:
        // constructors
        vec3();
        vec3(float v1, float v2, float v3);

        // copy constructor / assignment
        vec3(const vec3& vec);
        vec3& operator=(const vec3& vec);

        // operator overloads
        vec3 operator-();

        float operator[](int index) const;
        float& operator[](int index);

        vec3 operator+(const vec3& rhs) const;
        vec3 operator-(const vec3& rhs) const;
        vec3 operator*(const vec3& rhs) const;
        vec3 operator/(const vec3& rhs) const;
        
        vec3 operator*(float rhs) const;
        vec3 operator/(float rhs) const;

        vec3& operator+=(const vec3& rhs);
        vec3& operator-=(const vec3& rhs);
        vec3& operator*=(const vec3& rhs);
        vec3& operator/=(const vec3& rhs);

        vec3& operator*=(float rhs);
        vec3& operator/=(float rhs);

        // member accessors
        float x() const;
        float y() const;
        float z() const;
        float r() const;
        float g() const;
        float b() const;

        // utility methods
        float length() const;
        float length_squared() const;

        vec3& normalize();

    private:
        float m_array[3];
};

vec3 operator*(float lhs, const vec3& rhs);

#endif
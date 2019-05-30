#include "vec3.h"

#include <stdexcept>

vec3::vec3(){
	this->m_array[0] = 0;
	this->m_array[1] = 0;
	this->m_array[2] = 0;
}

vec3::vec3(float v1, float v2, float v3){
	this->m_array[0] = v1;
	this->m_array[1] = v2;
	this->m_array[2] = v3;
}

vec3::vec3(const vec3& vec){
	this->m_array[0] = vec.m_array[0];
	this->m_array[1] = vec.m_array[1];
	this->m_array[2] = vec.m_array[2];
}

vec3& vec3::operator=(const vec3& vec){
	this->m_array[0] = vec.m_array[0];
	this->m_array[1] = vec.m_array[1];
	this->m_array[2] = vec.m_array[2];
}

vec3 vec3::operator-(){
	vec3 negatedVector(
        -1 * this->m_array[0],
        -1 * this->m_array[1],
        -1 * this->m_array[2]
    );

    return negatedVector;
}

float vec3::operator[](int index) const{
	if(index < 0 || 3 <= index){
        throw std::out_of_range("Index");
    }

    return this->m_array[index];
}

float& vec3::operator[](int index){
	if(index < 0 || 3 <= index){
        throw std::out_of_range("Index");
    }

    return this->m_array[index];
}

vec3 vec3::operator+(const vec3& rhs) const{
    vec3 sum(
        this->m_array[0] + rhs.m_array[0],
        this->m_array[1] + rhs.m_array[1],
        this->m_array[2] + rhs.m_array[2]
    );

    return sum;
}

vec3 vec3::operator-(const vec3& rhs) const{
    vec3 diff(
        this->m_array[0] - rhs.m_array[0],
        this->m_array[1] - rhs.m_array[1],
        this->m_array[2] - rhs.m_array[2]
    );

    return diff;
}

vec3 vec3::operator*(const vec3& rhs) const{
    vec3 product(
        this->m_array[0] * rhs.m_array[0],
        this->m_array[1] * rhs.m_array[1],
        this->m_array[2] * rhs.m_array[2]
    );

    return product;
}

vec3 vec3::operator/(const vec3& rhs) const{
    vec3 quotient(
        this->m_array[0] * rhs.m_array[0],
        this->m_array[1] * rhs.m_array[1],
        this->m_array[2] * rhs.m_array[2]
    );

    return quotient;
}

vec3 vec3::operator*(float rhs) const{
    vec3 product(
        this->m_array[0] * rhs,
        this->m_array[1] * rhs,
        this->m_array[2] * rhs
    );

    return product;
}

vec3 operator*(float lhs, const vec3& rhs){
    vec3 product = rhs * lhs;

    return product;
}

vec3 vec3::operator/(float rhs) const{
    vec3 quotient(
        this->m_array[0] * rhs,
        this->m_array[1] * rhs,
        this->m_array[2] * rhs
    );

    return quotient;
}

vec3& vec3::operator+=(const vec3& rhs){
	
}

vec3& vec3::operator-=(const vec3& rhs){
	
}

vec3& vec3::operator*=(const vec3& rhs){
	
}

vec3& vec3::operator/=(const vec3& rhs){
	
}

vec3& vec3::operator*=(float rhs){
	
}

vec3& vec3::operator/=(float rhs){
	
}

float vec3::x() const{
	
}

float vec3::y() const{
	
}

float vec3::z() const{
	
}

float vec3::r() const{
	
}

float vec3::g() const{
	
}

float vec3::b() const{
	
}

float vec3::length() const{
	
}

float vec3::length_squared() const{
	
}

vec3& vec3::normalize(){
	
}

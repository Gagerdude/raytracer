#include <stdexcept>

template <typename T>
ImageWrapper<T>::ImageWrapper(int x_size, int y_size, int z_size){
    this->m_x = x_size;
    this->m_y = y_size;
    this->m_z = z_size;

    long size = x_size * y_size * z_size;

    this->m_array = new T[size];

    for(long i = 0; i < size; i++){
        this->m_array[i] = 0;
    }
}

template <typename T>
ImageWrapper<T>::~ImageWrapper(){
    if(this->m_array){
        delete[] this->m_array;
    }
}

template <typename T>
ImageWrapper<T>::ImageWrapper(const ImageWrapper<T>& array){
    this->m_x = array.m_x;
    this->m_y = array.m_y;
    this->m_z = array.m_z;

    long size = this->m_x * this->m_y * this->m_z;

    this->m_array = new T[size];

    for(long i = 0; i < size; i++){
        this->m_array[i] = array.m_array[i];
    }
}

template <typename T>
ImageWrapper<T>& ImageWrapper<T>::operator=(const ImageWrapper<T>& rhs){
    this->m_x = rhs.m_x;
    this->m_y = rhs.m_y;
    this->m_z = rhs.m_z;

    long size = this->m_x * this->m_y * this->m_z;

    delete[] this->m_array;

    this->m_array = new T[size];

    for(long i = 0; i < size; i++){
        this->m_array[i] = rhs.m_array[i];
    }

    return *this;
}

template <typename T>
const T& ImageWrapper<T>::get(int x, int y, int z) const{
    if(x < 0 || m_x <= x){
        throw std::out_of_range("X");
    } else if(y < 0 || m_y <= y){
        throw std::out_of_range("Y");
    } else if(z < 0 || m_z <= z){
        throw std::out_of_range("Z");
    } else {
        return this->m_array[x * this->m_y * this->m_z + y * this->m_z + z];
    }
}

template <typename T>
T& ImageWrapper<T>::get(int x, int y, int z){
    if(x < 0 || m_x <= x){
        throw std::out_of_range("X");
    } else if(y < 0 || m_y <= y){
        throw std::out_of_range("Y");
    } else if(z < 0 || m_z <= z){
        throw std::out_of_range("Z");
    } else {
        return this->m_array[x * this->m_y * this->m_z + y * this->m_z + z];
    }
}

template <typename T>
void ImageWrapper<T>::set(const T& value, int x, int y, int z){
    if(x < 0 || m_x <= x){
        throw std::out_of_range("X");
    } else if(y < 0 || m_y <= y){
        throw std::out_of_range("Y");
    } else if(z < 0 || m_z <= z){
        throw std::out_of_range("Z");
    } else {
        this->m_array[x * this->m_y * this->m_z + y * this->m_z + z] = value;
    }
}
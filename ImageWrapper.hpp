template <typename T>
ImageWrapper<T>::ImageWrapper(int x_size, int y_size=0, int z_size=0){
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
ImageWrapper<T>::ImageWrapper(const ImageWrapper& array){
    this->m_x = array.m_x;
    this->m_y = array.m_y;
    this->m_z = array.m_z;

    long size = x_size * y_size * z_size;

    this->m_array = new T[size];

    for(long i = 0; i < size; i++){
        this->m_array[i] = array.m_array[i];
    }
}

template <typename T>
ImageWrapper& ImageWrapper<T>::operator=(const ImageWrapper& rhs){
    this->m_x = rhs.m_x;
    this->m_y = rhs.m_y;
    this->m_z = rhs.m_z;

    long size = x_size * y_size * z_size;

    delete[] this->m_array;

    this->m_array = new T[size];

    for(long i = 0; i < size; i++){
        this->m_array[i] = rhs.m_array[i];
    }
}

template <typename T>
const T& ImageWrapper<T>::get(int x, int y, int z) const{
    if(0 <= x && 0 <= y && 0 <= z && x < this->m_x && y < this->m_y && z < this->m_z){
        return this->m_array[x * this->m_y * this->m_z + y * this->m_z + z];
    }
}

template <typename T>
T& ImageWrapper<T>::get(int x, int y, int z){
    if(0 <= x && 0 <= y && 0 <= z && x < this->m_x && y < this->m_y && z < this->m_z){
        return this->m_array[x * this->m_y * this->m_z + y * this->m_z + z];
    }
}

template <typename T>
void ImageWrapper<T>::set(int x, int y, int z, const T& value){
    if(0 <= x && 0 <= y && 0 <= z && x < this->m_x && y < this->m_y && z < this->m_z){
        this->m_array[x * this->m_y * this->m_z + y * this->m_z + z] = value;
    }
}
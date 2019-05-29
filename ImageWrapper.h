#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

template <typename T>
class ImageWrapper{
    public:
        // constructor/destructor, need at least one dimension of size
        ImageWrapper(int x_size, int y_size=0, int z_size=0);
        ~ImageWrapper();

        // copy constructor and assignment overload
        ImageWrapper(const ImageWrapper& array);
        ImageWrapper& operator=(const ImageWrapper& rhs);

        // getter and setter for array elements
        const T& get(int x, int y=0, int z=0) const;
        T& get(int x, int y=0, int z=0);

        void set(const T& value, int x, int y=0, int z=0);

        // size accessors
        int x() const { return m_x; };
        int y() const { return m_y; };
        int z() const { return m_z; };

        // array access
        T* data() { return m_array; };
    private:
        // internal 1D array used to store 3D array
        T* m_array;

        // internal sizes of the logical 3D array
        int m_x, m_y, m_z;

        long index(int x, int y, int z);
};

#include "ImageWrapper.hpp"

#endif
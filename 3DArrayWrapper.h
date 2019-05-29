#ifndef _3DARRAYWRAPPER_H
#define _3DARRAYWRAPPER_H

template <typename T>
class 3DArrayWrapper{
    public:
        // constructor/destructor, need at least one dimension of size
        3DArrayWrapper(int x_size, int y_size=0, int z_size=0);
        ~3DArrayWrapper();

        // copy constructor and assignment overload
        3DArrayWrapper(const 3DArrayWrapper& array);
        3DArrayWrapper& operator=(const 3DArrayWrapper& rhs);

        // getter and setter for array elements
        const T& get(int x, int y=0, int z=0) const;
        T& get(int x, int y=0, int z=0);

        void set(int x, int y=0, int z=0);
    private:
        // internal 1D array used to store 3D array
        T* m_array;

        // internal sizes of the logical 3D array
        int m_x, m_y, m_z;
};

#endif
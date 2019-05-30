#ifndef PNGWRITER_H
#define PNGWRITER_H

#include <png.h>

#include <string>
#include "ImageWrapper.h"

class PNGWriter {
    public:
        PNGWriter(std::string fileName);
        ~PNGWriter();

        void write(ImageWrapper<unsigned char> image);
        void write(ImageWrapper<float> image);

    private:
        png_image m_image;

        std::string m_file;
};

#endif
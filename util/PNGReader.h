#ifndef PNGREADER_H
#define PNGREADER_H

#include <png.h>

#include <string>
#include <fstream>
#include "ImageWrapper.h"

class PNGReader {
    public:
        PNGReader(std::string fileName);
        ~PNGReader();
        
        ImageWrapper<unsigned char> image;

    private:
        png_image m_image;

        std::string m_file;

        bool validate(std::ifstream& stream);
};

#endif
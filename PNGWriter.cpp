#include "PNGWriter.h"
#include <cstring>

PNGWriter::PNGWriter(std::string fileName){
    this->m_file = fileName;

    memset(&this->m_image, 0, sizeof(this->m_image));
    this->m_image.version = PNG_IMAGE_VERSION;
    this->m_image.flags = 0;
    this->m_image.colormap_entries = 0;
}

PNGWriter::~PNGWriter(){
    png_image_free(&this->m_image);
}

void PNGWriter::write(ImageWrapper<unsigned char> image){
    // setup image dimensions
    this->m_image.width = image.x();
    this->m_image.height = image.y();
    if(image.z() == 3){
        this->m_image.format = PNG_FORMAT_RGB;
    } else if (image.z() == 4){
        this->m_image.format = PNG_FORMAT_RGBA;
    }

    png_image_write_to_file(
        &this->m_image, this->m_file.c_str(), false, (void*)image.data(),
        -1 * image.y() * image.z(), nullptr
    );
}
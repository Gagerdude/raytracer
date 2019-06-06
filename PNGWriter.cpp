#include "PNGWriter.h"

#include <cstring>
#include <cmath>

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
        -1 * image.x() * image.z(), nullptr
    );
}

void PNGWriter::write(ImageWrapper<double> image){
    // setup image dimensions
    this->m_image.width = image.x();
    this->m_image.height = image.y();
    
    if(image.z() == 3){
        this->m_image.format = PNG_FORMAT_RGB;
    } else if (image.z() == 4){
        this->m_image.format = PNG_FORMAT_RGBA;
    }

    // take the doubles, and scale them to 8 bit values
    ImageWrapper<unsigned char> scaled_image(image.x(), image.y(), image.z());

    for(int i = 0; i < image.x(); i++){
        for(int j = 0; j < image.y(); j++){
            for(int k = 0; k < image.z(); k++){
                // clamp the value to be between 0 and 255
                if(image.get(i, j, k) >= 1){
                    scaled_image.set(255, i, j, k);
                } else if(image.get(i, j, k) <= 0){
                    scaled_image.set(0, i, j, k);
                } else {
                    scaled_image.set(std::sqrt(image.get(i, j, k)) * 255, i, j, k);
                }
            }
        }
    }

    // write to the png file
    png_image_write_to_file(
        &this->m_image, this->m_file.c_str(), false, (void*)scaled_image.data(),
        -1 * scaled_image.x() * scaled_image.z(), nullptr
    );
}
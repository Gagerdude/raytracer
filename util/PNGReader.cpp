#include "PNGReader.h"

#include <iostream>

void read_from_stream(png_structp pngPtr, png_bytep data, png_size_t length){
    png_voidp stream = png_get_io_ptr(pngPtr);

    ((std::istream*)stream)->read((char*)data, length);
}

PNGReader::PNGReader(std::string fileName){
    std::ifstream inFile(fileName);

    if(!inFile.is_open()){
        std::cerr << "Couldn't Open " << fileName << std::endl;

        return;
    }

    if(!validate(inFile)){
        std::cerr << "File " << fileName << " is not of .png format" << std::endl;

        return;
    }

    png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if(pngPtr == nullptr){
        std::cerr << "Couldn't initialize PNG read struct for " << fileName << std::endl;

        return;
    }

    png_infop infoPtr = png_create_info_struct(pngPtr);

    if(infoPtr == nullptr){
        std::cerr << "Couldn't initialize PNG info struct for " << fileName << std::endl;
    
        png_destroy_read_struct(&pngPtr, (png_infopp)0,  (png_infopp)0);

        return;
    }

    png_set_read_fn(pngPtr, (png_voidp)&inFile, read_from_stream);

    png_set_sig_bytes(pngPtr, 8);

    png_read_info(pngPtr, infoPtr);

    png_uint_32 imgWidth = png_get_image_width(pngPtr, infoPtr);
    png_uint_32 imgHeight = png_get_image_height(pngPtr, infoPtr);
    png_uint_32 bitdepth = png_get_bit_depth(pngPtr, infoPtr);
    png_uint_32 channels = png_get_channels(pngPtr, infoPtr);
    png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);

    image = ImageWrapper<unsigned char>(imgWidth, imgHeight, channels);

    png_bytepp rowPtrs = new png_bytep[imgHeight];

    unsigned char* data = image.data();

    const unsigned int stride = imgWidth * bitdepth * channels / 8;

    for(unsigned int i = 0; i < imgHeight; i++){
        png_uint_32 rowStart = (imgHeight- i - 1) * stride;
        rowPtrs[imgHeight - 1 - i] = (png_bytep)data + rowStart;
    }

    png_read_image(pngPtr, rowPtrs);

    png_read_end(pngPtr, infoPtr);
    delete[] (png_bytep)rowPtrs;
    png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
}

PNGReader::~PNGReader(){

}

bool PNGReader::validate(std::ifstream& inFile){
    const int png_sig_size = 8;

    png_byte png_signature[png_sig_size];

    inFile.read((char*)png_signature, png_sig_size);

    if(!inFile.good()){
        return false;
    } else {
        return png_sig_cmp(png_signature, 0, png_sig_size) == 0;
    }
}
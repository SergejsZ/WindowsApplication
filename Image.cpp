#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"



bool Image::load(string filename)
{
    ifstream ifs(filename, std:: ios::binary);
    string magicNumber;
    ifs >> magicNumber;

    ifs >> this->w;
    ifs >> this->h;
    int p;
    ifs >> p;
ifs.ignore(256,'\n');
    if (p==255)
    {
        delete[]pixels;
        pixels = new Rgb[w*h];
        unsigned char pix[3];
        for (int i = 0; i < w*h; i++)
        {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            pixels[i].r = pix[0];
            pixels[i].g = pix[1];
            pixels[i].b = pix[2];

        }
        return true;
    }
    return false;

}
bool Image::loadRaw(string filename)
{
    return false;
}
bool Image::savePPM(string filename)
{
    if (w == 0 || h == 0) { fprintf(stderr, "Can't save an empty image\n"); return false; }
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << w << " " << h << "\n255\n";
        unsigned char pix[3];
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < w * h; ++i) {
            pix[1] = static_cast <unsigned char> (this->pixels[i].r);
            pix[2] = static_cast <unsigned char> (this->pixels[i].g);
            pix[3] = static_cast <unsigned char> (this->pixels[i].b);
           ofs.write(reinterpret_cast<char*>(pix),3);
        }
        ofs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();

    }
    return true;
}

void Image::filterRed()
{
    for(int i = 0; i < w*h; i++)
    {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterGreen()
{
    for(int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }

}
void Image::filterBlue()
{
    for(int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
    }

}

void Image::greyScale()
{
    //https://cboard.cprogramming.com/c-programming/152994-ppm-image-manipulations.html
    int i, average = 0;
    for (i = 0; i < w*h; i++)
    {

        average = (pixels[i].r + pixels[i].g + pixels[i].b) / 3;
        this->pixels[i] = average;
        this->pixels[i] = average;
        this->pixels[i] = average;
    }

}
void Image::flipHorizontal() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w / 2; j++) {
            swap(pixels[j + i * w], pixels[i * w + (w - j)]);
        }
    }
}
void Image::flipVertically() {
    for (int i = 0; i < h / 2; i++) {
        for (int j = 0; j < w; j++) {
            swap(pixels[j + i * w], pixels[j + (h - 1 - i) * w]);
        }
    }
}
void Image::AdditionalFunction2()
{

}
void Image::AdditionalFunction3()
{

}
void Image::AdditionalFunction1()
{

}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}
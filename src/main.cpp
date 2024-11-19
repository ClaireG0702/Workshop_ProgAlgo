#include <sil/sil.hpp>
#include <iostream>
#include "random.hpp"

// TODO : refaire les filtres du début (keepOnlyGreen -> rotation)

sil::Image splitRGB(sil::Image &image)
{
    sil::Image editedImage{image};

    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            if(x < 30) {
                editedImage.pixel(x, y).b = image.pixel(x + 30, y).b;
            } else if (x > image.width() - 31) {
                editedImage.pixel(x, y).r = image.pixel(x - 30, y).r;
            } else {
                editedImage.pixel(x, y).r = image.pixel(x - 30, y).r;
                editedImage.pixel(x, y).b = image.pixel(x + 30, y).b;
            }
        }
    }

    return editedImage;
}

int main()
{
    {
        sil::Image image{"images/logo.png"};
        sil::Image editedImage{splitRGB(image)};
        editedImage.save("output/splitRGB.png");
    }
}
#include <sil/sil.hpp>
#include <iostream>
#include "random.hpp"
#include <vector>

void keepOnlyGreen(sil::Image &image) {
    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;
        }
    }
}

void swapChannels(sil::Image &image) {
    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            std::swap(image.pixel(x, y).r, image.pixel(x, y).b);
        }
    }
}

void blackAndWhite(sil::Image &image) {
    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            float gray = 0.2126 * image.pixel(x, y).r + 0.7152 * image.pixel(x, y).g + 0.0722 * image.pixel(x, y).b;
        
            image.pixel(x, y) = glm::vec3 (gray);
        }
    }
}

void negative(sil::Image &image) {
    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            image.pixel(x, y).r = 1.0f - image.pixel(x, y).r;
            image.pixel(x, y).g = 1.0f - image.pixel(x, y).g;
            image.pixel(x, y).b = 1.0f - image.pixel(x, y).b;
        }
    }
}

void gradient(sil::Image &image) {
    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            image.pixel(x, y) = glm::vec3 (static_cast<float>(x) / static_cast<float>(image.width() - 1));
        }
    }
}

void mirror(sil::Image &image) {
    for(int x{0}; x < image.width()/2; x++) {
        for(int y{0}; y < image.height(); y++) {
            std::swap(image.pixel(x, y), image.pixel(image.width()-(x+1), y));
        }
    }
}

void noisy(sil::Image &image) {
    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            if(true_with_probability(0.3f)) {
                image.pixel(x, y).r = random_float(0, 1);
                image.pixel(x, y).g = random_float(0, 1);
                image.pixel(x, y).b = random_float(0, 1);
            }
        }
    }
}

sil::Image rotation(sil::Image &image) {
    sil::Image rotatedImage{image.height(), image.width()};

    for(int x{0}; x < rotatedImage.width(); x++) {
        for(int y{0}; y < rotatedImage.height(); y++) {
            rotatedImage.pixel(x, y) = image.pixel(y, image.height() - x - 1);
        }
    }

    return rotatedImage;
}

sil::Image splitRGB(sil::Image &image)
{
    sil::Image editedImage{image.width(), image.height()};

    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            if(x > 31) {    
                editedImage.pixel(x, y).r = image.pixel(x - 30, y).r;
            }
            if (x < image.width() - 31) {
                editedImage.pixel(x, y).b = image.pixel(x + 30, y).b;
            }
            editedImage.pixel(x, y).g = image.pixel(x, y).g;
        }
    }

    return editedImage;
}

void higherLuminosity(sil::Image &image) {
    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            image.pixel(x, y).r = std::sqrt(image.pixel(x, y).r);
            image.pixel(x, y).g = std::sqrt(image.pixel(x, y).g);
            image.pixel(x, y).b = std::sqrt(image.pixel(x, y).b);
        }
    }
}
void lowerLuminosity(sil::Image &image) {
    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            image.pixel(x, y).r = std::pow(image.pixel(x, y).r, 2);
            image.pixel(x, y).g = std::pow(image.pixel(x, y).g, 2);
            image.pixel(x, y).b = std::pow(image.pixel(x, y).b, 2);
        }
    }
}

void disc(sil::Image &image) {
    int rayon{100};
    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            int dx = x - image.width()/2;
            int dy = y - image.height()/2;

            if (dx * dx + dy * dy <= rayon * rayon) {
                image.pixel(x, y).r = 1.0f;
                image.pixel(x, y).g = 1.0f;
                image.pixel(x, y).b = 1.0f;
            }
        }
    }
}
void circle(sil::Image &image) {
    int rayon{100};
    int thickness{5};

    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            int dx = x - image.width()/2;
            int dy = y - image.height()/2;

            if ((dx * dx + dy * dy <= rayon * rayon) && (dx * dx + dy * dy > (rayon - thickness) * (rayon - thickness))) {
                image.pixel(x, y).r = 1.0f;
                image.pixel(x, y).g = 1.0f;
                image.pixel(x, y).b = 1.0f;
            }
        }
    }
}
void rosace(sil::Image &image) {
    int rayon{100};
    int thickness{3};

    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            int dx = x - image.width()/2;
            int dy = y - image.height()/2;

            if ((dx * dx + dy * dy <= rayon * rayon) && (dx * dx + dy * dy > (rayon - thickness) * (rayon - thickness))) {
                image.pixel(x, y).r = 1.0f;
                image.pixel(x, y).g = 1.0f;
                image.pixel(x, y).b = 1.0f;
            }
        }
    }
    int centreX = image.width() / 2;
    int centreY = image.height() / 2;
    float angleStep = 2 * 3.14 / 6;
    for (int i = 0; i < 6; i++) {
        float angle = i * angleStep;
        int offsetX = static_cast<int>(rayon * cos(angle));
        int offsetY = static_cast<int>(rayon * sin(angle));

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                int dx = x - centreX - offsetX;
                int dy = y - centreY - offsetY;

                if ((dx * dx + dy * dy <= rayon * rayon) && (dx * dx + dy * dy > (rayon - thickness) * (rayon - thickness))) {
                    image.pixel(x, y).r = 1.0f;
                    image.pixel(x, y).g = 1.0f;
                    image.pixel(x, y).b = 1.0f;
                }
            }
        }
    }
}

sil::Image mosaic(sil::Image &image) {
    sil::Image mosaic{image.width() * 5, image.height() * 5};

    for(int x{0}; x < mosaic.width(); x++) {
        for(int y{0}; y < mosaic.height(); y++) {
            int oldX {x % image.width()};
            int oldY {y % image.height()};

            mosaic.pixel(x, y) = image.pixel(oldX, oldY);
        }
    }

    return mosaic;
}
sil::Image mirrorMosaic(sil::Image &image) {
    sil::Image mosaic{image.width() * 5, image.height() * 5};

    for(int x{0}; x < mosaic.width(); x++) {
        for(int y{0}; y < mosaic.height(); y++) {
            int oldX {x % image.width()};
            int oldY {y % image.height()};

            bool mirrorX {(x / image.width()) % 2 == 1};
            bool mirrorY {(y / image.height()) % 2 == 1}; 

            if (mirrorX) {
                oldX = image.width() - oldX - 1;
            }
            if (mirrorY) {
                oldY = image.height() - oldY - 1;
            }

            mosaic.pixel(x, y) = image.pixel(oldX, oldY);
        }
    }

    return mosaic;
}

void glitch(sil::Image &image) {
    int number_glitch = 80;

    for (int i = 0; i < number_glitch; ++i) {
        int rectangle1_x = random_int(0, image.width() - 1);
        int rectangle1_y = random_int(0, image.height() - 1);
        int rectangle_width = random_int(5, 20); 
        int rectangle_height = random_int(1, 10); 

        int rectangle2_x = random_int(0, image.width() - 1);
        int rectangle2_y = random_int(0, image.height() - 1);

        rectangle_width = std::min(rectangle_width, image.width() - std::max(rectangle1_x, rectangle2_x));
        rectangle_height = std::min(rectangle_height, image.height() - std::max(rectangle1_y, rectangle2_y));

        for (int x = 0; x < rectangle_width; ++x) {
            for (int y = 0; y < rectangle_height; ++y) {
                std::swap(image.pixel(rectangle1_x + x, rectangle1_y + y), image.pixel(rectangle2_x + x, rectangle2_y + y));
            }
        }
    }
}

void test(sil::Image &image) {
    for(int x{0}; x < image.width(); x++){
        for(int y{0}; y < image.height(); y++) {
            if(true_with_probability(0.3f)) {
                std::swap(image.pixel(x, y).r, image.pixel(x, y).g);
            } else if (true_with_probability(0.2f)) {
                std::swap(image.pixel(random_int(x, image.width()), random_int(y, image.height())), image.pixel(x, y));
            }
        }
    }
}
void test2(sil::Image &image) {
    for(int x{0}; x < image.width(); x++){
        for(int y{0}; y < image.height(); y++) {
            if(true_with_probability(0.4f)) {
                std::swap(image.pixel(x, y).b, image.pixel(x, y).g);
            } else if (true_with_probability(0.2f)) {
                image.pixel(x, y).g = 0.f;
                image.pixel(x, y).b = 0.f;
            }
        }
    }
}
void test3(sil::Image &image) {
    
}

int main()
{
    // {
    //     sil::Image image{"images/logo.png"};
    //     keepOnlyGreen(image);
    //     image.save("output/keepOnlyGreen.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     swapChannels(image);
    //     image.save("output/swapChannels.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     blackAndWhite(image);
    //     image.save("output/blackAndWhite.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     negative(image);
    //     image.save("output/negative.png");
    // }
    // {
    //     sil::Image image{300, 200};
    //     gradient(image);
    //     image.save("output/gradient.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mirror(image);
    //     image.save("output/mirror.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     noisy(image);
    //     image.save("output/noisy.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     sil::Image rotatedImage{rotation(image)};
    //     rotatedImage.save("output/rotation.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     sil::Image editedImage{splitRGB(image)};
    //     editedImage.save("output/splitRGB.png");
    // }
    // {
    //     sil::Image image1{"images/photo.jpg"};
    //     higherLuminosity(image1);
    //     image1.save("output/higherLuminosity.png");
    //     sil::Image image2{"images/photo.jpg"};
    //     lowerLuminosity(image2);
    //     image2.save("output/lowerLuminosity.png");
    // }
    // {
    //     sil::Image discImage{500, 500};
    //     disc(discImage);
    //     discImage.save("output/disc.png");
    //     sil::Image circleImage{500, 500};
    //     circle(circleImage);
    //     circleImage.save("output/circle.png");
    //     sil::Image rosaceImage{600, 600};
    //     rosace(rosaceImage);
    //     rosaceImage.save("output/rosace.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     sil::Image mosaicImage{mosaic(image)};
    //     mosaicImage.save("output/mosaic.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     sil::Image mosaicImage{mirrorMosaic(image)};
    //     mosaicImage.save("output/mirrorMosaic.png");
    // }
    {
        sil::Image image{"images/logo.png"};
        glitch(image);
        image.save("output/glitch.png");
    }
    // {
    //     sil::Image image{"images/logo.png"};
    //     test(image);
    //     image.save("output/tests/test1.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     test2(image);
    //     image.save("output/tests/test2.png");
    // }

    return 0;
}
#include <sil/sil.hpp>
#include <iostream>
#include "random.hpp"

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
    sil::Image editedImage{image};

    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            if(x < 31) {
                editedImage.pixel(x, y).b = image.pixel(x + 30, y).b;
            } else if (x >= image.width() - 30) {
                editedImage.pixel(x, y).r = image.pixel(x - 30, y).r;
            } else {
                editedImage.pixel(x, y).r = image.pixel(x - 30, y).r;
                editedImage.pixel(x, y).b = image.pixel(x + 30, y).b;
            }
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

int main()
{
    {
        sil::Image image{"images/logo.png"};
        keepOnlyGreen(image);
        image.save("output/keepOnlyGreen.png");
    }
    {
        sil::Image image{"images/logo.png"};
        swapChannels(image);
        image.save("output/swapChannels.png");
    }
    {
        sil::Image image{"images/logo.png"};
        blackAndWhite(image);
        image.save("output/blackAndWhite.png");
    }
    {
        sil::Image image{"images/logo.png"};
        negative(image);
        image.save("output/negative.png");
    }
    {
        sil::Image image{300, 200};
        gradient(image);
        image.save("output/gradient.png");
    }
    {
        sil::Image image{"images/logo.png"};
        mirror(image);
        image.save("output/mirror.png");
    }
    {
        sil::Image image{"images/logo.png"};
        noisy(image);
        image.save("output/noisy.png");
    }
    {
        sil::Image image{"images/logo.png"};
        sil::Image rotatedImage{rotation(image)};
        rotatedImage.save("output/rotation.png");
    }
    {
        sil::Image image{"images/logo.png"};
        sil::Image editedImage{splitRGB(image)};
        editedImage.save("output/splitRGB.png");
    }
    {
        sil::Image image1{"images/photo.jpg"};
        higherLuminosity(image1);
        image1.save("output/higherLuminosity.png");
        sil::Image image2{"images/photo.jpg"};
        lowerLuminosity(image2);
        image2.save("output/lowerLuminosity.png");
    }
    {
        sil::Image discImage{500, 500};
        disc(discImage);
        discImage.save("output/disc.png");
        sil::Image circleImage{500, 500};
        circle(circleImage);
        circleImage.save("output/circle.png");
        sil::Image rosaceImage{600, 600};
        rosace(rosaceImage);
        rosaceImage.save("output/rosace.png");
    }
    {
        
    }

    return 0;
}
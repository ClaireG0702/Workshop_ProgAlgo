#include <sil/sil.hpp>
#include <iostream>
#include "random.hpp"
#include <vector>

void keepOnlyGreen(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;
        }
    }
}

void swapChannels(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y).r, image.pixel(x, y).b);
        }
    }
}

void blackAndWhite(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float gray = 0.2126 * image.pixel(x, y).r + 0.7152 * image.pixel(x, y).g + 0.0722 * image.pixel(x, y).b;

            image.pixel(x, y) = glm::vec3(gray);
        }
    }
}

void negative(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 1.0f - image.pixel(x, y).r;
            image.pixel(x, y).g = 1.0f - image.pixel(x, y).g;
            image.pixel(x, y).b = 1.0f - image.pixel(x, y).b;
        }
    }
}

void gradient(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = glm::vec3(static_cast<float>(x) / static_cast<float>(image.width() - 1));
        }
    }
}

void mirror(sil::Image &image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y), image.pixel(image.width() - (x + 1), y));
        }
    }
}

void noisy(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (true_with_probability(0.3f))
            {
                image.pixel(x, y).r = random_float(0, 1);
                image.pixel(x, y).g = random_float(0, 1);
                image.pixel(x, y).b = random_float(0, 1);
            }
        }
    }
}

sil::Image rotation(sil::Image &image)
{
    sil::Image rotatedImage{image.height(), image.width()};

    for (int x{0}; x < rotatedImage.width(); x++)
    {
        for (int y{0}; y < rotatedImage.height(); y++)
        {
            rotatedImage.pixel(x, y) = image.pixel(y, image.height() - x - 1);
        }
    }

    return rotatedImage;
}

sil::Image splitRGB(sil::Image &image)
{
    sil::Image editedImage{image.width(), image.height()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x > 31)
            {
                editedImage.pixel(x, y).r = image.pixel(x - 30, y).r;
            }
            if (x < image.width() - 31)
            {
                editedImage.pixel(x, y).b = image.pixel(x + 30, y).b;
            }
            editedImage.pixel(x, y).g = image.pixel(x, y).g;
        }
    }

    return editedImage;
}

void higherLuminosity(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = std::sqrt(image.pixel(x, y).r);
            image.pixel(x, y).g = std::sqrt(image.pixel(x, y).g);
            image.pixel(x, y).b = std::sqrt(image.pixel(x, y).b);
        }
    }
}
void lowerLuminosity(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = std::pow(image.pixel(x, y).r, 2);
            image.pixel(x, y).g = std::pow(image.pixel(x, y).g, 2);
            image.pixel(x, y).b = std::pow(image.pixel(x, y).b, 2);
        }
    }
}

void disc(sil::Image &image)
{
    int rayon{100};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int dx = x - image.width() / 2;
            int dy = y - image.height() / 2;

            if (dx * dx + dy * dy <= rayon * rayon)
            {
                image.pixel(x, y).r = 1.0f;
                image.pixel(x, y).g = 1.0f;
                image.pixel(x, y).b = 1.0f;
            }
        }
    }
}
void circle(sil::Image &image)
{
    int rayon{100};
    int thickness{5};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int dx = x - image.width() / 2;
            int dy = y - image.height() / 2;

            if ((dx * dx + dy * dy <= rayon * rayon) && (dx * dx + dy * dy > (rayon - thickness) * (rayon - thickness)))
            {
                image.pixel(x, y).r = 1.0f;
                image.pixel(x, y).g = 1.0f;
                image.pixel(x, y).b = 1.0f;
            }
        }
    }
}
void rosace(sil::Image &image)
{
    int rayon{100};
    int thickness{3};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int dx = x - image.width() / 2;
            int dy = y - image.height() / 2;

            if ((dx * dx + dy * dy <= rayon * rayon) && (dx * dx + dy * dy > (rayon - thickness) * (rayon - thickness)))
            {
                image.pixel(x, y).r = 1.0f;
                image.pixel(x, y).g = 1.0f;
                image.pixel(x, y).b = 1.0f;
            }
        }
    }
    int centreX = image.width() / 2;
    int centreY = image.height() / 2;
    float angleStep = 2 * 3.14 / 6;
    for (int i = 0; i < 6; i++)
    {
        float angle = i * angleStep;
        int offsetX = static_cast<int>(rayon * cos(angle));
        int offsetY = static_cast<int>(rayon * sin(angle));

        for (int x = 0; x < image.width(); x++)
        {
            for (int y = 0; y < image.height(); y++)
            {
                int dx = x - centreX - offsetX;
                int dy = y - centreY - offsetY;

                if ((dx * dx + dy * dy <= rayon * rayon) && (dx * dx + dy * dy > (rayon - thickness) * (rayon - thickness)))
                {
                    image.pixel(x, y).r = 1.0f;
                    image.pixel(x, y).g = 1.0f;
                    image.pixel(x, y).b = 1.0f;
                }
            }
        }
    }
}

sil::Image mosaic(sil::Image &image)
{
    sil::Image mosaic{image.width() * 5, image.height() * 5};

    for (int x{0}; x < mosaic.width(); x++)
    {
        for (int y{0}; y < mosaic.height(); y++)
        {
            int oldX{x % image.width()};
            int oldY{y % image.height()};

            mosaic.pixel(x, y) = image.pixel(oldX, oldY);
        }
    }

    return mosaic;
}
sil::Image mirrorMosaic(sil::Image &image)
{
    sil::Image mosaic{image.width() * 5, image.height() * 5};

    for (int x{0}; x < mosaic.width(); x++)
    {
        for (int y{0}; y < mosaic.height(); y++)
        {
            int oldX{x % image.width()};
            int oldY{y % image.height()};

            bool mirrorX{(x / image.width()) % 2 == 1};
            bool mirrorY{(y / image.height()) % 2 == 1};

            if (mirrorX)
            {
                oldX = image.width() - oldX - 1;
            }
            if (mirrorY)
            {
                oldY = image.height() - oldY - 1;
            }

            mosaic.pixel(x, y) = image.pixel(oldX, oldY);
        }
    }

    return mosaic;
}

void glitch(sil::Image &image)
{
    int number_glitch = 80;

    for (int i = 0; i < number_glitch; ++i)
    {
        int rectangle1_x = random_int(0, image.width() - 1);
        int rectangle1_y = random_int(0, image.height() - 1);
        int rectangle_width = random_int(5, 20);
        int rectangle_height = random_int(1, 10);

        int rectangle2_x = random_int(0, image.width() - 1);
        int rectangle2_y = random_int(0, image.height() - 1);

        rectangle_width = std::min(rectangle_width, image.width() - std::max(rectangle1_x, rectangle2_x));
        rectangle_height = std::min(rectangle_height, image.height() - std::max(rectangle1_y, rectangle2_y));

        for (int x = 0; x < rectangle_width; ++x)
        {
            for (int y = 0; y < rectangle_height; ++y)
            {
                std::swap(image.pixel(rectangle1_x + x, rectangle1_y + y), image.pixel(rectangle2_x + x, rectangle2_y + y));
            }
        }
    }
}

float brightness(glm::vec3 pixel)
{
    return 0.2126 * pixel.r + 0.7152 * pixel.g + 0.0722 * pixel.b;
}
// Tri de toute l'image
void pixelsSorting1(sil::Image &image)
{
    for (int i{0}; i < image.pixels().size(); i++)
    {
        float record{-1};
        int selectedPixel{i};

        for (int j{i}; j < image.pixels().size(); j++)
        {
            auto pix = image.pixels().at(j);
            float bright = brightness(pix);

            if (bright > record)
            {
                selectedPixel = j;
                record = bright;
            }
        }

        std::swap(image.pixels().at(selectedPixel), image.pixels().at(i));
    }
}
// Tri par colonnes
void pixelsSorting2(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        float record{-1};

        for (int i{0}; i < image.height(); i++)
        {
            float record{-1};
            auto selectedPixel{image.pixel(x, i)};

            for (int j{i}; j < image.height(); j++)
            {
                auto pix = image.pixel(x, j);
                float bright = brightness(pix);

                if (bright > record)
                {
                    selectedPixel = pix;
                    record = bright;
                }
            }

            std::swap(selectedPixel, image.pixel(x, i));
        }
    }
}
// Tri par lignes
void pixelsSorting3(sil::Image &image)
{
    for (int y{0}; y < image.height(); y++)
    {
        float record{-1};

        for (int i{0}; i < image.width(); i++)
        {
            float record{-1};
            auto selectedPixel{image.pixel(i, y)};

            for (int j{i}; j < image.width(); j++)
            {
                auto pix = image.pixel(j, y);
                float bright = brightness(pix);

                if (bright > record)
                {
                    selectedPixel = pix;
                    record = bright;
                }
            }

            std::swap(selectedPixel, image.pixel(i, y));
        }
    }
}
// Tri par blocs
void pixelsSorting4(sil::Image &image){
    for (int i=0; (i + 70) < image.pixels().size(); i++)
    {
        if (random_int(0, 150) == 75){
            std::sort(image.pixels().begin() + i, image.pixels().begin() + (i + 70), [](glm::vec3 const& color1, glm::vec3 const& color2) {
                return brightness(color1) > brightness(color2);
            });
            i = i + 70;
        }
    }
}

glm::vec3 srgb_to_linear(glm::vec3 c){
    for(int i = 0; i < 3; i++ ){
        if (c[i] <= 0.04045){
            c[i] = c[i] / 12.92;
        }
        else{
            c[i] = pow((c[i] + 0.055) / 1.055, 2.4);
        }
    } 
    return c;
}
glm::vec3 linear_to_oklab(glm::vec3 c) 
{
    c = srgb_to_linear(c);
    float l = 0.4121656120f * c.r + 0.5362752080f * c.g + 0.0514575653f * c.b;
    float m = 0.2118591070f * c.r + 0.6807189584f * c.g + 0.1074065790f * c.b;
    float s = 0.0883097947f * c.r + 0.2818474174f * c.g + 0.6302613616f * c.b;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);

    return {
        0.2104542553f*l_ + 0.7936177850f*m_ - 0.0040720468f*s_,
        1.9779984951f*l_ - 2.4285922050f*m_ + 0.4505937099f*s_,
        0.0259040371f*l_ + 0.7827717662f*m_ - 0.8086757660f*s_,
    };
}
glm::vec3 linear_to_srgb(glm::vec3 c){
    for(int i = 0; i < 3; i++ ){
        if (c[i] <= 0.0031308){
            c[i] = c[i] * 12.92;
        }
        else{
            c[i] = 1.055 * pow(c[i], 1.0/2.4) - 0.055; 
        }
    } 
    return c;
    
}
glm::vec3 oklab_to_linear(glm::vec3 c) 
{
    float l_ = c.r + 0.3963377774f * c.g + 0.2158037573f * c.b;
    float m_ = c.r - 0.1055613458f * c.g - 0.0638541728f * c.b;
    float s_ = c.r - 0.0894841775f * c.g - 1.2914855480f * c.b;

    float l = l_*l_*l_;
    float m = m_*m_*m_;
    float s = s_*s_*s_;

    return linear_to_srgb({
        + 4.0767245293f*l - 3.3072168827f*m + 0.2307590544f*s,
        - 1.2681437731f*l + 2.6093323231f*m - 0.3411344290f*s,
        - 0.0041119885f*l - 0.7034763098f*m + 1.7068625689f*s,
    });
}
void coloredGradient(sil::Image &image) {
    glm::vec3 color1 = linear_to_oklab({0.2, 1, 0.7});
    glm::vec3 color2 =  linear_to_oklab({1, 0.6, 0.3});

    for (int x{0}; x < image.width(); ++x) {
        for (int y{0}; y < image.height(); ++y) {
            // image.pixel(x, y) = glm::mix(color1, color2, static_cast<float>(x) / static_cast<float>(image.width() - 1));
            image.pixel(x, y) = oklab_to_linear(glm::mix(color1, color2, static_cast<float>(x) / static_cast<float>(image.width() - 1))); 
        }
    }
}

void test(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (true_with_probability(0.3f))
            {
                std::swap(image.pixel(x, y).r, image.pixel(x, y).g);
            }
            else if (true_with_probability(0.2f))
            {
                std::swap(image.pixel(random_int(x, image.width()), random_int(y, image.height())), image.pixel(x, y));
            }
        }
    }
}
void test2(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (true_with_probability(0.4f))
            {
                std::swap(image.pixel(x, y).b, image.pixel(x, y).g);
            }
            else if (true_with_probability(0.2f))
            {
                image.pixel(x, y).g = 0.f;
                image.pixel(x, y).b = 0.f;
            }
        }
    }
}
void test3(sil::Image &image)
{
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
    // {
    //     sil::Image image{"images/logo.png"};
    //     glitch(image);
    //     image.save("output/glitch.png");
    // }
    // {
        // sil::Image image1{"images/logo.png"};
        // pixelsSorting1(image1);
        // image1.save("output/pixelsSorting1.png");
        // sil::Image image2{"images/logo.png"};
        // pixelsSorting2(image2);
        // image2.save("output/pixelsSorting2.png");
        // sil::Image image3{"images/logo.png"};
        // pixelsSorting3(image3);
        // image3.save("output/pixelsSorting3.png");
        // sil::Image image4{"images/logo.png"};
        // pixelsSorting4(image4);
        // image4.save("output/pixelsSorting4.png");
    // }
    {
        sil::Image image{300, 200};
        coloredGradient(image);
        image.save("output/coloredGradient.png");
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
#include <iostream>
#include <vector>
#include <tbb/tbb.h>
#include "ch01.h"

using ImagePtr = std::shared_ptr<ch01::Image>;

using std::cout;
using std::endl;

ImagePtr applyGamma(ImagePtr img_ptr, double gamma);
ImagePtr applyTint(ImagePtr img_ptr, const double *tints);
void writeImage(ImagePtr img_ptr);

void figure_1_10(const std::vector<ImagePtr> &img_vector)
{
    const double tint_array[]= {0, 0.75, 0};
    tbb::flow::graph g;
    int i = 0;
    tbb::flow::source_node<ImagePtr> src(g, 
    [&i, &img_vector] (ImagePtr &out) -> bool {
        if (i < img_vector.size())
     {
            out = img_vector[i++];
            return true;
        }
        else
        {
            return false;
        }
    }, false);
    
    tbb::flow::function_node<ImagePtr, ImagePtr> gamma(g, 
        tbb::flow::unlimited, 
        [] (ImagePtr img) -> ImagePtr {
        return applyGamma(img, 1.4);
    });

    tbb::flow::function_node<ImagePtr, ImagePtr> tint(g, 
        tbb::flow::unlimited,  
        [tint_array] (ImagePtr img) -> ImagePtr {
            return applyTint(img, tint_array);
        }
    );

    tbb::flow::function_node<ImagePtr> write(g, 
        tbb::flow::unlimited, 
        [] (ImagePtr img) {
            writeImage(img);
        }
    );
    tbb::flow::make_edge(src, gamma);
    tbb::flow::make_edge(gamma, tint);
    tbb::flow::make_edge(tint, write);

    src.activate();
    g.wait_for_all();

}

ImagePtr applyGamma(ImagePtr img_ptr, double gamma)
{
    auto output_img_ptr = std::make_shared<ch01::Image>(img_ptr->name() + "_gamma", ch01::IMAGE_WIDTH, ch01::IMAGE_HEIGHT);
    auto in_rows = img_ptr->rows();
    auto out_rows = output_img_ptr->rows();
    const int height = in_rows.size();
    const int width = in_rows[1] - in_rows[0];
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            const ch01::Image::Pixel &p = in_rows[i][j];
            double v = 0.3*p.bgra[2] + 0.59*p.bgra[1] + 0.11*p.bgra[0];
            double res = pow(v, gamma);
            if (res > ch01::MAX_BGR_VALUE)
            {
                res= ch01::MAX_BGR_VALUE;
            }
            out_rows[i][j] = ch01::Image::Pixel(res, res, res);
        }
    }
    return output_img_ptr;
}

ImagePtr applyTint(ImagePtr img_ptr, const double *tints)
{
    auto output_img_ptr = std::make_shared<ch01::Image>(img_ptr->name() + "_gamma", ch01::IMAGE_WIDTH, ch01::IMAGE_HEIGHT);
    auto in_rows = img_ptr->rows();
    auto out_rows = output_img_ptr->rows();
    const int height = in_rows.size();
    const int width = in_rows[1] - in_rows[0];
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            const ch01::Image::Pixel &p = in_rows[i][j];
            std::uint8_t b = (double)p.bgra[0] + (ch01::MAX_BGR_VALUE - p.bgra[0])*tints[0];
            std::uint8_t g = (double)p.bgra[1] + (ch01::MAX_BGR_VALUE - p.bgra[1])*tints[1];
            std::uint8_t r = (double)p.bgra[2] + (ch01::MAX_BGR_VALUE - p.bgra[2])*tints[2];

            out_rows[i][j] = ch01::Image::Pixel(
                (b > ch01::MAX_BGR_VALUE) ? ch01::MAX_BGR_VALUE : b,
                (g > ch01::MAX_BGR_VALUE) ? ch01::MAX_BGR_VALUE : g,
                (r > ch01::MAX_BGR_VALUE) ? ch01::MAX_BGR_VALUE : r
            );
        }
    }
    return output_img_ptr;
}

void writeImage(ImagePtr img_ptr)
{
    img_ptr->write((img_ptr->name() + ".bmp").c_str());
}
int main()
{
    std::vector<ImagePtr> image_vector;
    for (size_t i = 2000; i < 200000000;  i *= 10)
    {
        image_vector.push_back(ch01::makeFractalImage(i));
    }
    tbb::tick_count t0 = tbb::tick_count::now();
    figure_1_10(image_vector);
    cout<<"Time: "<<(tbb::tick_count::now() - t0).seconds()<< " seconds"<<endl;
    return 0;
}
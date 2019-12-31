#include <iostream>
#include <vector>
#include <tbb/tbb.h>
#include "ch01.h"

using ImagePtr = std::shared_ptr<ch01::Image>;

ImagePtr applyGamma(ImagePtr img_ptr, double gamma);
ImagePtr applyTint(ImagePtr img_ptr, const double *tints);
void writeImage(ImagePtr img_ptr);

void figure_1_07(cosnt std::vector<ImagePtr> &img_vector)
{
    const double tint_array[]= {0.75, 0, 0};
    for (ImagePtr img:img_vector)
    {
        img = applyGamma(img, 1.4);
        img = applyTint(img, tint_array);
        writeImage(img);
    }
}

ImagePtr applyGamma(ImagePtr img_ptr, double gamma)
{
    auto output_img_ptr = std::make_shared<ch01::Image>(img_ptr->name() + "_gamma", ch01::IMAGE_WIDTH, ch01::IMAGE_HEIGHT);
    auto in_rows = img_ptr->rows();
    auto out_rows = output_img_ptr->rows();
    const int height = in_rows.size();
    const int width = in_rows[1] - in_rows[0];
    

}

int main()
{
    return 0;

}
#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include<vector>

//reviewed
void Image::lighten() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).l + .1 >= 1) {
                getPixel(x,y).l = 1;
            } else {
                getPixel(x,y).l += .1;
            }
        }
    }
}

//reviewed
void Image::lighten(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if(getPixel(x,y).l + amount >= 1) {
                getPixel(x,y).l = 1;
            } else {
                getPixel(x,y).l += amount;
            }
        }
    }
}

//reviewed
void Image::darken() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).l <= 0) {
                getPixel(x,y).l = 0;
            } else {
                getPixel(x,y).l -= .1;
            }
        }
    }
}

//reviewed
void Image::darken(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).l - amount <= 0) {
                getPixel(x,y).l = 0;
            } else {
                getPixel(x,y).l -= amount;
            }
        }
    }
}

//reviewed
void Image::saturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x,y).s >= 1) {
                getPixel(x,y).s = 1;
            } else {
                getPixel(x, y).s += .1;
            }
        }
    }
}

//reviewed
void Image::saturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x, y).s + amount >= 1) {
                getPixel(x, y).s = 1;
            } else {
                getPixel(x, y).s = 1;
            }
        }
    }
}

//reviewed
void Image::desaturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x, y).s - .1 <= 0) {
                getPixel(x, y).s = 0;
            } else {
                getPixel(x, y).s -= .1;
            }
        }
    }
}

//reviewed
void Image::desaturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            if (getPixel(x, y).s - amount < 0) {
                getPixel(x, y).s = 0;
            } else {
                getPixel(x, y).s -= amount;
            }
        }
    }
}

//reviewed
void Image::grayscale() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; x < height(); y++) {
            getPixel(x, y).s = 0;
        }
    }
}

//reviewed
void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            getPixel(x, y).h += degrees;
            while(getPixel(x, y).h > 360 ||getPixel(x, y).h < 0) {
                if (getPixel(x, y).h > 360) {
                    getPixel(x, y).h = (getPixel(x, y).h - 360);
                } else {
                    getPixel(x, y).h = 360 - std::abs(getPixel(x, y).h);
                }
            }
        }
    }
}

//reviewed
void Image::illinify() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            int o_dist = std::abs(getPixel(x, y).h - 11);
            int b_dist = std::abs(getPixel(x, y).h - 216);
            if (o_dist < b_dist) {
                getPixel(x, y).h = 11;
            } else {
                getPixel(x, y).h = 216;
            }
        }
    }
}

//not tested
void Image::scale(double factor) {
    // nearest neighbor
    Image savedImg = Image(width(), height());
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            savedImg.getPixel(x,y) = getPixel(x,y);
        }
    }

    resize(width() * factor, height() * factor);

    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            int new_x = (x/factor);
            int new_y = (y/factor);
            getPixel(x,y) = savedImg.getPixel(new_x,new_y);
        }
    }
}

//not tested
void Image::scale(unsigned w, unsigned h) {
    //copy the image
    unsigned int imageWidth = width();
    Image savedImg = Image(width(), height());
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            savedImg.getPixel(x,y) = getPixel(x,y);
        }
    }

    unsigned revised_w = w;
    unsigned revised_h = h;

    if (width() > height() && ((double(w) / h) != (double(width()) / height()))) {
        if (w > h && w * (double(height()) / width()) <= h) {
            revised_h = w * (double(height()) / width());
        } else if (w > h) {
            revised_w = h * (double(width()) / height());
        } else {
            revised_h = w * (double(height()) / width());
        }
    } else if ((double(w) / h) != (double(width()) / height())) {
        if (w > h && w * (double(height()) / width()) <= h) {
            revised_h = w * (double(height()) / width());
        } else if (w > h) {
            revised_w = h * (double(width()) / height());
        } else {
            revised_h = w * (double(height()) / width());
    }
 }

    resize(revised_w, revised_h);
    double factor = double(revised_w)/imageWidth;

    for (unsigned x = 0; x < revised_w; x++) {
        for (unsigned y = 0; y < revised_h; y++) {
            int new_x = int(x/factor);
            int new_y = int(y/factor);
            getPixel(x,y) = savedImg.getPixel(new_x,new_y);
        }
    }
}



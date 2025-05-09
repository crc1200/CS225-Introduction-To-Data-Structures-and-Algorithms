/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */
 #include "cs225/HSLAPixel.h"
 #include "cs225/PNG.h"


class Image: public cs225::PNG {
    public:
        Image() : cs225::PNG() {};
        Image(unsigned int width, unsigned int height) : cs225::PNG(width, height) {};
        void lighten();
        void lighten(double amount);
        void darken();
        void darken(double amount);
        void saturate();
        void saturate(double amount);
        void desaturate();
        void desaturate(double amount);
        void grayscale();
        void rotateColor(double degrees);
        void illinify();
        void scale(double factor);
        void scale(unsigned w, unsigned h);
    private:
};

#pragma once
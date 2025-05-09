/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
 #include "cs225/HSLAPixel.h"
 #include "cs225/PNG.h"
 #include <vector>
 #include "Image.h"
 #include <tuple>

 class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        StickerSheet(const StickerSheet &other);
        const StickerSheet & operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index);
        int countAvailable();
        Image render();
        Image getImage() const;
        std::vector<std::tuple<Image*, int, int>> getLayers() const;

    private:
        std::vector<std::tuple<Image*, int, int>> layers;
        Image image;
 };
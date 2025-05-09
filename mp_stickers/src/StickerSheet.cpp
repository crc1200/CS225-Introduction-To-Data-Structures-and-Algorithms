#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include<vector>
#include <tuple>
#include "StickerSheet.h"


StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    image = picture;
    std::vector<std::tuple<Image*, int, int>> n_l(max);
    layers = n_l;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    image = other.getImage();
    layers = other.getLayers();
}

Image StickerSheet::getImage() const {
    return image;
}

std::vector<std::tuple<Image*, int, int>> StickerSheet::getLayers() const {
    return layers;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    image = other.getImage();
    layers = other.getLayers();
    return other;
}
void StickerSheet::changeMaxStickers(unsigned max) {
    std::vector<std::tuple<Image*, int, int>> n_layer(max);
    for (unsigned int i = 0; i < max; i++) {
        if (i < layers.size() && std::get<0>(layers[i]) != NULL) {
            n_layer[i] = layers[i];
        }
    }
    layers = n_layer;
}

int StickerSheet::countAvailable() {
    int count = 0;
    for (unsigned int i = 0; i < layers.size(); i++) {
        if (std::get<0>(layers[i]) == NULL) {
            count += 1;
        }
    }
    return count;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (countAvailable() == 0) {
        return -1;
    }
    int loc = 0;
    while (std::get<0>(layers[loc]) != NULL) {
        loc += 1;
    }
    std::tuple <Image*, int, int> insert(&sticker, x, y);
    layers[loc] = insert;
    return loc;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index >= layers.size()) {
        return false;
    } else {
        if (std::get<0>(layers[index]) == NULL) {
            return false;
        }
        std::tuple <Image*, int, int> insert(std::get<0>(layers[index]), x, y);
        layers[index] = insert;
    }
    return true;
}
void StickerSheet::removeSticker(unsigned index) {
    std::tuple <Image*, unsigned, unsigned> blank(NULL, 0, 0);
    layers[index] = blank;
}

Image * StickerSheet::getSticker(unsigned index) {
    if (index >= layers.size() || std::get<0>(layers[index]) == NULL) {
        return NULL;
    }
    return std::get<0>(layers[index]);
}
Image StickerSheet::render() {
    Image poster = Image(image);
    for (unsigned int l = 0; l < layers.size(); l++) {
        if (std::get<0>(layers[l]) != NULL) {
            Image* sticker = std::get<0>(layers[l]);
            unsigned int h = sticker->height();
            unsigned int w = sticker->width();
            unsigned int starting_x = std::get<1>(layers[l]);
            unsigned int starting_y = std::get<2>(layers[l]);
            if ((starting_y + h) >= poster.height()) {
                poster.resize(poster.width(), starting_y + h);
            }
            if ((starting_x + w) >= poster.width()) {
                poster.resize(starting_x + w, poster.height());
            }
            for (unsigned int sticker_x = 0; sticker_x < w; sticker_x++) {
                for (unsigned int sticker_y = 0; sticker_y < h; sticker_y++) {
                    unsigned int x_loc = starting_x + sticker_x;
                    unsigned int y_loc = starting_y + sticker_y;
                    if (sticker->getPixel(sticker_x, sticker_y).a != 0) {
                        poster.getPixel(x_loc, y_loc) = sticker->getPixel(sticker_x, sticker_y);
                    }
                }
            } 
        }
        
    }
    return poster;
}









#include "oxygine-framework.h";
#include "tile.h"

using namespace oxygine;

Tile::Tile(int8_t p, Resources& gameResources) {
    pos = p;
    Point tile_size = Point(core::getDisplaySize().y / 8, core::getDisplaySize().y / 8);
    Point corner = core::getDisplaySize() / 2 - tile_size * 4;
    this->setAnchor(0.5, 0.5);
    this->setResAnim(gameResources.getResAnim((p + p / 8) % 2 ? "dark_tile" : "light_tile"));
    this->setPosition(corner + Point((p % 8) * tile_size.x, (p / 8) * tile_size.x) + tile_size / 2);
    this->setRotationDegrees(90*p);
    this->setSize(tile_size);
}

void Tile::highlight(Color col) {
    this->addTween(Sprite::TweenAddColor(col), 200);
}

void Tile::animateScale(float scale) {
    this->addTween(Sprite::TweenScale(scale), 50);
}


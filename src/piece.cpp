#include "oxygine-framework.h"
#include "piece.h"

using namespace oxygine;

void Piece::highlight(Color col) {
    this->addTween(Sprite::TweenAddColor(col), 200);
}

King::King(int8_t p, int8_t t, Resources& gameResources) {
    Point tile_size = Point(core::getDisplaySize().y / 8, core::getDisplaySize().y / 8);
    Point corner = core::getDisplaySize() / 2 - tile_size * 4;
    this->setAnchor(0.5, 0.5);
    this->setResAnim(gameResources.getResAnim("figures"), 0, t);
    this->setPosition(corner + Point((p % 8) * tile_size.x, (p / 8) * tile_size.x) + tile_size / 2);
    this->setScale(tile_size.x / 400.);
    this->pos = p;
    this->team = t;
}

Queen::Queen(int8_t p, int8_t t, Resources& gameResources) {
    Point tile_size = Point(core::getDisplaySize().y / 8, core::getDisplaySize().y / 8);
    Point corner = core::getDisplaySize() / 2 - tile_size * 4;
    this->setAnchor(0.5, 0.5);
    this->setResAnim(gameResources.getResAnim("figures"), 1, t);
    this->setPosition(corner + Point((p % 8) * tile_size.x, (p / 8) * tile_size.x) + tile_size / 2);
    this->setScale(tile_size.x / 400.);
    this->pos = p;
    this->team = t;
}

Bishop::Bishop(int8_t p, int8_t t, Resources& gameResources) {
    Point tile_size = Point(core::getDisplaySize().y / 8, core::getDisplaySize().y / 8);
    Point corner = core::getDisplaySize() / 2 - tile_size * 4;
    this->setAnchor(0.5, 0.5);
    this->setResAnim(gameResources.getResAnim("figures"), 2, t);
    this->setPosition(corner + Point((p % 8) * tile_size.x, (p / 8) * tile_size.x) + tile_size / 2);
    this->setScale(tile_size.x / 400.);
    this->pos = p;
    this->team = t;
}

Knight::Knight(int8_t p, int8_t t, Resources& gameResources) {
    Point tile_size = Point(core::getDisplaySize().y / 8, core::getDisplaySize().y / 8);
    Point corner = core::getDisplaySize() / 2 - tile_size * 4;
    this->setAnchor(0.5, 0.5);
    this->setResAnim(gameResources.getResAnim("figures"), 3, t);
    this->setPosition(corner + Point((p % 8) * tile_size.x, (p / 8) * tile_size.x) + tile_size / 2);
    this->setScale(tile_size.x / 400.);
    this->pos = p;
    this->team = t;
}

Rook::Rook(int8_t p, int8_t t, Resources& gameResources) {
    Point tile_size = Point(core::getDisplaySize().y / 8, core::getDisplaySize().y / 8);
    Point corner = core::getDisplaySize() / 2 - tile_size * 4;
    this->setAnchor(0.5, 0.5);
    this->setResAnim(gameResources.getResAnim("figures"), 4, t);
    this->setPosition(corner + Point((p % 8) * tile_size.x, (p / 8) * tile_size.x) + tile_size / 2);
    this->setScale(tile_size.x / 400.);
    this->pos = p;
    this->team = t;
}

Pawn::Pawn(int8_t p, int8_t t, Resources& gameResources) {
    Point tile_size = Point(core::getDisplaySize().y / 8, core::getDisplaySize().y / 8);
    Point corner = core::getDisplaySize() / 2 - tile_size * 4;
    this->setAnchor(0.5, 0.5);
    this->setResAnim(gameResources.getResAnim("figures"), 5, t);
    this->setPosition(corner + Point((p % 8) * tile_size.x, (p / 8) * tile_size.x) + tile_size / 2);
    this->setScale(tile_size.x / 400.);
    this->pos = p;
    this->team = t;
}

Empty::Empty(int8_t p) {
    pos = p;
    team = 2;
}

std::vector<int8_t> King::possible_moves(spSprite pieces[]) {
    spPiece* pi = (spPiece*)pieces;
    std::vector<int8_t> possible_moves;

    
    if ((pos % 8 != 7) && pi[pos+1]->team != team) possible_moves.push_back(pos+1);
    if ((pos % 8 != 0) && pi[pos-1]->team != team) possible_moves.push_back(pos-1);
    if ((pos / 8 != 0) && pi[pos-8]->team != team) possible_moves.push_back(pos-8);
    if ((pos / 8 != 7) && pi[pos+8]->team != team) possible_moves.push_back(pos+8);

    if ((pos % 8 != 7) && (pos / 8 != 0) && 
    pi[pos-7]->team != team) possible_moves.push_back(pos-7);

    if ((pos % 8 != 0) && (pos / 8 != 0) && 
    pi[pos-9]->team != team) possible_moves.push_back(pos-9);

    if ((pos % 8 != 0) && (pos / 8 != 7) && 
    pi[pos+7]->team != team) possible_moves.push_back(pos+7);

    if ((pos % 8 != 7) && (pos / 8 != 7) && 
    pi[pos+9]->team != team) possible_moves.push_back(pos+9);

    return possible_moves;
}

std::vector<int8_t> Rook::possible_moves(spSprite pieces[]) {
    spPiece* pi = (spPiece*)pieces;
    std::vector<int8_t> possible_moves;

    auto check = [&possible_moves, this, pi](int8_t n) {
        if (pi[n]->team == 2) {
            possible_moves.push_back(n);
            return false;}
        if (pi[n]->team != team) {
            possible_moves.push_back(n);}
        return true;
    }; 

    for(int i = pos - 8; i >= 0; i -= 8) if (check(i)) break;
    for(int i = pos + 8; i <= 63; i += 8) if (check(i)) break;
    for(int i = pos - 1; i >= 0 && (i + 1) % 8 > i % 8; i--) if (check(i)) break;
    for(int i = pos + 1; i <= 63 && (i - 1) % 8 < i % 8; i++) if (check(i)) break;
    
    return possible_moves;
}

std::vector<int8_t> Queen::possible_moves(spSprite pieces[]) {
    spPiece* pi = (spPiece*)pieces;
    std::vector<int8_t> possible_moves;

    auto check = [&possible_moves, this, pi](int8_t n) {
        if (pi[n]->team == 2) {
            possible_moves.push_back(n);
            return false;}
        if (pi[n]->team != team) {
            possible_moves.push_back(n);}
        return true;
    }; 

    for(int i = pos - 8; i >= 0; i -= 8) if (check(i)) break;
    for(int i = pos + 8; i <= 63; i += 8) if (check(i)) break;
    for(int i = pos - 1; (i + 1) % 8 > i % 8; i--) if (check(i)) break;
    for(int i = pos + 1; (i - 1) % 8 < i % 8; i++) if (check(i)) break;

    for(int i = pos - 7; i >= 0 && (i + 7) % 8 < i % 8; i -= 7) if (check(i)) break;
    for(int i = pos - 9; i >= 0 && (i + 9) % 8 > i % 8; i -= 9) if (check(i)) break;
    for(int i = pos + 7; i <= 63 && (i - 7) % 8 > i % 8; i += 7) if (check(i)) break;
    for(int i = pos + 9; i <= 63 && (i - 9) % 8 < i % 8; i += 9) if (check(i)) break;

    return possible_moves;
}

std::vector<int8_t> Bishop::possible_moves(spSprite pieces[]) {
    spPiece* pi = (spPiece*)pieces;
    std::vector<int8_t> possible_moves;

    auto check = [&possible_moves, this, pi](int8_t n) {
        if (pi[n]->team == 2) {
            possible_moves.push_back(n);
            return false;}
        if (pi[n]->team != team) {
            possible_moves.push_back(n);}
        return true;
    }; 

    for(int i = pos - 7; i >= 0 && (i + 7) % 8 < i % 8; i -= 7) if (check(i)) break;
    for(int i = pos - 9; i >= 0 && (i + 9) % 8 > i % 8; i -= 9) if (check(i)) break;
    for(int i = pos + 7; i <= 63 && (i - 7) % 8 > i % 8; i += 7) if (check(i)) break;
    for(int i = pos + 9; i <= 63 && (i - 9) % 8 < i % 8; i += 9) if (check(i)) break;

    return possible_moves;
}

std::vector<int8_t> Knight::possible_moves(spSprite pieces[]) {
    spPiece* pi = (spPiece*)pieces;
    std::vector<int8_t> possible_moves;

    if (pos - 16 >= 0) {
        if (pos % 8 - 1 >= 0 && pi[pos-17]->team != team) possible_moves.push_back(pos-17);
        if (pos % 8 + 1 <= 7 && pi[pos-15]->team != team) possible_moves.push_back(pos-15);
    }
    if (pos + 16 <= 63) {
        if (pos % 8 - 1 >= 0 && pi[pos+15]->team != team) possible_moves.push_back(pos+15);
        if (pos % 8 + 1 <= 7 && pi[pos+17]->team != team) possible_moves.push_back(pos+17);
    }
    if (pos % 8 - 2 >= 0) {
        if (pos - 8 >= 0 && pi[pos-10]->team != team) possible_moves.push_back(pos-10);
        if (pos + 8 <= 63 && pi[pos+6]->team != team) possible_moves.push_back(pos+6);
    }
    if (pos % 8 + 2 <= 7) {
        if (pos - 8 >= 0 && pi[pos-6]->team != team) possible_moves.push_back(pos-6);
        if (pos + 8 <= 63 && pi[pos+10]->team != team) possible_moves.push_back(pos+10);
    }

    return possible_moves;
}

std::vector<int8_t> Pawn::possible_moves(spSprite pieces[]) {
    spPiece* pi = (spPiece*)pieces;
    std::vector<int8_t> possible_moves;
    if (team == 0 && pos-8 >= 0) {
        if (pi[pos-8]->team == 2) {
            possible_moves.push_back(pos-8);
            if (pos / 8 == 6 && pi[pos-16]->team == 2) {
                possible_moves.push_back(pos-16);
            }
        }
        if (pos % 8 > 0 && pi[pos-9]->team != team && pi[pos-9]->team != 2) possible_moves.push_back(pos-9);
        if (pos % 8 < 7 && pi[pos-7]->team != team && pi[pos-7]->team != 2) possible_moves.push_back(pos-7);
    }

    else if (pos + 8 <= 63) {
        if (pi[pos+8]->team == 2) {
            possible_moves.push_back(pos+8);
            if (pos / 8 == 1 && pi[pos+16]->team == 2) {
                possible_moves.push_back(pos+16);
            }
        }
        if (pos % 8 > 0 && pi[pos+7]->team != team && pi[pos+7]->team != 2) possible_moves.push_back(pos+7);
        if (pos % 8 < 7 && pi[pos+9]->team != team && pi[pos+9]->team != 2) possible_moves.push_back(pos+9);
    }

    return possible_moves;
}





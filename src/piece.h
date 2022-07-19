#include "oxygine-framework.h";

using namespace oxygine;

class Piece : public Sprite
{
private:
public:
    Piece() {};
    int8_t pos;
    int8_t team;
    void highlight(Color col);
    virtual std::vector<int8_t> possible_moves(spSprite* pieces) {};
    ~Piece() {};

};

typedef intrusive_ptr<Piece> spPiece;

class King : virtual public Piece
{
public:
    King(int8_t p, int8_t t, Resources& gameResources);
    std::vector<int8_t> possible_moves(spSprite pieces[]);
   
};

class Queen : public Piece
{
public:
    Queen(int8_t p, int8_t t, Resources& gameResources);
    std::vector<int8_t> possible_moves(spSprite pieces[]);
};

class Bishop : public Piece
{
public:
    Bishop(int8_t p, int8_t t, Resources& gameResources);
    std::vector<int8_t> possible_moves(spSprite pieces[]);
};

class Knight : public Piece
{
public:
    Knight(int8_t p, int8_t t, Resources& gameResources);
    std::vector<int8_t> possible_moves(spSprite pieces[]);
};

class Rook : public Piece
{
public:
    Rook(int8_t p, int8_t t, Resources& gameResources);
    std::vector<int8_t> possible_moves(spSprite pieces[]);
};

class Pawn : public Piece
{
public:
    Pawn(int8_t p, int8_t t, Resources& gameResources);
    std::vector<int8_t> possible_moves(spSprite pieces[]);
};

class Empty : public Piece
{
public:
    Empty(int8_t p);
};


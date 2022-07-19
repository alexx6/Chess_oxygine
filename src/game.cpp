#include "oxygine-framework.h"
#include <functional>
#include <array>
#include "tile.h"
#include "piece.h"


using namespace oxygine;

Resources gameResources;

class Game: public Actor
{
private:
    int8_t board_state[64]  = { 7, 8, 9,  10, 11, 9,  8,  7,
                                12,12,12, 12, 12, 12, 12, 12,
                                0, 0, 0,  0,  0,  0,  0,  0,
                                0, 0, 0,  0,  0,  0,  0,  0,
                                0, 0, 0,  0,  0,  0,  0,  0,
                                0, 0, 0,  0,  0,  0,  0,  0,
                                6, 6, 6,  6,  6,  6,  6,  6,
                                1, 2, 3,  4,  5,  3,  2,  1};
    spPiece pieces[64];
    spTile tiles[64];
    spPiece selected = nullptr;
    int8_t turn = 0;
    std::vector<int8_t> possible_moves;

public:
    Game()
    {
        EventCallback cb = CLOSURE(this, &Game::OverOutClick);

        //Creating tiles
        for(int i = 0; i < 64; i++) {
            spTile tile = new Tile(i, gameResources);
            tiles[i] = tile;
            addChild(tile);
        }

        for(int i = 0; i < 64; i++) {
            spPiece piece;

            if (board_state[i] == 0) {
                piece = new Empty(i);
                addChild(piece);
                pieces[i] = piece;
                continue;
            }
            switch (board_state[i])
            {
            case 6:
                piece = new Pawn(i, 0, gameResources);
                break;
            case 12:
                piece = new Pawn(i, 1, gameResources);
                break;
            case 1:
                piece = new Rook(i, 0, gameResources);
                break;
            case 7:
                piece = new Rook(i, 1, gameResources);
                break;
            case 2:
                piece = new Knight(i, 0, gameResources);
                break;
            case 8:
                piece = new Knight(i, 1, gameResources);
                break;
            case 3:
                piece = new Bishop(i, 0, gameResources);
                break;
            case 9:
                piece = new Bishop(i, 1, gameResources);
                break;
            case 4:
                piece = new Queen(i, 0, gameResources);
                break;
            case 10:
                piece = new Queen(i, 1, gameResources);
                break;
            case 5:
                piece = new King(i, 0, gameResources);
                break;
            case 11:
                piece = new King(i, 1, gameResources);
                break;

            default:
                break;
            }
            
            piece->addEventListener(TouchEvent::OVER, cb);
            piece->addEventListener(TouchEvent::OUTX, cb);
            piece->addEventListener(TouchEvent::CLICK, cb);
      
            addChild(piece);
            pieces[i] = piece;
        }

        getStage()->addEventListener(TouchEvent::MOVE, CLOSURE(this, &Game::TileSelection));
        getStage()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Game::TileClick));

    }

    void OverOutClick(Event* e) {
        Piece* cur = (Piece*)e->currentTarget.get();
        
        if (turn != cur->team || selected == cur) return;

        if (e->type == TouchEvent::OVER) {
            cur->highlight(Color(0,100,0));
        }
        if (e->type == TouchEvent::OUTX) {
                cur->highlight(Color(0,0,0));
        }

        
        if (e->type == TouchEvent::CLICK) {

            if (selected) {
                selected->highlight(Color(0,0,0));
                tiles[selected->pos]->highlight(Color(0,0,0));
                for (int8_t a : possible_moves) {
                    tiles[a]->highlight(Color(0,0,0));
                }
                possible_moves.clear();
            }

            possible_moves = cur->possible_moves((spSprite*)pieces);

            for (int8_t a : possible_moves) {
                tiles[a]->highlight(Color(100,255,0));
            }
        
            tiles[cur->pos]->highlight(Color(0,0,100));
            selected = cur;
        }
        

    }

    void TileSelection (Event* e){
        for (auto t : tiles) {
            if (t->computeStageBounds().pointIn(((TouchEvent*)e)->localPosition)) {
                t->animateScale(0.9);
            }
            else {
                t->animateScale(1.);
            }
        }
    }

    void TileClick (Event* e)
    {
        spTile cur;

        for (int i = 0; i < 64; i++) {
            if (tiles[i]->computeStageBounds().pointIn(((TouchEvent*)e)->localPosition)) {
                for(auto a : possible_moves) {
                    if (a == i) {
                        MakeAMove(i);
                    }
                }
            }
        }
    }

    void MakeAMove (int8_t d) {
        selected->addTween(Sprite::TweenPosition(tiles[d]->getPosition()), 400);
        pieces[selected->pos] = new Empty(selected->pos);
        selected->pos = d;
        if (pieces[d]->team != 2) {
            spTweenQueue tweenQueue = new TweenQueue();
            tweenQueue->add(Sprite::TweenAlpha(0), 200);
            pieces[d]->addTween(tweenQueue);
            tweenQueue->detachWhenDone();
        }
        pieces[d] = selected;
        selected = nullptr;
        turn = 1 - turn;
        possible_moves.clear();
        for(auto t : tiles) {
            t->highlight(Color(0,0,0));
        }
        for(auto t : pieces) {
            t->highlight(Color(0,0,0));
        }
    }
};




typedef oxygine::intrusive_ptr<Game> spGame;

void init()
{
    gameResources.loadXML("res.xml");
    spGame game = new Game;
    getStage()->addChild(game);
}


void destroy()
{
    gameResources.free();
}

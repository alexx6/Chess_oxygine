#include "oxygine-framework.h";
using namespace oxygine;

class Tile : public Sprite
{
    private:
        int8_t pos;
    
    public:
        Tile(int8_t p, Resources& gameResources); 
        void highlight(Color col);
        void animateScale(float scale);

};

typedef intrusive_ptr<Tile> spTile;
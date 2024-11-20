#include "axmol.h"

// #include "TcpClient.h"
using namespace ax;
class TcpClient;
class MovementComp;
struct CDat;
class Actor
{
public:
    Actor();
    Actor(CDat a);
    ~Actor();
    Node* sprite = nullptr;
    Vec2 mPosition;
    Vec2 mTarget;

    void update(float delta);
    void setPos(Vec2 pos) { mPosition = pos; }
    int id;
    int img_num;
    void getsprite(Actor* a);
    Vec2 getPosition() { return mPosition; }
    float mTimer = 0;
    void asdf();
    MovementComp* mMoveComp = nullptr;
};

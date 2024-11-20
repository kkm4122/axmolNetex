
#include"Actor.h"
#include"MovementComp.h"
#include"MainScene.h"


Actor::Actor() {}

Actor::Actor(CDat a)
{
    setPos(Vec2(a.Posx, a.Posy));
    img_num = a.img_num;
    id      = a.id;
    getsprite(this);
    sprite->setPosition(this->mPosition);
}

Actor::~Actor()
{
    delete mMoveComp;
}

void Actor::update(float delta)
{
    if (mMoveComp)
    {
        mMoveComp->update(delta);

        sprite->setPosition(this->mPosition);
    }
}

void Actor::getsprite(Actor* a)
{
    switch (a->img_num)
    {
    case 0:
        a->sprite = Sprite::create("CloseSelected.png"sv);
        // a->sprite->retain();
        break;
    case 1:
        a->sprite = Sprite::create("cow.png"sv);
        // a->sprite->retain();
        break;
    case 2:
        a->sprite = Sprite::create("farmer.png"sv);
        // a->sprite->retain();
        break;

    default:
        break;
    }
}

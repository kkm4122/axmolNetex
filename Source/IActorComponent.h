#pragma once
#include"axmol.h"
class Actor;
//struct ActorMessage;

class IActorComponent
{
public:
	IActorComponent(Actor* actor) : mActor(actor) {}
    virtual ~IActorComponent() {}
	virtual void update(float delta) = 0;
    //virtual void MessageProc(ActorMessage& msg){};

    std::string_view getName() { return mCompName; }

    bool move = false;
    bool idle = true;
    
 public:
    std::string_view mCompName;
	Actor* mActor;
    bool isEnabled = true;
};


#pragma once
#include "IActorComponent.h"
#include "MainScene.h"


class MovementComp : public IActorComponent
{
public:
    const static std::string COMPONENT_NAME;

    bool IsTargetForce = false;

public:
    MovementComp(Actor* actor);
    ~MovementComp();

    void update(float delta);
    //virtual void MessageProc(ActorMessage& msg)override;

    void Do_TargetForce();
   
    ax::Vec2 Vec2DNormalized(ax::Vec2 target);
    double length(ax::Vec2 v1, ax::Vec2 v2);

    
    //타겟 관련 함수
    bool IsArrived();
    void setTarget(ax::Vec2 target);
    void SetTargetList(std::list<Vec2>& list);
    void PushTargetList(Vec2 v1);
    void CheckTargetList();

    double getTimeToReachTarget();
    // 경과시간 체크 루틴 ~~~~~~~~~~~~~~~~~~~~~
    void Start경과시간() { m경과시간 = 0.0; }
    void Stop경과시간() { m경과시간 = -1.0; }

    double getSpeed() const { return mSpeed; }
    void setSpeed(float speed) { mSpeed = speed; }
    ax::Vec2 getVelocity() const { return mVelocity; }

public:
    float mSpeed     = 50.f;
    double m경과시간 = -1.0;

    
    ax::Vec2 mCurrentFrameMovement;

public:
    void _setTarget(ax::Vec2 target);

    ax::Vec2 mWorldTargetPos;
    ax::Vec2 mVelocity;
    std::list<Vec2> mTargetList;
};

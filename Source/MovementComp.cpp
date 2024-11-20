//#include "pch.h"
#include "MovementComp.h"
#include "MainScene.h"
#include "Actor.h"
//#include "ActorMessage.h"
//#include "UnitComp.h"

const std::string MovementComp::COMPONENT_NAME = "MovementComp";

MovementComp::MovementComp(Actor* actor) : IActorComponent(actor)
{
    mCompName        = COMPONENT_NAME;
    actor->mMoveComp = this;
}

MovementComp::~MovementComp() {}

void MovementComp::update(float delta)
{
    if (!isEnabled)
        return;

    mVelocity = ax::Vec2(0, 0);

    if (m경과시간 != -1.0)
        m경과시간 += delta;

    // 아래에 넣을것
    CheckTargetList();
    if (IsTargetForce)
        Do_TargetForce();
    mVelocity.normalize();

    mCurrentFrameMovement = mVelocity * delta * getSpeed();
    mActor->mPosition += mCurrentFrameMovement;

    if (mCurrentFrameMovement.length() > 0.01f)
    {
        idle = false;
        move = true;
    }
    else
    {
        idle = true;
        move = false;
    }

}

//void MovementComp::MessageProc(ActorMessage& msg)
//{
//    switch (msg.msgType)
//    {
//    case ActorMessage::MoveToTarget:
//    {
//        AMsgData_Vec2* data = (AMsgData_Vec2*)msg.data;
//        setTarget(data->pos);
//    }
//    case ActorMessage::AddToNextTarget:
//    {
//        PushTargetList(((AMsgData_Vec2*)msg.data)->pos);
//    }
//    break;
//    }
//}

void MovementComp::Do_TargetForce()
{
    if (IsArrived())
    {
        IsTargetForce = false;
    }
    else
        mVelocity += getSpeed() * Vec2DNormalized(mActor->mTarget);
}

bool MovementComp::IsArrived()
{
    if (1.0 > length(mWorldTargetPos, mActor->mPosition))
    {
        // mActor->mBehavior = Idle;
        return true;
    }
    return false;
}

void MovementComp::setTarget(ax::Vec2 target)
{
    mTargetList.clear();
    _setTarget(target);
}

void MovementComp::SetTargetList(std::list<Vec2>& list)
{
    mTargetList = list;
}

void MovementComp::PushTargetList(Vec2 v1)
{
    mTargetList.push_back(v1);
}

void MovementComp::CheckTargetList()
{
    if (mTargetList.size() < 1)
        return;

    if (!IsTargetForce)
    {
        Vec2 pos = mTargetList.front();
        mTargetList.pop_front();
        _setTarget(pos);
    }
}

double MovementComp::getTimeToReachTarget()
{
    double dist = length(mActor->getPosition(), mActor->mTarget);
    double T    = dist / mSpeed;
    return T;
}

ax::Vec2 MovementComp::Vec2DNormalized(ax::Vec2 target)
{
    ax::Vec2 vec = target;

    double vector_length = vec.length();

    if (vector_length > 2)
    {
        vec.x /= vector_length;
        vec.y /= vector_length;
    }

    return vec;
}

double MovementComp::length(ax::Vec2 v1, ax::Vec2 v2)
{
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;

    return sqrt(dx * dx + dy * dy);
}

void MovementComp::_setTarget(ax::Vec2 target)
{
    IsTargetForce   = true;
    mWorldTargetPos = target;
    mActor->mTarget = mWorldTargetPos - mActor->getPosition();
}

/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmol.dev/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainScene.h"
#include <iostream>
#include "TcpClient.h"
#include<time.h>
using namespace ax;
//extern enum DT;
//extern struct CDat;
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
        "MainScene.cpp\n");
}

MainScene::~MainScene()
{
    mPlayerActor->~Actor();
    client->SendDelete();
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    srand((unsigned int)time(NULL));
    

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
        AX_CALLBACK_1(MainScene::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
        float y = safeOrigin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // Some templates (uncomment what you  need)
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = AX_CALLBACK_2(MainScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = AX_CALLBACK_2(MainScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = AX_CALLBACK_2(MainScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    //auto mouseListener           = EventListenerMouse::create();
    //mouseListener->onMouseMove   = AX_CALLBACK_1(MainScene::onMouseMove, this);
    //mouseListener->onMouseUp     = AX_CALLBACK_1(MainScene::onMouseUp, this);
    //mouseListener->onMouseDown   = AX_CALLBACK_1(MainScene::onMouseDown, this);
    //mouseListener->onMouseScroll = AX_CALLBACK_1(MainScene::onMouseScroll, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    auto keyboardListener           = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed  = AX_CALLBACK_2(MainScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = AX_CALLBACK_2(MainScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 11);



    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(
            Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    //// add "HelloWorld" splash screen"
    //sprite = Sprite::create("HelloWorld.png"sv);
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //    auto drawNode = DrawNode::create();
    //    drawNode->setPosition(Vec2(0, 0));
    //    addChild(drawNode);

    //    drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size, Color4B::BLUE);
    //}

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();
    client = new TcpClient("127.0.0.1", 20202);

    
    //172.30.1.26
    //127.0.0.1
    InitsyncServer();
    return true;
}


void MainScene::onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesBegan detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesMoved detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesEnded detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onMouseDown(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseDown detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseUp detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseMove(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseMove detected, X:%f  Y:%f", e->getCursorX(), e->getCursorY());
}

void MainScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseScroll detected, X:%f  Y:%f", e->getScrollX(), e->getScrollY());
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    //AXLOG("onKeyPressed, keycode: %d", static_cast<int>(code));
    Vec2 pos = mPlayerActor->sprite->getPosition();
    
    switch (code)
    {
    
    case ax::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        pos.x -= 5;
        mPlayerActor->sprite->setPosition(pos);
        client->dat.x = pos.x;
        client->dat.y = pos.y;

        client->SendPos();
        break;
    case ax::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        pos.x += 5;
        mPlayerActor->sprite->setPosition(pos);
        client->dat.x = pos.x;
        client->dat.y = pos.y;

        client->SendPos();
        break;
    case ax::EventKeyboard::KeyCode::KEY_UP_ARROW:
        pos.y += 5;
        mPlayerActor->sprite->setPosition(pos);
        client->dat.x = pos.x;
        client->dat.y = pos.y;

        client->SendPos();
        break;
    case ax::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        pos.y -= 5;
        mPlayerActor->sprite->setPosition(pos);
        client->dat.x = pos.x;
        client->dat.y = pos.y;

        client->SendPos();
        break;
    
    default:
        break;
    }
    
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    
}

void MainScene::update(float delta)
{
    //Netdt+=delta;
    switch (_gameState)
    {
    case GameState::init:
    {
        _gameState = GameState::update;
        break;
    }

    case GameState::update:
    {
        timeval timeout = {0, 10};
        //Vec2 pos = sprite->getPosition();
        bool checksocket = false;
        bool senddat     = false;
        if (client->Select(timeout))
        {

            if (!client->RecvDataS())
            {  // 리시브 실패
                break;
            }
            else  // mactorlist actor로 수정요함
            {
                char* b;
                while (b = client->GetPacket())//패킷이 없을때까지 실행
                {
                    bool Go = false;
                    int a   = 0;

                    DT sendType;
                    memcpy(&sendType, b + a, sizeof(sendType));
                    a += sizeof(sendType);
                    CDat as;
                    memcpy(&as, b + a, sizeof(CDat));
                    if (as.id == client->dat.id)
                    {
                        continue;
                    }
                    switch (sendType)
                    {
                    case DT::REQUESTACTOR:

                        for (auto Data : mActorList)
                        {
                            if (Data == nullptr)
                            {
                                auto actor = new Actor(as);
                                Data       = actor;
                                this->addChild(actor->sprite);
                                Go = true;
                            }
                        }
                        if (!Go)
                            pushActorD(as);

                        senddat = true;
                        //}

                        break;
                    case DT::POS:
                        for (auto Data : mActorList)
                        {

                            if (Data->id == as.id)
                            {
                                Data->sprite->setPosition(as.x, as.y);
                            }
                        }
                        break;
                    case DT::SOCKETDATA:

                        for (auto Data : mActorList)
                        {
                            if (Data->id == as.id)
                            {
                                Go = true;
                                break;
                            }
                        }

                        if (!Go)
                            pushActorD(as);

                        break;
                    case DT::DELETEACTOR:

                        for (auto Data : mActorList)
                        {
                            if (Data->id == as.id)
                            {
                                Data->sprite->removeFromParent();
                                Data = nullptr;

                            }
                        }
                        break;
                    default:
                        break;
                    }
                }
                client->endRecv();

                // sprite->setPosition(client->dat.x,client->dat.y);
            }
        }
        
        if (senddat)
        {
            client->SendData();
            AXLOG("dat %d : SENDDATA\n", client->dat.id);
            
        }
        break;
    }

    case GameState::pause:
    {
        /////////////////////////////
        // Add your codes below...like....
        //
        // anyPauseStuff()

        break;
    }

    case GameState::menu1:
    {    /////////////////////////////
        // Add your codes below...like....
        // 
        // UpdateMenu1();
        break;
    }

    case GameState::menu2:
    {    /////////////////////////////
        // Add your codes below...like....
        // 
        // UpdateMenu2();
        break;
    }

    case GameState::end:
    {    /////////////////////////////
        // Add your codes below...like....
        // 
        // CleanUpMyCrap();
        menuCloseCallback(this);
        break;
    }

    } //switch
}

void MainScene::menuCloseCallback(ax::Object* sender)
{
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

     // EventCustom customEndEvent("game_scene_close_event");
     //_eventDispatcher->dispatchEvent(&customEndEvent);
}

// 초기 서버 동기화
void MainScene::InitsyncServer()
{
   
        auto actor = new Actor();
        actor->setPos(Vec2((rand() % 150) + 200, (rand() % 150) + 200));
        actor->img_num      = rand() % 3;
        client->dat.img_num = actor->img_num;
        client->dat.x       = actor->Pos.x;
        client->dat.y       = actor->Pos.y;
        actor->id           = client->dat.id;
        actor->getsprite(actor);
        actor->sprite->setPosition(actor->Pos);
        this->addChild(actor->sprite);
        mActorList.push_back(actor);
        //요청 액터들1
        mPlayerActor = actor;
        client->SendReqActor();
        AXLOG("dat %d : ReqActor\n", client->dat.id);
        
    
}

void MainScene::pushActorD(CDat a)
{
    auto actor = new Actor();
    actor->setPos(Vec2(a.x, a.y));
    actor->img_num      = a.img_num;
    
    actor->id           = a.id;
    actor->getsprite(actor);
    actor->sprite->setPosition(actor->Pos);
    this->addChild(actor->sprite);
    mActorList.push_back(actor);
    // 요청 액터들1
}

Actor::Actor() {}

Actor::Actor(CDat a)
{
    setPos(Vec2(a.x, a.y));
    img_num = a.img_num;
    id      = a.id;
    getsprite(this);
    sprite->setPosition(this->Pos);
}

Actor::~Actor()
{
    
}

void Actor::getsprite(Actor* a)
{
    switch (a->img_num)
    {
    case 0:
        a->sprite = Sprite::create("CloseSelected.png"sv);
        //a->sprite->retain();
        break;
    case 1:
        a->sprite = Sprite::create("cow.png"sv);
        //a->sprite->retain();
        break;
    case 2:
        a->sprite = Sprite::create("farmer.png"sv);
        //a->sprite->retain();
        break;

    default:
        break;
    }
}

#include "BackButton.h"

#include "../PageManager.h"
#include "../utils/config.h"
#include "../utils/helper.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

using namespace cocos2d;

void BackButton::onEnter()
{
    Layer::onEnter();

    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setSwallowsTouches(false);
    setTouchEnabledWithFixedPriority(-100);
}

void BackButton::onExit()
{
    setTouchEnabled(false);
    
    Node::onExit();
}

bool BackButton::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    const auto bb = btn->getBoundingBox();
    const auto mid = Point(bb.getMidX(), bb.getMidY());
    const auto loc = convertTouchToNodeSpace(touch);
    return (loc - mid).getLength() <= 120;
}

void BackButton::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    PageManager::shared().scrollUp();
    SimpleAudioEngine::getInstance()->playEffect("click.mp3");
}

bool BackButton::init()
{
    if (!Layer::init()) {
        return false;
    }

    btn = Sprite::createWithSpriteFrameName("arrow.png");
    btn->setAnchorPoint({0, 0});
    btn->setScale(0.8 * config::getScaleFactor());
    btn->setColor(Color3B::BLACK);
    addChild(btn);

    setContentSize(btn->getContentSize() * btn->getScale());

    return true;
}
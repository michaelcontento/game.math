#include "BackButton.h"

#include "../PageManager.h"
#include "../utils/config.h"

using namespace cocos2d;

void BackButton::onEnter()
{
    Node::onEnter();

    Director::getInstance()
        ->getTouchDispatcher()
        ->addTargetedDelegate(this, 0, true);
}

void BackButton::onExit()
{
    Director::getInstance()
        ->getTouchDispatcher()
        ->removeDelegate(this);

    Node::onExit();
}

bool BackButton::ccTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    const auto bb = btn->getBoundingBox();
    const auto mid = Point(bb.getMidX(), bb.getMidY());
    const auto loc = convertTouchToNodeSpace(touch);
    return (loc - mid).getLength() <= 120;
}

void BackButton::ccTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    PageManager::shared().scrollUp();
}

bool BackButton::init()
{
    if (!Node::init()) {
        return false;
    }

    btn = Sprite::createWithSpriteFrameName("arrow.png");
    btn->setAnchorPoint({0, 0});
    btn->setScale(0.5 * config::getScaleFactor() * config::getScaleFactorHeightMagic());
    btn->setColor(Color3B::BLACK);
    addChild(btn);

    setContentSize(btn->getContentSize() * btn->getScale());

    return true;
}
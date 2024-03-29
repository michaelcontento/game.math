#include "AnswerButton.h"

#include <avalon/utils/platform.h>
#include "../utils/fonts.h"
#include "../utils/config.h"
#include "../utils/color.h"
#include "../utils/QuestionString.h"
#include "../pages/Page.h"
#include "../pages/GamePage.h"
#include "../PageManager.h"

using namespace cocos2d;

void AnswerButton::onEnter()
{
    Layer::onEnter();

    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setSwallowsTouches(false);
    setTouchEnabledWithFixedPriority(-100);
}

void AnswerButton::onExit()
{
    setTouchEnabled(false);
    
    Layer::onExit();
}

bool AnswerButton::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    return !hasBeenUsed && isAnswerVisible();
}

bool AnswerButton::isAnswerVisible() const
{
    return question->isVisible();
}

void AnswerButton::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (!enabled || !onTouchBegan(touch, event)) {
        return;
    }

    static const auto padding = config::getAnswerButtonPadding();
    const auto bb = Rect(0, padding * -0.5, getContentSize().width, getContentSize().height + padding);
    const auto loc = convertTouchToNodeSpace(touch);
    if (!bb.containsPoint(loc)) {
        return;
    }
    
    hasBeenUsed = true;
    
    indicatorLabelLeft->stopAllActions();
    indicatorLabelRight->stopAllActions();

    const auto posY = indicatorLabelRight->getPositionY();
    indicatorLabelLeft->runAction(EaseOut::create(MoveTo::create(0.15, {endPosLeft, posY}), 3));
    indicatorLabelRight->runAction(EaseOut::create(MoveTo::create(0.15, {endPosRight, posY}), 3));

    if (isRight) {
#if AVALON_PLATFORM_IS_TIZEN
        indicatorLabelLeft->setString("=");
        indicatorLabelRight->setString("=");
#else
        indicatorLabelLeft->setString("✓");
        indicatorLabelRight->setString("✓");
#endif
        page->answeredRight();
    } else {
#if AVALON_PLATFORM_IS_TIZEN
        indicatorLabelLeft->setString("X");
        indicatorLabelRight->setString("X");
#else
        indicatorLabelLeft->setString("✗");
        indicatorLabelRight->setString("✗");
#endif
        page->answeredWrong();
    }
}

AnswerButton* AnswerButton::create(GamePage& page, const cocos2d::Color3B& color)
{
    AnswerButton* pRet = new AnswerButton();
    if (pRet && pRet->init(page, color)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool AnswerButton::init(GamePage& page, const cocos2d::Color3B& color)
{
    if (!Layer::init()) {
        return false;
    }

    this->page = &page;

    setContentSize(config::getAnswerButtonSize());
    addBackground(color);
    addLabels();

    question = QuestionString::create(82);
    question->setPosition(Point(getContentSize() / 2));
    question->setHeight(getContentSize().height * 0.95);
    addChild(question);

    return true;
}

void AnswerButton::setAnswerString(const std::string& text)
{
    hasBeenUsed = false;
    indicatorLabelLeft->setPositionX(startPosLeft);
    indicatorLabelRight->setPositionX(startPosRight);

    question->setText(text);
}

void AnswerButton::setIsRight(const bool flag)
{
    isRight = flag;
}

bool AnswerButton::isRightAnswer() const
{
    return isRight;
}

void AnswerButton::fadeOutAnswer(const float duration)
{
    if (!isAnswerVisible()) {
        return;
    }

    question->stopAllActions();
    question->runAction(FadeOut::create(duration));

    // do not call stopAllActions() here because we can currently be in
    // the "slide in" animation!
    indicatorLabelLeft->runAction(FadeOut::create(duration));
    indicatorLabelRight->runAction(FadeOut::create(duration));
}

void AnswerButton::hideAnswer()
{
    question->stopAllActions();
    question->setOpacity(0);

    indicatorLabelLeft->stopAllActions();
    indicatorLabelLeft->setOpacity(0);
    indicatorLabelRight->stopAllActions();
    indicatorLabelRight->setOpacity(0);
}

void AnswerButton::showAnswer()
{
    question->stopAllActions();
    question->setOpacity(255);

    indicatorLabelLeft->stopAllActions();
    indicatorLabelLeft->setOpacity(255);
    indicatorLabelRight->stopAllActions();
    indicatorLabelRight->setOpacity(255);
}

void AnswerButton::addBackground(const cocos2d::Color3B& color)
{
    auto draw = DrawNode::create();
    addChild(draw);

    auto size = getContentSize();
    Point verts[] = {{0, 0}, {0, size.height}, {size.width, size.height}, {size.width, 0}};

    draw->drawPolygon(verts, 4, color::toRGBA(color), 0, {});
}

void AnswerButton::addLabels()
{
    indicatorLabelLeft = fonts::createLight("", 76);
    indicatorLabelLeft->setColor(Color3B::WHITE);
    indicatorLabelLeft->setAnchorPoint({0.5, 0.5});
    indicatorLabelLeft->setPositionX(startPosLeft);
    indicatorLabelLeft->setPositionY(getContentSize().height / 2);
    addChild(indicatorLabelLeft);

    indicatorLabelRight = fonts::createLight("", 76);
    indicatorLabelRight->setColor(indicatorLabelLeft->getColor());
    indicatorLabelRight->setAnchorPoint(indicatorLabelLeft->getAnchorPoint());
    indicatorLabelRight->setPositionX(startPosRight);
    indicatorLabelRight->setPositionY(indicatorLabelLeft->getPositionY());
    addChild(indicatorLabelRight);
}

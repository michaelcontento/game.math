#ifndef MATH_CATEGORYPAGE_H
#define MATH_CATEGORYPAGE_H

#include <unordered_set>
#include "cocos2d.h"
#include "Page.h"

class LevelButton;

class CategoryPage : public Page
{
public:
    CREATE_FUNC(CategoryPage);
    bool init() override;
    void onTouch(cocos2d::Touch* touch, cocos2d::Event* event) override;

private:
    std::unordered_set<LevelButton*> levelButtons {};
    void addHeadlineLabel();
    void addLevelButtons();
};

#endif // MATH_CATEGORYPAGE_H
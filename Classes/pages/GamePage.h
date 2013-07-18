#ifndef MATH_GAMEPAGE_H
#define MATH_GAMEPAGE_H

#include <vector>
#include <unordered_set>
#include "cocos2d.h"
#include "Page.h"
#include "../puzzle/Question.h"

class AnswerButton;
class GameTimer;
class HintButton;

class GamePage : public Page
{
public:
    static GamePage* create(void) = delete;
    static GamePage* create(const Page& parentPage);
    bool init(const Page& parentPage);

    bool allQuestionsAnswered() const;
    void answeredWrong();
    void answeredRight();
    
    void timeover();
    bool isTimeover() const;
    bool isStarted() const;

    bool isVisible() const override;

private:
    static constexpr unsigned short questionAmount = 10;
    const Page* parentPage = nullptr;
    GameTimer* timer = nullptr;
    HintButton* hints = nullptr;
    cocos2d::Node* progressBar = nullptr;
    cocos2d::LabelTTF* question = nullptr;
    std::vector<AnswerButton*> answerButtons {};
    std::unordered_set<puzzle::Question> questions {};
    bool timeoverAlreadyHandled = false;
    cocos2d::Node* starContainer = nullptr;
    std::deque<cocos2d::Sprite*> stars {};
    static constexpr int maxStars = 3;
    bool acceptAnswers = true;

    void addTimer();
    void addStars();
    void addHints();
    void addQuestion();
    void addAnswerButtons();
    void addProgressbar();

    cocos2d::Sprite* createStar() const;
    void handleAllQuestionsAnswered();
    void handleTimeover();
    void handleNoMoreStars();

    void markQuestionAnswered();
    void updateProgressbar();
    void setNextQuestion();
    void configureAndAlignQuestionLabel(cocos2d::LabelTTF& label) const;
    cocos2d::Color3B getNextAnswerButtonColor(const cocos2d::Color3B& color) const;
};

#endif // MATH_GAMEPAGE_H
#ifndef MATH_PUZZLE_GENERATOR_H
#define MATH_PUZZLE_GENERATOR_H

#include <string>
#include <unordered_set>
#include <random>
#include <utility>
#include "Question.h"
#include "Operator.h"
#include "NumberRange.h"

namespace puzzle {

class Generator
{
public:
    std::string question;
    std::string answer;
    std::unordered_set<Operator> operators;
    std::unordered_set<NumberRange> ranges;

    Generator(std::string question, std::string answer, std::unordered_set<Operator> operators, std::unordered_set<NumberRange> ranges)
    : question(question), answer(answer), operators(operators), ranges(ranges)
    {}

    Question generate();

private:
    static const std::string tokenDelimiterLeft;
    static const std::string tokenDelimiterRight;
    static const std::string tokenNumber;
    static const std::string tokenOperator;
    static std::random_device randDevice;

    std::pair<std::string, int> generateQuestionAndAnswer();
    int getNumber(const Operator& op);
    void throwIfContainsUnhandledTokens(const std::string& checkStr) const;
    std::pair<int, int> getWrongAnswers(const int rightAnswer);
};

} // namespace puzzle

#endif // MATH_PUZZLE_GENERATOR_H

/**
 * [addition-01]
 * Q = 11 + 11
 * A = 11
 *
 * [addition-02]
 * Q = 11 + ? = 11
 * A = 11
 *
 * [addition-03]
 * Q = 11
 * A = 11 + 11
 *
 * [addition-04]
 * Q = Smallest?
 * A = 11 + 11
 *
 * [addition-05]
 * Q = 11 + 11 + 11
 * A = 11
 *
 * [addition-06]
 * Q = 11 + 11
 * A = 11 + 11
 *
 * [addition-07]
 * Q = Largest?
 * A = 11 + 11
 *
 * [addition-08]
 * Q = MIXED 11
 * A = MIXED 11
 * 
 * !! MULT-04a: 11 x (11 +- 11)
 *
 * Generator g1 {""{number} {operator} {number}", "{number}"};
 * Generator g2 {"{number} {operator} {hidden}", "{hidden}"};
 * Generator g3 {"{answer}", "{number} {operator} {number}"};
 * Generator g4 {"numberest?", "{number} {operator} {number}"}; // ?
 * Generator g5 {"{number} {operator} {number} {operator} {number}", "{number}"};
 * Generator g6 {"{number} {operator} {number}", "{number} {operator} {number}"}; // ?
 * Generator g7 {"Largest?", "{number} {operator} {number}"}; // ?
 * GeneratorMixer g8 {g1, g2, g3, g4, g5, g6, g7};
 */
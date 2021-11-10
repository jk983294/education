#ifndef EDUCATION_DATA_H
#define EDUCATION_DATA_H

#include <cmath>
#include <sstream>
#include <string>

enum OpType { Plus = 0, Minus, Prod, Div };

char ToString(OpType type) {
    switch (type) {
        case Minus:
            return '-';
        case Prod:
            return '*';
        case Div:
            return '/';
        case Plus:
        default:
            return '+';
    }
}

struct PlusEntry {
    int x{0};
    int y{0};
    int result{0};
    bool hasCalcError{false};
    OpType type{OpType::Plus};

    PlusEntry() = default;

    std::string get_question_expr() {
        std::stringstream ss;
        ss << x << " " << ToString(type) << " " << y << " = ";
        return ss.str();
    }

    std::string get_answer_expr() { return get_question_expr() + std::to_string(result); }

    bool calc() {
        switch (type) {
            case Minus:
                result = x - y;
                break;
            case Prod:
                result = x * y;
                break;
            case Div:
                result = x / y;
                if (y == 0 || std::abs(x) % std::abs(y) != 0) hasCalcError = true;
                break;
            case Plus:
            default:
                result = x + y;
                break;
        }
        return hasCalcError;
    }

    bool operator==(PlusEntry const& rhs) const { return x == rhs.x && y == rhs.y && type == rhs.type; }
    bool operator<(PlusEntry const& rhs) const {
        if (x < rhs.x) return true;
        if (rhs.x < x) return false;
        if (y < rhs.y) return true;
        if (rhs.y < y) return false;
        if (type < rhs.type) return true;
        if (rhs.type < type) return false;
        return false;
    }
};

#endif

#pragma once

#include <memory>
#include "date.h"
#include "test_runner.h"


using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    Or,
    And,
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event)const = 0;
};

class DateComparisonNode :public Node {
public:
    DateComparisonNode(Comparison& comp, const Date& date);
    bool Evaluate(const Date& date, const string& event)const override;
private:
    const Comparison comp_;
    const Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison& comp, const string& event);
    bool Evaluate(const Date& d, const string& e)const override;
private:
    const Comparison comp_;
    const string event_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation new_op, shared_ptr<Node> new_left, shared_ptr<Node> new_right);
    bool Evaluate(const Date& date, const string& event)const override;
private:
    shared_ptr<Node> left_, right_;
    LogicalOperation operation_;
};

class EmptyNode :public Node {
public:
    bool Evaluate(const Date& d, const string& e)const override;
};
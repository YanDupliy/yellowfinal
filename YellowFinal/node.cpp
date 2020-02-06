#include "node.h"

using namespace std;

DateComparisonNode::DateComparisonNode(Comparison& comp, const Date& date) : comp_(comp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	switch (comp_) {
	case Comparison::Equal:
		return date == this->date_;
	case Comparison::Greater:
		return date > this->date_;
	case Comparison::GreaterOrEqual:
		return date >= this->date_;
	case Comparison::NotEqual:
		return date != this->date_;
	case Comparison::Less:
		return date < this->date_;
	case Comparison::LessOrEqual:
		return date <= this->date_;
	default:
		throw runtime_error("Such comparison doesn't exist for date comparison");
	}
}

EventComparisonNode::EventComparisonNode(Comparison& comp, const string& event) : comp_(comp), event_(event) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event)const {
	switch (comp_) {
	case Comparison::Equal:
		return event == this->event_;
	case Comparison::NotEqual:
		return event != this->event_;
	default:
		throw runtime_error("Such comparison doesn't exist for event comparison");
	}
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation operation, shared_ptr<Node> left, shared_ptr<Node> right) :
	operation_(operation), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event)const {
	switch (operation_) {
	case LogicalOperation::And:
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
	case LogicalOperation::Or:
		return left_->Evaluate(date, event) || right_->Evaluate(date, event);
	default:
		throw runtime_error("Such logical operation doesn't exist");
	}
}

bool EmptyNode::Evaluate(const Date& d, const string& e)const {
	return true;
}
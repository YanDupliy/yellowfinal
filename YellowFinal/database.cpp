#include "database.h"

#include <iostream>
#include "date.h"

using namespace std;

void Database::Add(const Date& date, const string& event) {
	storage[date].insert(event);
	if (storage[date].size() > storage2[date].size()) {
		storage2[date].push_back(event);
	}
};

set<string> Database::Find(const Date& date) const {
	if (storage.count(date) > 0) {
		return storage.at(date);
	}
	else {
		return {};
	}
};

void Database::Print(ostream& s) const {
	for (const auto& item : storage2) {
		for (const string& event : item.second) {
			s << item.first << " " << event << endl;
		}
	}
};

string Database::Last(const Date& date) const {
	auto it = storage2.upper_bound(date);
	if (it != storage2.begin()) {
		--it;
	}
	else {
		return "No entries";
	}
	return it->first.str() + ' ' + it->second.back();
}
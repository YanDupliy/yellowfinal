#pragma once

#include <set>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "date.h"

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);

	set<string> Find(const Date& date) const;

	void Print(ostream& s) const;

	string Last(const Date& date) const;

	template<typename T>
	vector<string> FindIf(T predicate)const {
		vector<string> output;
		for (auto it = storage2.begin(); it != storage2.end(); ++it) {
			for (auto itset = it->second.begin(); itset != it->second.end(); ++itset) {
				if (predicate(it->first, *itset)) {
					string s;
					s = it->first.str()+ ' ' + *itset;
					output.push_back(s);					
				}
			}
		}
		return output;
	}

	template<typename T>
	int RemoveIf(T predicate) {
		int counter = 0;
		vector<Date> keys;
		
		for (auto it = storage.begin(); it != storage.end(); ++it) {
			
			for (auto itset = it->second.begin(); itset != it->second.end();) {
				if (predicate(it->first, *itset)) {
					itset = it->second.erase(itset);
					counter++;
				}
				else {
					itset++;
				}
			}
			
			if (it->second.empty()) {
				keys.push_back(it->first);
			}

			set<string> check = it->second;
			auto del = stable_partition(storage2[it->first].begin(), storage2[it->first].end(), [check](const string& s2) 
			{
					bool res = false;
					for (auto s : check) {
						if (s2 == s) { 
							res = true;
							break;
						}
					}
				return res;
			});
			
			storage2[it->first].erase(del, storage2[it->first].end());
		}
		
		for (const auto& key : keys) {
			storage.erase(key);
			storage2.erase(key);
		}
		return counter;
	}
private:
	map<Date, set<string>> storage;
	map<Date, vector<string>> storage2;
};
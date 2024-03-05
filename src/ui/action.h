#pragma once

#include "functional"
#include "vector"

class Action : std::vector<std::function<void()>> {
	public:
		void add(const std::function<void()>& f) {
			this->push_back(f);
		}

		void invoke() {
			for (auto f : *this) {
				f();
			}
		}
};

template <typename T>
class Action1 : std::vector<std::function<void(T)>> {
	public:
		void add(const std::function<void(T)>& f) {
			this->push_back(f);
		}

		void invoke() {
			for (auto f : *this) {
				f();
			}
		}
};
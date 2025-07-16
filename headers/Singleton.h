#pragma once

template <typename T>

class Singleton {
public :
	static T& getInstance() {
		if (!instance) {
			instance = new T();
		}
		return *instance;
	}
	Singleton(const Singleton& other) = delete;
	Singleton& operator = (const Singleton& other) = delete;

private :
	Singleton(){}
	~Singleton(){}
	static T* instance;
};

template <typename T>
T* Singleton <T> ::instance = nullptr;




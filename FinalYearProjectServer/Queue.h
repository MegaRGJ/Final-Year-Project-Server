#pragma once
#include <queue>
#include <mutex>
#include <list>

template<typename T> class Queue
{
private:
	std::mutex mutex;
	std::queue<T> queue;

public:
	void push(T var)
	{
		std::unique_lock<std::mutex> lock(mutex);
		queue.push(var);
	}

	T pop()
	{
		std::unique_lock<std::mutex> lock(mutex);
		T var = std::move(queue.front());
		queue.pop();
		return var;
	}
	
	std::vector<T> popAll()
	{
		std::unique_lock<std::mutex> lock(mutex);

		size_t size = queue.size();

		std::vector<T> vector;
		vector.reserve(size);

		for (size_t i = 0; i < size; i++)
		{
			vector.push_back(queue.front());
			queue.pop();
		}
		
		return vector;
	}

	bool isEmpty()
	{
		std::unique_lock<std::mutex> lock(mutex);
		return queue.empty();
	}
};
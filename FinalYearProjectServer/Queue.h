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
		T var;
		std::swap(var, queue.front());
		queue.pop();
		return var;
	}
	
	T[]  popAll()
	{
		std::unique_lock<std::mutex> lock(mutex);
		int size = queue.size();
		T[size] arr;
		
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = queue.front;
			queue.pop();
		}

		return T;
	}

	)
	bool empty()
	{
		std::unique_lock<std::mutex> lock(mutex);
		return queue.empty();
	}
};
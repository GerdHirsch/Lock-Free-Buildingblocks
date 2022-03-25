/*
 * Single Producer Single Consumer wait-free Queue
 * From accu 2017 Lock-free programming with modern C++ Timur Doumler
 * there is one more element needed than NumElements
 */

#include <array>
#include <atomic>
#include <cstddef>

template<class ElementType, std::size_t MaxElements>
class SPSCWaitFreeQueue{
public:
	bool push(ElementType const &newElement){
		auto oldWritePos = writePosition.load(std::memory_order_relaxed);
		auto newWritePos = getPositionAfter(oldWritePos);

		// Queue full
		if(newWritePos == readPosition.load(std::memory_order_relaxed))
			return false;

		ringBuffer[oldWritePos] = newElement;

		writePosition.store(newWritePos, std::memory_order_release);
		return true;
	}

	bool pop(ElementType& returnedElement){
		auto oldWritePos = writePosition.load(std::memory_order_acquire);
		auto oldReadPos  = readPosition.load(std::memory_order_relaxed);

		//Queue empty
		if(oldWritePos == oldReadPos)
			return false;

		returnedElement = std::move(ringBuffer[oldReadPos]);

		readPosition.store(getPositionAfter(oldReadPos), std::memory_order_relaxed);
		return true;

	}

private:
	static constexpr std::size_t getPositionAfter(std::size_t position){
		return ++position == ringBufferSize ? 0 : position;
	}
	std::atomic<size_t> writePosition{};
	std::atomic<size_t> readPosition{};
	static constexpr std::size_t ringBufferSize = MaxElements + 1;
	std::array<ElementType, ringBufferSize> ringBuffer;
};

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void demoWaitFreeQueueSingleThreaded(){
	cout << __PRETTY_FUNCTION__ << endl;
	constexpr std::size_t NumElements = 5;

	SPSCWaitFreeQueue<std::size_t, NumElements> queue;

	for(std::size_t i=1; queue.push(i); ++i)
		;

	std::size_t element{};
	while(queue.pop(element)){
		cout << "element: " << element << endl;
	}
}

void demoWaitFreeQueueMultiThreaded(){
	using namespace std::chrono_literals;

	cout << __PRETTY_FUNCTION__ << endl;

	constexpr std::size_t NumElements = 50;
	SPSCWaitFreeQueue<std::size_t, NumElements> queue;
	std::atomic<bool> stopProducer{false};
	std::atomic<bool> stopConsumer{false};

	auto consumerTask = [&queue, &stopConsumer]{
		std::size_t element{};
		while(!stopConsumer.load(std::memory_order_relaxed)){
			if(queue.pop(element))
				cout << "element: " << element << endl;
			else
				cout << "queue empty" << endl;
		}
	};

	auto producerTask = [&queue, &stopProducer, &stopConsumer]{
		for(std::size_t i=1; true; ++i){
			if(!queue.push(i)){
//				cout << "queue full" << endl;
				std::this_thread::yield();
				queue.push(i); // retry
			}
			if(stopProducer.load(std::memory_order_relaxed)){
				stopConsumer.store(true, std::memory_order_relaxed);
				return;
			}
		}
	};
	std::thread consumerThread(consumerTask);
	std::thread producerThread(producerTask);

	std::this_thread::sleep_for(5ms);
	stopProducer.store(true, std::memory_order_relaxed);

	producerThread.join();
	consumerThread.join();
}

/*
 * Single Producer Single Consumer wait-free Queue
 * From accu 2017 Lock-free programming with modern C++ Timur Doumler
 * there is one more element needed than NumElements
 */


#include <BasicBuildingBlocks/SPSCWaitFreeQueue.h>
#include <BasicBuildingBlocks/CacheLineCell.h>


#include <atomic>
#include <cstddef>

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void demoWaitFreeQueueSingleThreaded(){
	cout << __PRETTY_FUNCTION__ << endl;
	static constexpr std::size_t elementsPerCacheLine = 4;
	using ElementType = std::size_t;

	using QueueElementType = CacheLineCell<ElementType, elementsPerCacheLine>;
	constexpr std::size_t NumElements = 5;
	SPSCWaitFreeQueue<QueueElementType, NumElements> queue;

	for(std::size_t i=1; queue.push(i); ++i)
		;

	QueueElementType element{};
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

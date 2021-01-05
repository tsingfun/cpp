/*
 * thread.cpp
 *
 *  Created on: 2019年11月29日
 *      Author: qpzhou
 */
#include <thread>
#include <functional>
#include <iostream>
#include "threadpool.hpp"
#include "isolated_threadpool.hpp"

void test(int a) {
	std::cout << a << std::endl;
}

void callback() {
	std::cout << std::this_thread::get_id() << "   callback" << std::endl;
}

int main() {
	// 函数
	std::function<void(int)> aa = test;
	aa(123);

	// 线程
	std::thread t1(callback);
	t1.join();

	std::thread t2([] {std::cout << "thread 2" << std::endl; });
	t2.join();

	std::threadpool pool;
	//pool.init(10);
	pool.commit([]{
		std::cout << "thread pool run." << std::endl;
	});

	Env env;
	std::isolated_threadpool iso_pool(&env, 10);
	iso_pool.commit([]{
		std::cout << "isolated thread pool run." << std::endl;
	});
	
	return 0;
}

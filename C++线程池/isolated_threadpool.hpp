#ifndef ISOLATED_THREAD_POOL_H
#define ISOLATED_THREAD_POOL_H

/**
 * 上下文隔离的线程池
 * 1、可以为每一个线程指定独立的上下文，从而实现无锁。
 * 2、由于上下文环境不同，回调任务必须指定线程ID委托给原线程执行。
*/
#include <vector>
#include <queue>
#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include "utility/Macros.h"
#include "utility/StringUtils.hpp"
#include "platform/os.h"
#include "utility/Stopwatch.hpp"

class Env {};
class Context{
public:
	void set_id(int id) { id_ = id; }
private:
	int id_;
};

namespace std {
static size_t g_task_queue_;
static size_t g_task_dequeue_;
static size_t g_task_total_ms;

using Task = function<void()>;
class TaskThread {
public:
	TaskThread(Env* env, int id) : env_(env), id_(id) {
		name_ = utility::StringFormat("isolated_thread#%d", id_);
		OS::SetCurrentThreadName(name_);
		context_.reset(new Context());
		context_->set_id(id_);
	}
	~TaskThread(){}

	void Schedule(Task task) {
		unique_lock<mutex> lock {lock_};
		tasks_.emplace(std::move(task));
		task_cv_.notify_one();
	}

	void Start() {
		thread_ = make_unique<thread>([=]{
			Run();
		});
		cout << name_ << " started." << endl;
	}

	void Quit() {
		run_ = false;
		task_cv_.notify_all();
		if (thread_->joinable())
			thread_->join();
		thread_ = nullptr;
	}
private:
	// 处理任务
	void Run() {
		while (run_) {
			Task task; //获取一个待执行的任务
			{
				unique_lock<mutex> lock{lock_};
				task_cv_.wait(lock, [this]{
					return !run_ || !tasks_.empty();
				}); //wait直到队列中有任务
				if (!run_ && tasks_.empty())
					return;
				task = move(tasks_.front()); //先进先出
				tasks_.pop();
				g_task_dequeue_++;
			}

			utility::Stopwatch sw;
			sw.Start();
			//context_->StartCycle(begin.ToEpochDelta().ToMilliseconds());

			// 执行任务
			task(); //context_->Evaluate(task);

			sw.Stop();
			g_task_total_ms += (size_t)sw.GetElapsedMilliseconds();
			//context_->EndCycle();
		}

		context_.reset();
		cout << name_ << " quit." << endl;
	}

	Env* const env_;
	unique_ptr<Context> context_;

	int id_;
	string name_;

	unique_ptr<thread> thread_;	//实体线程
	atomic<bool> run_{ true };	//线程池是否执行
	queue<Task> tasks_;			//任务队列
	mutex lock_;				//同步
	condition_variable task_cv_;//条件阻塞

	DISALLOW_COPY_AND_ASSIGN(TaskThread);
};

class isolated_threadpool {
	vector<unique_ptr<TaskThread>> threads_;
	int AllocateThread() {
		int thread_slot = cur_thread_;
		cur_thread_ = (cur_thread_ + 1) % threads_.size();
		return thread_slot;
	}
	int cur_thread_;
public:
	isolated_threadpool(Env* env, unsigned short size) {
		if (size <= 0) {
			cout << "isolated threadpool size must > 0 !!!" << endl;
			return;
		}
		threads_.resize(size);
		cur_thread_ = 0;
		for (int i = 0; i < size; i++) {
			threads_[i] = make_unique<TaskThread>(env, i);
			threads_[i]->Start();
		}
	}

	~isolated_threadpool() {
		// 所有线程退出
		for (size_t i = 0; i < threads_.size(); i++) {
			threads_[i]->Quit();
			threads_[i] = nullptr;
		}
		cur_thread_ = 0;
		threads_.resize(0);
	}

	// 提交一个任务，可以指定线程执行，否则自动分配
	void commit(Task task, int thread_id = -1) {
		if (thread_id > (int)threads_.size() - 1) {
			cout << "Invalid thread id:" << thread_id << endl;
			return;
		}
		if (thread_id == -1)
			thread_id = AllocateThread();
		threads_[thread_id]->Schedule(task);
		g_task_queue_++;
	}
};
}

#endif // end of ISOLATED_THREAD_POOL_H

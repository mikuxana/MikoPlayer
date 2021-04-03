//
// Created by root on 2021/4/2.
//

#ifndef MIKOPLAYER_SAFE_QUEUE_H
#define MIKOPLAYER_SAFE_QUEUE_H

#include <pthread.h>
#include <queue>

using std::queue;

namespace miko {
    template<class _T>class safe_queue {
    // 函数指针 形如
//    typedef void (*callback)(_T&)
        using callback = void (*)(_T&);

    private:
        queue<_T> q;

        pthread_mutex_t mutex;
        pthread_cond_t cond;
        callback cb = nullptr;


    public:
        safe_queue() {
            pthread_mutex_init(&mutex, nullptr);
            pthread_cond_init(&cond, nullptr);
        }


        ~safe_queue() {
            pthread_mutex_destroy(&mutex);
            pthread_cond_destroy(&cond);
        }


        void push(_T value) {
            pthread_mutex_lock(&mutex);
            q.push(value);
            // 通知有新数据到达
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
        }

        int pop(_T &value) {
            int res = 0;
            pthread_mutex_lock(&mutex);
            while (q.empty()) {
                pthread_cond_wait(&cond, &mutex);
            }

            if (!q.empty()) {
                value = q.front();
                q.pop();
                res = 1;
            }

            pthread_mutex_unlock(&mutex);
            return res;
        }


        void clear() {
            pthread_mutex_lock(&mutex);
            while (q.empty()) {
                _T &value = q.front();
                // 释放value, value可能是指针
                // 使用函数指针回调
                if (this -> cb)
                    this->cb(value);

                q.pop();
            }
            pthread_mutex_unlock(&mutex);
        }

        void set_callback(callback cb){
            this->cb = cb;
        }
    };
}


#endif MIKOPLAYER_SAFE_QUEUE_H

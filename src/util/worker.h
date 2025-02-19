#ifndef CSYNTH_WORKER_H
#define CSYNTH_WORKER_H

#include <pthread.h>

#include "./error.h"
#include "./logger.h"

typedef void (*worker_job)(void *context);

/** @brief See worker_create. */
typedef struct Worker
{
    /** @brief Function to be called by the worker thread. */
    worker_job job;
    /** @brief Additional context passed into callback. */
    void *context;
    /** @brief Mutex for synchronizing access to the context. */
    pthread_mutex_t mutex;
    /** @brief Condition variable for signaling the worker thread. */
    pthread_cond_t cond;
    /** @brief Worker thread handle. */
    pthread_t thread;
} Worker;

void worker_run(Worker *worker, worker_job job, void *context)
{
    pthread_mutex_lock(&worker->mutex);
    worker->job = job;
    worker->context = context;
    pthread_cond_signal(&worker->cond);
    pthread_mutex_unlock(&worker->mutex);
}

static void worker_stop(__attribute__((unused)) void *unused) {}

static void *worker_thread(void *worker_)
{
    Worker *worker = (Worker *)worker_;
    while (1)
    {
        pthread_mutex_lock(&worker->mutex);
        while (worker->job == NULL)
        {
            pthread_cond_wait(&worker->cond, &worker->mutex);
        }
        if (worker->job == worker_stop)
        {
            break;
        }
        worker_job job = worker->job;
        void *context = worker->context;
        worker->job = NULL;
        pthread_mutex_unlock(&worker->mutex);
        job(context);
    }
    return NULL;
}

/**
 * @brief Initialize a worker that calls a callback on separate thread.
 */
csError worker_init(Worker *worker)
{
    int result = pthread_mutex_init(&worker->mutex, NULL);
    if (result != 0)
    {
        log_error("pthread_mutex_init failed: %s", strerror(result));
        return error_type(csErrorThread);
    }
    result = pthread_cond_init(&worker->cond, NULL);
    if (result != 0)
    {
        log_error("pthread_cond_init failed: %s", strerror(result));
        return error_type(csErrorThread);
    }
    result = pthread_create(&worker->thread, NULL, worker_thread, worker);
    if (result != 0)
    {
        log_error("pthread_create failed: %s", strerror(result));
        return error_type(csErrorThread);
    }
    return csErrorNone;
}

void worker_free(Worker *worker)
{
    pthread_mutex_lock(&worker->mutex);
    worker->job = worker_stop;
    pthread_cond_signal(&worker->cond);
    pthread_mutex_unlock(&worker->mutex);
    pthread_mutex_destroy(&worker->mutex);
    pthread_cond_destroy(&worker->cond);
    pthread_join(worker->thread, NULL);
}

#endif // CSYNTH_WORKER_H

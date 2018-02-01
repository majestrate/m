#ifndef LLARP_THREADPOOL_H
#define LLARP_THREADPOOL_H
#include <llarp/ev.h>
#ifdef __cplusplus
extern "C" {
#endif

struct llarp_threadpool;

struct llarp_threadpool *llarp_init_threadpool(int workers);
void llarp_free_threadpool(struct llarp_threadpool **tp);

typedef void (*llarp_thread_work_func)(void *);

/** job to be done in worker thread */
struct llarp_thread_job {
  /**
      called async after work is executed
   */
  struct llarp_ev_caller *caller;
  void *data;

  /** user data to pass to work function */
  void *user;
  /** called in threadpool worker thread */
  llarp_thread_work_func work;
};

void llarp_threadpool_queue_job(struct llarp_threadpool *tp,
                                struct llarp_thread_job j);

void llarp_threadpool_start(struct llarp_threadpool *tp);
void llarp_threadpool_join(struct llarp_threadpool *tp);

#ifdef __cplusplus
}
#endif

#endif
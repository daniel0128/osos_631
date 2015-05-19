# Non-busy-timer-sleep

remain old timer_sleep function(a busy sleep).

use semaphore to implement non-busy-sleep

maintain a list and a node:

static struct list timer_wait_list;

struct timer_wait_node{

  struct semaphore sem;
  
  struct list_elem elem;
  
  struct thread *t;
  
};

add a new field in thread to record finish time: finish

how to sleep?

void timer_non_busy_sleep(int microSecounds)

compute a wake up time:

  t->finish = timer_get_timestamp() + microSecounds;
  
  put a timer_wait_node(say twn) back to the timer wait list
  
  semaphore down twn and it will sleep

how to wake up?

  wake_up function:
 
  go through the timer_wait_list and find the thread which should wake up by comparing the finish time and current time. 

  If current time is later--->the thread should wake

where to wake up?

  timer_interrupt?
  
  thread_tick?
  
->schedule?
  
    

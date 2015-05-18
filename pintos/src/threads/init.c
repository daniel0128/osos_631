
#include <debug.h>
#include <random.h>
#include <stdbool.h>
#include "stdio.h"
#include <stdint.h>
#include <string.h>

#include "../devices/gpio.h"
#include "../devices/framebuffer.h"
#include "../devices/serial.h"
#include "../devices/timer.h"
#include "../devices/video.h"
#include "interrupt.h"
#include "init.h"
#include "palloc.h"
#include "malloc.h"
#include "synch.h"
#include "thread.h"
#include "vaddr.h"

/* -ul: Maximum number of pages to put into palloc's user pool. */
static size_t user_page_limit = SIZE_MAX;

/* Tasks for the Threads. */
static struct semaphore task_sem;

static void hello_test(void *);

struct wait_node {
  struct lock mutex;
  struct condition cv;
  bool done;
};

static struct wait_node sync_node;

static void many_1(void *);
static void many_2(void *);
static void many_3(void *);
static void many_4(void *);
static void many_5(void *);
static void many_6(void *);


/*
 * kernel.c
 *
 *  Created on: Oct 22, 2014
 *      Author: jcyescas
 */

static void test_swi_interrupt() {
  unsigned short green = 0x7E0;
  SetForeColour(green);
  generate_swi_interrupt(); // Function defined in interrupts.s
}


/* Initializes the Operating System. The interruptions have to be disabled at entrance.
*
*  - Sets interruptions
*  - Sets the periodic timer
*  - Set the thread functionality
*/
void init() {

  /* Initializes ourselves as a thread so we can use locks,
    then enable console locking. */
  thread_init();

  /* Initializes the frame buffer and console. */
  framebuffer_init();
  serial_init();
  video_init();

  printf("\nOsOs Kernel Initializing");

  /* Initialize memory system. */
  palloc_init (user_page_limit);
  malloc_init ();

  /* Initializes the Interrupt System. */
  interrupts_init();
  timer_init();

//  thread_create("First Test", PRI_MAX, &first_test, NULL);


  /* Starts preemptive thread scheduling by enabling interrupts. */


  timer_msleep(5000000);
  printf("\nFinish booting.");

  /* Initialize the task_sem to coordinate the main thread with workers */
    printf("\nthread will be start");

  sema_init(&task_sem, 0);

  thread_create("Many 1", PRI_MAX, &many_1, NULL);
    thread_start();
//  thread_create("Many 2", PRI_MAX, &many_2, NULL);
//  thread_create("Many 3", PRI_MAX, &many_3, NULL);
//  thread_create("Many 4", PRI_MAX, &many_4, NULL);
//  thread_create("Many 5", PRI_MAX, &many_5, NULL);
//  thread_create("Many 6", PRI_MAX, &many_6, NULL);

  sema_down(&task_sem);

  printf("\nAll done.");
  thread_exit ();
}
static void many_1(void *aux){
    timer_non_busy_sleep(15000000);
    int i;
    for(i=0;i<100;i++){
        printf("====11111111111111=====\n");
    }
}

static void many_2(void *aux){
    int i;
    for(i=0;i<100;i++){
        printf("====22222222222222=====\n");
    }
}static void many_3(void *aux){
    int i;
    for(i=0;i<100;i++){
        printf("====33333333333333=====\n");
    }
}static void many_4(void *aux){
    int i;
    for(i=0;i<100;i++){
        printf("====44444444444444=====\n");
    }
}static void many_5(void *aux){
    int i;
    for(i=0;i<100;i++){
        printf("====55555555555555=====\n");
    }
}static void many_6(void *aux){
    int i;
    for(i=0;i<10;i++){
        printf("====66666666666666=====\n");
        timer_non_busy_sleep(5000000);
    }
}



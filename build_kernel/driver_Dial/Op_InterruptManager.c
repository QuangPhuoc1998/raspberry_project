#include "Op_InterruptManager.h"
#include "Mid_DialControl.h"

static struct task_struct *etx_thread;
int thread_function(void *pv);

#define TIMEOUT (1)    //milliseconds

static struct timer_list etx_timer;

void timer_callback(struct timer_list * data)
{
    /* do your timer stuff here */
    Mid_DialHandler();
    /*
       Re-enable timer. Because this function will be called only first time. 
       If we re-enable this will work like periodic timer. 
    */
    mod_timer(&etx_timer, jiffies + msecs_to_jiffies(TIMEOUT));
}

uint8_t Op_InterruptManagerInit(void)
{
    uint8_t ret = 1;
    etx_thread = kthread_create(thread_function,NULL,"Sensor Thread");
    if(etx_thread) 
    {
        wake_up_process(etx_thread);
        ret = 0;
    } 
    else 
    {
        pr_err("Cannot create kthread\n");
    }

    timer_setup(&etx_timer, timer_callback, 0);
    mod_timer(&etx_timer, jiffies + msecs_to_jiffies(TIMEOUT));

    return ret;
}
void Op_InterruptManagerDeinit(void)
{
    del_timer(&etx_timer);
    kthread_stop(etx_thread);
}

void ProcessMain(void);

int thread_function(void *pv)
{
    msleep(1000);
    while(!kthread_should_stop())
    {
        msleep(1000);
        ProcessMain();
    }
    return 0;
}
void ProcessMain(void)
{

}

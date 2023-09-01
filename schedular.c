#include "schedular.h"
#include "CAN.h"

/* Scheduler function */
void scheduler(void)
{
    int i;
    while (true)
    {
      for ( i = 0; i < NUM_TASKS; i++)
      {
        if (tasks[i].ready && value == tasks[i].id)
        {
          tasks[i].func();
        }
      }
        /* Find highest priority ready task
        int highest_priority = -1;
        int highest_priority_task = -1;
        for (i = 0; i < NUM_TASKS; i++)
        {
            if (tasks[i].ready && tasks[i].periodicity > highest_priority)
            {
                highest_priority = tasks[i].periodicity;
                highest_priority_task = i;
            }
        }
        
         Run the highest priority task
        if (highest_priority_task >= 0)
        {
            tasks[highest_priority_task].func();
            //tasks[highest_priority_task].last_executed = time(NULL);
             Task is not ready until its period expires 
            tasks[highest_priority_task].ready = false;
        }
        
         Check if any tasks are ready to be run again
        for (i = 0; i < NUM_TASKS; i++)
        {
            //if (time(NULL) - tasks[i].last_executed >= tasks[i].period)
            {
            //    tasks[i].ready = true;
            }
        }*/
    }
}
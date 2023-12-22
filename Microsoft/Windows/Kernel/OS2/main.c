/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                              uC/OS-II
*                                            EXAMPLE CODE
*
* Filename : main.c
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_mem.h>
#include  <os.h>

#include  "app_cfg.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK  StartupTaskStk[APP_CFG_STARTUP_TASK_STK_SIZE];
#define TASK_STACKSIZE      2048

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void task (void* p_arg);
//static void task2 (void* p_arg);
//static void task3(void* p_arg);
//static void task4(void* p_arg);
//static void task5(void* p_arg);
static  void  StartupTask (void  *p_arg);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*
* Notes       : none
*********************************************************************************************************
*/

int  main (void)
{
#if OS_TASK_NAME_EN > 0u
    CPU_INT08U  os_err;
#endif


    CPU_IntInit();

    Mem_Init();                                                 /* Initialize Memory Managment Module                   */
    CPU_IntDis();                                               /* Disable all Interrupts                               */
    CPU_Init();                                                 /* Initialize the uC/CPU services                       */

    /*Initialize Output File*/
    OutFileInit();
    /*Input File*/
    InputFile();


    /*Dynamic Create the Stack size*/
    Task_STK = malloc(TASK_NUMBER * sizeof(int*));

    /*for each pointer, allocate storage for an array of ints*/
    int n;
    for (n = 0; n < TASK_NUMBER; n++) {
        Task_STK[n] = malloc(TASK_STACKSIZE * sizeof(int));
    }

    OSInit();                                              /* Initialize uC/OS-II                                  */
    /*Create Task Set*/

    for (n = 0; n < TASK_NUMBER; n++)
    {
        OSTaskCreateExt(task,                                 /*Create the task1*/
            &TaskParameter[n],
            &Task_STK[n][TASK_STACKSIZE - 1],
            TaskParameter[n].TaskPriority,
            TaskParameter[n].TaskID,
            &Task_STK[n][0],
            TASK_STACKSIZE,
            &TaskParameter[n],
            (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    }

    //OSTaskCreateExt(task1,                                 /*Create the task1*/
    //    &TaskParameter[0],
    //    &Task_STK[0][TASK_STACKSIZE - 1],
    //    TaskParameter[0].TaskPriority,
    //    TaskParameter[0].TaskID,
    //    &Task_STK[0][0],
    //    TASK_STACKSIZE,
    //    &TaskParameter[0],
    //    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    //OSTaskCreateExt(task2,                                 /*Create the task2*/
    //    &TaskParameter[1],
    //    &Task_STK[1][TASK_STACKSIZE - 1],
    //    TaskParameter[1].TaskPriority,
    //    TaskParameter[1].TaskID,
    //    &Task_STK[1][0],
    //    TASK_STACKSIZE,
    //    &TaskParameter[1],
    //    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    //OSTaskCreateExt(task3,                                 /*Create the task2*/
    //    &TaskParameter[2],
    //    &Task_STK[2][TASK_STACKSIZE - 1],
    //    TaskParameter[2].TaskPriority,
    //    TaskParameter[2].TaskID,
    //    &Task_STK[2][0],
    //    TASK_STACKSIZE,
    //    &TaskParameter[2],
    //    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    //OSTaskCreateExt(task4,                                 /*Create the task1*/
    //    &TaskParameter[3],
    //    &Task_STK[3][TASK_STACKSIZE - 1],
    //    TaskParameter[3].TaskPriority,
    //    TaskParameter[3].TaskID,
    //    &Task_STK[3][0],
    //    TASK_STACKSIZE,
    //    &TaskParameter[3],
    //    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    //OSTaskCreateExt(task5,                                 /*Create the task1*/
    //    &TaskParameter[4],
    //    &Task_STK[4][TASK_STACKSIZE - 1],
    //    TaskParameter[4].TaskPriority,
    //    TaskParameter[4].TaskID,
    //    &Task_STK[4][0],
    //    TASK_STACKSIZE,
    //    &TaskParameter[4],
    //    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    /*
    OSTaskCreateExt( StartupTask,                               /* Create the startup task                              
                     0,
                    &StartupTaskStk[APP_CFG_STARTUP_TASK_STK_SIZE - 1u],
                     APP_CFG_STARTUP_TASK_PRIO,
                     APP_CFG_STARTUP_TASK_PRIO,
                    &StartupTaskStk[0u],
                     APP_CFG_STARTUP_TASK_STK_SIZE,
                     0u,
                    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if OS_TASK_NAME_EN > 0u
    OSTaskNameSet(         APP_CFG_STARTUP_TASK_PRIO,
                  (INT8U *)"Startup Task",
                           &os_err);
#endif
    */
    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)   */

    while (DEF_ON) {                                            /* Should Never Get Here.                               */
        ;
    }
}




void task(void* p_arg) {
    task_para_set* task_data;
    task_data = p_arg;
    while (1)
    {        
        
        OSTimeDly(task_data->TaskPeriodic);
    }
}

//void task2(void* p_arg) {
//    task_para_set* task_data;
//    task_data = p_arg;
//    while (1)
//    {
//        
//        OSTimeDly(task_data->TaskPeriodic);
//    }
//}
//
//void task3(void* p_arg) {
//    task_para_set* task_data;
//    task_data = p_arg;
//    while (1)
//    {
//
//        OSTimeDly(task_data->TaskPeriodic);
//    }
//}
//
//void task4(void* p_arg) {
//    task_para_set* task_data;
//    task_data = p_arg;
//    while (1)
//    {
//
//        OSTimeDly(task_data->TaskPeriodic);
//    }
//}
//
//void task5(void* p_arg) {
//    task_para_set* task_data;
//    task_data = p_arg;
//    while (1)
//    {
//
//        OSTimeDly(task_data->TaskPeriodic);
//    }
//}


/*
*********************************************************************************************************
*                                            STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'StartupTask()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  StartupTask (void *p_arg)
{
   (void)p_arg;

    OS_TRACE_INIT();                                            /* Initialize the uC/OS-II Trace recorder               */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
    
    APP_TRACE_DBG(("uCOS-III is Running...\n\r"));

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        OSTimeDlyHMSM(0u, 0u, 1u, 0u);
		APP_TRACE_DBG(("Time: %d\n\r", OSTimeGet()));
    }
}


#include "common.h"
#include "string.h"

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

// Define me if you want debugging, remove me for release!
//#define configASSERT( x )     if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

static __inline__ void dumbdelay_ms(uint32_t ms );

static void taskLed(void *pvParameters) {
    for(;;){
        GPIOC_PCOR |= (1 << 5);
        vTaskDelay(100);
        GPIOC_PSOR |= (1 << 5);
        vTaskDelay(100);
    }
}

/**
** @brief		Entry point to program
*/
int main( void )
{
    int idx;

    // Initialize on board LED
    PORTC_PCR5 = PORT_PCR_MUX( 0x1 );	// LED is on PC5 (pin 13), config as GPIO (alt = 1)
    GPIOC_PDDR = ( 1 << 5 );			// make this an output pin
    GPIOC_PCOR = ( 1 << 5 );			// start with LED off

    /* Configure pin as output */
    /* GPIOC_PDDR: PDD|=0x20 */
    GPIOC_PDDR |= GPIO_PDDR_PDD(0x20);

    /* Set initialization value */
    /* GPIOC_PDOR: PDO&=~0x20 */
    GPIOC_PDOR &= (uint32_t)~(uint32_t)(GPIO_PDOR_PDO(0x20));

    /* Initialization of Port Control register */
    /* PORTC_PCR5: ISF=0,MUX=1 */
    PORTC_PCR5 = (uint32_t)((PORTC_PCR5 & (uint32_t)~(uint32_t)(
            PORT_PCR_ISF_MASK |
            PORT_PCR_MUX(0x06)
    )) | (uint32_t)(
            PORT_PCR_MUX(0x01)
    ));

    // Flash a little startup sequence, this isn't necessary at all, just nice
    // to see a familiar sign before things start breaking!
    for ( idx = 0; idx < 3; idx ++ )
    {
        // Set LED
        GPIOC_PSOR = ( 1 << 5 );
        dumbdelay_ms( 50 );

        // Clear LED
        GPIOC_PCOR = ( 1 << 5 );
        dumbdelay_ms( 50 );
    }

    // Create a task
    xTaskCreate( taskLed,		            	// The task's callback function
                 "LED_ON",						// Task name
                 configMINIMAL_STACK_SIZE,		// We can specify different stack sizes for each task? Cool!
                 NULL,							// Parameter to pass to the callback function, we have nothhing to pass..
                 0,								// Priority, this is our only task so.. lets just use 0
                 NULL );						// We could put a pointer to a task handle here which will be filled in when the task is created

    // Start the tasks and timer running, this should never return freertos will
    // branch directly into the idle task.
    vTaskStartScheduler();

    for(;;)
    {
        // We should never get here, so just sit in this loop forever...
        // Probably better to flash a error sequence here so we know something
        // has gone horribly wrong...
    }
}

/**
 * @brief		Delay using a loop.
 * @param[in]	ms		Delay in ms.
 */
static __inline__ void dumbdelay_ms( const uint32_t ms )
{
	uint32_t loops;
	uint32_t index;

	// Calc delay in clock cycles
	loops = ms * ( (uint32_t)mcg_clk_hz / 10000 );

	// Dumb delay
	for ( index = 0; index < loops; index++ );
}

/*!
 * \brief	Called by the system when a hard fault is encountered.
 * 			Flashes our led at 20hz indefinitely.
 */
void HardFault_Handler()
{

}

/**
 * @brief		If enabled, this hook will be called in case of a stack
 * 				overflow.
 * @param[in]	pxTask		Task handle.
 * @param[in]	pcTaskName	Pointer to task name.
 */
void vApplicationStackOverflowHook( xTaskHandle pxTask, char *pcTaskName )
{

	/* This will get called if a stack overflow is detected during the context
	 switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
	 problems within nested interrupts, but only do this for debug purposes as
	 it will increase the context switch time. */
	(void)pxTask;
	(void)pcTaskName;
	taskDISABLE_INTERRUPTS();
	/* Write your code here ... */
	for(;;) {}
}

/**
 * @brief		If enabled, this hook will be called by the RTOS for every
 *				tick increment.
 */
void vApplicationTickHook( void )
{


	/* Called for every RTOS tick. */
	/* Write your code here ... */
}

/**
 * @brief		If enabled, this hook will be called when the RTOS is idle.
 *				This might be a good place to go into low power mode.
 */
void vApplicationIdleHook( void )
{

	/* Called whenever the RTOS is idle (from the IDLE task).
	 Here would be a good place to put the CPU into low power mode. */
	/* Write your code here ... */
}

/**
 * @brief		If enabled, the RTOS will call this hook in case memory
 *				allocation failed.
 */
void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	 free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	 internally by FreeRTOS API functions that create tasks, queues, software
	 timers, and semaphores.  The size of the FreeRTOS heap is set by the
	 configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	taskDISABLE_INTERRUPTS();
	/* Write your code here ... */
	for(;;) {}
}

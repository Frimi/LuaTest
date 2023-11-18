
#ifndef LUAPROJECTCONFIG_H_
#define LUAPROJECTCONFIG_H_


//The pointer size in this project is not size_t (16 Bit).
#define  luaPointerSize_t uint32_t

//#define DONT_USE_LUA_HEAP_MANAGEMENT_FUNCTIONS

#ifdef DONT_USE_LUA_HEAP_MANAGEMENT_FUNCTIONS
//The FreeRTOS functions shall be used.

//extern void *pvPortMalloc( size_t xWantedSize );
//extern void vPortFree( void *pv );

extern void *malloc( size_t xWantedSize );
extern void free( void *pv );

#define luaMallocFunction(xWantedSize) malloc(xWantedSize)
#define luaFreeFunction(pv) free(pv)
#else

//This project has to tasks which execute a lua interpreter. Therefore the lua memory calls
//must be protected.

extern void vTaskSuspendAll(void);
extern short xTaskResumeAll(void);

#define LUA_MEM_ENTER_CRITICAL_SECTION() vTaskSuspendAll()
#define LUA_MEM_LEAVE_CRITICAL_SECTION() xTaskResumeAll()
#endif

#define LUA_HEAP_SIZE (2 * 13000)


#endif /* LUAPROJECTCONFIG_H_ */

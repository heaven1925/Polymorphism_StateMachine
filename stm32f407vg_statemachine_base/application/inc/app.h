/*******************************************************************************
  * @file    app.h
  * @author	 Atakan ERTEKiN
  * @version V1.0.0
  * @date	 	 06.03.2023 - ...
  * @rev     V1.0.0
  * @brief	 State Machine Embedded Software Programming Application
********************************************************************************/

#ifndef __APP_H__
#define	__APP_H__

#include <stdlib.h>
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "stm32f4xx.h"

/*
* State Machine Main Types
*/
typedef enum
{
	STATE_A , 
	STATE_B ,  
	STATE_C
}State_Type;


/*
* State Machine Virtual Function Queues
*/
enum
{
		STATE_A_MAIN = 0,
	 /* Other sub states can be added here */
};

enum
{
		STATE_B_MAIN = 0,
	 /* Other sub states can be added here */
};

enum
{
		STATE_C_MAIN = 0,
	 /* Other sub states can be added here */
};


/*
* State Machine Time Parameters
*/
typedef struct
{
	uint32_t prevTime;
	uint32_t nowTime;
	float		 deltaTime;
}StateTime_Type;



/*
* State Machine Main Class
*/
typedef struct
{
	struct OpsVTable const* vptr;
}MainState_Type;

/*
* State Machine Ops
*/
struct OpsVTable {
	
	void (*StateA_MAIN) (MainState_Type const * const param);
	void (*StateB_MAIN) (MainState_Type const * const param);
	void (*StateC_MAIN) (MainState_Type const * const param);
	
};

/*
* Ops Definitions 
*/
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
static inline void MainState_RunA_Vcall(MainState_Type const * const param)
{
	(*param->vptr->StateA_MAIN)(param);
}

static inline void MainState_RunB_Vcall(MainState_Type const * const param)
{
	(*param->vptr->StateB_MAIN)(param);
}

static inline void MainState_RunC_Vcall(MainState_Type const * const param)
{
	(*param->vptr->StateC_MAIN)(param);
}
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


/*
* Main State Machine Constructor Function
*/
void MainState_CTOR( MainState_Type* const param	);


/*
* Polymorphism Function Decleration
*/
void	System_StateA_MAIN( MainState_Type* const modules[] );
void	System_StateB_MAIN( MainState_Type* const modules[] );
void	System_StateC_MAIN( MainState_Type* const modules[] );


void 	App_MAIN(void);









#endif /* __APP_H__ */


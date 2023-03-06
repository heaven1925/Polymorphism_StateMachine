/*******************************************************************************
  * @file    app.h
  * @author	 Atakan ERTEKiN
  * @version V1.0.0
  * @date	 	 06.03.2023 - ...
  * @rev     V1.0.0
  * @brief	 State Machine Embedded Software Programming Application
	******************************************************************************
	* @warning   Dont forget to define extern parameters in main.h
********************************************************************************/

#include "app.h"
#include "main.h"

int a,b,c;
char* pbuffer;

static int Clock;

StateTime_Type 	time_a;
StateTime_Type 	time_b;
StateTime_Type 	time_c;

State_Type 			MAINstate;

/*
* Local Function Definitions
*/
static void 	StateA_MAIN( MainState_Type const * const param );
static void 	StateB_MAIN( MainState_Type const * const param );
static void 	StateC_MAIN( MainState_Type const * const param );

/*
* Main State Machine Object
*/
MainState_Type MAIN_StateMachine;

/*
* State Table Virtual Pointer Initialize
*/
static void (*stateTable[])(MainState_Type* const modules[]) =
{
	System_StateA_MAIN ,
	System_StateB_MAIN ,
	System_StateC_MAIN
};

/*
* State Functions from different modules
*/
MainState_Type* const sys_modules[] =
{
	 &MAIN_StateMachine
};

	
void MainState_CTOR( MainState_Type* const param )
{
	
	/* Initial Virtual Table */
	static const struct OpsVTable vTable =
	{
		&StateA_MAIN,
		&StateB_MAIN,
		&StateC_MAIN
	};
	
	param->vptr = &vTable;
	
}


void	System_StateA_MAIN( MainState_Type* const modules[] )
{
	MainState_RunA_Vcall( modules[ STATE_A_MAIN ] );
	
	/*
	
	If any child added State-A 
	
	for( uint8_t loopVal = 0 ; modules[ loopVal ] != (MainState_Type*)0 ; loopVal++ )
	{
		MainState_RunA_Vcall( modules[ loopVal ] );
	}
	
	*/
	
}

void	System_StateB_MAIN( MainState_Type* const modules[] )
{
	MainState_RunB_Vcall( modules[ STATE_B_MAIN ] );
	
	/*
	
	If any child added State-A 
	
	for( uint8_t loopVal = 0 ; modules[ loopVal ] != (MainState_Type*)0 ; loopVal++ )
	{
		MainState_RunA_Vcall( modules[ loopVal ] );
	}
	
	*/
	
}

void	System_StateC_MAIN( MainState_Type* const modules[] )
{
	MainState_RunC_Vcall( modules[ STATE_C_MAIN ] );
	
	/*
	
	If any child added State-A 
	
	for( uint8_t loopVal = 0 ; modules[ loopVal ] != (MainState_Type*)0 ; loopVal++ )
	{
		MainState_RunA_Vcall( modules[ loopVal ] );
	}
	
	*/
	
}


void 	App_MAIN(void)
{
	
	MainState_CTOR(&MAIN_StateMachine);
	
	while(1)
	{
		stateTable[MAINstate](sys_modules);
		
		Clock++;
		HAL_Delay(100);
	}
	
}


static void 	StateA_MAIN( MainState_Type const * const param )
{
	if( Clock == 2 )
	{
		 MAINstate = STATE_B;
	}
	
	time_a.nowTime = HAL_GetTick();
	
	time_a.deltaTime = time_a.nowTime - time_a.prevTime ;
	
	//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	
	a++;
	
	pbuffer = (char*)malloc( 50*sizeof(char) );
	sprintf( &pbuffer[0] , " a = %d : tick = %d \n" , a , time_a.nowTime );
	HAL_UART_Transmit( &huart4 , (uint8_t*)&pbuffer[0] , 50 , 100);
	free(pbuffer);
	
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13 );
	
	//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
	
	time_a.deltaTime /= 100;
	
	time_a.prevTime = time_a.nowTime;
	
	
}

static void 	StateB_MAIN( MainState_Type const * const param )
{
	if( Clock == 5 )
	{
		  MAINstate = STATE_C;
	}
		
	time_b.nowTime = HAL_GetTick();
	
	time_b.deltaTime = time_b.nowTime - time_b.prevTime ;
	
	//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	
	b++;
	
	pbuffer = (char*)malloc( 50*sizeof(char) );
	sprintf( &pbuffer[0] , " b = %d : tick = %d \n\r" , b , time_b.nowTime );
	HAL_UART_Transmit( &huart4 , (uint8_t*)&pbuffer[0] , 50 , 100);
	free(pbuffer);
	
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14 );
	
	//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
	
	time_b.deltaTime /= 100;
	
	time_b.prevTime = time_b.nowTime;
	
}

static void 	StateC_MAIN( MainState_Type const * const param )
{
	if( Clock == 9 )
	{
		Clock = 0; 
		MAINstate = STATE_A;
	}
		
	time_c.nowTime = HAL_GetTick();
	
	time_c.deltaTime = time_c.nowTime - time_c.prevTime ;
	
	//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	
	c++;
	
	pbuffer = (char*)malloc( 50*sizeof(char) );
	sprintf( &pbuffer[0] , " c = %d : tick = %d \n\r" , c , time_c.nowTime );
	HAL_UART_Transmit( &huart4 , (uint8_t*)&pbuffer[0] , 50 , 100);
	free(pbuffer);
	
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15 );
	
	//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
	
	time_c.deltaTime /= 100;
	
	time_c.prevTime = time_c.nowTime;	
}
	



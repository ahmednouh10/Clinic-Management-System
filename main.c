#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//for comparing strings for the password

#include "std_types.h"
#include "bit_math.h"
#include "prototypes.h"		//all the macros , function prototypes, global values, structs

//********************************** Global Values **********************************//
u32 mode;
u32 numOfpatients = 0;
u32 numOfreservations = 0;


void main(void)
{
	printf("Welcome to our Clinic Management System");
	printf("\n");

	//first lets initialize the 5 slots we have
	InitializeSlots();

	HomePage();

	printf("\n");

	switch(mode)
	{
		case 1:
			AdminMode();
			break;
		case 2:

			UserMode();
			break;
		case 3:
			printf("Exiting the system...");
			break;
		default:
			HomePage();
			break;
	}

	if (mode == 3)
	{
		return;
	}
}


//HomePage to make the user choose again which mode he wants
u32 HomePage()
{
	printf("Kindly choose how you will login:\n");
	printf("1. Admin Mode	\t\t	2. User Mode\n");
	printf("3. Exit..\n");
	printf("Enter your choice: ");
	scanf("%d",&mode);
}

void InitializeSlots()
{
	u32 startTime = 1400;
	u32 i;

	for(i=0; i<MAXIMUM_SLOTS; i++)
	{
		Slot[i].start_time = startTime;
		Slot[i].end_time = startTime + 30;
		Slot[i].checkAvailability = 1;
		startTime += 30;
	}
}




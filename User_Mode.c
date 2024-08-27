#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//for comparing strings for the password

#include "std_types.h"
#include "bit_math.h"
#include "prototypes.h"	//all the macros , function prototypes, global values, structs



//**********************************User Mode**********************************//
void UserMode()
{
	u32 user_features_choice;
	printf("You logged as a user!\n");
	printf("Welcome to the User Page!\n");


	while (1)
	{
		printf("Features:\n");
		printf("1. View the patient's record\n");
		printf("2. View today's reservation\n");
		printf("3. Exit...\n");

		printf("Enter your choice: ");
		scanf("%d",&user_features_choice);
		printf("\n");

		switch(user_features_choice)
		{
			case 1:
				ViewPatient();
				printf("\n");
				break;
			case 2:
				TodaysReservation();
				printf("\n");
				break;
			case 3:
				printf("System is exiting user mode\n");
				HomePage();
				//return;
				break;
			default:
				printf("Invalid choice!!\n");
				break;
		}
	}
}


void ViewPatient()
{
	u32 i, pID, f=0;

	printf("Enter the patient's ID: ");
	scanf("%d", &pID);

	for (i=0; i<numOfpatients; i++)
	{
		if ( pID == Patient[i].ID )
		{
			f=1;
			printf("The information of the patient with the ID %d you entered: ",Patient[i].ID);
			printf("\n");
			printf("Patient's name: %s",Patient[i].patientName);
			printf("Patient's age: %d",Patient[i].age);
			printf("Patient's gender: %c",Patient[i].gender);
			printf("\n");
			break;
		}
	}

	if ( f==0 )
	{
		printf("There is no patient with this ID!");
	}
}


void TodaysReservation()
{
	u32 i;

	printf("Today's Reservations:  ");
	printf("\n");

	for( i=0; i<numOfreservations; i++)
	{
		u32 patient_ID_today = Reservations[i].patient_ID;
        u32 slotNum_today = Reservations[i].slotNum;

        printf("Patient ID: %d, Slot: %d:%d - %d:%d\n",
								patient_ID_today,
								Slot[slotNum_today].start_time / 100,
								Slot[slotNum_today].start_time % 100,
								Slot[slotNum_today].end_time / 100,
								Slot[slotNum_today].end_time % 100
				);
	}
}

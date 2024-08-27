#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//for comparing strings for the password

#include "std_types.h"
#include "bit_math.h"
#include "prototypes.h"	//all the macros , function prototypes, global values, structs

//**********************************Admin Mode**********************************//
void AdminMode()
{
	u32 passwordAttempts = 0;	//counter for the number of trials
	u32 admin_features_choice;
	u32 flag=0;

	//now we will check if the admin exceeded the number of trials "3" allowed or not
	while (passwordAttempts < TRIALS)
	{
		if ( checkPassword() )	//will go to check if password is correct
		{
			break;
		}
		else
		{
			passwordAttempts++;
		}
	}

	if (passwordAttempts == TRIALS)
		{
			printf("Oops! You exceeded the number of trials for logging in.");
			printf("\n");
			printf("Exiting...");
			printf("\n");
			flag = 1;
			//HomePage();
			//break;
			//return;
		}

	//if the password was correct, the admin should choose which feature he needs
	//the program should be working forever, unless the admin chose to "exit"

	if (flag == 1)
	{
		HomePage();
	}
	else
	{
		printf("You logged as an admin!\n");
		printf("Welcome to the Admin Page!\n");
		while (1)
		{
			printf("Features:\n");
			printf("1. Add a new patient record\n");
			printf("2. Edit a patient's record\n");
			printf("3. Reserve a slot with the doctor\n");
			printf("4. Cancel a reservation\n");
			printf("5. Exit...\n");

			printf("Enter your choice: ");
			scanf("%d",&admin_features_choice);
			printf("\n");

			switch(admin_features_choice)
			{
				case 1:
					AddPatient();
					break;
				case 2:
					EditPatient();
					break;
				case 3:
					ReserveSlot();
					break;
				case 4:
					CancelReservation();
					break;
				case 5:
					printf("System is exiting admin mode\n");
					//return;
					HomePage();
					break;
				default:
					printf("Invalid choice!!\n");
					break;
			}
		}
	}
}


u32 checkPassword()		//int(u32) because it has to return either a 0 or 1 in the if condition
{
	u8 entered_password[10];

	printf("Kindly enter your password: ");
	scanf("%s",&entered_password);

	if ( strcmp(entered_password, "1234") == 0)
	{
		return 1;		//The entered password is correct.
	}
	else
	{
		printf("The password entered is incorrect");
		printf("\n");
		return 0;		//The entered password is incorrect.
	}
}


void AddPatient()
{
	struct patientData newPatient;

	printf("Enter the patient's name: ");
	scanf("%s",&newPatient.patientName);
	printf("\n");

	printf("Enter the patient's age: ");
	scanf("%d",&newPatient.age);
	printf("\n");

	printf("Enter (F/M) for the patient's gender: ");
	//scanf("%c",&newPatient.gender);		//does not take from a character and it skips it in the console!!!
	scanf("%s",&newPatient.gender);
	printf("\n");

	printf("Enter the patient's ID: ");
	scanf("%d",&newPatient.ID);
	printf("\n");

	//The ID must be unique, if the entered ID is already exists, the system shall reject it
	u32 i;
	for (i=0; i<numOfpatients; i++)
	{
		if (Patient[i].ID == newPatient.ID)
		{
			printf("This ID already exists for another patient!\n");
			return;
		}
	}

	//Add the new patient to the array
	Patient[numOfpatients] = newPatient;
	numOfpatients++;
	printf("New patient is successfully added to the system!\n");
}


void EditPatient()
{
	u32 i, id, flag=0;

	printf("Please enter the ID of the patient you wish to edit his/her information");
	scanf("%d",&id);
	printf("\n");

	for(i=0; i<numOfpatients; i++)
	{
		if (Patient[i].ID == id)
		{
			flag=1;
			printf("You can now edit the record. Leave a blank space to keep the current data.\n");

			printf("Update the name: ");
            u8 newName[50];
            scanf("%s", newName);
            if (strcmp(newName, " ") != 0)
			{
                strcpy(Patient[i].patientName, newName);
            }

			printf("Update the age: ");
            int newAge;
            scanf("%d", &newAge);
            if (newAge != 0)
			{
                Patient[i].age = newAge;
            }

			printf("Update the gender: ");
            u8 newGender;
            scanf(" %c", &newGender);
            if (newGender != '\0')
			{
                Patient[i].gender = newGender;
            }

			break;
		}
		if (flag==0)
		{
			printf("Patient with ID is not found!\n");
		}
	}

}


void ReserveSlot()
{
	u32 patientID, reservedSlot;
	printf("Enter the patient's ID: ");
	scanf("%d",&patientID);
	printf("\n");

	//In order to check if the entered ID exists in the patient's array
	u32 i, patientIndex=-1;
	for (i=0; i<numOfpatients; i++)
	{
		if ( Patient[i].ID == patientID )
		{
			patientIndex = i;
			break;
		}
	}

	//What if it is not found? It shouldn't accept a reservation for a not registered user
	if (patientIndex == -1)
	{
		printf("This ID is not registered!\n");
		return;
	}


	//Now, print the available slots
	printf("Available slots:\n");
	for (i=0; i<MAXIMUM_SLOTS; i++)
	{
		if ( Slot[i].checkAvailability )
		{
			printf("%d. %d:%d - %d:%d\n",	//get the Units and Tens by division and mod operation
							i + 1,
							Slot[i].start_time / 100,
							Slot[i].start_time % 100,
							Slot[i].end_time / 100,
							Slot[i].end_time % 100);
		}
	}

	//Choose the slot
	printf("Enter the number of slot that the patients wants: ");
	scanf("%d",&reservedSlot);

	//Make sure that the user entered a correct choice
	//(!Slot[reservedSlot-1].checkAvailability)---> Checks if slot at specified index is not available "Already Taken"
	if ( (reservedSlot < 1) || (reservedSlot >= MAXIMUM_SLOTS) || (!Slot[reservedSlot - 1].checkAvailability) )
	{
        printf("Invalid slot choice.\n");
        return;
	}


	// Reserve the slot by marking it as unavailable and adding a reservation
    Slot[reservedSlot - 1].checkAvailability = 0;
    Reservations[numOfreservations].patient_ID = patientID;
    Reservations[numOfreservations].slotNum = reservedSlot - 1;
    numOfreservations++;

    printf("Slot reserved successfully.\n");
}


void CancelReservation()
{
	u32 patient_id, i;
	printf("Enter the ID of the patient to cancel his/her reservation: ");
    scanf("%d", &patient_id);

	//Search for the index of this reservation in the reservations array
    u32 reserveIndex = -1;
    for (i=0; i<numOfreservations; i++)
	{
        if (Reservations[i].patient_ID == patient_id)
		{
            reserveIndex = i;
            break;
        }
    }

    //What if there was no reservation for this patient?
    if (reserveIndex == -1) {
        printf("No reservations found for this patient.\n");
        return;
    }


	//Cancel the reservation by making the slot available again
    Slot[Reservations[reserveIndex].slotNum].checkAvailability = 1;

    printf("Reservation is  cancelled successfully.\n");

}


#ifndef SUPPORT_H_
#define SUPPORT_H_


extern u32 mode;
extern u32 numOfpatients;
extern u32 numOfreservations;
//********************************** MACROS: #define **********************************//


//the admin mode has only 3 trials to enter the password
#define TRIALS 3

//we have only 5 slots
#define MAXIMUM_SLOTS 5

//Lets assume that we have a maximum number of patients (because i'm using array for patients)
#define MAXIMUM_PATIENTS 10

//Assuming that the maximum reservations are 10
#define MAXIMUM_RESERVATIONS 10







//**********************************Structs Definition**********************************//


//Each patient has some information stored
struct patientData
{
	u32 ID;
	u8 patientName[50];
	u32 age;
	u8 gender;	//F: Female or M: Male
};
struct patientData Patient[MAXIMUM_PATIENTS];



/*Each slot has a start and an end time.
	Plus, we have to check if it is available, if already reserved, shouldn't appear.*/

struct slotData
{
	u32 start_time;
	u32 end_time;
	u32 checkAvailability;	//if 1-->Available	0-->Already reserved
};
struct slotData Slot[MAXIMUM_SLOTS];



//Each reservation should have the id of the patient and the slot he reserved
struct reservingData
{
	u32 patient_ID;
	u32 slotNum;
	//struct slotNo;	//this is a pointer that will point to the already reserved slot
};
struct reservingData Reservations[MAXIMUM_RESERVATIONS];




//**********************************Function Prototypes**********************************//
u32 HomePage();
void UserMode();
void ViewPatient();
void TodaysReservation();

void AdminMode();
u32 checkPassword();
void AddPatient();
void EditPatient();
void ReserveSlot();
void CancelReservation();

void InitializeSlots();

//When I change them to linked list will need these functions
//void AddSlot();
//void RemoveSlot();
//void AvailableSlots();









#endif
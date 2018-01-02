#include"cal.h"

void taskList(struct calendar *head)
{
	int ch, month;
	struct month *m;

	printf("\n1.Add A Task.\n2.Finished A Task.\n3.View TaskList.\n");
	printf("Enter your choice: ");
	scanf("%d", &ch);
	__fpurge(stdin);

	printf("\nEnter the month for which you want to perform the above task [1 to 12]: ");
	scanf("%d", &month);
	__fpurge(stdin);
	switch(month)
	{
		case 1: m = head->jan;
				break;
		case 2: m = head->feb;
				break;
		case 3: m = head->mar;
				break;
		case 4: m = head->jan;
				break;
		case 5: m = head->feb;
				break;
		case 6: m = head->mar;
				break;
		case 7: m = head->jan;
				break;
		case 8: m = head->feb;
				break;
		case 9: m = head->mar;
				break;
		case 10: m = head->jan;
				 break;
		case 11: m = head->feb;
				 break;
		case 12: m = head->mar;
				 break;
		default: printf("\nInvalid Month Number Entered....\n");
				 return;
	}

	switch(ch)
	{
		case 1: enqueue(m->queue);
				break;
		case 2: dequeue(m->queue);
				break;
		case 3: showTaskList(m->queue);
				break;
		default: printf("\nInvalid Option Selected ....\n");
				 return;
	}
}

void enqueue(struct priorityQueue *pq)
{
    char *task = (char*)malloc(sizeof(char)*500);
    int pri;

	__fpurge(stdin);
    printf("\nEnter The Task:  ");
    gets(task);

	__fpurge(stdin);
    printf("How important is this task.....[Higher Number Represents Higher Priority.]:  ");
    scanf("%d", &pri);
	__fpurge(stdin);

	struct taskNode *temp = (struct taskNode*)malloc(sizeof(struct taskNode));
	temp->task = task;
	temp->priority = pri;
	temp->link = NULL;

	if(pq->head == NULL)
	{
		pq->head = temp;	
	}

	else if(pq->head->priority < pri)
	{
		temp->link = pq->head;
		pq->head = temp;
	}

	else
	{
		struct taskNode *p = pq->head;
		while(p->link!=NULL)
		{
			if(p->link->priority < pri)
				break;
			p = p->link;
		}
		temp->link = p->link;
		p->link = temp;
	}
	printf("\nYour Task Was Successfully Added!\n");
}

void dequeue(struct priorityQueue *pq)
{
	if(pq->head == NULL)
	{
		printf("\nThere is no task present for this month....You are free to enjoy life!!!\n");
		return;
	}

	else
	{
		struct taskNode *temp = pq->head;
		pq->head = pq->head->link;
		printf("\nYou have successfully completed the task ->\" %s \". Congrats!!!\n", temp->task);
		free(temp);
		return;
	}
}

void showTaskList(struct priorityQueue *pq)
{
	struct taskNode *p = pq->head;

	if(p == NULL)
	{
		printf("\n\nThere is no task present for this month....You are free to enjoy life!!!\n");
		return;
	}

	else
	{
		printf("\n\nThe Task List for this month is as follows: \n");

		int i = 1;
		while(p != NULL)
		{
			printf("%d. %s [Priority given: %d]\n", i, p->task, p->priority);
			p = p->link;
			++i;
		}
		printf("\n");
	}
}

void showSetup()
{
	printf("\n\n");
	int c;
	FILE *file;
	file = fopen("ReadMe.txt", "r+");
	if (file) 
	{
		while ((c = getc(file)) != EOF)
			putchar(c);
		fclose(file);
	}
	else
		printf("\nFailed to read\n");
	return;
}


void setUp(struct calendar *head)
{
	int year;
	printf("\nEnter the current year : ");
	scanf("%d", &year);

	if(year > 2025 || year < 2000)
	{
		printf("\nPlease enter a year in between 2000 and 2025: ");
		while(1)
		{
			scanf("%d", &year);
			if(year>=2000 && year<=2025)
				break;
			printf("Invalid Year. Please enter the year again.....\n");
		}
	}

	head->year = year;
	//printf("%d", head->year);

	struct calendar *temp;
	for(int i = 1; i <= 12; ++i)
	{
		temp = (struct month*)malloc(sizeof(struct month));
		switch(i)
		{
			case 1: head->jan = temp;
					setUpMonth(head->jan, year, 1);
					break;
			case 2: head->feb = temp;
					setUpMonth(head->feb, year, 2);
					break;
			case 3: head->mar = temp;
					setUpMonth(head->mar, year, 3);
					break;
			case 4: head->apr = temp;
					setUpMonth(head->apr, year, 4);
					break;
			case 5: head->may = temp;
					setUpMonth(head->may, year, 5);
					break;	
			case 6: head->jun = temp;
					setUpMonth(head->jun, year, 6);
					break;	
			case 7: head->jul = temp;
					setUpMonth(head->jul, year, 7);
					break;	
			case 8: head->aug = temp;
					setUpMonth(head->aug, year, 8);
					break;	
			case 9: head->sep = temp;
					setUpMonth(head->sep, year, 9);
					break;	
			case 10: head->oct = temp;
					setUpMonth(head->oct, year, 10);
					break;
			case 11: head->nov = temp;
					setUpMonth(head->nov, year, 11);
					break;	
			case 12: head->dec = temp;
					setUpMonth(head->dec, year, 12);
					break;														
		}
	}
}


void setUpMonth(struct month *month, int year, int mNo)
{
	struct days *temp = (struct days*)malloc(sizeof(struct days));
	struct priorityQueue *q = (struct priorityQueue*)malloc(sizeof(struct priorityQueue));
	q->head = NULL;

	month->firstDay = temp;
	month->queue = q;
	month->month = mNo;

	switch(mNo)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: setUpDays(month->firstDay, 31);
				 break;
		case 2: if(isLeapYear(year)) 
					setUpDays(month->firstDay, 29);
				else
					setUpDays(month->firstDay, 28);
				break;
		default: setUpDays(month->firstDay, 30);
	}
}


void setUpDays(struct days *day, int noOfDays)
{
	//Yet to find out the day.

	struct days *temp;
	for(int  i = 1; i <= noOfDays; ++i)
	{
		temp = (struct days*)malloc(sizeof(struct days));
		day->date = i;
		day->note = NULL;
		day->event = NULL;
		if(i == noOfDays)
		{
			free(temp);
			temp = NULL;
		}
		day->nextDay = temp;
		day = day->nextDay;
	}
}


int isLeapYear(int year)
{
    if(year % 400 == 0 || (year % 100!=0 && year % 4 ==0))
       return 1;
    return 0;
}


void createNote(struct calendar *head)
{
	int day, month;
	printf("\nEnter the date for which you want to add a note[ dd mm ]: ");
	scanf("%d %d", &day, &month);
	printf("The date entered is: %d-%d-%d\n", day, month, head->year);

	switch(month)
	{
		case 1: goToDay(head->jan->firstDay, day);
				break;
		case 2: goToDay(head->feb->firstDay, day);
				break;
		case 3: goToDay(head->mar->firstDay, day);
				break;
		case 4: goToDay(head->apr->firstDay, day);
				break;
		case 5: goToDay(head->may->firstDay, day);
				break;
		case 6: goToDay(head->jun->firstDay, day);
				break;
		case 7: goToDay(head->jul->firstDay, day);
				break;
		case 8: goToDay(head->aug->firstDay, day);
				break;
		case 9: goToDay(head->sep->firstDay, day);
				break;
		case 10: goToDay(head->oct->firstDay, day);
				 break;
		case 11: goToDay(head->nov->firstDay, day);
				 break;
		case 12: goToDay(head->dec->firstDay, day);
				 break;
		default: printf("\nInvalid date entered....!!!\n");
				 return;
	}
}


void goToDay(struct days *temp, int day)
{
	if(day>31 || day<1)
	{
		printf("\nThe date entered is invalid....\n");
		return;
	}
	else
	{
		for(int i = 1 ; i < day && (temp!=NULL); ++i)
		{
			temp = temp->nextDay;
		}

		if(temp!= NULL && temp->note != NULL)
		{
			printf("\nThere is already a note created for this date.\
			\nCurrent version of the application doesn't support feature for multiple notes.\
			\nPlease try out the Beta version for accessing this feature.\n");
			return;
		}
		else if(temp!=NULL)
		{
			char *x = (char*)malloc(sizeof(char)*500);

			__fpurge(stdin);
			printf("\nEnter the note to be added :\n");
			gets(x);
			__fpurge(stdin);

			temp->note = x;
			//printf("%s", temp->note);
			
			printf("\nThe note was created successfully!!!\n");
		}
		else
		{
			printf("\nThe date entered is invalid....\n");
			return;
		}
	}
}

void overView(struct calendar *head)
{
	int month;
	
	printf("\nEnter the month for which you want to overview the calendar for as an integer[1 to 12]: ");
	scanf("%d", &month);

	while(!(month>0 && month<13))
	{
		printf("\nInvalid Month Entered.....Please re-enter the month: ");
		scanf("%d", &month);
	}

	struct month *m;
	switch(month)
	{
		case 1: m = head->jan;
				break;
		case 2: m = head->feb;
				break;
		case 3: m = head->mar;
				break;
		case 4: m = head->apr;
				break;
		case 5: m = head->may;
				break;
		case 6: m = head->jun;
				break;
		case 7: m = head->jul;
				break;
		case 8: m = head->aug;
				break;
		case 9: m = head->sep;
				break;
		case 10: m = head->oct;
				 break;
		case 11: m = head->nov;
				 break;
		case 12: m = head->dec;
				 break;
	}

	//To print the days of the month.
	printf("\n\n\t\t\t    The overview for the month is :\n\n");
	printf("\t\tSun\tMon\tTue\tWed\tThu\tFri\tSat\n");
	printf("\t\t---------------------------------------------------\n");

	struct days *p = m->firstDay;

	int x = findDay(p->date, m->month, head->year);
	int i = x;
	while(x>0)
	{
		printf("\t");
		--x;
	}


	while(1)
	{
		printf("\t\t");
		for(; i<7; ++i)
		{
			if(p->note != NULL || p->event != NULL)
			{
				printf("*");
			}
			else
				printf(" ");
			printf("%d\t",p->date);
			p = p->nextDay;
			if(p == NULL)
				break;
		}
		printf("\n");
		if(p == NULL)
			break;
		i = 0;
	}
	printf("\n\n");

	int count = 0;

	printf("The list of events for the month is:\n");
	p = m->firstDay;
	while(1)
	{
		if(p->event != NULL)
		{
			count++;
		}
		p = p->nextDay;
		if(p == NULL)
			break;
	}

	if(count != 0)
	{
		p = m->firstDay;
		while(1)
		{
			if(p->event != NULL)
			{
				printf("[%d-%d-%d]: %s\n", p->date, m->month, head->year, p->event);
			}
			p = p->nextDay;
			if(p == NULL)
				break;
		}
	}
	else
	{
		printf("There are no events for this month.\n");
	}

	count = 0;

	printf("\n\nThe list of notes added for this month is: \n");
	p = m->firstDay;
	while(1)
	{
		if(p->note != NULL)
		{
			count++;
		}
		p = p->nextDay;
		if(p == NULL)
			break;
	}

	if(count != 0)
	{
		p = m->firstDay;
		while(1)
		{
			if(p->note != NULL)
			{
				printf("[%d-%d-%d]: %s\n", p->date, m->month, head->year, p->note);
			}
			p = p->nextDay;
			if(p == NULL)
				break;
		}
	}
	else
	{
		printf("There are no notes added for this month.");
	}
	printf("\n\n");

}

int findDay(int d, int m, int y)
{
	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char week[7][10];

	int date, mon, year, i, r, s = 0 ;

	strcpy(week[0], "Sunday") ;
	strcpy(week[1], "Monday") ;
	strcpy(week[2], "Tuesday") ;
	strcpy(week[3], "Wednesday") ;
	strcpy(week[4], "Thursday") ;
	strcpy(week[5], "Friday") ;
	strcpy(week[6], "Saturday") ;

	date = d;
	mon = m;
	year = y;

	if( (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)) )
		month[1] = 29 ;

 	for(i = 0 ; i < mon - 1 ; i++)
  		s = s + month[i] ;

 	s = s + (date + year + (year / 4) - 2) ;
 	s = s % 7 ;

  	if( (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)) )
 	{
		if(s==0)
  	    {
			printf("\nThe day is : %s", week[6]) ;
			return 6;
		}
   		//printf("\nThe day is : %s", week[s-1]) ;
   		return s-1;
    }
 	else
 	{
 		//printf("\nThe day is : %s", week[s]) ;
 		return s;
	}
}

void calSync(struct calendar *head)
{
	char x[500];

	__fpurge(stdin);
	printf("\nEnter the name of your csv events file to be synced: ");
	gets(x);
	__fpurge(stdin);

	char y[50] = {'S','y','n','c',' ','F','i','l','e','s','/'};
	strcat(y,x);
	//printf("%s\n",y);

	printf("\n");
	int c;
	FILE *file;
	file = fopen( y, "r+");
	if (!file) 
	{
		printf("\nFailed to read\n");
		return;
	}
	else
	{
		printf("The file contents are as follows : \n\n");
		while ((c = getc(file)) != EOF)
			putchar(c);
		printf("\n");
	}

	rewind(file);

	char *day, *month, *year, *event, z[500], date[20];
	fgets(z, 100, file);

	while(!feof(file) && z != NULL)
	{
		strcpy(date, strtok(z, ","));
		event = strtok(NULL,"\n");
		day = strtok(date, "/");
		month = strtok(NULL, "/");
		year = strtok(NULL, "/");

		insertEvents(atoi(day), atoi(month), atoi(year), event, head);

		fgets(z, 100, file);
	}
	
	printf("\nThe File Was Successfully Synced!!!\n");
}

void insertEvents(int day, int month, int year, char *event, struct calendar *head)
{
	struct month *m;

	//printf("%d %d", year, head->year);
	//return;

	if(year != head->year)
	{
		printf("\nEnter a file pertaining to this years calendar....\n");
		return;
	}

	switch(month)
	{
		case 1: m = head->jan;
				break;
		case 2: m = head->feb;
				break;
		case 3: m = head->mar;
				break;
		case 4: m = head->apr;
				break;
		case 5: m = head->may;
				break;
		case 6: m = head->jun;
				break;
		case 7: m = head->jul;
				break;
		case 8: m = head->aug;
				break;
		case 9: m = head->sep;
				break;
		case 10: m = head->oct;
				 break;
		case 11: m = head->nov;
				 break;
		case 12: m = head->dec;
				 break;
		default: return;
	}

	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: if(day < 1 || day >31) return;
				 break;
		case 2: if(isLeapYear(year)) 
					if(day < 1 || day >29) return;
				else
					if(day < 1 || day >28) return;
				break;
		default: if(day < 1 || day >30) return;
	}

	//printf("hello\n");

	struct days *p = m->firstDay;

	for(int i = 1; i < day; ++i)
	{
		p = p->nextDay;
	}

	char *str = (char*)malloc(sizeof(char)*500);
	strcpy(str, event);

	p->event = str;
}
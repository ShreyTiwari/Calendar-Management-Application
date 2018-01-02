#include"cal.h"

void main()
{
    char readme[3];
    int ch = 1;
    struct calendar cal;


    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\tWELCOME\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");

    printf("\n\t\tHERE IS A CALENDAR MANAGEMENT APPLICATION THAT WILL MAKE YOUR LIFE SO MUCH SIMPLER !!\n");
    printf("\n We Highly Recommend Reading The \"Readme\" File In Order To Get An Idea About The Functions And Operations Offered By This App.\n");

    printf(" Do You Want To Go Through The Guidelines [Yes/No]:  ");
    gets(readme);
    
    if(!strcmp(readme,"yes") || !strcmp(readme,"Yes"))
    {
        showSetup();
    }

    printf("\nLets Begin By Setting Up The Application....\n");
    setUp(&cal);

    while(ch)
    {
        printf("\nSo What Would You Like To Do ....\n");
        printf("\n1.Sync Your Calendar\n2.Create A Note\n3.Manage Your Task List\n4.Overview A Month's Schedule\n5.Exit\n");
        printf("Enter Your Choice Here: ");
        scanf("%d", &ch);
        __fpurge(stdin);
        
        switch(ch)
        {
            case 1: calSync(&cal);
                    break;
            case 2: createNote(&cal);
                    break;
            case 3: taskList(&cal);
                    break;
            case 4: overView(&cal);
                    break;
            default: printf("\n\n-------------------------------------------------------------------------------------------------------------------------------\n");
                     printf("\t\t\t\t\t\tThank You!!\n");
                     printf("-------------------------------------------------------------------------------------------------------------------------------\n");
                     ch = 0;
        }

    }
}
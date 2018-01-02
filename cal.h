#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>

struct calendar
{
    int year;
    struct month *jan;
    struct month *feb;
    struct month *mar;
    struct month *apr;
    struct month *may;
    struct month *jun;
    struct month *jul;
    struct month *aug;
    struct month *sep;
    struct month *oct;
    struct month *nov;
    struct month *dec;
};

struct month
{
    int month;
    struct days *firstDay;
    struct priorityQueue *queue;
};

struct days
{
    int date;
    char *note;
    char *event;
    struct day *nextDay;
};

struct priorityQueue
{
    struct taskNode *head;
};

struct taskNode
{
    int priority;
    char *task;
    struct taskNode *link;
};

void showSetup();
void setUp();
void setUpMonth();
void setUpDays();
int isLeapYear();
int findDay();

void createNote();
void goToDay();
void overView();

void taskList();
void enqueue(struct priorityQueue *pq);
void dequeue(struct priorityQueue *pq);
void showTaskList(struct priorityQueue *pq);

void calSync();
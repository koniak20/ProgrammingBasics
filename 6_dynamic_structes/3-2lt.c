#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Day
    {
        MON,
        TUE,
        WED,
        THU,
        FRI,
        SAT,
        SUN
    };

    /**********************/
    /* Struktura 'Lesson' */
    /**********************/
    struct Lesson
    {
        char *className;
        enum Day day;
        int hour;
        int minute;
        int duration;
    };

	enum bool{
		false,true
	};

    /********************/
    /* Struktura 'Node' */
    /********************/
    struct Node
    {
        struct Lesson lesson;
        struct Node *next;
    };
	int isLess(struct Node* a, struct Lesson lesson){
		if(	a->lesson.hour < lesson.hour || (a->lesson.hour == lesson.hour && a->lesson.minute < lesson.minute))
			return 1;
		else
			return 0;
	}

	void List__insert(struct Node* list, struct Lesson lesson ){
			struct Node* curr = list;
			while(!isLess(curr,lesson)){
				if(curr->next == NULL)
					break;
				curr = curr->next;
			}
			struct Node* new = (struct Node*) malloc(sizeof(struct Node));
			new->lesson = lesson;
			new->next =	curr->next;
			curr->next = new;
	}	
	void Node__delete(struct Node* last, struct Node* delete){
			last->next = delete->next;
			free(delete);
	}
	enum bool areSame(struct Lesson a, struct Lesson b){
			if(a.day == b.day && a.hour == b.hour && a.minute == b.minute && a.duration == b.duration && !strcmp(a.className,b.className))
				return true;
			else
				return false;

	}
	void List__remove(struct Node* list, struct Lesson lesson){
		struct Node* curr = list;
		while(curr != NULL && curr->next != NULL && areSame(curr->next->lesson,lesson)){
			curr = curr->next;	
		}
		if(curr != NULL && curr->next != NULL)
			Node__delete(curr,curr->next);
	}
	void Node__print(struct Node* current){
			char *dayNames[] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
    	    printf("Przedmiot: \e[31m%s\e[0m\nDzień tygodnia: \e[31m%s\e[0m\nGodzina rozpoczęcia [Czas trwania]: \e[31m%02d:%02d [%d]\e[0m\n\n", current->lesson.className, dayNames[current->lesson.day], current->lesson.hour, current->lesson.minute, current->lesson.duration);
	}
	void List__print(struct Node* list){
			struct Node* head = list;
			for(;head !=NULL; head = head->next){
				Node__print(head);
			}
	}
	void List__destroy(struct Node** list){
			if(*list == NULL){
				printf("Lista nie istnieje\n");
				return;
			}
			if((*list)->next != NULL)
				List__destroy(&((*list)->next));
			free(*list);
			*list = NULL;
	}

int main(){
	struct Node *list = (struct Node*) malloc(sizeof(struct Node));
    struct Lesson lesson;

    lesson.className = "Podstawy Programowania";
    lesson.day = WED;
    lesson.hour = 12;
    lesson.minute = 50;
    lesson.duration = 90;
	list->lesson = lesson;
	list->next = NULL;

    lesson.className = " Programowania";
    lesson.day = WED;
    lesson.hour = 11;
    lesson.minute = 50;
    lesson.duration = 90;
	
	List__insert(list,lesson);
	List__print(list);



}

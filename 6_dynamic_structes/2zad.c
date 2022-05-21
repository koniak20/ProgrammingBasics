#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Program, który pokazuje jak utworzyć trzyelementową listę jednokierunkową
 *
 * @author Stanisław Polak
 * @version 1.0 22-05-2020
*/
int main(void)
{
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

	void List__insert(struct Node* list, struct Lesson lesson, enum bool begin){
			struct Node* curr = list;
			while(!begin){
				if(curr->next != NULL)
					curr = curr->next;
			}
			struct Node* new = (struct Node*) malloc(sizeof(struct Node));
			if(begin){	
				if(list != NULL)
					*new = *curr;
				else{
					new->lesson = lesson;
					new->next = NULL;
					list = new;
				}
				curr->lesson = lesson;
				curr->next = new;
			}
			else{
				new->lesson = lesson;
				new->next = NULL;
				curr->next = new;
			}
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
	struct Node *list = (struct Node*) malloc(sizeof(struct Node));
    struct Lesson lesson;

    lesson.className = "Podstawy Programowania";
    lesson.day = WED;
    lesson.hour = 12;
    lesson.minute = 50;
    lesson.duration = 90;
	list->lesson = lesson;
	list->next = NULL;

    //List__insert(list, lesson, true);
    lesson.className = "Wychowanie fizyczne";
    lesson.day = MON;
    lesson.hour = 8;
    lesson.minute = 00;
    lesson.duration = 90;
    List__insert(list, lesson, true);

    List__print(list); // Funkcja powinna wypisać:
                       // Wychowanie fizyczne, Poniedziałek 8:00 [90]
                       // Podstawy programowania, Środa 12:50 [90]
    List__remove(list, lesson);
    List__print(list); // Funkcja powinna wypisać:
                       // Podstawy programowania, Środa 12:50 [90]

    List__destroy(&list); // Likwidacja listy
    List__destroy(&list); // Wypisuje: "Lista nie istnieje"

    return 0;
}

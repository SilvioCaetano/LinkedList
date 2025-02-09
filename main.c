#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *next;
    int data;
} Node;

Node *head = NULL;

Node *addNode(int data)
{
    Node *new = NULL;

    if( head == NULL )
    {
        new = malloc(sizeof(Node));

        if( new == NULL )        
            return NULL;            
        
        new->data = data;
        head = new;
        new->next = NULL;        
    }
    else
    {
        new = malloc(sizeof(Node));

        if( new == NULL )        
            return NULL;            
        
        new->data = data;
        new->next = head;
        head = new;
    }

    return new;
}

int removeNode(int data)
{
    Node *current = head;
    Node *prev = head;
    while ( current != NULL )
    {
        if(current->data == data)
        {
            if(current == head)
            {
                if(current->next != NULL)
                {
                    head = current->next;
                    free(current);
                    current = NULL;
                }
                else
                {
                    free(head);
                    head = NULL;
                }
            }
            else
            {
                prev->next = current->next;
                free(current);
                current = NULL;
            }

            return 1;
        }
        
        prev = current;
        current = current->next;
    }

    return 0;
}

Node *insertNode(int data, int position)
{
    Node *current = head;
    while( current != NULL && position != 0 )
    {
        position--;
    }
    if(position != 0)
    {
        printf("Requested position is too far into list.\n");
        return NULL;
    }

    Node *new = malloc(sizeof(Node));
    if(new == NULL)
        return NULL;
    
    new->data = data;
    new->next = current->next;
    current->next = new;

    return new;
}

void printList()
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("\n");
    return;
}

void freeList()
{   
    Node *current = head;
    Node *next = NULL;
    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

void printMenu()
{
    printf("You have the following options:\n");
    printf("\t1. Add a node to the list.\n");    
    printf("\t2. Remove a node from the list.\n");
    printf("\t3. Insert a node to the list.\n");
    printf("\t4. Print your list.\n");
    printf("\t5. Quit.\n");
    return;
}

void runApplication()
{
     int option = -1;
    int data = 0;
    int position = 0;

    while (option != 5)
    {
        printMenu();
        int num_received = scanf("%d", &option);
        if( num_received == 1 && option > 0 && option <= 4 )
        {
            switch (option)
            {                
                case 1:
                    printf("What data should I insert?:\n");
                    scanf("%d", &data);
                    Node *new = addNode(data);
                    break;
                case 2:
                    printf("What data should I remove?:\n");
                    scanf("%d", &data);
                    int success = removeNode(data);
                    if(!success)
                    {
                        printf("Element not found.\n");
                    }
                    break;
                case 3:
                    printf("What data should I insert?:\n");
                    scanf("%d", &data);
                    printf("What position?");
                    scanf("%d", &position);
                    new = insertNode(data, position);
                    if(new == NULL)
                        printf("Failed to insert into list\n");
                    break;
                case 4:
                    printList();
                    break;
                case 5:
                    break;
            }
        }
    }
    
    freeList();
}

int main(int argc, char const *argv[])
{
    runApplication();
    return 0;
}

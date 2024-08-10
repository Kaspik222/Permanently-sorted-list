#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    char data;
    struct List* next;
} List;


// Прототипи усіх функцій
List* createNode(char);
void insert(List**, char);
void deleteList(List**);
void deleteElement(List**, char*);
void printList(List*);
void cleanInputBuffer();
// Кінець прототипів

int main(void) {
    List* list = 0;
    // insert(&list, 'B'); insert(&list, 'C'); insert(&list, 'A'); insert(&list, 'F');
    short int choice = 0;
    while (choice != 3) {
        printf("Enter your choice:\n"
            "\t1 to insert an element into the list.\n"
            "\t2 to delete an element from the list.\n\t3 to end.\n?  ");
        while (scanf("%hd", &choice) != 1) {
            puts("Invalid input. Please enter a number!\n");
            cleanInputBuffer();
        }
        char ch; // character, which user will enter for deleting either insert
        switch (choice) {
        case 1:
            while (1) {
                printf("Enter a character (A-Z either a-z): ");
                cleanInputBuffer();
                ch = getchar();
                if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) break;
                cleanInputBuffer();
            }
            insert(&list, ch);
            puts("The list is:");
            printList(list);
            break;
        case 2:
            while (1) {
                printf("Enter a character to be deleated (A-Z either a-z): ");
                cleanInputBuffer();
                ch = getchar();
                if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) break;
                cleanInputBuffer();
            }
            char isHave = 0;
            List* curr = list;
            while (curr != NULL) {
                if (curr->data == ch) { isHave = 1; break; }
                curr = curr->next;
            }
            if (isHave) deleteElement(&list, &ch);
            else printf("%c not found.\n", ch);
            printList(list);
            break;
        case 3: puts("Exiting program."); break;
        default: puts("Invalid choice.\n"); break;
        };
    }
    deleteList(&list);
    return 0;
}

List* createNode(char data) {
    List* root = (List*)malloc(sizeof(List));
    if (!root) { perror("Error with allocation memory! Exit..."); return NULL; }
    root->data = data; root->next = 0;
    return root;
}

void insert(List** head, char character) {
    List* temp = createNode(character);
    if (NULL == *head) { *head = temp; return; }
    List* curr = *head, * prev = 0;
    while (curr != NULL && character > curr->data) { prev = curr; curr = curr->next; }
    temp->next = curr;
    (!prev) ? (*head = temp) : (prev->next = temp);
}

void deleteList(List** head) {
    List* temp = 0;
    while ((temp = *head) != NULL) {
        *head = temp->next;
        free(temp);
    }
}

void deleteElement(List** head, char* ch) {
    List* curr = *head, * prev = 0;
    while (curr->next != NULL && curr->data != (*ch)) { prev = curr; curr = curr->next; }
    (prev) ? (prev->next = curr->next) : (*head = curr->next);
    free(curr);
}

void printList(List* head) {
    List* temp = head;
    while (temp != NULL) {
        printf("%c --> ", temp->data);
        temp = temp->next;
    }
    puts("NULL");
}

void cleanInputBuffer() {
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}

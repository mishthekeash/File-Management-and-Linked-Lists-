/* doubly_linked_list.c
 *
 * Implement a sorted linked list of strings with operations Insert
 * in alphabetical order, Print, Member, Delete, Free_list.
 * The list nodes are doubly linked.
 *
 * Input:    Single character lower case letters to indicate operations,
 *           possibly followed by value needed by operation -- e.g. 'i'
 *           followed by "hello" to insert the string "hello" -- no
 *           double or single quotes.
 *
 * Output:   Results of operations.
 *
 * Compile:  gcc -g -Wall -o doubly_linked_list doubly_linked_list.c
 *
 * Run:      ./doubly_linked_list
 *
 */

/* You may not add any new header file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Max 99 chars + '\0' */
#define STRING_MAX 100

struct list_node_s {
    char*  data;
    struct list_node_s* prev_p;
    struct list_node_s* next_p;
};

/* Pointers to the head and tail of the list */
struct list_s {
    struct list_node_s* h_p;
    struct list_node_s* t_p;
};

void Insert(struct list_s* list_p, char string[]);
void Print(struct list_s* list_p);
int  Member(struct list_s* list_p, char string[]);
void Delete(struct list_s* list_p, char string[]);
void Free_list(struct list_s* list_p);
char Get_command(void);
void Get_string(char string[]);
void Free_node(struct list_node_s* node_p);
struct list_node_s* Allocate_node(int size);
void Print_node(char title[], struct list_node_s* node_p);


/*-----------------------------------------------------------------*/
int main(void) {
    char          command;
    char          string[STRING_MAX];
    struct list_s list;

    list.h_p = list.t_p = NULL;
    /* start with empty list */

    command = Get_command();
    while (command != 'q' && command != 'Q') {
        switch (command) {
            case 'i':
            case 'I':
                Get_string(string);
                Insert(&list, string);
                break;
            case 'p':
            case 'P':
                Print(&list);
                break;
            case 'm':
            case 'M':
                Get_string(string);
                if (Member(&list, string))
                    printf("%s is in the list\n", string);
                else
                    printf("%s is not in the list\n", string);
                break;
            case 'd':
            case 'D':
                Get_string(string);
                Delete(&list, string);
                break;
            case 'f':
            case 'F':
                Free_list(&list);
                break;
            default:
                printf("There is no %c command\n", command);
                printf("Please try again\n");
        }
        command = Get_command();
    }
    Free_list(&list);

    return 0;
}  /* main */


/*-----------------------------------------------------------------*/
/* Function:   Allocate_node
 * Purpose:    Allocate storage for a list node
 * Input arg:  size = number of chars needed in data member (including
 *                storage for the terminating null)
 * Return val: Pointer to the new node
 */
struct list_node_s* Allocate_node(int size) {

//TODO: Complete me
    struct list_node_s* node_p = malloc(sizeof(struct list_node_s));
    if (node_p == NULL) { //check if malloc failed
        printf("%s\n","Error: malloc failed in Allocate_node");}
    else {
            node_p->prev_p = NULL;
            node_p->next_p = NULL;
            node_p->data = malloc(sizeof (size));
    }

    return node_p;

}  /* Allocate_node */


/*-----------------------------------------------------------------*/
/* Function:   Insert
 * Purpose:    Insert new node in correct alphabetical location in list
 * Input arg:  string = new string to be added to list
 * In/out arg: list_p = pointer to struct storing head and tail ptrs
 * Note:       If the string is already in the list, print a message
 *                and return, leaving list unchanged
 */
void Insert(struct list_s* list_p, char string[]) {

//TODO: Complete me
    struct list_node_s* curr_p = list_p->h_p;
    int length = strlen(string);
    //check if string is already in list
    if (Member(list_p, string) == 1) {
        printf("%s\n","Error: string is already in list");
        return;
    }
    struct list_node_s* new_node_p = Allocate_node(length + 1);
    strcpy(new_node_p->data, string);
    //check if list is empty
    if(curr_p==NULL){
        list_p->h_p = new_node_p;
        list_p->t_p = new_node_p;
        return;
    }
    else{
        while(curr_p!=NULL){
            //if strings not equal
            if(strcmp(curr_p->data, string) > 0){
                if(curr_p->prev_p == NULL){
                    new_node_p->next_p = curr_p;
                    curr_p->prev_p = new_node_p;
                    list_p->h_p = new_node_p;
                    return;
                }
                else{
                    new_node_p->next_p = curr_p;
                    new_node_p->prev_p = curr_p->prev_p;
                    curr_p->prev_p->next_p = new_node_p;
                    curr_p->prev_p = new_node_p;
                    return;
                }
            }
            else{
                //alphabetical order
                if(curr_p->next_p == NULL){
                    new_node_p->prev_p = curr_p;
                    curr_p->next_p = new_node_p;
                    list_p->t_p = new_node_p;
                    return;
                }
                else{
                    curr_p = curr_p->next_p;
                }
            }
        }



    }



}  /* Insert */

/*-----------------------------------------------------------------*/
/* Function:   Print
 * Purpose:    Print the contents of the nodes in the list
 * Input arg:  list_p = pointers to first and last nodes in list
 *
 * Hint: The implementation of this function (below) shows how
 * to traverse a linked list.
 */
void Print(struct list_s* list_p) {
    struct list_node_s* curr_p = list_p->h_p;

    printf("list = ");

    while (curr_p != NULL) {
        printf("%s ", curr_p->data);
        curr_p = curr_p->next_p;
    }
    printf("\n");
}  /* Print */


/*-----------------------------------------------------------------*/
/* Function:   Member
 * Purpose:    Search list for string
 * Input args: string = string to search for
 *             list_p = pointers to first and last nodes in list
 * Return val: 1, if string is in the list, 0 otherwise
 */
int  Member(struct list_s* list_p, char string[]) {

//TODO: Complete me
    struct list_node_s* curr_p = list_p->h_p;
    while(curr_p!=NULL){
        if(strcmp(curr_p->data, string) == 0){
            return 1;
        }
        else{
            curr_p = curr_p->next_p;
        }
    }

    return 0;
}  /* Member */


/*-----------------------------------------------------------------*/
/* Function:   Free_node
 * Purpose:    Free storage used by a node of the list
 * In/out arg: node_p = pointer to node to be freed
 */
void Free_node(struct list_node_s* node_p) {
    free(node_p->data);
    free(node_p);
}  /* Free_node */


/*-----------------------------------------------------------------*/
/* Function:   Delete
 * Purpose:    Delete node containing string.
 * Input arg:  string = string to be deleted
 * In/out arg  list_p = pointers to head and tail of list
 * Note:       If the string is in the list, it will be unique.  So
 *             at most one node will be deleted.  If the string isn't
 *             in the list, the function just prints a message and
 *             returns, leaving the list unchanged.
 */
void Delete(struct list_s* list_p, char string[]) {

//TODO: Complete me
    struct list_node_s* curr_p = list_p->h_p;
    if(Member(list_p, string) == 0){
        printf("%s\n","Error: string is not in list");
        return;
    }
    else{
        while(curr_p!=NULL){
            if(strcmp(curr_p->data, string) == 0){
                if(curr_p->prev_p == NULL){
                    if(curr_p->next_p == NULL){
                        list_p->h_p = NULL;
                        list_p->t_p = NULL;
                        Free_node(curr_p);
                        return;
                    }
                    else{
                        list_p->h_p = curr_p->next_p;
                        curr_p->next_p->prev_p = NULL;
                        Free_node(curr_p);
                        return;
                    }
                }
                else{
                    if(curr_p->next_p == NULL){
                        list_p->t_p = curr_p->prev_p;
                        curr_p->prev_p->next_p = NULL;
                        Free_node(curr_p);
                        return;
                    }
                    else{
                        curr_p->prev_p->next_p = curr_p->next_p;
                        curr_p->next_p->prev_p = curr_p->prev_p;
                        Free_node(curr_p);
                        return;
                    }
                }
            }
            else{
                curr_p = curr_p->next_p;
            }
        }
    }

}  /* Delete */

/*-----------------------------------------------------------------*/
/* Function:   Free_list
 * Purpose:    Free storage used by list
 * In/out arg: list_p = pointers to head and tail of list
 */
void Free_list(struct list_s* list_p) {

//TODO: Complete me
    struct list_node_s* curr_p = list_p->h_p;
    struct list_node_s* temp_p;
    while(curr_p!=NULL){
        temp_p = curr_p;
        curr_p = curr_p->next_p;
        Free_node(temp_p);
    }
    list_p->h_p = NULL;
    list_p->t_p = NULL;
}  /* Free_list */

  /* Free_list */


/*-----------------------------------------------------------------*/
/* Function:   Get_command
 * Purpose:    Find and return the next non-whitespace character in
 *             the input stream
 * Return val: The next non-whitespace character in stdin
 */
char Get_command(void) {
    char c;

    printf("Please enter a command (i, d, m, p, f, q):  ");
    /* Put the space before the %c so scanf will skip white space */
    scanf(" %c", &c);
    return c;
}  /* Get_command */

/*-----------------------------------------------------------------*/
/* Function:   Get_string
 * Purpose:    Read the next string in stdin (delimited by whitespace)
 * Out arg:    string = next string in stdin
 */
void Get_string(char string[]) {

    printf("Please enter a string:  ");
    scanf("%s", string);
}  /* Get_string */


/*-----------------------------------------------------------------*/
/* Function:  Print_node
 * Purpose:   Print the data member in a node or NULL if the
 *            pointer is NULL
 * In args:   title:  name of the node
 *            node_p:  pointer to node
 */
void Print_node(char title[], struct list_node_s* node_p) {
    printf("%s = ", title);
    if (node_p != NULL)
        printf("%s\n", node_p->data);
    else
        printf("NULL\n");
}  /* Print_node */


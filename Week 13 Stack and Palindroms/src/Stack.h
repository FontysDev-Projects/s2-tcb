#ifndef __STACK_H__
#define __STACK_H__
#include <stdlib.h>
#include <stdio.h>

/*
* Creates the new stack. Returns 0 on success
*/
int stack_create(void);

/*
* Destroys the stack.
*/
void stack_destroy(void);

/*
* Pushes a new elemenrt on the stack
* returns 0 on success
* returns -1 on error
*/
int stack_push(const char *elem);

/*
* Pops an element from the stack
* returns 0 on success
* returns -1 on error 
*/
int stack_pop(char *elem);

/*
 * Show the top element of the stack
 * return 0 on success
 * return -1 on error or empty
 */
int stack_top(char *elem);

#endif
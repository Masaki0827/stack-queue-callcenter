#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"


/*
 * Define your call struct here.
 */
typedef struct {
    int id;               // Call ID
    char caller_name[30]; // Caller’s name
    char call_reason[100]; // Call reason
} Call;

// Function prototypes
void receive_call(struct queue* queue);
void answer_call(struct queue* queue, struct stack* stack);
void display_stack(struct stack* stack);
void display_queue(struct queue* queue);
void clear_input_buffer(); // Function to clear input buffer after reading string


int main(int argc, char const *argv[]) {
	struct queue* call_queue = queue_create(); // Create a new queue for incoming calls
    struct stack* answered_calls = stack_create(); // Create a new stack for answered calls
    int option;

    do {
        printf("1. Receive a new call\n");
        printf("2. Answer a call\n");
        printf("3. Current state of the stack   answered calls\n");
        printf("4. Current state of the queue   calls to be answered\n");
        printf("5. Quit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        clear_input_buffer(); // Clear the input buffer after reading an integer

        switch (option) {
            case 1:
                receive_call(call_queue);
                break;
            case 2:
                answer_call(call_queue, answered_calls);
                break;
            case 3:
                display_stack(answered_calls);
                break;
            case 4:
                display_queue(call_queue);
                break;
            case 5:
                printf("Quitting the program.\n");
                break;
            default:
                printf("Invalid option. Please choose again.\n");
        }
    } while (option != 5);

    // Cleanup
    queue_free(call_queue);
    stack_free(answered_calls);
    return 0;
}

/*
 * This function receives a new call from the user.
 *
 * This prompts the user to enter the caller's name and the reason,
 * stores this information in a new `Call` structure, and enqueues the call
 * into the specified queue. The function also sets a unique ID based on
 * the current size of the queue.
 *
 * Params:
 *   queue - the queue to which the new call will be added. It may not be NULL.
 */
void receive_call(struct queue* queue) {
    Call* new_call = (Call*)malloc(sizeof(Call));
   
    printf("Enter caller's name: ");
    fgets(new_call->caller_name, sizeof(new_call->caller_name), stdin);
    strtok(new_call->caller_name, "\n"); // Remove trailing newline

    printf("Enter call reason: ");
    fgets(new_call->call_reason, sizeof(new_call->call_reason), stdin);
    strtok(new_call->call_reason, "\n"); // Remove trailing newline

    new_call->id = queue_size(queue) + 1; // Set call ID based on queue size *note start from 1

    queue_enqueue(queue, (void*)new_call); // Add call to the queue
    printf("The call has been successfully added to the queue!\n");
}

/*
 * This function answers a call from the queue and pushes the answered call 
 * to the stack.
 *
 * It checks if there are any calls in the queue. If the queue is empty, 
 * message is displayed to notice no message, and the function exits early. If 
 * there is a call to be answered, it dequeues the first call from the queue,
 * pushes it onto the stack, and displays the details of the answered call.
 *
 * Params:
 *   queue - the queue from which the call will be answered. It may not be NULL.
 *   stack - the stack where the answered call will be stored. It may not be NULL.
 */
void answer_call(struct queue* queue, struct stack* stack) {
    if (queue_isempty(queue)) {
        printf("No more calls need to be answered at the moment!\n");
        return;
    }

    Call* answered_call = (Call*)queue_dequeue(queue); // Get the first call from the queue
    stack_push(stack, (void*)answered_call); // Push it onto the stack

    printf("The following call has been answered and added to the stack!\n");
    printf("Call ID: %d\n", answered_call->id);
    printf("Caller’s name: %s\n", answered_call->caller_name);
    printf("Call reason: %s\n", answered_call->call_reason);

}

/*  
 * This function displays the current state of the stack, which includes 
 * information about the calls that have been answered.
 *
 * It first checks if the stack is empty. If it is, a message is printed 
 * to indicate that no calls have been answered. If there are answered 
 * calls in the stack, the function retrieves the details of the last 
 * answered call (the top of the stack) and displays the number of 
 * answered calls along with the details of the last call.
 *
 * Params:
 *   stack - the stack containing the answered calls. It may not be NULL.
 */
void display_stack(struct stack* stack) {
    if (stack_isempty(stack)) {
        printf("No calls have been answered yet!\n");
        return;
    }

    Call* last_call = (Call*)stack_top(stack); // Get the last answered call
    printf("Number of calls answered: %d\n", stack_size(stack));
    printf("Details of the last call answered:\n");
    printf("Call ID: %d\n", last_call->id);
    printf("Caller’s name: %s\n", last_call->caller_name);
    printf("Call reason: %s\n", last_call->call_reason);
}

/*
 * This function displays the current state of the queue, which includes 
 * information about the calls that are waiting to be answered.
 *
 * It first checks if the queue is empty. If it is, it prints that there 
 * are no calls to be answered. If there are calls in the queue, the 
 * function retrieves the details of the first call (the front of the 
 * queue) and displays the number of calls waiting to be answered along 
 * with the details of the first call.
 *
 * Params:
 *   queue - the queue containing the calls to be answered. It may not be NULL.
 */
void display_queue(struct queue* queue) {
    if (queue_isempty(queue)) {
        printf("Number of calls to be answered: 0\n");
        return;
    }

    Call* first_call = (Call*)queue_front(queue); // Get the first call in the queue
    printf("Number of calls to be answered: %d\n", queue_size(queue));
    printf("Details of the first call to be answered:\n");
    printf("Call ID: %d\n", first_call->id);
    printf("Caller’s name: %s\n", first_call->caller_name);
    printf("Call reason: %s\n", first_call->call_reason);
}

/*
 * This function clears the input buffer to remove any leftover characters
 * after reading input from the user. This is particularly useful when 
 * using input functions like `scanf` or `fgets`, as these functions may
 * leave extra characters in the buffer, which can affect subsequent input 
 * operations.
 *
 * The function reads characters from the standard input one at a time 
 * until it encounters a newline character or the end of file (EOF).
 *
 * Params:
 *   None.
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n') {}
}
  



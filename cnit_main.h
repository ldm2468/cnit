#ifndef CNIT_MAIN_H
#define CNIT_MAIN_H

#include "cnit.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef DISABLE_COLORS
    #define CONSOLE_GREEN ""
    #define CONSOLE_RED ""
    #define CONSOLE_RESET ""
#else
    #define CONSOLE_GREEN "\033[0;32m"
    #define CONSOLE_RED "\033[0;31m"
    #define CONSOLE_RESET "\033[0m"
#endif

typedef struct cnit_node {
    struct cnit_node *next;
    int (*f)();
    const char *msg;
} cnit_node;

cnit_node cnit_origin = { NULL, NULL, NULL };
cnit_node *cnit_last = &cnit_origin;
int cnit_test_count = 0;

/**
 * Add a new test to be run. The test function must take zero arguments,
 * and return an integer. To signify that the test has failed, use CNIT_FAIL().
 * Return zero at the end of the function to signal that it has succeeded.
 * @param fptr The pointer to the function.
 * @param msg A message that represents the test.
 */
void cnit_add_test(int (*fptr)(), const char *msg) {
    cnit_node *next = (cnit_node *) malloc(sizeof(cnit_node));
    next->next = NULL;
    next->f = fptr;
    next->msg = msg;

    cnit_last->next = next;
    cnit_last = next;
    cnit_test_count++;
}

/**
 * Runs all the added tests. Returns 0 if all tests passed, and non-zero if a test failed.
 * @return 0 if all tests passed, non-zero otherwise.
 */
int cnit_run_tests() {
    cnit_node *curr_node = cnit_origin.next;
    int passed = 0;
    int curr_test = 1;
    printf("Running tests...\n");
    while (curr_node) {
        int line = curr_node->f();
        cnit_node *next_node = curr_node->next;
        if (line) {
            printf("%3d / %3d | " CONSOLE_RED "X" CONSOLE_RESET " | %s | line %d\n",
                   curr_test, cnit_test_count, curr_node->msg, line);
        } else {
            printf("%3d / %3d | " CONSOLE_GREEN "O" CONSOLE_RESET " | %s\n",
                   curr_test, cnit_test_count, curr_node->msg);
            passed++;
        }
        curr_test++;
        free(curr_node);
        curr_node = next_node;
    }
    printf("%d/%d tests passed. (%.0f%%)\n", passed, cnit_test_count, (double) passed / cnit_test_count * 100);
    return passed != cnit_test_count;
}

#endif

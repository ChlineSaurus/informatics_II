#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Functions already implemented */
struct month *init_months(struct month *head);

void free_months(struct month *head);

/* given month struct */
struct month {
    int month_number;
    char *month_name;
    struct month *next;
};

void print_months(struct month *head) {
    struct month *currentMonth = head;
    while (currentMonth != NULL) {
        printf("%s (%d), ", currentMonth->month_name, currentMonth->month_number);
        currentMonth = currentMonth->next;
    }
    printf("\n");
}

struct month *get_previous_month(struct month *head, struct month *searchedMonth) {
    if (head == NULL) {
        printf("Linked-list doesn't contain any elements");
        return NULL;
    } else if (searchedMonth == NULL) {
        printf("Searched month doesn't exist");
        return NULL;
    } else if (searchedMonth == head) {
        return head;
    }

    struct month *currentMonth = head;
    while (currentMonth->next != searchedMonth) {
        currentMonth = currentMonth->next;
        if (currentMonth->next == NULL) {
            printf("Linked-list doesn't contain searched month");
            return NULL;
        }
    }
    return currentMonth;
}

struct month *swap_month(struct month *head, struct month *a, struct month *b) {
    if (a == b) {
        return head;
    }

    struct month *a_prev = get_previous_month(head, a);
    struct month *b_prev = get_previous_month(head, b);
    struct month *temp_b_next = b->next;

    //differentiate between "a and b are neighbours" and "a and b aren't neighbours"
    if (a->next == b) {
        b->next = a;
    } else {
        b->next = a->next;
        b_prev->next = a;
    }

    a->next = temp_b_next;

    //differentiate between "a is at the start" and "a isn't at the start"
    if (a == head) {
        head = b;
    } else {
        a_prev->next = b;
    }
    return head;
}

struct month *selection_sort(struct month *head) {
    struct month * j;
    struct month * current_min;
    struct month * i = head;

    while (i != NULL) {
        current_min = i;
        j = i->next;
        print_months(head);
        while (j != NULL) {
            if (current_min->month_number > j->month_number) {
                current_min = j;
            }
            j = j->next;
        }
        head = swap_month(head, i, current_min);
        i = current_min->next;
    }
    return head;
}

struct month *init_months(struct month *head) {
    int n = 12;
    int init_order[n];
    char *month_strings[] = {"January", "February", "March", "April",
                             "May", "June", "July", "August",
                             "September", "Oktober", "November", "Dezember"};
    struct month *h;
    struct month *p; /* trailing pointer */

    /* create random order with fisher-yates shuffle */
    for (int i = 0; i < n; ++i) {
        init_order[i] = i + 1;
    }
    srand(time(0));
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1); /* generate random index below i */
        /* swap a[i] with a[j] */
        int tmp = init_order[i];
        init_order[i] = init_order[j];
        init_order[j] = tmp;
    }

    /* create month linked list */
    h = malloc(sizeof(struct month)); /* first node, gets returned */
    h->month_number = init_order[0];  /*  */
    h->month_name = month_strings[h->month_number - 1];
    p = h; /* pointer that goes through list */
    for (int i = 1; i < n; ++i) {
        struct month *m = malloc(sizeof(struct month));
        /* printf("create month %d\n", i); */
        m->month_number = init_order[i];
        m->month_name = month_strings[m->month_number - 1];
        p->next = m; /* previous node points now to this */

        p = m; /* increment trailing pointer */
    }
    p->next = NULL;
    return h;
}

void free_months(struct month *head) {
    /* free month linked list */
    struct month *p = head;
    struct month *q = head->next;
    while (q) {
        free(p);
        p = q;
        q = q->next;
    }
    free(p);
}

int main(int argc, char *argv[]) {
    /* Init month linked list */
    struct month *head;
    head = init_months(head);

    /* Print the linked list as it is after initialization */
    print_months(head);

    head = selection_sort(head);
    print_months(head);

    /* Cleanup */
    free_months(head);
    return 0;
}

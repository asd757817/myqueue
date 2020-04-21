#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "queue.h"

struct queue_ele_t *queue_ele_new(char *str)
{
    struct queue_ele_t *new = malloc(sizeof(struct queue_ele_t));

    if (new) {
        new->next = NULL;
        if (str)
            new->value = str;
        return new;
    } else
        return NULL;
}

struct queue_t *queue_new()
{
    struct queue_t *q = malloc(sizeof(struct queue_t));

    if (q) {
        q->dummy = queue_ele_new(NULL);
        q->head = q->dummy;
        q->tail = q->dummy;
        pthread_mutex_init(&q->lock, NULL);
        return q;
    } else
        return NULL;
}

bool queue_insert(struct queue_t *q, struct queue_ele_t *buf)
{
    if (!q || !buf)
        return false;
    else {
        int len = strlen(buf->value);
        struct queue_ele_t *new = malloc(sizeof(struct queue_ele_t));

        new->value = malloc(sizeof(char) * len);
        strncpy(new->value, buf->value, len);

        if (!q->tail->next) {
            q->tail->next = new;
            q->tail = new;
            return true;
        } else {
            return false;
        }
    }
}

int queue_pop(struct queue_t *q, struct queue_ele_t *buf)
{
    if (!q || !buf)
        return -1;
    else {
        if (!q->head->next)
            return 0;
        else {
            struct queue_ele_t *head = q->head;
            memcpy(buf, q->head->next, sizeof(struct queue_ele_t));
            q->head = q->head->next;
            free(head);
            return true;
        }
    }
}

void queue_free(struct queue_t *q)
{
    struct queue_ele_t *next;
    do {
        next = q->head->next;
        free(q->head);
        q->head = next;
    } while (next);

    free(q->head);
}

static void queue_show(struct queue_t *q)
{
    struct queue_ele_t *next = q->head->next;
    if (!next)
        printf(" Queue is empty now.\n");
    else {
        printf(" %s ", next->value);
        next = next->next;
        while (next) {
            printf("-> %s ", next->value);
            next = next->next;
        }
        puts("");
    }
}

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    struct queue_t *q = queue_new();
    printf("==== Queue Init ====\n");
    queue_show(q);

    struct queue_ele_t *node_1, *node_2, *node_3, *buf;
    node_1 = queue_ele_new("N0de!!!");
    node_2 = queue_ele_new("2222222");
    node_3 = queue_ele_new("--333--");
    buf = queue_ele_new(NULL);

    printf("\n==== Insert node_1 ====\n");
    queue_insert(q, node_1);
    queue_show(q);

    printf("\n==== Insert node_2 ====\n");
    queue_insert(q, node_2);
    queue_show(q);

    printf("\n==== Pop out the head ====\n");
    queue_pop(q, buf);
    queue_show(q);

    printf("\n==== Insert node_3 ====\n");
    queue_insert(q, node_3);
    queue_show(q);

    printf("\n==== Pop out the head ====\n");
    queue_pop(q, buf);
    queue_show(q);

    printf("\n==== Show the value of buf ====\n");
    printf("\n buf->value is %s \n", buf->value);

    printf("\n==== Pop out the head ====\n");
    queue_pop(q, buf);
    queue_show(q);

    return 0;
}


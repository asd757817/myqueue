#include <pthread.h>
#include <stdlib.h>

struct queue_ele_t {
    struct queue_ele_t *next;
    char *value;
};

struct queue_t {
    struct queue_ele_t *head;
    struct queue_ele_t *tail;
    struct queue_ele_t *dummy;
    pthread_mutex_t lock;
};

struct queue_ele_t *queue_ele_new(char *str);
struct queue_t *queue_new();
bool queue_insert(struct queue_t *q, struct queue_ele_t *buf);
int queue_pop(struct queue_t *q, struct queue_ele_t *buf);
void queue_free(struct queue_t *q);


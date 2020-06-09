#ifndef __data_table_h__
#define __data_table_h__

#include <stdbool.h>
#include <stdint.h>

#define table_get_as(type, table, key) \
  ((type*)table_get((table), (key))) 

typedef void (*table_fun_t)(void*);

struct bucket {
  uint32_t hash;
  char *key;
  void *item;
  struct bucket *next;
};

typedef struct table {
  int count;
  int capacity;
  struct bucket **buckets;
} table_t;

extern table_t *table_create(int initial_capacity);
extern void     table_free(table_t *table);

extern bool  table_contains(const table_t *table, const char *key);
extern void *table_get(const table_t *table, const char *key);
extern void  table_set(table_t *table, const char *key, void *item);

extern void  table_foreach(table_t *table, table_fun_t fun);

extern void  table_remove(table_t *table, const char *key, table_fun_t fun);

#endif // __data_table_h__


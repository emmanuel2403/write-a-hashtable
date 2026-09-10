#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"

static void test_create_table(void)
{
    ht_hash_table* ht = ht_new();

    assert(ht != NULL);

    ht_del_hash_table(ht);

    printf("test_create_table passed\n");
}

static void test_insert_and_search(void)
{
    ht_hash_table* ht = ht_new();

    ht_insert(ht, "name", "Emmanuel");

    char* result = ht_search(ht, "name");

    assert(result != NULL);
    assert(strcmp(result, "Emmanuel") == 0);

    ht_del_hash_table(ht);

    printf("test_insert_and_search passed\n");
}

static void test_multiple_insertions(void)
{
    ht_hash_table* ht = ht_new();

    ht_insert(ht, "language", "C");
    ht_insert(ht, "project", "Hash Table");
    ht_insert(ht, "editor", "VS Code");

    assert(strcmp(ht_search(ht, "language"), "C") == 0);
    assert(strcmp(ht_search(ht, "project"), "Hash Table") == 0);
    assert(strcmp(ht_search(ht, "editor"), "VS Code") == 0);

    ht_del_hash_table(ht);

    printf("test_multiple_insertions passed\n");
}

static void test_missing_key(void)
{
    ht_hash_table* ht = ht_new();

    char* result = ht_search(ht, "does_not_exist");

    assert(result == NULL);

    ht_del_hash_table(ht);

    printf("test_missing_key passed\n");
}

static void test_update_existing_key(void)
{
    ht_hash_table* ht = ht_new();

    ht_insert(ht, "language", "C");
    ht_insert(ht, "language", "Python");

    char* result = ht_search(ht, "language");

    assert(result != NULL);
    assert(strcmp(result, "Python") == 0);

    ht_del_hash_table(ht);

    printf("test_update_existing_key passed\n");
}

static void test_delete(void)
{
    ht_hash_table* ht = ht_new();

    ht_insert(ht, "name", "Emmanuel");

    assert(ht_search(ht, "name") != NULL);

    ht_delete(ht, "name");

    assert(ht_search(ht, "name") == NULL);

    ht_del_hash_table(ht);

    printf("test_delete passed\n");
}

static void test_delete_missing_key(void)
{
    ht_hash_table* ht = ht_new();

    ht_insert(ht, "one", "1");

    ht_delete(ht, "missing");

    assert(strcmp(ht_search(ht, "one"), "1") == 0);

    ht_del_hash_table(ht);

    printf("test_delete_missing_key passed\n");
}

static void test_many_items(void)
{
    ht_hash_table* ht = ht_new();

    char key[32];
    char value[32];

    for (int i = 0; i < 1000; i++) {
        snprintf(key, sizeof(key), "key_%d", i);
        snprintf(value, sizeof(value), "value_%d", i);

        ht_insert(ht, key, value);
    }

    for (int i = 0; i < 1000; i++) {
        snprintf(key, sizeof(key), "key_%d", i);
        snprintf(value, sizeof(value), "value_%d", i);

        char* result = ht_search(ht, key);

        assert(result != NULL);
        assert(strcmp(result, value) == 0);
    }

    ht_del_hash_table(ht);

    printf("test_many_items passed\n");
}

static void test_delete_many_items(void)
{
    ht_hash_table* ht = ht_new();

    char key[32];
    char value[32];

    for (int i = 0; i < 100; i++) {
        snprintf(key, sizeof(key), "key_%d", i);
        snprintf(value, sizeof(value), "value_%d", i);

        ht_insert(ht, key, value);
    }

    for (int i = 0; i < 50; i++) {
        snprintf(key, sizeof(key), "key_%d", i);
        ht_delete(ht, key);
    }

    for (int i = 0; i < 50; i++) {
        snprintf(key, sizeof(key), "key_%d", i);

        assert(ht_search(ht, key) == NULL);
    }

    for (int i = 50; i < 100; i++) {
        snprintf(key, sizeof(key), "key_%d", i);
        snprintf(value, sizeof(value), "value_%d", i);

        char* result = ht_search(ht, key);

        assert(result != NULL);
        assert(strcmp(result, value) == 0);
    }

    ht_del_hash_table(ht);

    printf("test_delete_many_items passed\n");
}

int main(void)
{
    test_create_table();
    test_insert_and_search();
    test_multiple_insertions();
    test_missing_key();
    test_update_existing_key();
    test_delete();
    test_delete_missing_key();
    test_many_items();
    test_delete_many_items();

    printf("\nAll hash table tests passed!\n");

    return 0;
}
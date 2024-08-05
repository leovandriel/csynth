#include "../../src/mem/key_list.h"
#include "../util/test.h"

void test_key_list_add(void)
{
    KeyList list = {0};
    KeyboardEvent event = {.time = 1, .key = 2};
    assert_long_equal(key_list_add(&list, event), csErrorNone);
    event = (KeyboardEvent){.time = 3, .key = 4};
    assert_long_equal(key_list_add(&list, event), csErrorNone);
    assert_long_equal(list.head->time, 1);
    assert_long_equal(list.head->key, 2);
    assert_long_equal(list.head->next->time, 3);
    assert_long_equal(list.head->next->key, 4);
    assert_ptr_equal(list.head->next, list.tail);
    key_list_clear(&list);
}

void test_key_list_file(void)
{
    KeyList list1 = {0};
    key_list_add(&list1, (KeyboardEvent){.time = 1, .key = 2});
    key_list_add(&list1, (KeyboardEvent){.time = 3, .key = 4});
    char buffer[1024] = {0};
    FILE *file1 = fmemopen(buffer, sizeof(buffer), "w");
    key_list_write_file(&list1, file1);
    assert_long_equal(fclose(file1), 0);
    assert_string_equal(buffer, "2 1000\n4 3000\n");
    key_list_clear(&list1);
    FILE *file2 = fmemopen(buffer, sizeof(buffer), "r");
    KeyList list2 = {0};
    key_list_read_file(&list2, file2);
    assert_long_equal(fclose(file2), 0);
    assert_long_equal(list2.head->time, 1);
    assert_long_equal(list2.head->key, 2);
    assert_long_equal(list2.head->next->time, 3);
    assert_long_equal(list2.head->next->key, 4);
    key_list_clear(&list2);
}

void test_key_list(void)
{
    test_key_list_add();
    test_key_list_file();
}
#include "../../src/mem/key_list.h"
#include "../util/test.h"

void test_key_list(void)
{
    KeyList list = NULL;
    KeyboardEvent event = {
        .time = 1,
        .key = 2,
    };
    assert_long_equal(key_list_add(&list, event), csErrorNone);
    event = (KeyboardEvent){
        .time = 3,
        .key = 4,
    };
    assert_long_equal(key_list_add(&list, event), csErrorNone);
    assert_long_equal(list->time, 3);
    assert_long_equal(list->key, 4);
    assert_long_equal(list->next->time, 1);
    assert_long_equal(list->next->key, 2);
    key_list_clear(&list);
}

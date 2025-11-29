#include "../../src/util/note.h"
#include "./test.h"
#include <math.h>
#include <string.h>

void test_note_frequency_to_offset(void)
{
    assert_double_equal(note_frequency_to_index(440.0), 57.0);
    assert_double_equal(note_frequency_to_index(880.0), 69.0);
    assert_double_equal(note_frequency_to_index(220.0), 45.0);
    double c5_offset = note_frequency_to_index(523.25);
    assert_double_equal(c5_offset, 59.9999625927725972);
    double low_offset = note_frequency_to_index(1.0);
    assert_double_equal(low_offset, -48.3763165622959193);
    double high_offset = note_frequency_to_index(20000.0);
    assert_double_equal(high_offset, 123.0762319922974797);
}

void test_note_ij_to_string(void)
{
    char buffer[32];
    int result;

    result = note_ij_to_string(48, 0, buffer, sizeof(buffer));
    assert_long_equal(result, (int)strlen("C4"));
    assert_string_equal(buffer, "C4");

    result = note_ij_to_string(50, 0, buffer, sizeof(buffer));
    assert_long_equal(result, (int)strlen("D4"));
    assert_string_equal(buffer, "D4");

    result = note_ij_to_string(52, 0, buffer, sizeof(buffer));
    assert_long_equal(result, (int)strlen("E4"));
    assert_string_equal(buffer, "E4");

    result = note_ij_to_string(53, 0, buffer, sizeof(buffer));
    assert_long_equal(result, (int)strlen("F4"));
    assert_string_equal(buffer, "F4");

    result = note_ij_to_string(55, 0, buffer, sizeof(buffer));
    assert_long_equal(result, (int)strlen("G4"));
    assert_string_equal(buffer, "G4");

    result = note_ij_to_string(57, 0, buffer, sizeof(buffer));
    assert_long_equal(result, (int)strlen("A4"));
    assert_string_equal(buffer, "A4");

    result = note_ij_to_string(59, 0, buffer, sizeof(buffer));
    assert_long_equal(result, (int)strlen("B4"));
    assert_string_equal(buffer, "B4");

    result = note_ij_to_string(60, 0, buffer, sizeof(buffer));
    assert_long_equal(result, (int)strlen("C5"));
    assert_string_equal(buffer, "C5");

    result = note_ij_to_string(36, 0, buffer, sizeof(buffer));
    assert_long_equal(result, (int)strlen("C3"));
    assert_string_equal(buffer, "C3");

    result = note_ij_to_string(48, 0, buffer, 2);
    assert_long_equal(result, 2);
}

void test_note_offset_to_string(void)
{
    char buffer[32];
    note_index_to_string(57.0, buffer, sizeof(buffer));
    assert_string_equal(buffer, "A4");
    note_index_to_string(69.0, buffer, sizeof(buffer));
    assert_string_equal(buffer, "A5");
    note_index_to_string(45.0, buffer, sizeof(buffer));
    assert_string_equal(buffer, "A3");
    note_index_to_string(48.0, buffer, sizeof(buffer));
    assert_string_equal(buffer, "C4");
    note_index_to_string(60.0, buffer, sizeof(buffer));
    assert_string_equal(buffer, "C5");
    note_index_to_string(0.0, buffer, sizeof(buffer));
    assert_not_null(buffer);
    note_index_to_string(3.86, buffer, sizeof(buffer));
    assert_not_null(buffer);
    note_index_to_string(58.0, buffer, sizeof(buffer));
    assert_not_null(buffer);
    note_index_to_string(56.0, buffer, sizeof(buffer));
    assert_not_null(buffer);
    note_index_to_string(59.0, buffer, sizeof(buffer));
    assert_string_equal(buffer, "B4");
    note_index_to_string(55.0, buffer, sizeof(buffer));
    assert_string_equal(buffer, "G4");
}

void test_note(void)
{
    test_note_frequency_to_offset();
    test_note_ij_to_string();
    test_note_offset_to_string();
}

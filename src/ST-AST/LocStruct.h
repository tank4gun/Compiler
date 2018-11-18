#pragma once

struct LocStruct {
    LocStruct(const LocStruct &other) {
        first_line = other.first_line;
        first_column = other.first_column;
        last_line = other.last_line;
        last_column = other.last_column;
    }

    LocStruct() {
        first_line = 1;
        first_column = 1;
        last_line = 1;
        last_column = 1;
    }
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};
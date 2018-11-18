#pragma once

typedef struct YYLTYPE
{
    int first_line = -1;
    int first_column = -1;
    int last_line = -1;
    int last_column = -1;
} YYLTYPE;
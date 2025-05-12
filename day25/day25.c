#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int day25_pt1();
int day25_pt2();

const int DAY25_ROW = 3010;
const int DAY25_COL = 3019;
const uint64_t DAY25_INIT_CODE = 20151125;

int day25_pt1()
{
    int diag = 1;
    int row = 1;
    int col = 1;
    uint64_t prev = DAY25_INIT_CODE;
    uint64_t curr = 1;
    int elems = 1;

    while (row != DAY25_ROW || col != DAY25_COL)
    {
        if (elems == diag)
        {
            row = diag + 1;
            col = 1;
            diag++;
            elems = 1;
        }
        else
        {
            row--;
            col++;
            elems++;
        }
        curr = (prev * 252533) % 33554393;
        prev = curr;
    }

    return curr;
}
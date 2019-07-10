#include <iostream>
#include <algorithm>

using namespace std;

/*
row[8] : row # for each queen
TC : Traceback counter
(a,b) : 1st queen placement at (r = a, c = b)
*/
int row[8], TC, a, b, line_counter;
bool place(int r, int c)
{
    // check previously placed queens
    for (int prev = 0; prev < c; prev++)
    {
        // check if same row or same diagonal
        if (row[prev] == r || (abs(row[prev] - r) == abs(prev - c)))
        {
            return false;
        }
    }
    return true;
}

void backtrack(int c)
{
    // candidata solution; (a,b) has 1 initial queen
    if (c == 8 && row[b] == a)
    {
        printf_s("%2d %d", ++line_counter, row[0] + 1);
        for (int j = 0; j < 8; j++)
        {
            printf_s("%d", row[j] + 1);
            printf_s(" ");
        }
        printf_s("\n");
    }

    // try all possible rows
    for (int r = 0; r < 8; r++)
    {
        if (place(r,c))
        {
            row[c] = r; // place a queen at this col and row
            backtrack(c + 1);
        }
    }
}

int main()
{
    scanf_s("%d", &TC);
    while (TC--)
    {
        scanf_s("%d %d", &a, &b);
        a--;
        b--;
        memset(row, 0, sizeof(row));
        line_counter = 0;
        printf_s("Solution column \n");
        printf_s("# 1 2 3 4 5  6 8 8 \n");
        backtrack(0);
        if (TC)
        {
            printf_s("\n");
        }
    }
    return 0;
}

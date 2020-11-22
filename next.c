#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define max_depth 8

typedef struct
{
    int     depth;
}           stack;


char     backet[1000];


void        check_for_casts(char casted[1000])
{
    for (int i = 0; i < 1000; i++)
    {
        if (casted[i] != 0)
            printf("%d ", i);
    }
    printf("\n");
}

int              calculate_score(int *inv, int *other)
{
    int total;
    total = 0;
    for (int i = 0; i < 4; i++)
        total += (inv[i] + other[i]) * (i + 1);
    return total;
}

void            update_inv(int  *inv, int *cast)
{
    for (int i = 0; i < 4; i++)
        inv[i] += cast[i];
}

int            check_balance(int *inv, int *target)
{
    for (int i = 0; i < 4; i++)
    {
        if ((inv[i] + target[i]) < 0)
            return (0);
    }
    return (1);
}

int             is_enough(int *inv, int *other)
{
    int total = 0;


    for (int i = 0; i < 4; i++)
    {
        total += inv[i] + other[i];
    }
    if (total > 10)
        return 0;
    return (1);
}

int             get_current_casts_length(int  **casts, int len_casts, int *inv, char *casted)
{
    int     len;

    len = 0;
    for (int i = 0; i < len_casts; i++)
    {
        if (check_balance(inv, casts[i]) && (!casted[casts[i][4] * casts[i][6]]) && is_enough(inv, casts[i]))
            len++;
    }
    return (len);
}
 
int             **get_current_casts(int **casts, int len_casts, int *inv, int *current_length, char *casted)
{
    *current_length = get_current_casts_length(casts, len_casts, inv, casted);
    int  **current_casts = malloc(sizeof(char *) * (*current_length));
    int len;

    len = 0;
    for (int i = 0; i < len_casts; i++)
    {
        if (check_balance(inv, casts[i]) && (!casted[casts[i][4] * casts[i][6]]) && is_enough(inv, casts[i]))
        {
            current_casts[len] = casts[i];
            len++;
        }
    }
    return (current_casts);
}




int         *create_inv(int a, int b, int c, int d, int score)
{
    int *inv = malloc(sizeof(int ) * 5);
    inv[0] = a;
    inv[1] = b;
    inv[2] = c;
    inv[3] = d;
    inv[4] = score;
    return (inv);
}

void         insert_cast(int **casts, int *cast, int *len_cast)
{
    casts[*len_cast] = cast;
    (*len_cast)++;
}

int         *create_cast(int a, int b, int c, int d, int id, int repeatable, int times)
{
    int     *cast = malloc(sizeof(int) * 7);
    cast[0] = a * times;
    cast[1] = b * times;
    cast[2] = c * times;
    cast[3] = d * times;
    cast[4] = id;
    cast[5] = repeatable;
    cast[6] = times;
    return (cast);
}

void       free_casts(int ***addr_casts)
{
    int **casts = *addr_casts;
    for (int i = 0; i < 30; i++)
        free(casts[i]);
    free(*addr_casts);
}


int         *create_target(int a, int b, int c, int d, int id, int price)
{
    int     *cast = malloc(sizeof(int) * 7);
    cast[0] = a;
    cast[1] = b;
    cast[2] = c;
    cast[3] = d;
    cast[4] = id;
    cast[5] = price;
    return (cast);
}

int        looking_for_target(int *start, int *end, int **casts, int len_casts, char casted[1000], int *found, int depth)
{
    if (depth == max_depth)
    {
        *found = 0;
        return (10000);
    }
    if (check_balance(start, end))
    {
        *found = 1;
        return (depth);
    }
    char        rest_cast[1000];
    int         vinv[4];
    int         casts_length;
    int         **current_casts;
    int         ltarget;
    int         ntarget;

    memset(vinv, 0, sizeof(char) * 1000);
    current_casts = get_current_casts(casts, len_casts, start, &casts_length, casted);
    memset(rest_cast, 0, sizeof(char) * 1000);
    for (int i = 0; i < casts_length; i++)
        rest_cast[current_casts[i][4] * current_casts[i][6]] = 1;
    ltarget = looking_for_target(start, end, casts, len_casts, rest_cast, found,  depth + 1);
    for (int i = 0; i < casts_length; i++)
    {
        memcpy(vinv, start, sizeof(int) * 4);
        update_inv(vinv, current_casts[i]);
        memcpy(rest_cast, casted, sizeof(char) * 1000);
        rest_cast[current_casts[i][4] * current_casts[i][6]] = 1;
        ntarget = looking_for_target(vinv, end, casts, len_casts, rest_cast, found, depth + 1);
        ltarget = fmin(ltarget, ntarget);
    }
    free(current_casts);
    return (ltarget);
}

int        *get_best_cast(int *start, int *end, int **casts, int len_casts, char casted[1000],int *found, int depth)
{
    char        rest_cast[1000];
    int         vinv[4];
    int         casts_length;
    int         **current_casts;
    int         ltarget;
    int         ntarget;
    int         *to_cast;
    memset(vinv, 0, sizeof(char) * 1000);
    current_casts = get_current_casts(casts, len_casts, start, &casts_length, casted);
    memset(rest_cast, 0, sizeof(char) * 1000);
    for (int i = 0; i < casts_length; i++)
        rest_cast[current_casts[i][4] * current_casts[i][6]] = 1;
    ltarget = looking_for_target(start, end, casts, len_casts, rest_cast, found, depth + 1);
    to_cast = NULL;
    for (int i = 0; i < casts_length; i++)
    {
        memcpy(vinv, start, sizeof(int) * 4);
        update_inv(vinv, current_casts[i]);
        memcpy(rest_cast, casted, sizeof(char) * 1000);
        rest_cast[current_casts[i][4] * current_casts[i][6]] = 1;
        ntarget = looking_for_target(vinv, end, casts, len_casts, rest_cast, found, depth + 1);
        if (ltarget >= ntarget)
        {
            to_cast = current_casts[i];
            ltarget = ntarget;
        }
    }
    free(current_casts);
    return (to_cast);
}
int arr[21][7] = {
    { 2,  0,  0,  0, 78,  0,  1},
    {-1,  1,  0,  0, 79,  0,  1},
    { 0, -1,  1,  0, 80,  0,  1},
    { 0,  0, -1,  1, 81,  0,  1},
    { 0,  6,  4, -4, 31,  1,  2},
    { 0,  9,  6, -6, 31,  1,  3},
    { 0,  3,  2, -2, 31,  1,  1},
    {-6,  0,  0,  2,  0,  1,  2},
    {-9,  0,  0,  3,  0,  1,  3},
    {-3,  0,  0,  1,  0,  1,  1},
    {-8,  0,  4,  0, 11,  1,  2},
    {-12, 0, 6, 0, 11, 1, 3},
    {-4,  0,  2,  0, 11,  1,1},
    { 8,  2, -2,  0, 28,  1, 2},
    {12,  3, -3,  0, 28,  1, 3},
    { 4,  1, -1,  0, 28,  1, 1},
    { 0,  0, -4,  4, 39,  1, 2},
    { 0,  0, -6,  6, 39,  1, 3},
    { 0,  0, -2,  2, 39,  1, 1},
    {1, 1, 0, 0, 50, 1, 1},
    {0, 0, 0, 1, 40 , 1, 1}
};


int        main(void)
{
    int *target = create_target(0, -2, -2, -2, 72, 22);
    int *inv = create_inv(3, 0, 0, 0, 0);
    int found;

    int **casts = malloc(sizeof(int *) * 30);
    for (int i = 0; i < 21; i++)
    {
        casts[i] = create_cast(arr[i][0], arr[i][1], arr[i][2], arr[i][3],
        arr[i][4], arr[i][5], arr[i][6]);
    }
    char casted[1000];
    memset(casted, 0, sizeof(char) * 1000);
    for (int i = 0; i < 6; i++)
    {
        int *less = get_best_cast(inv, target, casts, 21, casted, &found, 0);
        printf("found %d\n", found);
        printf("\n");
        if (!less)
        {
            printf("Rest\n");
            memset(casted, 0, sizeof(char) * 1000);
            continue;
        }
        casted[less[4] * less[6]] = 1;
        update_inv(inv, less);
    }
    for (int i = 0; i < 4; i++)
        printf("%d ", inv[i]);
    printf("\n");
    return (0);
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char     backet[1000];
int     len = 0;

typedef struct
{
    int      score;
    int      depth;
}       step_tuple;


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
    int prime[] = {2,3,7,13};
    total = 0;
    for (int i = 0; i < 4; i++)
        total += (inv[i] + other[i]) * prime[i];
    return total;
}

int         calculate_best(int *inv, int *target)
{
    int total = 0;

    for (int i = 0; i < 4; i++)
    {
        if ((target[i] + inv[i]) < 0)
            total += (inv[i] + target[i]) * pow(10, i + 1);
    }
    return (total);
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

void display_vect(int *vect, int n)
{
    for (int i =0; i < n; i++)
        printf(". ");
    printf("vect ");
    for (int i = 0; i < 4; i++)
        printf("%d ", vect[i]);
    printf("\n");
}
step_tuple      *next_step(int **casts, int len_casts, int *my_inv, int *target, char casted[1000], int depth)
{
    step_tuple      *step = malloc(sizeof(step_tuple));
    step_tuple      *next_one;
    int             current_len;
    int             **current_casts;
    char            rest_cast[1000];
    int             *vertual_inv;

    vertual_inv = malloc(sizeof(int) * 4);
    if (check_balance(my_inv, target))
    {
        step->score = abs(calculate_best(my_inv, target));
        step->depth = depth;
    }
    else if (depth == 0)
    {
        step->score = abs(calculate_best(my_inv, target));
        step->depth = depth;
    }
    else
    {
        current_casts = get_current_casts(casts, len_casts, my_inv, &current_len, casted);
        memset(rest_cast, 0, sizeof(char) * 1000);
        for (int index = 0; index < current_len; index++)
            rest_cast[current_casts[index][4] * current_casts[index][6]] = 1;

        next_one = next_step(casts, len_casts, my_inv, target, rest_cast, depth - 1);
        step->score = next_one->score;
        step->depth = next_one->depth;
        free(next_one);
        for (int idx = 0; idx < current_len; idx++)
        {
            memcpy(rest_cast, casted, sizeof(char) * 1000);
            rest_cast[current_casts[idx][4] * current_casts[idx][6]] = 1;
            memcpy(vertual_inv, my_inv, sizeof(int) * 4);
            update_inv(vertual_inv, current_casts[idx]);
            next_one = next_step(casts, len_casts, vertual_inv, target, rest_cast, depth - 1);
            if (step->score > next_one->score)
            {
                step->score = next_one->score;
                step->depth = next_one->depth;
            }
            else if (step->score == next_one->score)
                step->depth = fmax(step->depth, next_one->depth);
            free(next_one);
        }
        free(current_casts);
    }
    free(vertual_inv);
    return (step);
}


int     *best_step(int **casts, int len_casts, int *my_inv, int *target, char casted[1000], int depth)
{
    step_tuple      *next_one;
    int             current_len;
    int             **current_casts;
    char            rest_cast[1000];
    int             vertual_inv[4];
    int             min_score;
    int             *best_cast;
    int             max_depth;

    memset(vertual_inv, 0, sizeof(int) * 4);
    current_casts = get_current_casts(casts, len_casts, my_inv, &current_len, casted);
    memset(rest_cast, 0, sizeof(char) * 1000);
    for (int index = 0; index < current_len; index++)
        rest_cast[current_casts[index][4] * current_casts[index][6]] = 1;
    next_one = next_step(casts, len_casts, my_inv, target, rest_cast, depth - 1);
    min_score = next_one->score;
    max_depth = next_one->depth;
    best_cast = NULL;
    free(next_one);
    for (int idx = 0; idx < current_len; idx++)
    {
        memcpy(rest_cast, casted, sizeof(char) * 1000);
        rest_cast[current_casts[idx][4] * current_casts[idx][6]] = 1;
               
        memcpy(vertual_inv, my_inv, sizeof(int) * 4);
        update_inv(vertual_inv, current_casts[idx]);
        next_one = next_step(casts, len_casts, vertual_inv, target, rest_cast, depth - 1);
        if (min_score > next_one->score)
        {
            min_score = next_one->score;
            max_depth = next_one->depth;
            best_cast = current_casts[idx];
        }
        else if (min_score == next_one->score && max_depth <= next_one->depth)
        {
            max_depth = next_one->depth;
            best_cast = current_casts[idx];
        }
        free(next_one);
    }
    free(current_casts);
    return (best_cast);
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

int         count_number_steps(int *inv, int *target, int **casts, int len_casts, char casted[1000])
{
    int     vertual_inv[4];
    char    vertual_casted[1000];
    int     *cast;
    memcpy(vertual_casted, casted, sizeof(char) * 1000);
    memcpy(vertual_inv, inv, sizeof(int) * 4);
    for (int i  = 0; i < 20; i++)
    {
        cast = best_step(casts, len_casts, vertual_inv, target, vertual_casted, 6);
        if (!cast)
        {
            printf("problem\n");
            memset(vertual_casted, 0, 1000 * sizeof(char));
            continue;
        }
        update_inv(vertual_inv, cast);
        display_vect(vertual_inv, 0);
        if (check_balance(vertual_inv, target))
            return (i);
    }
    return (-1);
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
int         main(void)
{
    memset(backet, 0, sizeof(char) * 1000);
    int *inv = create_inv(3, 0, 0, 0, 0);
    int *target = create_target(-1, -1, -1, -1, 21, 22);
    int **casts = malloc(sizeof(int *) * 30);
    int cast_length = 21;
    for (int i = 0; i < 21; i++)
        casts[i] = create_cast(arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6]);
    printf("number of steps %d\n", count_number_steps(inv, target, casts, 21, backet));
    free(inv);
    free(target);
    free_casts(&casts);
    return (0);
}
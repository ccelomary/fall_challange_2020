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
        if (inv[i] + target[i] < 0)
            return (0);
    }
    return (1);
}

int             is_enough(int   *inv, int *other)
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

int             get_current_casts_length(int  **casts, int len_casts, int *inv)
{
    int     len;

    len = 0;
    for (int i = 0; i < len_casts; i++)
    {
        if (check_balance(inv, casts[i]))
            len++;
    }
    return (len);
}

int             **get_current_casts(int **casts, int len_casts, int *inv, int *current_length, char *casted)
{
    *current_length = get_current_casts_length(casts, len_casts, inv);
    int  **current_casts = malloc(sizeof(char *) * (*current_length));
    int len;

    len = 0;
    for (int i = 0; i < len_casts; i++)
    {
        if (check_balance(inv, casts[i]) && (!casted[casts[i][4] * casts[i][6]]))
        {
            current_casts[len] = casts[i];
            len++;
        }
    }
    return (current_casts);
}

step_tuple      *next_step(int **casts, int len_casts, int *my_inv, int *target, char casted[1000], int depth)
{
    step_tuple      *step = malloc(sizeof(step_tuple));
    step_tuple      *next_one;
    int             current_len;
    int             **current_casts;
    char            rest_cast[1000];
    int             vertual_inv[4];
    if (check_balance(my_inv, target))
    {
        step->score = abs(calculate_score(my_inv, target));
        step->depth = depth;
    }
    else if (depth == 0)
    {
        step->score = abs(calculate_score(my_inv, target));
        step->depth = depth;
    }
    else
    {
        memset(vertual_inv, 0, sizeof(int) * 4);
        current_casts = get_current_casts(casts, len_casts, my_inv, &current_len, casted);
        memset(rest_cast, 0, sizeof(char) * 1000);
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
                step->depth = fmin(step->depth, next_one->depth);
            free(next_one);
        }
    }
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
        else if (min_score == next_one->score && max_depth < next_one->depth)
        {
            max_depth = next_one->depth;
            best_cast = current_casts[idx];
        }
        free(next_one);
    }
    return (best_cast);
}



int         main(void)
{
    return (0);
}
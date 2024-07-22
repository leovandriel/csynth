//
// func_tools.h - A collection of tools for working with functions.
//
#ifndef CSYNTH_FUNC_TOOLS_H
#define CSYNTH_FUNC_TOOLS_H

#include "../core/func.h"

#define FUNC_STATS_MAX 1000

void func_print_name(const char *name)
{
    size_t name_len = strlen(name);
    bool has_eval = name_len > 5 && strncmp(name + name_len - 5, "_eval", 5) == 0;
    printf("%.*s", (int)name_len - (has_eval ? 5 : 0), name);
}

void func_print_indent(Func *func, size_t indent)
{
    func_print_name(func->name);
    printf("(");
    const char *start = func->arg_names;
    for (size_t i = 0, j = 0; i < func->count; i++)
    {
        const char *end = strchr(start, ',');
        if (i > 0)
        {
            printf(",");
        }
        printf("\n");
        for (size_t i = 0; i < indent; i++)
        {
            printf("  ");
        }
        if (end != NULL)
        {
            printf("%.*s", (int)(end - start), start);
            end++;
            if (*end == ' ')
            {
                end++;
            }
            if (*end != '\0')
            {
                start = end;
            }
        }
        else
        {
            if (i < func->count - 1 || j > 0)
            {
                printf("%s%ld", start, j++);
            }
            else
            {
                printf("%s", start);
            }
        }
        printf(" = ");
        func_print_indent(func->args[i], indent + 1);
    }
    if (func->count > 0)
    {
        printf("\n");
        for (size_t i = 1; i < indent; i++)
        {
            printf("  ");
        }
    }
    printf(")");
}

void func_print(Func *func)
{
    func_print_indent(func, 1);
    printf(";\n");
}

typedef struct
{
    const char *name;
    size_t count;
} FuncStatItem;

typedef struct
{
    FuncStatItem items[FUNC_STATS_MAX];
    size_t count;
} FuncStat;

void func_stats_add(FuncStat *stat, Func *func)
{
    for (size_t i = 0; i < func->count; i++)
    {
        func_stats_add(stat, func->args[i]);
    }
    for (size_t i = 0; i < stat->count; i++)
    {
        if (stat->items[i].name == func->name)
        {
            stat->items[i].count++;
            return;
        }
    }
    if (stat->count < FUNC_STATS_MAX)
    {
        stat->items[stat->count++] = (FuncStatItem){.name = func->name, .count = 1};
    }
    else
    {
        fprintf(stderr, "func_stat_add: Exceeded maximum number of items\n");
    }
}

int func_stats_compare(FuncStatItem *item_a, FuncStatItem *item_b)
{
    return item_a->count != item_b->count ? (int)(item_a->count - item_b->count) : strcmp(item_a->name, item_b->name);
}

FuncStat func_stats(Func *func)
{
    FuncStat stat = {0};
    func_stats_add(&stat, func);
    qsort(stat.items, stat.count, sizeof(FuncStatItem), (int (*)(const void *, const void *))func_stats_compare);
    return stat;
}

void func_stats_print(Func *func)
{
    FuncStat stat = func_stats(func);
    size_t sum = 0;
    printf("Func stats:\n");
    for (size_t i = 0; i < stat.count; i++)
    {
        printf("  ");
        func_print_name(stat.items[i].name);
        printf(": %ld\n", stat.items[i].count);
        sum += stat.items[i].count;
    }
    printf("Total: %ld\n", sum);
}

#endif // CSYNTH_FUNC_TOOLS_H

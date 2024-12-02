#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SIZE 1000

char **get_input(char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read = 0;
    char **input = NULL;
    
    if (NULL == filename)
        return NULL;
    input = malloc(sizeof(char *) * DATA_SIZE);
    if (NULL == input)
        return NULL;
    fp = fopen(filename, "r");
    if (NULL == fp)
    {
        free(input);
        return NULL;
    }
    for (int i = 0; -1 != (read = getline(&line, &len, fp)); i += 1)
    {
        input[i] = malloc(sizeof(char) * read);
        if (NULL == input[i])
        {
            for (int y = 0; NULL != input[y]; y += 1)
                free(input[y]);
            free(input);
            if (NULL != line)
                free(line);
            return NULL;
        }
        strncpy(input[i], line, read);
        input[i][read - 1] = '\0';
    }
    fclose(fp);
    if (NULL != line)
        free(line);
    return input;
}

int *report_to_int_array(char *report)
{
    int *array = NULL;
    char *tmp = NULL;
    size_t len = 0;

    if (NULL == report)
        return NULL;
    tmp = calloc(strlen(report) + 1, sizeof(char));
    if (NULL == tmp)
        return NULL;
    strncpy(tmp, report, strlen(report));
    for (const char *c = report; NULL != (c = strchr(c, ' ')); c += 1, len += 1);
    array = malloc(sizeof(int) * len + 1);
    if (NULL == array)
    {
        free(tmp);
        return NULL;
    }
    array[0] = atoi(strtok(tmp, " "));
    for (int i = 1; i < len + 1; i += 1)
        array[i] = atoi(strtok(NULL, " "));
    free(tmp);
    return array;
}

int check_safety(int *report, size_t size, int skip)
{
    int op = 0;
    int cmp = 0;

    if (NULL == report)
        return 1;
    op = 1 == skip ? (report[2] - report[0]) : (report[1] - report[0]);
    for (int i = 1; i < size; i += 1)
    {
        if (i == skip)
            continue;
        cmp = (i - 1) == skip ? report[i] - report[i - 2] : report[i] - report[i - 1];
        if (cmp == 0 || abs(cmp) > 3 || (op * cmp) < 0)
            return 1;
    }
    return 0;
}

unsigned int count_safe(char **input)
{
    unsigned int count = 0;
    int *report = NULL;
    size_t len = 0;

    for (int i = 0; i < DATA_SIZE; i += 1)
    {
        len = 0;
        report = report_to_int_array(input[i]);
        for (const char *c = input[i]; NULL != (c = strchr(c, ' ')); c += 1, len += 1);
        if (0 == check_safety(report, len + 1, -1))
            count += 1;
        free(report);
    }
    return count;
}

unsigned int count_safe_skip(char **input)
{
    unsigned int count = 0;
    int *report = NULL;
    size_t len = 0;

    for (int i = 0; i < DATA_SIZE; i += 1)
    {
        len = 0;
        report = report_to_int_array(input[i]);
        for (const char *c = input[i]; NULL != (c = strchr(c, ' ')); c += 1, len += 1);
        if (0 == check_safety(report + 1, len, -1))
        {
            count += 1;
            free(report);
            continue;
        }
        for (int y = 0; y < len + 1; y += 1)
        {
            if (0 == check_safety(report, len + 1, y))
            {
                count += 1;
                break;
            }
        }
        free(report);
    }
    return count;
}

int main(void)
{
    char **input = get_input("input");
    if (NULL == input)
        return 1;

    printf("%d safe reports found with no skip\n", count_safe(input));
    printf("%d safe reports found with one skip\n", count_safe_skip(input));
    for (int i = 0; i < DATA_SIZE; i += 1)
        free(input[i]);
    free(input);
    return 0;
}
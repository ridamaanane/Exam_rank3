#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

char *ft_strdup(char *str)
{
    int i = 0;
    char *dup;
    while (str[i])
        i++;
    dup = malloc(sizeof(char)  + 1);

    i = 0;
    while (str[i])
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char *get_next_line(int fd)
{
    static char buffer_read[BUFFER_SIZE];
    static int readed_num;
    static int copy_pos;
    static char line[70000];
    int i = 0;
    if (fd < 0 || BUFFER_SIZE < 0)
        return NULL;
    while (1) 
    {
        if (copy_pos >= readed_num)
        {
            readed_num = read(fd, buffer_read, BUFFER_SIZE);
            copy_pos = 0;
            if (readed_num <= 0)
                break;
        }
        line[i++] = buffer_read[copy_pos++];
        if (line[i - 1] == '\n')
            break;
    }
    line[i] = '\0';
    if (i == 0)
        return NULL;
    return (ft_strdup(line));
}
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    
    char *line = get_next_line(fd);
    if (line)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}
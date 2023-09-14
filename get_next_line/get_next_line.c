#include "get_next_line.h"

size_t  ft_strlen(char *str)
{
    size_t i;

    i = 0;
    if(!str)
        return(0);
    while(str[i])
        i++;
    if(str[i] == '\n')
        return(i + 1);
    return(i);
}

char *strjoin_line(char *s1, char *s2)
{
    size_t i;
    size_t j;
    char *s3;

    s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if(!s3)
        return(NULL);
    i = 0;
    j = 0;
    while(s1 && s1[i])
        s3[j++] = s1[i++];
    i = 0;
    while(s2[i])
    { 
        s3[j++] = s2[i];
        if(s2[i++] == '\n')
            break;
    }
    s3[j] = '\0';
    free(s1);
    return(s3);
}


int clear_buffer(char *buffer)
{
    size_t i;
    size_t j;
    size_t result;

    i = 0;
    j = 0;
    result = 0;
    while(buffer[i])
    {
        if(result)
            buffer[j++] = buffer[i];
        if(buffer[i] == '\n')
            result = 1;
        buffer[i] = 0;
        i++;
    }
    return(result);
}

char *get_next_line(int fd)
{
    char *line;
    static char buffer[BUFFER_SIZE + 1];

    if(fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    line = NULL;
    while (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0)
    {
        line = strjoin_line(line, buffer);
        if(clear_buffer(buffer) == 1)
            break;
        if(read(fd, buffer, BUFFER_SIZE) < 0)
        {
            free(line);
            return(NULL);
        }
    }
    return(line);
}
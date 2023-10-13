#pragma once

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

# define INT_MAX 2147483647

void	        ft_bzero(void *s, size_t n);
char	        *ft_newstr(size_t size);
size_t	        ft_strlen(const char *str);
char            *ft_strchr(const char *s, int c);
char	        *ft_strdup(const char *src);
char	        *ft_strjoin(char const *s1, char const *s2);
char	        *ft_substr(char const *s, unsigned int start, size_t len);
char            **ft_split(char const *s, char c);
int             fill_line(char **str, char **line, int fd);
int	            get_next_line(int fd, char **line);;
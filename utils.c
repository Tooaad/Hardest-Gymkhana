#include "utils.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*s2;

	i = 0;
	s2 = (unsigned char *)s;
	while (i < n)
	{
		s2[i] = 0;
		i++;
	}
}

char	*ft_newstr(size_t size)
{
	char	*ptr;

	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (size + 1));
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char    *ft_strchr(const char *s, int c)
{
    char    *str;

    str = (char *)s;
    while (*str != c)
    {
        if (*str == '\0')
            return (0);
        str++;
    }
    return (str);
}

char	*ft_strdup(const char *src)
{
	unsigned int		i;
	char				*dup_ptr;

	dup_ptr = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dup_ptr == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(src))
	{
		dup_ptr[i] = src[i];
		i++;
	}
	dup_ptr[i] = '\0';
	return (dup_ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = ft_newstr(size);
	while (i < size && ptr)
	{
		if (i < (size - ft_strlen(s2)))
			ptr[i] = s1[i];
		else
		{
			ptr[i] = s2[j];
			j++;
		}
		i++;
	}
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (s)
	{
		str = ft_newstr(len);
		if (!str)
			return (NULL);
		if (start < ft_strlen(s))
		{
			while (i < len)
			{
				str[i] = s[i + start];
				i++;
			}
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

static size_t    count_words(char *s, char c)
{
    size_t        nb_words;

    while (*s && *s == c)
        ++s;
    if (*s)
        nb_words = 1;
    else
        nb_words = 0;
    while (*s)
    {
        if (*s == c && s[1] && s[1] != c)
            ++nb_words;
        ++s;
    }
    return (nb_words);
}

char    **ft_split(char const *s, char c)
{
    size_t        nb_words;
    char        *wrd;
    char        **result;

    nb_words = count_words((char *)s, c);
    result = (char **)malloc(sizeof(char *) * (nb_words + 1));
    if (!result)
        return (NULL);
    wrd = (char *)s;
    while (*s)
    {
        if (*s == c)
        {
            if (wrd != s)
                *(result++) = ft_substr(wrd, 0, s - wrd);
            wrd = (char *)s + 1;
        }
        ++s;
    }
    if (wrd != s)
        *(result++) = ft_substr(wrd, 0, s - wrd);
    *result = NULL;
    return (result - nb_words);
}

int	fill_line(char **str, char **line, int fd)
{
	char	*clean;
	int		len;

	len = 0;
	while (str[fd][len] != '\n' && str[fd][len] != '\0')
		len++;
	if (str[fd][len] == '\n')
	{
		*line = ft_substr(str[fd], 0, len);
		clean = ft_strdup(str[fd] + len + 1);
		free(str[fd]);
		str[fd] = clean;
	}
	else if (str[fd][len] == '\0')
	{
		*line = ft_substr(str[fd], 0, len);
		free(str[fd]);
		str[fd] = NULL;
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[4096];
	char		buf[32 + 1];
	char		*clean;
	int			ret;

	if (fd < 0 || !line)
		return (-1);
	if (str[fd] == NULL)
		str[fd] = ft_newstr(1);
	ret = read(fd, buf, 32);
	while (ret > 0)
	{
		buf[ret] = '\0';
		clean = ft_strjoin(str[fd], buf);
		free(str[fd]);
		str[fd] = clean;
		if (ft_strchr(str[fd], '\n'))
			break ;
		ret = read(fd, buf, 32);
	}
	if (ret < 0)
		free(str[fd]);
	if (ret < 0)
		return (-1);
	return (fill_line(str, line, fd));
}
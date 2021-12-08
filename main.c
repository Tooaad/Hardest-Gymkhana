# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

# define INT_MAX 2147483647

typedef struct	s_node
{
	char			c;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct	s_trail
{
	int		*obstacles;
}				t_trail;

typedef struct	s_race
{
	t_trail	*trails;
	char	*speeds;
	int		*pos;
	int		total;
	int		ntrail;
	int		nobs;

}				t_race;

int *shortest_path(t_race *race)
{
	int	*shortest;
	int	min;
	int pos;

	shortest = (int *) malloc((race->nobs) * sizeof(int));
	min = INT_MAX;
	pos = 0;
	for(int j = 0; j < race->nobs; j++)
	{ 
		for (int i = 0; i < race->ntrail; i++)
		{
			if (race->trails[i].obstacles[j] < min)
			{
				min = race->trails[i].obstacles[j];
				pos = i;
			}
		}
		race->pos[j] = pos;
		shortest[j] = min;
		min = INT_MAX;
	}
	return shortest;
}

int calc_stamina(int *shortest, char *speed, int nobs)
{
	int total;

	total = 0;
	for(int i = 0; i < nobs; i++)
	{

		if (speed[i] == 'H')
			total += shortest[i] * 2;
		else
			total += shortest[i];
	}
	return total;
}

void take_speed(t_race *race, t_node *speed, char *sp, int *shortest, int i)
{
	if (i == 0)
	{
		speed->left = (t_node *) malloc((race->nobs) * sizeof(t_node));
		speed->right = (t_node *) malloc((race->nobs) * sizeof(t_node));
		speed->left->c = 'F';
		speed->right->c = 'H';
		sp[i] = 'F';
		take_speed(race, speed->left, sp, shortest, i + 1);
		free(speed->left);
		sp[i] = 'H';
		take_speed(race, speed->right, sp, shortest, i + 1);
		free(speed->right);
	}
	if (i < race->nobs)
	{
		if (speed->c == 'H')
		{
			speed->left = (t_node *) malloc((race->nobs) * sizeof(t_node));
			speed->left->c = 'F';
			sp[i] = 'F';
			take_speed(race, speed->left, sp, shortest, i + 1);
			free(speed->left);
			if (i == race->nobs - 1 || (sp[0] == 'H' && sp[1] == 'H'))
				return ;
			speed->right = (t_node *) malloc((race->nobs) * sizeof(t_node));
			speed->right->c = 'H';
			sp[i] = 'H';
			take_speed(race, speed->right, sp, shortest, i + 1);
			free(speed->right);
		}
		else if (speed->c == 'F')
		{
			speed->right = (t_node *) malloc((race->nobs) * sizeof(t_node));
			speed->right->c = 'H';
			sp[i] = 'H';
			take_speed(race, speed->right, sp, shortest, i + 1);
			free(speed->right);
		}
	}
	if ((calc_stamina(shortest, sp, race->nobs)) < race->total)
	{
		race->total = calc_stamina(shortest, sp, race->nobs);
		for (int j = 0; j < race->nobs; j++)
			race->speeds[j] = sp[j];
	}
}

void print_path(int *pos, char *speed, int total, int nobs)
{
	printf("%d\n", total);
	for (int i = 0; i < nobs; i++) 
		printf("    %d ", pos[i]);
	printf("\n");
	for (int i = 0; i < nobs; i++)
		printf("    %c ", speed[i]);
	printf("\n\n");
}

void start_race(t_race *race)
{
	t_node	speed;
	char	*sp;
	int		*shortest;

	shortest = shortest_path(race);
	race->speeds = (char *) malloc((race->nobs) * sizeof(char));
	sp = (char *) malloc((race->nobs) * sizeof(char));
	for (int i = 0; i < race->nobs; i++)	// Init to null
	{	
		race->speeds[i] = '\0';
		sp[i] = '\0';
	}
	
	take_speed(race, &speed, sp, shortest, 0);
	print_path(race->pos, race->speeds, race->total, race-> nobs);
	free(shortest);
	for (int j = 0; j < race->ntrail; ++j)
		free(race->trails[j].obstacles);
	free(sp);
	free(race->speeds);
	free(race->pos);
	free(race->trails);
}

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

void set_up(t_race *race, char *line, int fd)
{
	char	**obstacles;
	int		trails;
	int		j;

	j = 0;
	race->total = INT_MAX;
	obstacles = ft_split(line, ' ');
	race->ntrail = trails = atoi(obstacles[0]);
	race->nobs = atoi(obstacles[1]);
	free(obstacles[0]);
	free(obstacles[1]);
	free(obstacles);
	free(line);
	race->trails = (t_trail *) malloc((race->ntrail) * sizeof(t_trail));
	race->pos = (int *) malloc((race->nobs) * sizeof(int));
	while (trails > 0)
	{
		get_next_line(fd, &line);
		obstacles = ft_split(line, ' ');
		race->trails[j].obstacles = (int *) malloc((race->nobs) * sizeof(int));
		for (int i = 0; i < race->nobs; i++)
		{
			race->trails[j].obstacles[i] = atoi(obstacles[i]);
			free(obstacles[i]);
		}
		trails--;
		j++;
		free(obstacles);
		free(line);
	}
}

int main()
{
	t_race	race;
	char	*line;
	int		fd;

	race.trails = NULL;	
	fd = 0;
	while (get_next_line(fd, &line))
	{
		set_up(&race, line, fd);
		get_next_line(fd, &line);		// '\0' line
		if (line[0] == '\0')
			start_race(&race);
		free(line);
	}
	close(fd);
	free(line);
}

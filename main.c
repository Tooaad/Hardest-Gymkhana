# include "utils.h"

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
		sp[i++] = 'F';
		sp[i] = 'H';
		take_speed(race, speed->right, sp, shortest, i + 1);
		free(speed->right);
		sp[i++] = 'H';
		sp[i] = 'F';
		take_speed(race, speed->left, sp, shortest, i + 1);
		free(speed->left);
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
			if (i == race->nobs - 1 || (sp[i-2] == 'H' && sp[i-1] == 'H'))
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
	for (int i = 0; i < race->nobs; i++)
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

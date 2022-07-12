/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_ber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:00:13 by druth             #+#    #+#             */
/*   Updated: 2022/05/25 19:02:15 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_input_file_check(char *input, int fd, int track)
{
	while (input[track] != '\0')
		track++;
	if (input[track - 1] != 'r' || input[track - 2] != 'e'
		|| input[track - 3] != 'b' || input[track - 4] != '.')
		ft_error("Error\nso_long: invalid input file given.\n", 41, 1, NULL);
	fd = open(input, O_RDONLY);
	if (fd == -1)
		ft_error("Error\nso_long: unable to open inputted file.\n", 45, 1, NULL);
	return (fd);
}

void	ft_check_loop(t_map_data *map, char temp, int *track, char *min)
{
	if (temp == '\n' && map->num_col == 0)
		map->num_col = *track;
	else if (temp == '\n' && *track != map->num_col)
		ft_error("Error\nso_long: invalid input file given.\n", 41, 1, map);
	if (temp == '\n')
	{
		*track = 0;
		map->num_row++;
	}
	else if (temp != '0' && temp != '1' && temp != 'C'
		&& temp != 'E' && temp != 'P')
		ft_error("Error\nso_long: invalid input file given.\n", 41, 1, map);
	if (temp == 'E')
		*min = '1';
	else if (temp == 'C')
		map->collectables++;
	else if (temp == 'P' && map->player_x == -1)
	{
		map->player_x = *track - 1;
		map->player_y = map->num_row;
	}
	else if (temp == 'P')
		ft_error("Error\nso_long: invalid input file given.\n", 41, 1, map);
}

void	ft_check_ber(int fd, t_map_data *map)
{
	int		track;
	int		check;
	char	temp;
	char	min;

	track = 0;
	min = '0';
	while (track >= 0)
	{
		check = read(fd, &temp, 1);
		if (check == 0)
			break ;
		else if (check < 0)
			ft_error("Error\nso_long: read function returned error.\n",
				45, 1, map);
		track++;
		ft_check_loop(map, temp, &track, &min);
	}
	if (track > 0 && track != map->num_col - 1)
		ft_error("Error\nso_long: invalid input file given.\n", 41, 1, map);
	else if (track > 0)
		map->num_row++;
	if (min == '0' || map->collectables == 0 || map->player_x == -1)
		ft_error("Error\nso_long: invalid input file given.\n", 41, 1, map);
	close(fd);
}

void	ft_read_ber(int fd, t_map_data *map, int track, int check)
{
	if (fd < 0)
		ft_error("Error\nso_long: malloc function call failed.\n", 44, 1, map);
	map->map = (char **)malloc(sizeof(char *) * (map->num_row + 1));
	if (map->map == NULL)
		ft_error("Error\nso_long: malloc function call failed.\n", 44, 1, map);
	while (track < map->num_row)
	{
		map->map[track] = (char *)malloc(sizeof(char) * (map->num_col));
		if (map->map[track] == NULL)
			ft_error("Error\nso_long: malloc function call failed.\n",
				44, 1, map);
		check = read(fd, map->map[track], map->num_col);
		if (check == 0)
			break ;
		else if (check < 0)
			ft_error("Error\nso_long: read function returned error.\n",
				45, 1, map);
		map->map[track][map->num_col - 1] = '\0';
		track++;
	}
	map->map[track] = NULL;
	close(fd);
}

void	ft_check_outer_ber(t_map_data *map)
{
	int	track;

	track = 0;
	while (map->map[0][track] != '\0' && map->map[0][track] == '1'
		&& map->map[map->num_row - 1][track] == '1')
		track++;
	if (map->map[0][track] != '\0' || map->map[map->num_row - 1][track] != '\0')
		ft_error("Error\nso_long: invalid input file given.\n", 41, 1, map);
	track = 0;
	while (track < map->num_row && map->map[track][0] == '1'
		&& map->map[track][map->num_col - 2] == '1')
		track++;
	if (track != map->num_row)
		ft_error("Error\nso_long: invalid input file given.\n", 41, 1, map);
}

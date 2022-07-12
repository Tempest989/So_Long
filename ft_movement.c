/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:02:41 by druth             #+#    #+#             */
/*   Updated: 2022/05/25 19:02:43 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(char *output, int length, int error, t_map_data *map)
{
	if (error != 0)
		write(2, output, length);
	else
		write(1, output, length);
	if (map != NULL && map->map != NULL)
	{
		if (map->window)
			mlx_destroy_window(map->mlx, map->window);
		if (map->mlx != NULL)
			free(map->mlx);
		while (map->num_row >= 0)
		{
			free(map->map[map->num_row]);
			map->num_row--;
		}
		free(map->map);
	}
	exit(error);
}

void	ft_put_image(t_map_data *map, int height, int width)
{
	if (map->map[height][width] == '1')
		mlx_put_image_to_window(map->mlx,
			map->window, map->wall, width * 50, height * 50);
	else if (map->map[height][width] == '0')
		mlx_put_image_to_window(map->mlx,
			map->window, map->floor, width * 50, height * 50);
	else if (map->map[height][width] == 'C')
		mlx_put_image_to_window(map->mlx,
			map->window, map->pickup, width * 50, height * 50);
	else if (map->map[height][width] == 'P')
		mlx_put_image_to_window(map->mlx,
			map->window, map->player, width * 50, height * 50);
	else if (map->map[height][width] == 'E')
		mlx_put_image_to_window(map->mlx,
			map->window, map->exit, width * 50, height * 50);
}

void	ft_move_print(int move_num)
{
	char	output[10];
	int		track;

	track = 9;
	while (move_num != 0)
	{
		output[track] = move_num % 10 + '0';
		track--;
		move_num /= 10;
	}
	track++;
	write(1, "Number of Moves: ", 17);
	write(1, &output[track], 10 - track);
	write(1, "\n", 1);
}

int	ft_movement(t_map_data *map, int x, int y)
{
	if (map->map[y][x] == '1')
		return (0);
	ft_move_print(map->move_num);
	map->move_num++;
	if (map->map[y][x] == 'C')
		map->collectables--;
	else if (map->map[y][x] == 'E' && map->collectables == 0)
		ft_error("so_long: Finished, Congratulations!\n", 36, 0, map);
	if (map->exit_flag == 1)
	{
		map->map[map->player_y][map->player_x] = 'E';
		map->exit_flag = 0;
	}
	else
		map->map[map->player_y][map->player_x] = '0';
	if (map->map[y][x] == 'E')
		map->exit_flag = 1;
	map->map[y][x] = 'P';
	ft_put_image(map, y, x);
	ft_put_image(map, map->player_y, map->player_x);
	map->player_x = x;
	map->player_y = y;
	return (1);
}

int	ft_controls(int move, t_map_data *map)
{
	int	check;

	check = 0;
	if (move == 13)
		check = ft_movement(map, map->player_x, map->player_y - 1);
	else if (move == 1)
		check = ft_movement(map, map->player_x, map->player_y + 1);
	else if (move == 0)
		check = ft_movement(map, map->player_x - 1, map->player_y);
	else if (move == 2)
		check = ft_movement(map, map->player_x + 1, map->player_y);
	else if (move == 53)
		ft_error("so_long: Exiting....\n", 21, 0, map);
	return (1);
}

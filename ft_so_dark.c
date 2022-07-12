/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_so_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:32:56 by druth             #+#    #+#             */
/*   Updated: 2022/05/25 19:00:04 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_exit_press(t_map_data *map)
{
	ft_error("so_long: Exiting....\n", 21, 0, map);
	return (0);
}

void	ft_initialize(t_map_data *map)
{
	map->num_col = 0;
	map->num_row = 0;
	map->collectables = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->map = NULL;
	map->move_num = 1;
	map->mlx = NULL;
	map->window = NULL;
}

void	ft_initialize_images(t_map_data *map)
{
	int	width;
	int	height;

	map->floor = mlx_xpm_file_to_image(map->mlx,
			"./images/floor.xpm", &width, &height);
	map->wall = mlx_xpm_file_to_image(map->mlx,
			"./images/wall.xpm", &width, &height);
	map->player = mlx_xpm_file_to_image(map->mlx,
			"./images/player.xpm", &width, &height);
	map->exit = mlx_xpm_file_to_image(map->mlx,
			"./images/exit.xpm", &width, &height);
	map->pickup = mlx_xpm_file_to_image(map->mlx,
			"./images/item.xpm", &width, &height);
}

void	ft_graphics(t_map_data *map, int height, int width)
{
	int	temp_x;
	int	temp_y;

	while (height < map->num_row)
	{
		width = 0;
		while (map->map[height][width] != '\0')
		{
			if (map->map[height][width] == 'P')
			{
				temp_y = height - 2;
				while (++temp_y <= height + 1)
				{
					temp_x = width - 2;
					while (++temp_x <= width + 1)
						ft_put_image(map, temp_y, temp_x);
				}
				return ;
			}
			width++;
		}
		height++;
	}
}

int	main(int ac, char *av[])
{
	t_map_data	map;

	if (ac != 2)
		ft_error("Error\nso_long: invalid number of commandline arguments.\n",
			56, 1, NULL);
	ft_initialize(&map);
	ft_check_ber(ft_input_file_check(av[1], 0, 0), &map);
	ft_read_ber(open(av[1], O_RDONLY), &map, 0, 0);
	ft_check_outer_ber(&map);
	map.mlx = mlx_init();
	map.window = mlx_new_window(map.mlx, (map.num_col * 50 - 49),
			(map.num_row * 50), "so_long");
	ft_initialize_images(&map);
	ft_graphics(&map, 0, 0);
	mlx_key_hook(map.window, ft_controls, &map);
	mlx_hook(map.window, 17, 0, ft_exit_press, &map);
	mlx_loop(map.mlx);
	return (0);
}

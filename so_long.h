/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:03:13 by druth             #+#    #+#             */
/*   Updated: 2022/05/25 19:03:14 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./minilibx/mlx.h"

typedef struct s_map_data
{
	char	**map;
	int		num_col;
	int		num_row;
	int		player_x;
	int		player_y;
	char	exit_flag;
	int		collectables;
	int		move_num;
	void	*wall;
	void	*exit;
	void	*player;
	void	*floor;
	void	*pickup;
	void	*mlx;
	void	*window;
}	t_map_data;

void	ft_error(char *output, int length, int error, t_map_data *map);
int		ft_controls(int move, t_map_data *map);
int		ft_input_file_check(char *input, int fd, int track);
void	ft_check_ber(int fd, t_map_data *map);
void	ft_read_ber(int fd, t_map_data *map, int track, int check);
void	ft_check_outer_ber(t_map_data *map);
void	ft_put_image(t_map_data *map, int height, int width);

#endif

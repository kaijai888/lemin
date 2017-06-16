/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:31:46 by kzeng             #+#    #+#             */
/*   Updated: 2017/03/23 17:31:48 by kzeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define MAX(x, y) (x > y ? x : y)
# define MIN(x, y) (x > y ? y : x)
# define BUFF_SIZE 1
# define MAX_FD 1
# define MALLOC_CHECK(x) if (x == NULL) {return (-1);}
# define READ_CHECK(x) if (x == -1) {free(buf); return (-1);}

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct	s_list
{
	int			start;
	int			end;
	char		*start_room;
	char		*end_room;
	int			ants;
	int			*ant_number;
	char		**ant_location;
	int			*cost_map;
	int			cost;
	int			*filled_room;
	int			total_rooms;
	char		**rooms;
	int			*room_x;
	int			*room_y;
	int			total_links;
	char		***links;
	int			error;
	int			line;
	int			current;
	int			next_cost;
	int			reached_end;
	int			num;
	int			len;
	int			neg;
}				t_list;

/*
**	ft_add_link.c
*/
void			ft_setup_link(t_list *list);
void			ft_add_link_helper(t_list *list, char **split, int j, int k);
int				ft_add_link(t_list *list, char *line);

/*
**	ft_cost.c
*/
int				ft_set_cost_helper(t_list *list, int i);
void			ft_set_cost(t_list *list, int i, int m);
void			ft_update_helper(t_list *list, int i, char *before, char *next);
void			ft_get_link(t_list *list, int i, char **before, char **next);
void			ft_update_cost(t_list *list);

/*
**	ft_lemin_helper.c
*/
void			ft_initialize_list(t_list **list);
int				ft_nwords(char *s, char c, int i);
char			**ft_strsplit(char *s, char c);

/*
**	ft_lemin_helper2.c
*/
char			*ft_strsub(char *s, unsigned int start, size_t len);
char			*ft_strnew(size_t size);
char			*ft_strdup(char *s1);
char			*ft_strcpy(char *dst, char *src);
char			*ft_strncat(char *s1, char *s2, size_t n);

/*
**	ft_lemin_helper3.c
*/
int				ft_strcmp(char *s1, char *s2);
size_t			ft_strlen(char *str);
int				ft_isdigit(int c);
int				ft_atoi(t_list *list, char *num);

/*
**	ft_parse_input.c
*/
int				ft_read_input(t_list *list);
int				ft_add_first_room(t_list *list, char **split);
int				ft_add_room_helper(t_list *list, char **split);
int				ft_add_room(t_list *list, char *line);
int				ft_parse_line(char *ln, t_list *list, int i);

/*
**	ft_printf.c
*/
void			ft_putchar(char c);
void			ft_putstr(const char *s);
void			ft_putnbr(int nb);
int				ft_printf(const char *format, ...);

/*
**	ft_solve.c
*/
void			ft_setup(t_list *list, int i);
int				ft_next_cost(t_list *list, int i);
int				ft_ant_helper(t_list *list, int i, int j, int next);
int				ft_move_ants(t_list *list, int i, int at_start);
void			ft_move_ants_helper(t_list *list);

/*
**	get_next_line.c
*/
int				get_next_line(const int fd, char **line);

#endif

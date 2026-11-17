/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apazitor <apazitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 10:12:54 by apazitor          #+#    #+#             */
/*   Updated: 2026/11/17 14:23:17 by apazitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

char	*free_and_null(char **str)
{
	free (*str);
	*str = NULL;
	return (NULL);
}

static char	*grow_stash(char *stash, int len, int *cap, int need)
{
	char	*new_stash;
	int		new_cap;

	new_cap = *cap * 2;
	if (new_cap < need)
		new_cap = need;
	new_stash = malloc(new_cap);
	if (!new_stash)
		return (free_and_null(&stash));
	if (stash)
		ft_memcpy(new_stash, stash, len);
	new_stash[len] = '\0';
	free(stash);
	*cap = new_cap;
	return (new_stash);
}

int	read_chunk(int fd, char *buffer, char **stash, t_size	*sz)
{
	ssize_t	r_bytes;

	r_bytes = read(fd, buffer, BUFFER_SIZE);
	if (r_bytes <= 0)
		return (r_bytes);
	buffer[r_bytes] = '\0';
	if (sz -> len + r_bytes + 1 > sz -> cap)
	{
		*stash = grow_stash(*stash, sz->len, &(sz->cap), sz->len + r_bytes + 1);
		if (!*stash)
			return (-1);
	}
	ft_memcpy(*stash + sz->len, buffer, r_bytes + 1);
	sz->len += r_bytes;
	return (1);
}

char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	t_size	sz;
	int		status;

	if (ft_strchr(stash, '\n'))
		return (stash);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_and_null(&stash));
	buffer[0] = '\0';
	sz.len = ft_word_len(stash, ' ', 0);
	sz.cap = sz.len + (stash != NULL);
	status = 1;
	while (status > 0 && !ft_strchr(buffer, '\n'))
		status = read_chunk(fd, buffer, &stash, &sz);
	free(buffer);
	if (status < 0)
		free_and_null(&stash);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	if (!ft_strchr(stash, '\n'))
	{
		line = ft_strdup(stash);
		free(stash);
		stash = NULL;
		return (line);
	}
	//printf("%s\n", read_to_stash(fd, stash));
	return (ft_get_word_before_delim(&stash, '\n'));
}
// int main(void)
// {
// 	int f1 = open("input.txt", O_RDONLY);
// 	FILE *f2 = fopen("output.txt", "a");
// 	char *result1 = get_next_line(f1); //1
// 	char *result2 = get_next_line(f1); //2
// 	char *result3 = get_next_line(f1);
// 	fprintf(f2, "result1 : %s", result1); 
// 	fprintf(f2, "result2 : %s", result2);
// 	fprintf(f2, "result3 : %s", result3);
// 	free(result1);
// 	free(result2);
// 	fclose(f2);
// }
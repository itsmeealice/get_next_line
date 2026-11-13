/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apazitor <apazitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 10:12:54 by apazitor          #+#    #+#             */
/*   Updated: 2026/11/13 16:11:06 by apazitor         ###   ########.fr       */
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

char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	read_bytes;
	int		len;
	int		cap;

	len = 0;
	cap = 0;
	if (ft_strchr(stash, '\n'))
		return (stash);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_and_null(&stash));
	len = ft_strlen(stash);
	if (stash)
		cap = len + 1;
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (free_and_null(&stash));
		}
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		if (len + read_bytes + 1 > cap)
			stash = grow_stash(stash, len, &cap, len + read_bytes + 1);
		if (!stash)
			return (free_and_null(&buffer));
		ft_memcpy(stash + len, buffer, read_bytes + 1);
		len += read_bytes;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	if (read_bytes < 0)
		return (free_and_null(&stash));
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
	return (ft_get_word_before_delim(&stash, '\n'));
}
// int main(void)
// {
// 	int f1 = open("input.txt", O_RDONLY);
// 	FILE *f2 = fopen("output.txt", "a");
// 	char *result1 = get_next_line(f1); //1
// 	char *result2 = get_next_line(f1); //2
// 	fprintf(f2, "result1 : %s", result1); 
// 	fprintf(f2, "result2 : %s", result2);
// 	free(result1);
// 	free(result2);
// 	fclose(f2);
// }
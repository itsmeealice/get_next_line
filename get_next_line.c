/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apazitor <apazitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 10:12:54 by apazitor          #+#    #+#             */
/*   Updated: 2026/11/10 17:48:43 by apazitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static char	*free_and_null(char *str)
{
	free (str);
	return (NULL);
}

char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	read_bytes;
	char 	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_and_null(buffer));
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(stash, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free_and_null(stash);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		free(stash);
		stash = tmp;
	}
	free(buffer);
	return (stash);
}

char	*get_line_from_stash(char **stash)
{
	if (*stash == NULL)
		return (NULL);
	if (!ft_strchr(*stash, '\n'))
		return (*stash);
	return (ft_get_word_before_delim(stash, '\n'));
}
char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	return (get_line_from_stash(&stash));

}
int main(void)
{
	int f1 = open("input.txt", O_RDONLY);
	printf("%s", get_next_line(f1));
	printf("%s", get_next_line(f1));
	// printf("%s", get_next_line(f1));
}
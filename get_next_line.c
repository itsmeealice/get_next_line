/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apazitor <apazitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 10:12:54 by apazitor          #+#    #+#             */
/*   Updated: 2026/11/09 16:06:30 by apazitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char    *get_line(char * stash)
// {
// 	char *endlstr;

// 	endlstr = malloc(ft_strlen(ft_strchr(stash, '\n')));
// 	endlstr = ft_strchr(stash, '\n');
// 	printf("%s", ft_get_word_before_delim(stash, '\n'));
// 	return (endlstr);
// }

static char	*free_and_null(char *str)
{
	free (str);
	return (NULL);
}
// static char	*read_to_stash(int fd, char *stash)
// {
// 	char	*buffer;
// 	size_t	bytes;
// 	buffer = malloc(BUFFER_SIZE + 1);
// 	if (buffer == NULL)
// 		return (free_and_null(buffer));
// 	bytes = 1;
// 	while (bytes > 0 && !ft_strchr(stash, '\n'))
// 	{
// 		bytes = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes == -1)
// 		{
// 			free(buffer);
// 			return (free_and_null(stash));
// 		}
// 		buffer[bytes] = '\0';
// 		stash = ft_strjoin(stash, buffer);
// 		if(!stash)
// 			return(NULL);
// 	}
// 	free(buffer);
// 	return (stah)
// }
char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	read_bytes = 1;
	if (!buffer)
		return (free_and_null(buffer));
	while (read_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free_and_null(stash);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			break;
	}
	free (buffer);
	return (stash);

}

char	*get_line_from_stash(char **stash)
{
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
// int main(void)
// {
// 	int f1 = open("input.txt", O_RDONLY);
// 	printf("%s", get_next_line(f1));
// 	printf("%s", get_next_line(f1));
// 	printf("%s", get_next_line(f1));
// }
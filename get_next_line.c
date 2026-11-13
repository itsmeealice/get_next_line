/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apazitor <apazitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 10:12:54 by apazitor          #+#    #+#             */
/*   Updated: 2026/11/13 10:15:01 by apazitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

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

	if (ft_strchr(stash, '\n'))
		return (stash);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_and_null(stash));
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
		if(read_bytes == 0)
			break;
		buffer[read_bytes] = '\0';
		//printf("read_to_stash: %s\n", buffer);
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		if (!tmp)
		{
			free(buffer);
			return (NULL);
		}
		stash = tmp;
	}
	free(buffer);
	return (stash);
}

char	*get_line_from_stash(char **stash)
{
	char *line; 

	if (*stash == NULL)
		return (NULL);
	if (!ft_strchr(*stash, '\n'))
	{
		line = *stash;
		*stash = NULL;
		return (line);
	}
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
	FILE *f2 = fopen("output.txt", "a");
	char *result1 = get_next_line(f1); //1
	char *result2 = get_next_line(f1); //2
	char *result3 = get_next_line(f1); //3
	char *result4 = get_next_line(f1); //4
	char *result5 = get_next_line(f1); //5
	char *result6 = get_next_line(f1); //6
	char *result7 = get_next_line(f1);
	fprintf(f2, "result1 : %s", result1); 
	fprintf(f2, "result2 : %s", result2);
	fprintf(f2, "result3 : %s", result3);
	fprintf(f2, "result4 : %s", result4);
	fprintf(f2, "result5 : %s", result5);
	fprintf(f2, "result6 : %s", result6);
	fprintf(f2, "result7 : %s", result7);
	free(result1);
	free(result2);
	free(result3);
	free(result4);
	free(result5);
	free(result6);
	free(result7);
	fclose(f2);
}
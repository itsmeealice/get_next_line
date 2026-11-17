/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apazitor <apazitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:43:31 by apazitor          #+#    #+#             */
/*   Updated: 2026/11/17 12:11:17 by apazitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	searched_character;

	if (!s)
		return (NULL);
	i = 0;
	searched_character = (char)c;
	while (s[i] != '\0')
	{
		if ((s[i] == searched_character))
			return ((char *)&s[i]);
		i++;
	}
	if (searched_character == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;
	size_t	i;
	size_t	s_len;

	s_len = ft_word_len(s, ' ', 0);
	new_s = NULL;
	new_s = malloc(s_len + 1);
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

int	ft_word_len(const char *s, char delim, int with_delim_option)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (with_delim_option)
	{
		while (s[i] && s[i] != delim) 
			i++;
		if (s[i] == delim) 
			i++;

	}
	else
	{
		while (s[i])
			i++;
	}
	return (i);
}

char	*ft_get_word_before_delim(char **stash, char delim)
{
	int		i;
	char	*word;
	char	*new_stash;

	if (!stash || !*stash)
		return (NULL);
	i = ft_word_len(*stash, delim, 1);
	word = malloc(i + 1);
	if (!word)
		return (free_and_null(stash));
	ft_memcpy(word, *stash, i);
	word[i] = '\0';
	new_stash = NULL;
	if ((*stash)[i])
		new_stash = ft_strdup(*stash + i);
	if ((*stash)[i] && !new_stash)
	{
		free(word);
		return (free_and_null(stash));
	}
	free(*stash);
	*stash = new_stash;
	return (word);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*byte_dest;
	const unsigned char	*byte_src;
	size_t				i;

	byte_dest = (unsigned char *) dest;
	byte_src = (unsigned char *) src;
	if (n > 0 && src == NULL && dest == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		byte_dest[i] = byte_src[i];
		i++;
	}
	return (dest);
}

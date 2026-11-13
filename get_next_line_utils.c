/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apazitor <apazitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:43:31 by apazitor          #+#    #+#             */
/*   Updated: 2026/11/13 16:38:02 by apazitor         ###   ########.fr       */
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

	s_len = ft_strlen(s);
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

char	*ft_get_word_before_delim(char **stash, char delim)
{
	int		i;
	char	*word;
	char	*new_stash;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while ((*stash)[i] && (*stash)[i] != delim) //get the characters before sep
		i++;
	if ((*stash)[i] == delim) //get sep -- first handle the delim case
		i++;
	word = malloc(i + 1); //allocate memory for sep + null character
	if (!word)
		return (free_and_null(stash));
	ft_memcpy(word, *stash, i);
	word[i] = '\0'; //copy and terminate the word 
	if ((*stash)[i] == '\0') // just delete the pointer to the stash bc it is finished
		new_stash = NULL;
	else
	{
		new_stash = ft_strdup(*stash + i);
		if (!new_stash)
		{
			free(word);
			return (free_and_null(stash));
		}
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

int	ft_strlen(char const *str)
{
	int	i;
	int	nr;

	if (!str)
		return (0);
	i = 0;
	nr = 0;
	while (str[i] != '\0')
	{
		i++;
		nr++;
	}
	return (nr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apazitor <apazitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:43:31 by apazitor          #+#    #+#             */
/*   Updated: 2026/11/10 18:18:14 by apazitor         ###   ########.fr       */
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
	while ((*stash)[i] && (*stash)[i] != delim)
		i++;
	if ((*stash)[i] == delim)
		i++;
	word = malloc(i + 1);
	if (!word)
	{
		free(word);
		return (NULL);
	}
	ft_memcpy(word, *stash, i);
	word[i] = '\0';
	new_stash = ft_strdup(*stash + i);
	if (!new_stash)
	{
		free(new_stash);
		return (NULL);
	}
	free(*stash);
	*stash = new_stash;
	free(new_stash);
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
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	int		len_prefix;
	int		len_sufix;
	int		new_string_len;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	len_prefix = ft_strlen(s1);
	len_sufix = ft_strlen(s2);
	new_string_len = len_prefix + len_sufix + 1;
	new_string = malloc(new_string_len);
	if (new_string == NULL)
		return (NULL);
	ft_memcpy(new_string, s1, len_prefix);
	ft_memcpy(new_string + len_prefix, s2, len_sufix + 1);
	return (new_string);
}

int	ft_strlen(char const *str)
{
	int i;
	int nr;

	if (!str)	
		return(0);

	i = 0;
	nr = 0;
	while (str[i] != '\0')
	{
		i++;
		nr++;
	}
	return (nr);
}

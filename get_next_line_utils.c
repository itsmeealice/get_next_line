/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apazitor <apazitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:43:31 by apazitor          #+#    #+#             */
/*   Updated: 2026/11/09 16:05:15 by apazitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	searched_character;

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

char	*ft_get_word_before_delim(char **stash, char delim)
{
	int	i;
	char *word;

	word = NULL;
	if (*stash == NULL)
		return (NULL);
	i = 0;
	while ((*stash)[i] && (*stash)[i] != delim)
	{
		i++;
	}
	if((*stash)[i] == delim)
		i++;
	if (i)
		word = malloc(i + 1);
	if(!word)
		return (NULL);
	ft_memcpy(word, *stash, i);
	if ((*stash)[i] == delim)
	{
		word[i] = '\0';
		*stash += i + 1;
	}
	else 
		*stash += i;
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

	len_prefix = 0;
	len_sufix = 0;
	if (s1 != NULL)
		len_prefix = ft_strlen(s1);
	if (s2 != NULL)
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

	i = 0;
	nr = 0;
	while (str[i] != '\0')
	{
		i++;
		nr++;
	}
	return (nr);
}


// int main()
// {
//     char *str = "hello world etc etc";
//     char *p = ft_strchr(str, ' ');

//     printf("%s", p);
// }
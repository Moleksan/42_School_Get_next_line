/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moleksan <moleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:32:11 by moleksan          #+#    #+#             */
/*   Updated: 2024/01/15 12:33:00 by moleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_reads(int fd, char *str)
{
	int		len;
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (free(buff), free(str), NULL);
	len = 1;
	while (!ft_strchr(str, '\n') && len != 0)
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
			return (free(buff), free(str), NULL);
		buff[len] = '\0';
		str = ft_strjoin(str, buff);
	}
	return (free(buff), str);
}

char	*ft_print(char *str)
{
	int		len;
	char	*buff;

	len = 0;
	if (!str[len])
		return (NULL);
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	buff = malloc(sizeof(char) * (len + 2));
	if (!buff)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != '\n')
	{
		buff[len] = str[len];
		len++;
	}
	if (str[len] == '\n')
	{
		buff[len] = '\n';
		len++;
	}
	buff[len] = '\0';
	return (buff);
}

char	*ft_next_line(char *str)
{
	int		len;
	char	*buff;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	if (!str[len])
		return (free(str), NULL);
	buff = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!buff)
		return (free(str), NULL);
	len++;
	ft_strcpy(buff, &str[len]);
	return (free(str), buff);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*s;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_reads(fd, str);
	if (!str)
		return (NULL);
	s = ft_print(str);
	str = ft_next_line(str);
	return (s);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main()
// {
// 	int fd;
// 	char *line;

// 	fd = open("world.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		write(2, "Error in opening the file", 26);
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return 0;
// }
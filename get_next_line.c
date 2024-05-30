/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:25:08 by msawada           #+#    #+#             */
/*   Updated: 2024/05/30 18:02:00 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	get_char(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	buf_count;
	char		c;

	if (buf_count  == 0)
	{
		buf_count = read(fd, buf, BUFFER_SIZE);
	}
	buf_count -= 1;
	if(buf_count > 0)
	{
		c = buf[BUFFER_SIZE - buf_count - 1];
	}
	else if (buf_count == -1)
		c = EOF;
	return (c);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	c;

	while (1)
	{
		c = get_char(fd);
		if (c == EOF)
			break;
		add_char(&line, c);
		if (c == '\n')
			break;
	}
	add_end(&line);
	return (line);
}


// int	main(void)
// {
// 	int	fd = open("alternate_line_nl_no_nl", O_RDONLY);
// 	char	*str;

// 	str = NULL;
// 	str = get_next_line(fd);
// 	printf("\n-----------------------------------------\n(1)=%s$\n--------------------------------\n", str);
// 	str = get_next_line(fd);
// 	printf("\n-----------------------------------------\n(2)=%s$\n--------------------------------\n", str);
// 	str = get_next_line(fd);
// 	printf("\n-----------------------------------------\n(3)=%s$\n--------------------------------\n", str);
// 	str = get_next_line(fd);
// 	printf("\n-----------------------------------------\n(4)=%s$\n--------------------------------\n", str);
// 	str = get_next_line(fd);
// 	printf("\n-----------------------------------------\n(5)=%s$\n--------------------------------\n", str);
// 	free(str);
// 	// system("leaks a.out");
// 	close(fd);
// }
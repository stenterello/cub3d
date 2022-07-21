#include "../include/libft/libft.h"
#include <stdio.h>

int	main()
{
	char	*tmp;
	int		fd;

	fd = open("texture2.xpm", O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error opening file", 2);
		exit(1);
	}
	tmp = get_next_line(fd);
	while (tmp)
	{
		printf("%s\n", tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (0);
}

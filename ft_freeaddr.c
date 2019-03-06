#include "ft_traceroute.h"

void	ft_freeaddrinfo(struct addrinfo *curr)
{
	struct addrinfo *tmp;

	while (curr)
	{
		tmp = curr->ai_next;
		free(curr->ai_canonname);
		free(curr);
		curr = tmp;
	}
}

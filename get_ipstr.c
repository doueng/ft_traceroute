#include "ft_traceroute.h"

char		*get_ipstr(char *ipstr, void *addr)
{
	ft_bzero(ipstr, INET_ADDRSTRLEN + 1);
	inet_ntop(AF_INET,
			addr,
			ipstr,
			INET_ADDRSTRLEN);
	return (ipstr);
}

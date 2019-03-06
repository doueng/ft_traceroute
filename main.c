/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:59:58 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 11:59:59 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int			main(int argc, char *argv[])
{
	t_env		env;
	char		ipstr[INET_ADDRSTRLEN + 1];
	char		*destination;

	if (getuid() != 0)
		x(-1, ROOT);
	ft_bzero(&env, sizeof(env));
	destination = parse_args(&env, argc, argv);
	create_env(&env, destination);
	printf("traceroute to %s (%s), %d hops max, %u byte packets\n",
		destination,
		get_ipstr(ipstr, &((struct sockaddr_in*)env.dst_addr)->sin_addr),
		env.maxhops,
		env.packetsize);
	main_loop(&env);
	ft_freeaddrinfo(env.addrinfo);
	return (0);
}

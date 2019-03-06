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

static int	get_options(char *op_str)
{
	int options;

	options = 0;
	if (op_str[0] != '-')
		return (options);
	x(ft_strequ(op_str, "-") ? -1 : 0, USAGE);
	while (*++op_str)
	{
		*op_str == 'h' ? options |= H_OP : 0;
		if (ft_strchr("h", *op_str) == NULL)
			x(-1, USAGE);
	}
	return (options);
}

char		*get_ipstr(char *ipstr, void *addr)
{
	ft_bzero(ipstr, INET_ADDRSTRLEN + 1);
	inet_ntop(AF_INET,
			addr,
			ipstr,
			INET_ADDRSTRLEN);
	return (ipstr);
}

char		*parse_args(t_env *env, int argc, char *argv[])
{
	if (argc < 2)
		x(-1, USAGE);
	if ((*++argv)[0] == '-')
		env->options = get_options(*argv++);
	if (env->options & H_OP)
		x(-1, USAGE);
	return (*argv);
}

static void		ft_freeaddrinfo(struct addrinfo *curr)
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

int			main(int argc, char *argv[])
{
	t_env		env;
	char		ipstr[INET_ADDRSTRLEN + 1];
	char		*destination;

	if(getuid() != 0)
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

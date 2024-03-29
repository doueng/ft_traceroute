/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:59:54 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 11:59:55 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static struct sockaddr	*get_sockaddr(t_env *env, char *address)
{
	struct addrinfo	hints;
	struct addrinfo	*addrinfo;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_protocol = IPPROTO_UDP;
	addrinfo = NULL;
	if (0 != getaddrinfo(address, NULL, &hints, &addrinfo))
	{
		fprintf(stderr, "traceroute: cannot resolve %s: Unknown host\n",
				address);
		exit(-1);
	}
	env->addrinfo = addrinfo;
	return (addrinfo->ai_addr);
}

static void				set_timeout(int sockfd)
{
	struct timeval	timeout;

	ft_bzero(&timeout, sizeof(timeout));
	timeout.tv_sec = 0;
	timeout.tv_usec = 600000;
	x(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)),
		SETSOCK);
}

void					create_env(t_env *env, char *address)
{
	env->dst_addr = get_sockaddr(env, address);
	env->sendsock = x(socket(AF_INET, SOCK_RAW, IPPROTO_UDP), SOCKET);
	env->recvsock = x(socket(AF_INET, SOCK_RAW, IPPROTO_ICMP), SOCKET);
	env->maxhops = 30;
	env->packetsize = 60;
	env->port = 33433;
	set_timeout(env->recvsock);
}

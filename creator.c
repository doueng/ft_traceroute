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
	hints.ai_protocol = IPPROTO_ICMP;
	addrinfo = NULL;
	if (0 != getaddrinfo(address, NULL, &hints, &addrinfo))
	{
		fprintf(stderr, "traceroute: cannot resolve %s: Unknown host\n", address);
		exit(-1);
	}
	env->addrinfo = addrinfo;
	return (addrinfo->ai_addr);
}

static void				set_sockopts(t_env *env, int sockfd)
{
	struct timeval	timeout;

	ft_bzero(&timeout, sizeof(timeout));
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	x(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))
		, SETSOCK);
	x(setsockopt(sockfd, IPPROTO_IP, IP_TTL, &env->ttl, sizeof(env->ttl))
		, SETSOCK);
}

void					create_env(t_env *env, char *address)
{
	env->dst_addr = get_sockaddr(env, address);
	env->sockfd = x(socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP), SOCKET);
	env->ttl = 1;
	set_sockopts(env, env->sockfd);
}

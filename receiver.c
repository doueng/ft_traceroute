/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:06 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:07 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/* static void	update_msghdr(struct msghdr *msg) */
/* { */
/* 	struct iovec		*iov; */
/* 	struct sockaddr_in	sin; */
/* 	char				*databuff; */

/* 	databuff = xv(ft_memalloc(g_env.data_size), MALLOC); */
/* 	ft_bzero(&sin, sizeof(sin)); */
/* 	ft_bzero(msg, sizeof(msg)); */
/* 	iov = xv(ft_memalloc(sizeof(*iov)), MALLOC); */
/* 	msg->msg_name = &sin; */
/* 	msg->msg_namelen = sizeof(sin); */
/* 	msg->msg_iov = iov; */
/* 	msg->msg_iovlen = 1; */
/* 	iov[0].iov_base = databuff; */
/* 	iov[0].iov_len = g_env.data_size; */
/* } */

struct icmp	*receiver(t_env *env, struct ip *ip_recv, struct icmp *icmp_recv)
{
	int					ret;
	/* struct msghdr		msg; */
	char				*buff;
	size_t				buffsize;

	/* update_msghdr(&msg); */
	/* databuff = msg.msg_iov[0].iov_base; */
	/* ret = recvmsg(g_env.sockfd, &msg, MSG_WAITALL); */
	ft_bzero(icmp_recv, sizeof(icmp_recv));
	ft_bzero(ip_recv, sizeof(ip_recv));
	buffsize = sizeof(*ip_recv) + sizeof(*icmp_recv);
	buff = xv(ft_memalloc(buffsize), MALLOC);
	ret = recvfrom(env->sockfd, buff, buffsize, MSG_WAITALL, NULL, NULL);
	ft_memcpy(ip_recv, buff, sizeof(*ip_recv));
	ft_memcpy(icmp_recv, buff + sizeof(struct ip), ICMP_SIZE);
	if (ret == -1 && errno == EWOULDBLOCK)
	{
		fprintf(stderr,
				"Request timeout for icmp_seq %zu\n", env->seq);
		free(buff);
		return (NULL);
	}
	/* g_env.packets_recv++; */
	free(buff);
	return (icmp_recv);
}

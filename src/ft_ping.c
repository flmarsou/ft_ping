#include "ft_ping.h"

# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# include <sys/time.h>
# include <netinet/ip_icmp.h>

bool	g_is_running = true;

static void	interrupt_handler(i32 signum)
{
	(void)signum;

	g_is_running = false;

	write(1, "\n", 1);
}

static u16	checksum(void *data, u32 len)
{
	u32	sum = 0;
	u16	*buf = data;

	while (len > 1)
	{
		sum += *buf++;
		len -= 2;
	}
	if (len == 1)
		sum += *(u8 *)buf;

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);

	return ((u16)(~sum));
}

void	ft_ping(const t_ping ping)
{
	signal(SIGINT, interrupt_handler);

	u8				packet[sizeof(struct icmphdr) + ping.size];
	const u16		pid = getpid();
	u16				seq = 0;

	struct timeval	start;
	i32				sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sock < 0)
	{
		perror("socket");
		return ;
	}

	struct timeval	end;

	while (g_is_running)
	{
		// Build ICMP Echo Request
		// -----------------------
		struct icmphdr	*icmp = (struct icmphdr *)packet;
		memset(packet, 0, sizeof(packet));

		icmp->type = ICMP_ECHO;
		icmp->code = 0;
		icmp->un.echo.id = htons(pid);
		icmp->un.echo.sequence = htons(seq++);
		icmp->checksum = 0;
		icmp->checksum = checksum(packet, sizeof(packet));

		// Send ICMP packet
		// ----------------

		gettimeofday(&start, NULL);

		if (sendto(sock, packet, sizeof(packet), 0, (const struct sockaddr *)ping.addr, sizeof(*ping.addr)) == -1)
		{
			perror("sendto");
			break ;
		}

		// Receive ICMP reply
		// ------------------

		u8					recv_buffer[1024];
		struct sockaddr_in	from;
		socklen_t			from_len = sizeof(from);

		i64	bytes = recvfrom(sock, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr *)&from, &from_len);
		if (bytes < 0)
		{
			perror("recvfrom");
			break ;
		}

		const struct iphdr	*ip = (struct iphdr *)recv_buffer;
		const i32			iphdr_len = ip->ihl * 4;

		struct icmphdr	*reply = (struct icmphdr *)(recv_buffer + iphdr_len);
		if (reply->type != ICMP_ECHOREPLY || reply->un.echo.id != htons(pid))
			continue ;

		// Print echo result
		// -----------------

		gettimeofday(&end, NULL);
		const f64	rtt = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;

		printf("%lld bytes from %s -> Sequence=%d TTL=%d RTT=%.2fms\n",
			bytes - iphdr_len, ping.destination, seq, ip->ttl, rtt);

		sleep(ping.interval);
	}

	close(sock);
}

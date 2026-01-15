#pragma once

# include <stdbool.h>

# include <arpa/inet.h>

# include "ft_types.h"

typedef struct	s_ping
{
	// Arguments
	bool		audible;		// -a
	u32			count;			// -c <count>
	bool		date;			// -D
	u32			interval;		// -i <interval>
	bool		quiet;			// -q
	u32			size;			// -s <size>
	bool		verbose;		// -v

	const i8	*destination;	// Address

	// Data
	i8					ip[INET_ADDRSTRLEN];
	struct sockaddr_in	*addr;
}	t_ping;

bool	parse_arguments(const i32 argc, const i8 **argv, t_ping *ping);
bool	parse_dns(t_ping *ping);

void	print_help(const bool invalid_flag, const i8 flag);
void	print_ping(const t_ping ping);

void	ft_ping(const t_ping ping);

#pragma once

# include <stdbool.h>

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

}	t_ping;

bool	parse_arguments(const i32 argc, const i8 **argv, t_ping *ping);

void	print_help(bool invalid_flag, const i8 flag);
void	print_ping(t_ping ping);

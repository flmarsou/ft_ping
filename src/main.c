#include "ft_ping.h"

static void	init_ping(t_ping *ping)
{
	ping->audible = false;
	ping->count = 0;
	ping->date = false;
	ping->interval = 0;
	ping->quiet = false;
	ping->size = 0;
	ping->verbose = false;
	ping->destination = ((void*)0);
}

i32	main(const i32 argc, const i8 **argv)
{
	t_ping	ping;

	init_ping(&ping);

	if (!parse_arguments(argc, argv, &ping))
		return (1);

	if (!parse_dns(&ping))
		return (2);

	return (0);
}

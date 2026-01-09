#include "ft_ping.h"

# include <stdio.h>

void	print_help(bool invalid_flag, const i8 flag)
{
	if (invalid_flag)
		fprintf(stderr, "Error: invalid flag '%c'\n\n", flag);

	fprintf(stdout,
		"Usage:\n"
		"  ft_ping [options] <destination>\n\n"
		"Options:\n"
		"  <destination>      Domain Name (DNS) or IPv4 Address\n"
		"  -a                 Use audible ping\n"
		"  -c <count>         Stop after <count> replies\n"
		"  -D                 Print timestamp\n"
		"  -h / -?            Print help and exit\n"
		"  -i <interval>      Seconds between sending each packet\n"
		"  -q                 Quiet output\n"
		"  -s <size>          Use <size> as number of data bytes to be sent\n"
		"  -v                 Verbose output\n"
	);
}

void	print_ping(t_ping ping)
{
	printf("Audible:  %d\n", ping.audible);
	printf("Count:    %d\n", ping.count);
	printf("Date:     %d\n", ping.date);
	printf("Interval: %d\n", ping.interval);
	printf("Quiet:    %d\n", ping.quiet);
	printf("Size:     %d\n", ping.size);
	printf("Verbose:  %d\n", ping.verbose);
	printf("Dest:     %s\n", ping.destination);
}

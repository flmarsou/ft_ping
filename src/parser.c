#include "ft_ping.h"

# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include <netdb.h>

// ========================================================================== //
//    Argument Parser                                                         //
// ========================================================================== //

static bool	parse_single(const i8 *argument, bool *option)
{
	if (argument[2] != '\0')
	{
		print_help(true, argument[2]);
		return (false);
	}

	*option = true;
	return (true);
}

static bool	parse_multiple(const i8 *argument, const i8 *next_argument, u32 *option, i32 *iterator)
{
	if (*argument)
	{
		// Check if argument is a number
		for (u32 i = 0; argument[i]; ++i)
		if (!isdigit(argument[i]) && argument[i] != '-')
		{
			print_help(true, argument[i]);
			return (false);
		}

		// Check if the number is in range
		i64	number = atoll(argument);
		if (number < 1 || number > U32MAX)
		{
			fprintf(stderr, "Error: Invalid count value '%lld' out of range: 1 >= value <= 4294967295\n", number);
			return (false);
		}

		*option = number;
		return (true);
	}

	if (next_argument)
	{
		// Check if argument is a number
		for (u32 i = 0; next_argument[i]; ++i)
		if (!isdigit(next_argument[i]) && next_argument[i] != '-')
		{
			print_help(true, next_argument[i]);
			return (false);
		}

		// Check if the number is in range
		i64	number = atoll(next_argument);
		if (number < 1 || number > U32MAX)
		{
			fprintf(stderr, "Error: Invalid count value '%lld' out of range: 1 >= value <= 4294967295\n", number);
			return (false);
		}

		++(*iterator);
		*option = number;
		return (true);
	}

	fprintf(stderr, "Error: Missing argument for flag \"-%s\"\n", argument - 1);
	return (false);
}

static bool	parse_options(const i32 argc, const i8 **argv, t_ping *ping, i32 *i)
{
	for (; *i < argc; ++(*i))
	{
		if (argv[*i][0] != '-')
			break ;

		switch (argv[*i][1])
		{
			case ('a'):
				if (!parse_single(argv[*i], &ping->audible))
					return (false);
				break ;

			case ('c'):
				if (!parse_multiple(argv[*i] + 2, argv[*i + 1], &ping->count, i))
					return (false);
				break ;

			case ('D'):
				if (!parse_single(argv[*i], &ping->date))
					return (false);
				break ;

			case ('i'):
				if (!parse_multiple(argv[*i] + 2, argv[*i + 1], &ping->interval, i))
					return (false);
				break ;

			case ('q'):
				if (!parse_single(argv[*i], &ping->quiet))
					return (false);
				break ;

			case ('s'):
				if (!parse_multiple(argv[*i] + 2, argv[*i + 1], &ping->size, i))
					return (false);
				break ;

			case ('v'):
				if (!parse_single(argv[*i], &ping->verbose))
					return (false);
				break ;

			default:
				print_help(false, '\0');
				break ;
		}
	}

	return (true);
}

static bool	parse_destination(const i32 argc, const i8 **argv, t_ping *ping, i32 *i)
{
	if (*i < argc)
		ping->destination = argv[(*i)++];

	if (*i < argc)
	{
		fprintf(stderr, "Error: Too many destinations: \"%s\"\n\n", argv[*i]);
		print_help(false, '\0');
		return (false);
	}

	if (!ping->destination)
	{
		fprintf(stderr, "Error: Missing destination\n\n");
		print_help(false, '\0');
		return (false);
	}

	return (true);
}

bool	parse_arguments(const i32 argc, const i8 **argv, t_ping *ping)
{
	i32	i = 1;

	if (argc < 2)
	{
		print_help(false, '\0');
		return (false);
	}

	if (!parse_options(argc, argv, ping, &i))
		return (false);

	if (!parse_destination(argc, argv, ping, &i))
		return (false);

	return (true);
}

// ========================================================================== //
//    Address Parser                                                          //
// ========================================================================== //

bool	parse_dns(t_ping *ping)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct sockaddr_in	*addr;

	// If destination is already a valid IPv4 address
	if (inet_pton(AF_INET, ping->destination, ping->ip) == 1)
		return (true);

	// DNS resolution
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;		// IPv4 only
	hints.ai_socktype = SOCK_RAW;	// Any socket

	if (getaddrinfo(ping->destination, NULL, &hints, &res) || !res)
	{
		fprintf(stderr, "Error: Couldn't resolve DNS \"%s\"\n", ping->destination);
		return (false);
	}

	addr = (struct sockaddr_in *)res->ai_addr;
	inet_ntop(AF_INET, &addr->sin_addr, ping->ip, INET_ADDRSTRLEN);

	freeaddrinfo(res);

	return (true);
}

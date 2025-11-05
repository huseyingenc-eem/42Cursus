/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:00:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 16:40:07 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define RESET   "\033[0m"

typedef struct s_test
{
	char	*map_file;
	char	*expected_error;
	char	*test_name;
}	t_test;

static t_test g_tests[] = {
	{"assets/maps/error_no_player.ber", "exactly 1 player", "No Player"},
	{"assets/maps/error_no_exit.ber", "exactly 1 exit", "No Exit"},
	{"assets/maps/error_no_collectible.ber", "at least 1 collectible", "No Collectible"},
	{"assets/maps/error_two_players.ber", "exactly 1 player", "Two Players"},
	{"assets/maps/error_two_exits.ber", "exactly 1 exit", "Two Exits"},
	{"assets/maps/error_wall_top.ber", "surrounded by walls", "Wall Top Missing"},
	{"assets/maps/error_wall_bottom.ber", "surrounded by walls", "Wall Bottom Missing"},
	{"assets/maps/error_wall_left.ber", "surrounded by walls", "Wall Left Missing"},
	{"assets/maps/error_wall_right.ber", "surrounded by walls", "Wall Right Missing"},
	{"assets/maps/error_not_rectangular.ber", "length mismatch", "Not Rectangular"},
	{"assets/maps/error_invalid_char.ber", "Invalid character", "Invalid Character"},
	{"assets/maps/error_no_path_to_collectible.ber", "cannot reach", "No Path to Collectible"},
	{"assets/maps/error_no_path_to_exit.ber", "cannot reach", "No Path to Exit"},
	{NULL, NULL, NULL}
};

static char	*run_test(char *map_file)
{
	int		pipefd[2];
	pid_t	pid;
	static char	buffer[8192];
	ssize_t	n;
	ssize_t	total;
	int		status;

	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDERR_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		chdir("..");
		execlp("./so_long", "so_long", map_file, NULL);
		exit(1);
	}
	close(pipefd[1]);
	memset(buffer, 0, sizeof(buffer));
	total = 0;
	while ((n = read(pipefd[0], buffer + total, sizeof(buffer) - total - 1)) > 0)
		total += n;
	if (total > 0)
		buffer[total] = '\0';
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	return (buffer);
}

static int	check_output(char *output, char *expected)
{
	char	*line;

	if (!output || !expected)
		return (0);
	line = strchr(output, '\n');
	if (line)
		line++;
	if (line && strstr(line, expected))
		return (1);
	return (strstr(output, expected) != NULL);
}

static void	print_test_result(t_test *test, int passed, char *output)
{
	if (passed)
	{
		printf(GREEN "✓ PASS" RESET " | %s\n", test->test_name);
	}
	else
	{
		printf(RED "✗ FAIL" RESET " | %s\n", test->test_name);
		printf("  Expected: %s\n", test->expected_error);
		printf("  Got:      %.50s%s\n", output, strlen(output) > 50 ? "..." : "");
	}
}

static int	check_leaks(char *map_file)
{
	char	cmd[512];
	FILE	*fp;
	char	buffer[4096];
	int		has_leaks;

	has_leaks = 0;
	snprintf(cmd, sizeof(cmd),
		"valgrind --leak-check=full --show-leak-kinds=all "
		"--errors-for-leak-kinds=all --error-exitcode=1 "
		"../so_long %s 2>&1 | grep -E 'All heap blocks were freed|definitely lost|still reachable'",
		map_file);
	fp = popen(cmd, "r");
	if (!fp)
		return (-1);
	while (fgets(buffer, sizeof(buffer), fp))
	{
		if (strstr(buffer, "All heap blocks were freed"))
		{
			has_leaks = 0;
			break;
		}
		if (strstr(buffer, "definitely lost") || strstr(buffer, "still reachable"))
			has_leaks = 1;
	}
	pclose(fp);
	return (has_leaks);
}

int	main(int argc, char **argv)
{
	int		i;
	int		passed;
	int		failed;
	int		leak_count;
	int		leak_result;
	char	*output;
	int		run_leaks;

	run_leaks = (argc > 1 && strcmp(argv[1], "--leaks") == 0);
	printf(BLUE "╔════════════════════════════════════════════╗\n" RESET);
	printf(BLUE "║         SO_LONG AUTOMATIC TESTER          ║\n" RESET);
	printf(BLUE "╚════════════════════════════════════════════╝\n" RESET);
	printf("\n");
	passed = 0;
	failed = 0;
	i = 0;
	while (g_tests[i].map_file != NULL)
	{
		printf(YELLOW "[TEST %2d]" RESET " Testing: %-30s ", i + 1, g_tests[i].test_name);
		fflush(stdout);
		output = run_test(g_tests[i].map_file);
		if (check_output(output, g_tests[i].expected_error))
		{
			printf(GREEN "✓\n" RESET);
			passed++;
		}
		else
		{
			printf(RED "✗\n" RESET);
			print_test_result(&g_tests[i], 0, output);
			failed++;
		}
		i++;
	}
	printf("\n");
	printf(BLUE "╔════════════════════════════════════════════╗\n" RESET);
	printf(BLUE "║              TEST SUMMARY                  ║\n" RESET);
	printf(BLUE "╠════════════════════════════════════════════╣\n" RESET);
	printf("║  " GREEN "Passed: %2d" RESET " | " RED "Failed: %2d" RESET " | Total: %2d      ║\n",
		passed, failed, passed + failed);
	printf(BLUE "╚════════════════════════════════════════════╝\n" RESET);
	printf("\n");
	if (run_leaks)
	{
		printf(BLUE "╔════════════════════════════════════════════╗\n" RESET);
		printf(BLUE "║          MEMORY LEAK DETECTION             ║\n" RESET);
		printf(BLUE "╚════════════════════════════════════════════╝\n" RESET);
		printf("\n");
		leak_count = 0;
		i = 0;
		while (g_tests[i].map_file != NULL)
		{
			printf(YELLOW "[LEAK %2d]" RESET " %-35s ", i + 1, g_tests[i].test_name);
			fflush(stdout);
			leak_result = check_leaks(g_tests[i].map_file);
			if (leak_result == 0)
				printf(GREEN "✓ NO LEAKS\n" RESET);
			else
			{
				printf(RED "✗ LEAK!\n" RESET);
				leak_count++;
			}
			i++;
		}
		printf("\n");
		printf(BLUE "╔════════════════════════════════════════════╗\n" RESET);
		printf(BLUE "║          MEMORY LEAK SUMMARY               ║\n" RESET);
		printf(BLUE "╠════════════════════════════════════════════╣\n" RESET);
		printf("║  " GREEN "No Leaks: %2d" RESET " | " RED "Leaks: %2d" RESET " | Total: %2d   ║\n",
			i - leak_count, leak_count, i);
		printf(BLUE "╚════════════════════════════════════════════╝\n" RESET);
		printf("\n");
		if (leak_count > 0)
		{
			printf(RED "⚠️  MEMORY LEAKS DETECTED! ⚠️\n" RESET);
			return (1);
		}
		printf(GREEN "🎉 NO MEMORY LEAKS! 🎉\n" RESET);
	}
	if (failed == 0 && (!run_leaks || leak_count == 0))
	{
		printf(GREEN "🎉 ALL TESTS PASSED! 🎉\n" RESET);
		return (0);
	}
	else
	{
		if (!run_leaks)
			printf(YELLOW "💡 Tip: Run with --leaks to check memory leaks\n" RESET);
		printf(RED "⚠️  SOME TESTS FAILED! ⚠️\n" RESET);
		return (1);
	}
}

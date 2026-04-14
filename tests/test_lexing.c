#include "../includes/pipex.h"
#include <stdio.h>
#include <string.h>

typedef struct s_test {
	char	*input;
	int		expected_count;
	char	*test_name;
}	t_test;

void	print_tab(char **tab)
{
	int	i;

	if (!tab)
	{
		printf("NULL\n");
		return ;
	}
	i = 0;
	while (tab[i])
	{
		printf("  [%d]: '%s'\n", i, tab[i]);
		i++;
	}
}

void	test_tokenization(void)
{
	t_test	tests[] = {
		{"ls -la", 2, "simple command with args"},
		{"cat file.txt | grep test", 5, "piped commands"},
		{"echo \"hello world\"", 2, "quoted argument"},
		{"awk '{print $1}'", 2, "awk with curly braces"},
		{"sed 's/a/b/g' input.txt", 3, "sed with regex"},
		{"cut -d',' -f2 data.csv", 4, "cut with delim"},
		{"grep -E '^[a-z]+$' file", 4, "grep with regex"},
		{"sort | uniq | wc -l", 5, "multiple pipes"},
		{"tr 'a' 'A'", 3, "tr command"},
		{"head -n 10 | tail -n 5", 5, "head tail combined"},
		{"awk 'NR>1 {print $2}'", 2, "awk with condition"},
		{"sed -i 's/old/new/g' *", 4, "sed with wildcard"},
		{NULL, 0, NULL}
	};

	int	i;
	char	**result;

	printf("=== TOKENIZATION TESTS ===\n\n");
	i = 0;
	while (tests[i].input)
	{
		printf("Test: %s\n", tests[i].test_name);
		printf("Input: '%s'\n", tests[i].input);
		result = ft_split_almost_like_shell(tests[i].input);
		printf("Expected tokens: %d\n", tests[i].expected_count);
		printf("Result:\n");
		print_tab(result);
		
		if (result)
		{
			int j = 0;
			while (result[j])
				free(result[j++]);
			free(result);
		}
		printf("\n");
		i++;
	}
}

void	test_quote_removal(void)
{
	t_test	tests[] = {
		{"'hello'", 0, "single quotes"},
		{"\"world\"", 0, "double quotes"},
		{"'hello' \"world\"", 0, "mixed quotes"},
		{"echo \"a b c\"", 0, "quoted with spaces"},
		{"grep 'pattern'", 0, "grep pattern"},
		{"awk '{print $1}'", 0, "awk code"},
		{"sed 's/a/b/'", 0, "sed pattern"},
		{NULL, 0, NULL}
	};

	int	i;
	char	*result;

	printf("=== QUOTE REMOVAL TESTS ===\n\n");
	i = 0;
	while (tests[i].input)
	{
		printf("Test: %s\n", tests[i].test_name);
		printf("Input: '%s'\n", tests[i].input);
		result = ft_remove_quote(tests[i].input);
		printf("Output: '%s'\n", result ? result : "NULL");
		if (result)
			free(result);
		printf("\n");
		i++;
	}
}

void	test_path_resolution(char **envp)
{
	char	*commands[] = {
		"ls",
		"cat",
		"grep",
		"awk",
		"sed",
		"cut",
		"sort",
		"uniq",
		"wc",
		"tr",
		"head",
		"tail",
		"/usr/bin/python3",
		"/bin/sh",
		"nonexistent_cmd_xyz",
		NULL
	};

	int		i;
	char	*path;

	printf("=== PATH RESOLUTION TESTS ===\n\n");
	i = 0;
	while (commands[i])
	{
		path = ft_extract_path(commands[i], envp);
		printf("Command: %-20s -> %s\n", commands[i], path ? path : "NOT FOUND");
		if (path)
			free(path);
		i++;
	}
	printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	printf("\n");
	test_tokenization();
	printf("\n");
	test_quote_removal();
	printf("\n");
	test_path_resolution(envp);
	
	return (0);
}

/**
 * free_tab - clean a two dimension array
 *
 * @tab: two dimension array to be clean
 */
void free_tab(char **tab)
{
	int i = 0;

	for (; tab[i]; i++)
	{
		free(tab[i]);
	}
	free(tab);
}

/**
 * clean - clean one dimension buffers and two dimensions arrays
 *
 * @temp: one dimension buffer to be cleaned
 * @args: two dimensions array to be cleaned
 */
void clean(char *temp, char **args)
{
	free(temp);
	free_tab(args);
}

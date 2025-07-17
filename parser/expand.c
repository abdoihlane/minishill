#include "../mini.h"

char	*expand_variables(char *input)
{
	if (!input || !ft_strchr(input, '$'))
		return (ft_strdup(input));
	char *pos = ft_strchr(input, '$');
	if (!pos)
		return (ft_strdup(input));
	char *key = pos + 1;
	if (*key == '\0')
		return (ft_strdup(input));
	int i = 0;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	char *varname = ft_substr(key, 0, i);
	char *env = getenv(varname);

	char *prefix = ft_substr(input, 0, pos - input);
	char *suffix = ft_strdup(pos + 1 + i);

	char *tmp1 = ft_strjoin(prefix, env ? env : "");
	char *result = ft_strjoin(tmp1, suffix);

	free(varname);
	free(prefix);
	free(suffix);
	free(tmp1);
	return (result);
}

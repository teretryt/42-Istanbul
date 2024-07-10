/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 22:55:59 by rturker           #+#    #+#             */
/*   Updated: 2023/01/02 17:41:22 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "get_next_line.h"

int	is_sorted(t_stack *stack)
{
	while (stack->next != NULL)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	comparem(char *input, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strcmp(input, "sa\n") == 0)
		sa(stack_a);
	else if (ft_strcmp(input, "sb\n") == 0)
		sb(stack_b);
	else if (ft_strcmp(input, "ss\n") == 0)
		ss(stack_a, stack_b);
	else if (ft_strcmp(input, "ra\n") == 0)
		ra(stack_a);
	else if (ft_strcmp(input, "rb\n") == 0)
		rb(stack_b);
	else if (ft_strcmp(input, "rr\n") == 0)
		rr(stack_a, stack_b);
	else if (ft_strcmp(input, "rra\n") == 0)
		rra(stack_a);
	else if (ft_strcmp(input, "rrb\n") == 0)
		rrb(stack_b);
	else if (ft_strcmp(input, "rrr\n") == 0)
		rrr(stack_a, stack_b);
	else if (ft_strcmp(input, "pa\n") == 0)
		pa(stack_a, stack_b);
	else if (ft_strcmp(input, "pb\n") == 0)
		pb(stack_a, stack_b);
	else
		return (0);
	return (1);
}

void	check(t_stack *stack_a, t_stack *stack_b)
{
	char	*input;

	input = get_next_line(0);
	while (input)
	{
		if (comparem(input, &stack_a, &stack_b) == 0)
			break ;
		input = get_next_line(0);
	}
	free(input);
	if (is_sorted(stack_a) && get_stack_size(stack_b) == 0)
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		stack_size;
	int		ac2;
	char	**av2;

	if (ac < 2)
		return (0);
	av2 = av;
	ac2 = ac;
	if (ac == 2)
	{
		av2 = ft_split(av[1], ' ');
		av2[0] = word_create("./a.out", ' ');
		ac2 = word_counter(av[1], ' ');
	}
	if (!is_correct_input(av2))
		exit_error(NULL, NULL);
	stack_b = NULL;
	stack_a = fill_stack_values(ac2, av2);
	stack_size = get_stack_size(stack_a);
	check(stack_a, stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}

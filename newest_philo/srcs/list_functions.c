#include "philo_new.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n;

	n = (t_list *)ft_calloc(sizeof(t_list), 1);
	if (!n)
		return (NULL);
	n->content = content;
	n->next = NULL;
	return (n);
}


void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*move;

	if (!lst)
		return ;
	if (*lst)
	{
		move = *lst;
		while (move->next)
			move = move->next;
		move->next = new;
	}
	else
		*lst = new;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(tmp, del);
	}
	lst = NULL;
}

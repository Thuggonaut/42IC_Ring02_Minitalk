#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*head;
	void	*content;

	new_list = NULL;
	head = new_list;
	if (!(f || del))
		return (NULL);
	while (lst)
	{
		content = f(lst->content);
		if (!content)
		{
			return (free(content), ft_lstclear(&head, del), NULL);
		}
		new_list = ft_lstnew(content);
		if (!new_list)
		{
			return (free(content), ft_lstclear(&head, del), NULL);
		}
		ft_lstadd_back(&head, new_list);
		lst = lst->next;
	}
	return (head);
}

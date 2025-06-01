#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *current;
    t_list *next;

    if (!lst || !del)
        return;
    current = *lst;
    while (current)
    {
        next = current->next;
        if (current->content)
            del(current->content);
        free(current);
        current = next;
    }
    *lst = NULL;
}
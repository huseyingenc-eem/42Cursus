#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

/*
** ==================================================================
** =================== YARDIMCI FONKSİYONLAR ========================
** ==================================================================
*/

// Düğümün içeriğini (content) silmek için kullanılan fonksiyon.
// ft_lstdelone, ft_lstclear ve ft_lstmap'te hata durumunda kullanılır.
void	del_content(void *content)
{
	printf(" (Siliniyor: \"%s\")", (char *)content);
	free(content);
}

// Listenin elemanlarını ekrana yazdırmak için ft_lstiter'a verilecek fonksiyon.
void	print_content(void *content)
{
	printf(" -> [%s]", (char *)content);
}

// Yeni bir liste oluşturmak için ft_lstmap'e verilecek fonksiyon.
// Gelen içeriği kopyalar ve ilk harfini büyütür.
void	*map_function(void *content)
{
	char	*new_content;

	new_content = ft_strdup((char *)content);
	if (new_content)
		new_content[0] = ft_toupper(new_content[0]);
	return (new_content);
}

/*
** ==================================================================
** ======================= ANA TEST FONKSİYONU ======================
** ==================================================================
*/

int	main(void)
{
	t_list	*head = NULL;
	t_list	*last;
	t_list	*mapped_list;

	ft_lstadd_front(&head, ft_lstnew(ft_strdup("birinci")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("ikinci")));

	ft_lstiter(head,&print_content);
	printf("\n");


	ft_lstdelone(head->next,free);
	//head->next=NULL;

	ft_lstiter(head,&print_content);
	

	return (0);
}
#include "cub3d.h"

void	free_all()
{
	t_control *main;
	t_node	*prv;

	main = control_memo();
	prv = main->node;
	while (main->node != NULL)
	{
		prv = main->node->next;
		free(main->node);
		main->node = prv;
	}
	exit(1);
}

void	add_m_node(void *data)
{
	t_control *main;
	t_node	*n;
	t_node	*temp;

	main = control_memo();
	n = malloc(sizeof(t_node));
	if(!n)
		free_all();
	n->next = NULL;
	n->data = data;
	if(main->node == NULL)
		main->node = n;
	else
	{
		temp = main->node;
		while (temp != NULL && temp->next != NULL)
			temp = temp->next;
		temp->next = n;
	}
}
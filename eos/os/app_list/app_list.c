/*
 * app_queue.c
 *
 * Created: 8/23/2015 11:09:23 AM
 *  Author: Mihai
 */ 
#include <stdlib.h>
#include "../stdtypes.h"
#include "../errorcode.h"
#include "app_list.h"


UBYTE app_list_push(UBYTE app_identifier,void (*app_node)(void))
{
	ENABLE_PROTECTION();
	UBYTE lub_error_code=SUCCESS;
	struct S_List_Node *temporary_node=(struct S_List_Node*)malloc(sizeof(struct S_List_Node));
	
	if(temporary_node==NULL)
	{
		lub_error_code=EOOM;
		goto function_return;
	}
	if(app_list_search(app_identifier)!=NULL)
	{
		lub_error_code=EAPL;
		goto function_return;
	}
	
	temporary_node->app_identifier=app_identifier;
	temporary_node->app_node=app_node;
	temporary_node->next=NULL;
	if(app_list_root==NULL )
	{
		app_list_root=temporary_node;
		
	}
	else
	{
		struct S_List_Node *aux_node;
		for(aux_node=app_list_root;aux_node->next!=NULL;aux_node=aux_node->next);
		aux_node->next=temporary_node;
	}
	
	function_return:
	{
		DISABLE_PROTECTION();
		return lub_error_code;	
	}
	
	
}

void app_list_pop(UBYTE app_identifier)
{
	ENABLE_PROTECTION();
	if(app_list_root==NULL)
	{
		DISABLE_PROTECTION();
		return;
	}
	struct S_List_Node *temporary_node=NULL;
	struct S_List_Node *auxiliary_node=NULL;
	for(
		temporary_node=app_list_root;
		temporary_node!=NULL && temporary_node->next->app_identifier!=app_identifier;
		temporary_node=temporary_node->next
		);
	if(temporary_node->next!=NULL && temporary_node->next->app_identifier==app_identifier)
	{
		auxiliary_node=temporary_node->next;
		temporary_node->next=auxiliary_node->next;
		free(auxiliary_node);
	}	
	
	DISABLE_PROTECTION();	
	
}


struct S_List_Node *app_list_search(UBYTE app_identifier)
{
	
	struct S_List_Node *aux_node;
	for (
		aux_node = app_list_root; 
		aux_node != NULL && aux_node->app_identifier != app_identifier; 
		aux_node = aux_node->next
		);

	if (aux_node != NULL && aux_node->app_identifier == app_identifier)
	{
		return aux_node;	
	}
	return NULL;
}

_PUBLIC void app_list_execute()
{
	struct S_List_Node *list_iterator=app_list_root;
	void (*app_task)(void)=0;
	while(list_iterator!=NULL)
	{
		app_task=list_iterator->app_node;
		(*app_task)();
		list_iterator=list_iterator->next;
	}
	
}


_PUBLIC inline UBYTE app_register(UBYTE app_identifier,void (*app_node)(void))
{
		return app_list_push(app_identifier,app_node);
}
_PUBLIC inline void app_unregister(UBYTE app_identifier)
{
	app_list_pop(app_identifier);
	
}
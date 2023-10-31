#include <stdlib.h>
#include <stdio.h>

struct Node {
	int data;
	struct Node* next;
};
//Liberar memoria

void freemem( struct Node *head) {

	//Inicio por la cabeza
	struct Node* current = head;
	//Nodo para iterar
	struct Node* next;
	while ( current != NULL ) {
		//voy al nodo que sigue del actual
		next = current->next;
		//libero el actual
		free(current);
		current = next;
	}
}

//Agregar al principio de la lista 
//
void insert(int data ,struct  Node **head){
	// Reservo el espacio del nuevo nodo y obtengo su direccion
	struct Node* nuevo = (struct Node*)malloc(sizeof( struct Node));
	//Desreferencio el struct
	nuevo->data = data;
	// el next del nuevo nodo es la antigua cabeza
	nuevo->next = (*head);
	// el puntero cabeza ahora apunta a nuevo
	(*head) = nuevo;
}
/* Imprimir Lista */
//Agregar un nodo al final 

void finalnew( int data , struct Node * head) {
	struct Node* nuevo = (struct Node*)malloc(sizeof( struct Node));
	nuevo ->data = data;
	nuevo -> next = NULL;
	struct Node* current= head;
	struct Node* last;
	while ( current != NULL) {
		last = current;
		current = current ->next;
	}
	last -> next = nuevo;
}
//Obtener el elemento enesimo
void findIndex( int index, struct Node * head) {
	int count=0;
	struct Node* current = head;
	while ( current != NULL && count != index) {
		current = current -> next;
		count++;
	}

	if ( current == NULL ) {
		printf("No existe\n");
		return;
	}else {
		printf( "En el indice %d -> %d \n", index , current -> data);
		return;

	}

}
//Agregar un nodo en un indice cualquiera
void newNode(int index ,int data , struct Node * head) {
	//Si es en el indice 0 se agrega a la cabeza
	if ( index == 0 ) {
		insert( data , &head);
		return;
	}
	struct Node* current = head;
	int count = 0;
	struct Node* nuevo = (struct Node*)malloc(sizeof(struct Node));
	nuevo -> data = data;
        struct Node* prev = NULL;
	 while ( current != NULL && count != index) {
		 prev = current;
                current = current -> next;
                count++;
        }



        //Caso esquina indice mayor a elementos de la lista, por default lo agrega al final
        if ( current == NULL ){
                current -> next = nuevo;
		nuevo -> next = NULL;
                return;
        }
	//Caso donde se encuentra el indice
	prev -> next = nuevo;
	nuevo -> next = current;
	return;

}
void printList( struct Node* node) {

	while ( node != NULL) {
		printf("%d -> ", node -> data);
		node = node ->next;
	}
	printf("\n");
}
/* Eliminar un nodo por su valor*/

void deleteNode( int valor, struct Node **node){
	struct Node* current = *node;

	struct Node* prev = NULL;
	//Caso esquina eleminar el primer elemento
	if ( current != NULL && current -> data == valor){
		*node = current -> next;
		free(current);
		return;
	}

	//Buscar el nodo
	while(current != NULL && current -> data != valor ) {
		prev = current;
		current = current -> next;
	}

	//Nodo encontrado o final de la lista
	if ( current == NULL){
		printf("Nodo no encontrado \n");
		return;
	} 

	//Encontramos el nodo
	// El elemento anterior al nodo que queremos eliminar debe apuntar al next del nodo a eliminar
	prev ->next = current ->next;
	free(current);
}

//Buscar un nodo por su valor 
void searchNode( int valor, struct Node *node){
        struct Node* current = node;
        //Buscar el nodo
        while(current != NULL && current -> data != valor ) {
                current = current -> next;
        }

        //Nodo encontrado o final de la lista
        if ( current == NULL){
                printf("Nodo no encontrado \n");
                return;
        } else {
                printf("Nodo encontrado\n");
        }
}



int main() {
	struct Node* head = NULL;
	//Se inserta un nodo al inicio
	insert( 9, &head);
	//Se imprime la lista
	printf("Agregar un nodo al incio\n");
	printList(head);
	//Se inserta otro nodo al inicio
	insert( 7, &head);
	//Se imprime la lista
	printList(head);
	//Borrar el nodo
	printf("Borrar un nodo, %d\n", head ->data);
	deleteNode( 7 ,&head);
	printList(head);
	//Agregar un nodo al final
	printf("Agregar un nodo al final\n");
	finalnew( 8 , head);
	printList(head);
	insert(10, &head);
	printList(head);
	//Buscar en el indice 1
	printf("Buscar un nodo en un indice: 1\n");
	findIndex( 1, head);
	//Buscar en un indice que no existe 
	printf("Buscar un nodo en un indice que no existe\n");
	findIndex(10, head);
	//Agregar un nodo en un indice cualquiera
	printf("Agregar un nodo en un indice cualquiera\n");
	newNode( 1 , 4, head);
	printList(head);

	//Se libera memoria
	freemem(head);
}

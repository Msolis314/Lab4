En el presente laboratorio se buscó implementar operaciones en lista enlazadas.
Primero, para crear una lista se debe crear un tipo de dato struct para los nodos que contenga:
1. El dato almacenado en el nodo
2. Un puntero al siguiente elemento
Lo cuál se hace con el siguiente código: 
```C
struct Node {
	int data;
	struct Node* next;
};
```
En este caso el tipo de dato es `int` y resaltar que puntero es del tipo `Node*` haciendo referencia que apunta a otro nodo.
## Imprimir lista
Para imprimir la lista solo es necesario pasarle a una función el puntero a la cabeza y en un *while loop* imprimir el valor en `data` de cada nodo. En el loop se cambia el puntero temporal al que sigue, esto hasta llegar a `NULL`.
```C
while ( node != NULL) {
		printf("%d -> ", node -> data);
		node = node ->next;
	}
	printf("\n");

```
## Agregar un nodo al inicio
Para agregar un nodo al inicio de la lista se debe primero reservar el espacio en memoria para el nuevo nodo.
```C
struct Node* nuevo = (struct Node*)malloc(sizeof( struct Node));
```
Luego asignar el dato al nuevo nodo y hacer que su next apunte al puntero de la antigua cabeza.
```C
nuevo->data = data;
// el next del nuevo nodo es la antigua cabeza
nuevo->next = (*head);
// el puntero cabeza ahora apunta a nuevo
```
Ahora, es importante destacar que en este caso se necesita pasar un doble pointer a la función ya que hay que modificar el puntero de la cabeza al nuevo nodo.
```C
void insert(int data ,struct  Node **head)
```
## Agregar un nodo al final 
Para agregar un nodo se debe nuevamente reservar su espacio en el *heap*, pero ahora se apunta su cabeza a `NULL`.
```C
nuevo ->data = data;
nuevo -> next = NULL;
```

Seguidamente, utilizando los punteros temporales de `current` y `last` se itera en la lista actual hasta llegar al final esto para almacenar en `last` el puntero al último elemento actual. El next de este elemento ahora debe apuntar al nuevo nodo.
```C
while ( current != NULL) {
		last = current;
		current = current ->next;
	}
	last -> next = nuevo;
```
## Agregar un nodo en un índice cualquiera
Para agregar un nodo en cualquier posición, se sigue una lógica similar a la anterior para los casos extremos de que se trate del índice 0 que sería igual a agregarlo al inicio o un índice mayor que sería como agregarlo al final. Para el caso intermedio se debe iterar en la lista hasta encontrar el índice o llegar a NULL. Si sucede lo último significa que no existe el índice y se debe agregar al final del nodo, sino se almacena en un nodo temporal `prev` el nodo anterior al del índice `current` este ahora debe apuntar a nuevo y el next de nuevo debe apuntar a `current`.
```C
prev -> next = nuevo;
nuevo -> next = current;
```
## Obtener el elemento enésimo
Para está parte se utiliza la lógica menciona con anterioridad para encontrar el índice. Se itera por medio de un `while  ` y un contador por toda la lista usando un nodo temporal ` current` hasta que se llegue a `NULL` en dicho caso el índice no existe o se llegue a que el contador es igual al índice que significa que si existe y se imprime el valor en `data` de current.
```C
int count=0;
struct Node* current = head;
while ( current != NULL && count != index) {
	current = current -> next;
	count++;
}

```

## Buscar un nodo por su valor 
Para buscar un nodo nuevamente se usa un nodo temporal `current` para iterar por toda la lista hasta encontrar el nodo cuyo valor en `data` corresponda al valor buscado o llegar a `NULL` que significaría que no existe el nodo.
```C
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
```

## Eliminar un nodo por su valor 
Para eliminar un nodo por su valor se sigue la misma lógica que al buscarlo, nada más que hay que tomar en cuenta el caso esquina que el nodo sea el del inicio ya que esto significa que se debe cambiar el puntero de la cabeza al siguiente elemento antes de eliminarlo. Este es el motivo que se necesita pasar un *doble pointer* de la cabeza a la función.
```C
struct Node* current = *node;

struct Node* prev = NULL;
//Caso esquina eleminar el primer elemento
if ( current != NULL && current -> data == valor){
	*node = current -> next;
	free(current);
	return;
}
```
Si el anterior no es caso, se procede a iterar nuevamente por la lista al igual que en el ejercicio anterior. Nada más que ahora se debe guardar en otro nodo temporal el elemento antecesor de la lista. Si se llega a `NULL` el nodo no fue encontrado, de lo contrario se encontró el valor y para eliminarlo se debe primero apuntar el next del nodo anterior al next del nodo a eliminar para "reconectar" la lista. Luego se puede eliminar el nodo.
```C
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
```
## Liberar memoria 
Para liberar la memoria igual se debe iterar por toda la lista con dos nodos temporales. Uno `current` que guarde el valor actual y otro `next` que sirva para guardar el nodo siguiente e igualarlo a current después de liberar current.
```C
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
```
## Resultados 

Al llamar cada una de las funciones desde el main de la siguiente manera:
```C
//Se inserta un nodo al incio
	insert( 9, &head);
	//Se imprime la lista
	printf("Agregar un nodo al incio\n");
	printList(head);
	//Se inserta otro nodo al inicio
	insert( 7, &head);
	//Se imprime la lista
	printList(head);
	//Borrar el nodo
	printf("Borar un nodo\n");
	deleteNode( 7 ,&head);
	printList(head);
	//Agregar un nodo al final
	printf("Agregar un nodo al final\n");
	finalnew( 8 , head);
	printList(head);
	insert(10, &head);
	printList(head);
	//Buscar en el indice 1
	printf("Buscar un nodo en un indice\n");
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
```
Se obtiene el siguiente resultado, y por tanto se cumple el objetivo de realizar operaciones en listas:

![alt image](https://github.com/Msolis314/Clases/blob/main/La4Result.png)

Al correr el siguiente comando en la terminal: 

![alt image](https://github.com/Msolis314/Clases/blob/main/Screenshot%202023-10-27%20121916.png)


Se obtiene el siguiente reporte de valgrind y por tanto no hay *memory leaks* en el programa. 

![alt image](https://github.com/Msolis314/Clases/blob/main/Report.png)

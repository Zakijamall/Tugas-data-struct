#include <stdio.h>
#include <stdlib.h>

struct data{
	int age;
	struct data *next;
	struct data *prev;
};

struct data *head = NULL;
struct data *tail = NULL;

struct data *create_node(int age){
	struct data *node = (struct data*)malloc(sizeof(struct data));
	node->next = NULL;
	node->prev = NULL;
	node->age = age;
	
	return node;
}

void push_head(int age){
	struct data *node = create_node(age);
	
	if(!head){
	    head = tail = node;
    }
    else{
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void push_tail(int age){
	struct data *node = create_node(age);
	
	if(!node){
	    push_head(age);
    }
    else{
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void push_mid(int age) {
    struct data *slow = head;
    struct data *fast = head;
    struct data *node = create_node(age);

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    
    node->next = slow->next;
    node->prev = slow;
    
    if (slow->next != NULL){
        slow->next->prev = node;
        slow->next = node;
    }
    
}

void pop_head(){
	struct data *temp = head;
	head = head->next;
	head->prev = NULL;
	free(temp);
}

void pop_tail(){
	struct data *temp = tail;
	tail = tail->prev;
	tail->next = NULL;
	
	free(temp);
}

void pop_search(int age){
	struct data *curr = head;
	
	while(curr != NULL){
		if(curr->age == age){
		    if (curr->prev != NULL)
                curr->prev->next = curr->next;
            if (curr->next != NULL)
                curr->next->prev = curr->prev;
            if (curr == head)
                head = curr->next;
            if (curr == tail)
                tail = curr->prev;
			free(curr);
			return;
		}
		curr = curr->next;
	}
    printf("Data dengan umur %d tidak ditemukan.\n", age);
}

void print_linked_list(){
	struct data *temp = head;
	int count = 1;
	
	while(temp != NULL){
		printf("Data ke-%d : %d\n", count, temp->age);
		temp = temp->next;
		count++;
	}
}

int main(){
	
	head = create_node(2);
	tail = create_node(5);
	
	head->next = tail;
	tail->prev = head;
	
	//push depan
	push_head(1);
	//push belakang
	push_tail(10);
	//push tengah
	push_mid(3);
	push_mid(7);

	//push depan
	pop_head();
	
	pop_search(3);

	print_linked_list();
	
	return 0;
}

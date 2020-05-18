#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#define INITIALSIZE (1)
typedef struct node{
	char *key;
	char *value;
	struct node *next;
}c;
typedef struct dict{
	int size;
	int n;
	c **table;
}dict;
void grow(dict *);
void shrink(dict *);
dict *dictCreateMain(int size){
	dict *d;
	int i;
	d = (dict *)malloc(sizeof(dict));
	d->size = size;
	d->n =0;
	d->table= (c **)malloc(size*sizeof(c *));
	assert(d->table!=0);
	for(i=0;i<d->size;i++)
	d->table[i] = NULL;
	return d;
}
dict *dictCreate(){
	return dictCreateMain(INITIALSIZE);
}
void dictDestroy(dict *d){
	int i;
	c *p,*next;
	for(i=0;i<d->size;d++){
		for(p=d->table[i];p!=NULL;p=next){
			next = p->next;
			free(p->key);
			free(p->value);
			free(p);
		}
	}
	d->table=NULL;
	d=NULL;
}
unsigned long mhashfunction(char *key){
	int i=0;
	unsigned long h=0;
	unsigned char *s;
	for(s=key,i=1;*s;*s++,i++)
	h = h + (*s)*i;
	return h;	
}
void dictInsert(dict *d,char *key,char *val){
	c *temp = (c *)malloc(sizeof(c));
	unsigned long h;
	c *p;
	temp->key=strdup(key);
	temp->value = strdup(val);
	temp->next = NULL;
	h = mhashfunction(key)%d->size;
	temp->next = d->table[h];
	d->table[h] = temp;
	d->n++;
	if(d->n >= d->size)
	grow(d);
}

void grow(dict *d){
	dict *d2;
	dict temp;
	int i;
	c *p;
	d2 = dictCreateMain(d->size*2);	/*table doubling*/	
	for(i=0;i<d->size;i++){
		for(p=d->table[i];p!=NULL;p=p->next)
		dictInsert(d2,p->key,p->value);
	}
	temp = *d;
	*d = *d2;
	*d2 = temp;
	dictDestroy(d2);
}


char *dictSearch(dict *d,char *key){
	unsigned long h;
	h = mhashfunction(key) % d->size;
	c *node;
	for(node=d->table[h];node!=NULL;node=node->next)
	if(!strcmp(key,node->key))
	return node->value;
	return "Key not found!";
}
void dictDelete(dict *d,char *key){
	unsigned long h;
	h=mhashfunction(key)% d->size;
	c *node,*p;
	for(node=d->table[h];node!=NULL;node=node->next){
		if(!strcmp(key,node->key)){
		p = node->next;
		if(p!=NULL){
		node->next = p->next;
		node->key = p->key;
		node->value = p->value;
		free(p);
		}
		else{
			free(node);
		}
		return;
		}
	}
	
}/*
void shrink(dict *d){
	dict *d2;
	dict temp;
	int i;
	c *p;
	printf("%d\n",d->size/2);
	d2 = dictCreateMain(d->size/2);	Half the size of original	
	for(i=0;i<d->size;i++){
		for(p=d->table[i];p!=NULL;p=p->next)
		dictInsert(d2,p->key,p->value);
	}
			printf("duh");

	temp = *d;
	*d = *d2;
	*d2 = temp;
	dictDestroy(d2);
}
*/
int main(){
	int i;
	 char *key,*value;
	 key=(char *)malloc(100*sizeof(char));
	 value=(char *)malloc(100*sizeof(char));
	dict *d = dictCreate();
	 while(1){
	 	printf("0 -> Insert\n1 -> Delete\n2 -> Search \n");
	 	scanf("%d",&i);
	 	switch (i){
	 		case 0:
	 			printf("Enter key:\t");
	 			scanf(" %[^\n]s",key);
	 			printf("Enter value:\t ");
	 			scanf(" %[^\n]s",value);
	 			dictInsert(d,key,value);
	 			break;
	 		case 1:
	 			printf("Enter key:\t");
	 			scanf(" %[^\n]s",key);
	 			dictDelete(d,key);
	 			break;
	 		case 2:
	 			printf("Enter key:\t");
	 			scanf(" %[^\n]s",key);
	 			printf("%s\n",dictSearch(d,key));
	 			break;
		 }
	 }
}

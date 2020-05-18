#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define OVERHEAD (1.1) /*for open addressing overhead > 1 => m>=n */
#define NULLID (-1)
#define MIN_ID (0)
#define MAX_ID (999999999)
typedef struct hashtable{
	int size;
	int *table;
}c;
c *create_table(int,int *);
void destroytable(c *);
int contains_item(c *,int);
int main(){
	int *x,n,i;
	scanf("%d",&n);
	x=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	scanf("%d",&x[i]);
	c *mytable = create_table(n,x);
	printf("-------------------------------------------------------------------------------------------\n");
	for(i=0;i<mytable->size;i++)
	printf("(%d,%d)\n",i,mytable->table[i]);
	printf("-------------------------------------------------------------------------------------------\n");
	while(n!=-1){
		scanf("%d",&n);
		printf("%d\n",contains_item(mytable,n));
	}
	
}
c *create_table(int n,int *items){
	int size,probe,i;
	c *mhashTable = (c *)malloc(sizeof(c));
	size = (n*OVERHEAD + 1); /*hash table size*/
	mhashTable->size = size;
	printf("--%d\n",size);
	mhashTable->table = (int *)malloc((size)*sizeof(int));
	for(i=0;i<size;i++)
	mhashTable->table[i] = NULLID;
	for(i=0;i<n;i++){
		assert(items[i]>= MIN_ID);
		assert(items[i]<= MAX_ID);
		for(probe=items[i]%size; mhashTable->table[probe]!=NULLID; probe=(probe+1)%size); 	/*linear probing*/
		assert(mhashTable->table[probe]==NULLID);
		mhashTable->table[probe] = items[i];
	}
	return mhashTable;
}
void destroytable(c *mhashTable){
	free(mhashTable);
}
int contains_item(c *mhashTable,int id){
	int probe;
	if(id==-1)
	return 0;
	for(probe=id%mhashTable->size;mhashTable->table[probe]!=NULLID;probe=(probe+1)%mhashTable->size){
		if(mhashTable->table[probe]==id)
		return 1;
	}
	return 0;
}

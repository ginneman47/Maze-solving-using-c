//maze solving/pathfinding basic prototype
//test#1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define size 8

struct node {
    int row;
    int column;
    int status;
    struct node *up;
    struct node *down;
    struct node *left;
    struct node *right;
};

struct node *start=NULL;
struct node *end=NULL;

//struct node *set_node(int row, int column, char cell);
void set_links(struct node *ref[][size]);
//dfs traversal
void findpath(struct node *current,struct node *ref[][size]);


//stack that holds the values of the node pushed
struct stack{
    int hor;
    int ver;
    struct stack *link;
};

struct stack *top=NULL;
struct stack *create_stack(int row, int column);
void push(int row, int column);
void pop();

void display_path(int maze[][size],struct node *ref[][size]);

int main() {
struct node *adj[size][size];
for(int i=0; i<size; i++){
    for(int j=0; j<size; j++){
        adj[i][j]=(struct node *)malloc(sizeof(struct node));
    }
}
int maze[size][size];
   for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            scanf("%d",&maze[i][j]);
            if(maze[i][j]==0){
                adj[i][j]=NULL;
                free(adj[i][j]);
            }
            else{
                adj[i][j]->row=i;
                adj[i][j]->column=j;
                adj[i][j]->status=-1;
                adj[i][j]->up=NULL;
                adj[i][j]->down=NULL;
                adj[i][j]->left=NULL;
                adj[i][j]->right=NULL;
             if(maze[i][j]==2){
                start=adj[i][j];
            }
            else if(maze[i][j]==3){
                end=adj[i][j];
            }
        }
            
       }
    }
//printf("%d",sizeof(struct node));
printf("all possible links\n");
set_links(adj);
printf("\n");
printf("the path taken\n");
findpath(start,adj);
printf("\n");
display_path(maze,adj);
}

void set_links(struct node *ref[][size]){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(ref[i][j]!=NULL){
                //look up
                if(ref[i-1][j]!=NULL && (i-1)>=0){
                    printf("up-%d %d\n",i,j);
                    ref[i][j]->up=ref[i-1][j];
                }
                //look down
                if(ref[i+1][j]!=NULL && (i+1)<=size-1){
                    printf("down-%d %d\n",i,j);
                    ref[i][j]->down=ref[i+1][j];
                }
                //look left
                if(ref[i][j-1]!=NULL && (j-1)>=0){
                    printf("left-%d %d\n",i,j);
                    ref[i][j]->left=ref[i][j-1];
                }
                //look right
                if(ref[i][j+1]!=NULL && (j+1)<=size-1){
                    printf("right-%d %d\n",i,j);
                    ref[i][j]->right=ref[i][j+1];
                }
            }
        }
    }
}

struct stack *create_stack(int row, int column){
    struct stack *newstack;
    newstack=(struct stack *)malloc(sizeof(struct stack));
    newstack->hor=row;
    newstack->ver=column;
    newstack->link=NULL;
    
    return newstack;
}


//dfs traversal

void findpath(struct node *current,struct node *ref[][size]){
    if(current!=end){
        push(current->row,current->column);
        ref[current->row][current->column]->status=1;
        
        //call for next node
        if(current->up!=NULL && current->up->status==-1){
            printf("%d %d - current-up\n",current->row,current->column);
            findpath(current->up,ref);
        }
        else if(current->down!=NULL && current->down->status==-1){
            printf("%d %d - current-down\n",current->row,current->column);
            findpath(current->down,ref);
        }
        else if(current->left!=NULL && current->left->status==-1){
            printf("%d %d - current-left\n",current->row,current->column);
            findpath(current->left,ref);
        }
        else if(current->right!=NULL && current->right->status==-1){
            printf("%d %d - current-right\n",current->row,current->column);
            findpath(current->right,ref);
        }
        //this for backtracking
        else{
            pop();
            findpath(ref[top->hor][top->ver],ref);
        }
  }
  else if (current==end) {
      push(current->row,current->column);
      return ;
  }
}
void push(int row, int column){
    struct stack *newstack;
    newstack=create_stack(row,column);
    
    if(top==NULL){
        newstack->link=top;
        top=newstack;
    }
    else{
        newstack->link=top;
        top=newstack;
    }
}


void pop(){
    struct stack *temp;
    temp=top;
    top=top->link;
    free(temp);
}

void display_path(int maze[][size],struct node *ref[][size]){
    //path=9
    while(top!=NULL){
        if(ref[top->hor][top->ver]==start || ref[top->hor][top->ver]==end){
            pop();
        }
        else{
            maze[top->hor][top->ver]=9;
            pop();
        }
    }
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            printf("%d ",maze[i][j]);
        }
        printf("\n");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include "AST.h"
#include <string.h>

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char* car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->car = car;
	t->boo = NULL;
    t->left = left;
    t->right = right;
  } 
  else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char* car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

/* create an AST leaf from a value */
AST newLeafAST(double val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val = val;
	t->car = NULL;
	t->boo = NULL;
    t->left=NULL;
    t->right=NULL;
  } 
  else printf("MALLOC! ");
  return t;
}

AST newLeafBool(char* bool_str)
{
	AST t=(struct _tree*) malloc(sizeof(struct _tree));
	if(t!= NULL){

		// (strcmp(bool_str , "True")==0) = equals
		t->boo = (!strcmp(bool_str , "True")) ? "True": "False";
		t->car = NULL;
		t->left=NULL;
		t->right=NULL;
	}
	else printf("MALLOC! ");
	return t;
}




/* delete an AST */
void freeAST(AST t)
{
	if (t!=NULL) return;
	freeAST(t->left);
	freeAST(t->right);
	free(t);
}

/* infix print an AST*/
void printAST(AST t)
{
	if (t == NULL) return;
	printf("[ ");
	printAST(t->left);
	/* check if node is car|val */
	if (t->left==NULL){
		if(t->boo == NULL)
			printf("%f ",t->val); 
		else
			printf("%s ",t->boo); 
	}
	else printf("%s ",t->car);
	printAST(t->right);
	printf("] ");
  
}


void genAssembly(AST t, char* filename){
	// if filename != NULL, on ouvre et on redirige la sortie de printf
	FILE* Jsm_file = filename ? freopen(filename,"a+", stdout) : NULL;

	// fichier = freopen(file,"a+", stdout);

    if (t->left!=NULL) genAssembly(t->left,filename); 
    if (t->right!=NULL) genAssembly(t->right,filename);
    
   
	if (t->left==NULL){
		if(t->boo == NULL)
			printf("CsteNb %f\n",t->val); 
		else
			printf( "CsteBo %s\n",t->boo); 
	}
    
    else { // Write in
		if(!strcmp(t->car, "+"))
			printf("AddiNb\n");
		if(!strcmp(t->car, "*"))
			printf("MultNb\n");
		if(!strcmp(t->car, "-"))
			if(t->right == NULL) printf("NegaNb\n ");
			else printf("SubiNb\n");
		if(!strcmp(t->car, "/"))
			printf("DiviNb\n");
		// bool
		if(!strcmp(t->car, "=="))
			printf("Equals\n");
		if (!strcmp(t->car, "!")){
    		printf("Not \n");
		}
		if(!strcmp(t->car, "!="))
			printf("NoEql\n");
		if(!strcmp(t->car, ">="))
			printf("GrEqNb\n");
		if(!strcmp(t->car, ">"))
			printf("GrStNb\n");
		if(!strcmp(t->car, "<="))
			printf("LoEqNb\n");
		if(!strcmp(t->car, "<"))
			printf("LoStNb\n");
    }
    fclose(Jsm_file);
}


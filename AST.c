#include <stdio.h>
#include <stdlib.h>
#include "AST.h"
#include <string.h>

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char* car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->car=car;
    t->left=left;
    t->right=right;
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
    t->val=val;
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
		t->boo = (bool_str == "True") ? "True": "False";
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



void codeExtension(AST t, char* file){
	FILE* fichier = NULL;
	fichier = fopen(file,"a+");

    if (t->left!=NULL) codeExtension(t->left,file); 
    if (t->right!=NULL) codeExtension(t->right,file);
    
   
	if (t->left==NULL){
		if(t->boo == NULL)
			fprintf(fichier ,"CsteNb %f\n",t->val); 
		else
			fprintf(fichier, "CsteBo %s\n",t->boo); 
	}
    
    // else if (t->left != NULL && (t->right == NULL)){
    // 	if(strcmp(t->car, "-") == 0)
    // 		fprintf(fichier,"NegaNb \n");
    // 	else if (strcmp(t->car, "!") == 0)
    // 		fprintf(fichier,"Not \n");
    // } 
    else { // Write in
		if(!strcmp(t->car,"+"))
			fprintf(fichier,"AddiNb\n");
		else if(!strcmp(t->car,"*"))
			fprintf(fichier,"MultNb\n");
		else if(!strcmp(t->car,"-"))
			if(t->right == NULL) printf("NegaNb ");
			else printf("SubiNb");
		else if(!strcmp(t->car,"/"))
			fprintf(fichier,"DiviNb\n");
		// bool
		else if(!strcmp(t->car,"=="))
			fprintf(fichier,"Equals\n");
		else if (strcmp(t->car, "!"))
    		fprintf(fichier,"Not \n");
		else if(!strcmp(t->car,"!="))
			fprintf(fichier,"NoEql\n");
		else if(!strcmp(t->car, ">="))
			fprintf(fichier,"GrEqNb\n");
		else if(!strcmp(t->car,">"))
			fprintf(fichier,"GrStNb\n");
		else if(!strcmp(t->car, "<="))
			fprintf(fichier,"LoEqNb\n");
		else if(!strcmp(t->car,"<"))
			fprintf(fichier,"LoStNb\n");
    }
    fclose(fichier);
}



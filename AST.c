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
		t->val = -1;
		t->boo = NULL;
		t->var = NULL;
		t->left = left;
		t->right = right;
	} 
	else printf("MALLOC! ");
	return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char* car, AST son){
	return newBinaryAST(car, son, NULL);
}

/* create an AST leaf from a value */
AST newLeafAST(double val){
  	AST t=(struct _tree*) malloc(sizeof(struct _tree));
	if (t!=NULL){	/* malloc ok */
		t->car = NULL;
		t->val = val;
		t->boo = NULL;
		t->var = NULL;
		t->left = NULL;
		t->right = NULL;
	} 
	else printf("MALLOC! ");
	return t;
}

AST newLeafCar(char* car)
{
	AST t=(struct _tree*) malloc(sizeof(struct _tree));
	if (t!=NULL){	/* malloc ok */
		t->car = strdup(car);
		t->val = -1;
		t->boo = NULL;
		t->var = NULL;
		t->left = NULL;
		t->right = NULL;
	} 
	else printf("MALLOC! ");
	return t;
}


AST newLeafBool(char* bool_str)
{
	AST t=(struct _tree*) malloc(sizeof(struct _tree));
	if(t!= NULL){

		// (strcmp(bool_str , "True")==0) = equals
		t->car = NULL;
		t->val = -1;
		t->boo = (!strcmp(bool_str , "True")) ? "True": "False";
		t->var = NULL;
		t->left = NULL;
		t->right = NULL;
	}
	else printf("MALLOC! ");
	return t;
}

AST newLeafVar(char* variable)
{
	AST t=(struct _tree*) malloc(sizeof(struct _tree));
	if(t!= NULL){
		t->car = NULL;
		t->val = -1;
		t->boo = NULL;
		t->var = strdup(variable);
		t->left = NULL;
		t->right = NULL;
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
	if (t == NULL ) return;

	// on a créé un fils bait pour pouvoir différencier GetVar de SetVar   (...) "=" var -> bait 
	if(t->car != NULL){
		if(!strcmp(t->car, "bait")) return; 
	}
	
	printf("[ ");
	printAST(t->left);
	
	// values, variables
	if (t->left==NULL){
		if(t->val != -1){
			if(t->val == -9) 		printf("NaN ");
			else 					printf("%f ",t->val); 
		}			
		else if(t->boo != NULL)		printf("%s ",t->boo); 
		else if(t->var != NULL)		printf("%s ",t->var); 
	}
	// operators
	else 	printf("%s ",t->car);

	printAST(t->right);
	printf("] ");
  
}


void genAssembly(AST t){
	if (t == NULL) return;
    if (t->left != NULL) genAssembly(t->left); 
	if (t->right!= NULL) genAssembly(t->right);
    
	//prevent getVar on last Variable, put setVar in "="
	if(t->car != NULL){
		if(!strcmp(t->car, "bait")) return; 
	}
    
	// leafs (variables, values)
	if (t->left==NULL){
		if(t->val != -1){
			if(t->val == -9) 		printf("CsteNb NaN\n");
			else 					printf("CsteNb %f\n",t->val); 
		}		
		else if(t->boo != NULL)		printf("CsteBo %s\n",t->boo);
		else if(t->var != NULL)		printf("GetVar %s\n",t->var);
	}

	// operators
    else {
		// arithmetic operator
		if(!strcmp(t->car, "+"))	printf("AddiNb\n");
		if(!strcmp(t->car, "*"))	printf("MultNb\n");
		if(!strcmp(t->car, "-")){
			if(t->right == NULL) 	printf("NegaNb\n");
			else 					printf("SubiNb\n");
		}
		if(!strcmp(t->car, "/"))	printf("DiviNb\n");

		// boolean operator
		if(!strcmp(t->car, "=="))	printf("Equals\n");
		if (!strcmp(t->car, "!"))	printf("Not \n");
		if(!strcmp(t->car, "!="))	printf("NoEql\n");
		if(!strcmp(t->car, ">="))	printf("GrEqNb\n");
		if(!strcmp(t->car, ">"))	printf("GrStNb\n");
		if(!strcmp(t->car, "<="))	printf("LoEqNb\n");
		if(!strcmp(t->car, "<"))	printf("LoStNb\n");

		// variable affect operator
		if(!strcmp(t->car, "="))	printf("SetVar %s\n", t->right->car);
		if(!strcmp(t->car, "++")){	
									printf("CsteNb 1\n");
									printf("AddiNb\n");
		}

		//IfThenElse
		if(!strcmp(t->car, "ConJump"))	printf("ConJump 3\n");
		if(!strcmp(t->car, "jumpElse"))	printf("Jump 3\n");
	}
}

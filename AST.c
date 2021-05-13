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
	else {
		printf("%s ",t->car);
	}
	printAST(t->right);
	printf("] ");
}

int jStacker[10]; 
int jStackCount = 0;
int jCounter = 0;
int conditionSize;

void countJump(AST t)
{
	if (t == NULL ) return;
	if(t->car != NULL){ if(!strcmp(t->car, "bait")) return; }

	countJump(t->left);
	countJump(t->right);
	if(t->left == NULL){
		if(t->car != NULL)
			if(!strcmp(t->car, "jumpCpt"))
				jCounter = 0; // on met a 0 pour compter de nombre de noeud pour la condition
	}

	else{
		// printf("Aff %s", t->car); 

		if(!strcmp(t->car, "ConJump")) {
			conditionSize = jCounter;
			jCounter = 0;
		}
		else if(!strcmp(t->car, "jumpElse")){ // jump val pour if
			jStacker[ jStackCount ] = jCounter;
			printf("\n  if jump : %d", jStacker[ jStackCount ]);  // valeur du jump if ( jumpcond)
			jStackCount++; 	// prochaine case du tableau
			jCounter = 0; 	// reinit compteur
		}
		else if(!strcmp(t->car, "TF")) {
			jStacker[ jStackCount ] = jCounter-1;
			printf("\n  else jump : %d", jStacker[ jStackCount ]); // valeur du jump else
			jStackCount++; 	// prochaine case du tableau
			jCounter = 0;	// reinit compteur
		}
		else if(!strcmp(t->car, "=")) jCounter --; // setvar prend une ligne en moins.
		else if(!strcmp(t->car, "++")) jCounter ++;
		// while
		else if(!strcmp(t->car, "jumpBack")) { // arrives on jumpback so we know the number of nodes between
			jStacker[ jStackCount ] = jCounter; // on va après le jump de retour ( sortie de boucle )
			printf("\n jump back: %d", jStacker[ jStackCount ]); // valeur du jump else
			jStackCount++; 	// prochaine case du tableau
			jStacker[ jStackCount ] = (jCounter+ conditionSize)*-1 ; // back loop ( on doit ajouter la condition)
			jCounter = 0;	// reinit compteur
		}
		else if (!strcmp(t->car, "SplitCpt")) jCounter--;
		
	}
	jCounter++;
}

int * retCountJump(AST t){
	countJump(t);
	jCounter = 0;
	return jStacker;
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

		// get (x=5) (Becareful ! no negation on if strcmp) (diff = | while ;)
		if(strcmp(t->car, "=") && strcmp(t->car, "jumpBack") && strcmp(t->car, "jumpElse") 
			&& strcmp(t->car, ";") && strcmp(t->car, "ConJump")
		){
			if(t->left != NULL){
				if(t->left->car != NULL)
					if(!strcmp(t->left->car, "=")) printf("GetVar %s\n",t->left->right->car);
			}
			if(t->right != NULL){
				if(t->right->car != NULL)
					if(!strcmp(t->right->car, "=")) printf("GetVar %s\n",t->right->right->car);
			}
		}

		// arithmetic operator
		if(!strcmp(t->car, "+"))	printf("AddiNb\n");
		else if(!strcmp(t->car, "*"))	printf("MultNb\n");
		else if(!strcmp(t->car, "-")){
			if(t->right == NULL) 	printf("NegaNb\n");
			else 					printf("SubiNb\n");
		}
		else if(!strcmp(t->car, "/"))	printf("DiviNb\n");

		// boolean operator
		else if(!strcmp(t->car, "=="))	printf("Equals\n");
		else if (!strcmp(t->car, "!"))	printf("Not \n");
		else if(!strcmp(t->car, "!="))	printf("NoEql\n");
		else if(!strcmp(t->car, ">="))	printf("GrEqNb\n");
		else if(!strcmp(t->car, ">"))	printf("GrStNb\n");
		else if(!strcmp(t->car, "<="))	printf("LoEqNb\n");
		else if(!strcmp(t->car, "<"))	printf("LoStNb\n");

		// variable affect operator
		else if(!strcmp(t->car, "="))	printf("SetVar %s\n", t->right->car);
		else if(!strcmp(t->car, "++")){	
									printf("CsteNb 1\n");
									printf("AddiNb\n");
		}

		//IfThenElse
		else if(!strcmp(t->car, "ConJump"))		printf("ConJmp %d\n", jStacker[jCounter++]); // jStaker[0] puis incrémente jCounter
		else if(!strcmp(t->car, "jumpElse"))	printf("Jump %d\n", jStacker[jCounter++]);
		// AND OR
		else if(!strcmp(t->car, "&&"))	printf("AND\n"); 
		else if(!strcmp(t->car, "||"))	printf("OR\n");

		// do while
		else if(!strcmp(t->car, "jumpBack"))	printf("Jump %d\n", jStacker[jCounter++]);


	}
}

/*
*Program Name: cis27Spring2014ChristopherWongLab6Ex1.c
*Discussion: Lab 6 Execise 1
*Written By: Christopher Wong
*/ 

#include <stdio.h>
#include <stdlib.h>

struct Fraction {
  int num;
  int denom;
};

typedef struct Fraction* FracAddr;

struct ExpressionTerm {
  struct Fraction* FracAddr;
  char op;
};

typedef struct ExpressionTerm ExprTerm;
typedef ExprTerm* ExprTermAddr;
typedef ExprTerm* ExprTermPtr;

struct ExpressionListNode {
  ExprTermAddr termAddr;
  struct ExpressionListNode* next;
};

typedef struct ExpressionListNode ExprNode;
typedef struct ExpressionListNode* ExprNodeAddr;
typedef struct ExpressionListNode* ExprList;
typedef ExprList* ExprListAddr;

struct ExpressionNodeStack {
  int size;
  ExprNodeAddr top;
  ExprList* exprListAddr;
};

typedef struct ExpressionNodeStack ExprNodeStack;

void classinfo(void);
void menu (void);
FracAddr createFraction(void);
ExprTermAddr createExprTerm(FracAddr, char);
ExprNodeAddr createExprNode(ExprTermAddr);
int insertExprNode(ExprListAddr, ExprNodeAddr);
void displayInfix(ExprList);
void displayPostfix(ExprList);
ExprNodeAddr popEN(ExprNodeStack*);
int pushEN(ExprNodeStack*, ExprNodeAddr);
ExprListAddr converToPostFix(ExprList*, ExprList*);
void removeLast(ExprListAddr listAddr);
ExprList createInfix(void);
ExprList freeMemory(ExprList);
void evaluateExpr(ExprList);
struct Fraction* gcdBF(struct Fraction*);

int main() {
  classinfo();
  menu();

  return 0;
}
void classinfo() {
  printf("CIS 27 - C Programming"
    "\nLaney College"
    "\nChristopher Wong"
    "\n\nAssignment Information --"
    "\n  Assignment Number: Lab 06,"
    "\n                     Coding Assignment -- Exercise #1"
    "\n  Written by:        Christopher Wong"
    "\n  Submitted Date:    4/29/2014\n");
  return;
}
void menu() {
  ExprList exprList1 = 0;
  ExprListAddr postFixExprAddr = 0;
  int postFixList;
  int option;

  postFixList = 0;
  do {
    printf("\n**************************************"
      "\n*          EXPRESSIONS               *"
      "\n* 1. Creating/Updating infix         *"
      "\n* 2. Converting to postfix           *"
      "\n* 3. Displaying infix                *"
      "\n* 4. Displaying postfix              *"
      "\n* 5. Evaluating expression           *"
      "\n* 6. Quit                            *"
      "\n**************************************");
    printf("\nSelect the option (1 throuh 6): ");
    scanf("%d", &option);
    switch (option) {
    case 1:
      if (exprList1) {
        exprList1 = freeMemory(exprList1);
        postFixList = 0;
      }
      exprList1 = createInfix(); 
      break;
    case 2:
      if (exprList1) {
        postFixExprAddr = converToPostFix(&exprList1, postFixExprAddr);
        postFixList = 1;
      }
      else {
        printf("\n  Create infix first\n\n");
      }
      break;
    case 3:
      displayInfix(exprList1);
      break;
    case 4:
      if (postFixList == 1) {
        displayPostfix(*postFixExprAddr);
      }
      else {
        printf("\n  No postfix to print\n\n");
      }
      break;
    case 5:
      if (postFixList == 1) {
        evaluateExpr(*postFixExprAddr);
      }
      else {
        printf("\n  You must convert to postfix before you can evaluate\n\n");
      }
      break;
    case 6:
      printf("\n  Have Fun!\n\n");
      break;
    default:
      printf("\n  You should not be in this class!\n\n");
    }
  } while (option != 6);

  return;
}
FracAddr createFraction() {
  FracAddr frPtr = 0;
  int num;
  int denom;

  do {
    printf("  Enter the numerator: ");
    scanf("\t%d", &num);
    printf("  Enter the denominator: ");
    scanf("\t%d", &denom);
    if (denom == 0)
      printf("  Enter a denominator that is not 0");
    if (denom < 0) {
      num = -num;
      denom = -denom;
    }
  } while (denom == 0);
  frPtr = (struct Fraction*) malloc(sizeof(struct Fraction));
  frPtr->num = num;
  frPtr->denom = denom;

  return frPtr;
}
ExprTermAddr createExprTerm(FracAddr fracAddr, char op) {
  ExprTermAddr exprNodeAddr = 0;

  exprNodeAddr = (ExprTermAddr) malloc(sizeof(ExprTerm));
  exprNodeAddr->FracAddr = fracAddr;
  exprNodeAddr->op = op;

  return exprNodeAddr;
}
ExprNodeAddr createExprNode(ExprTermAddr exprTermAddr) {
  ExprNodeAddr exprNodeAddr = 0;

  exprNodeAddr = (ExprNodeAddr) malloc(sizeof(ExprNode));
  exprNodeAddr->termAddr = exprTermAddr;
  exprNodeAddr->next = 0;

  return exprNodeAddr;
}
int insertExprNode(ExprListAddr exprListAddr, ExprNodeAddr exprNodeAddr) {
  ExprList tmpPtr = 0;

  if (*exprListAddr == 0) {
    *exprListAddr = exprNodeAddr;
  }
  else {
    tmpPtr = *exprListAddr;

    while (tmpPtr->next != 0) {
      tmpPtr = tmpPtr->next;
    }
    tmpPtr->next = exprNodeAddr;
  }
  return 0;
}
void displayInfix(ExprList exprList) {
  ExprNodeAddr tmpNodeAddr = 0;

  tmpNodeAddr = exprList;
  if (tmpNodeAddr) {
    printf("\nInfix: ");
    while (tmpNodeAddr) {
      if (tmpNodeAddr->termAddr->FracAddr == 0) {
        printf("%c ", tmpNodeAddr->termAddr->op);
      }
      else {
        printf("%d/%d ", tmpNodeAddr->termAddr->FracAddr->num,
          tmpNodeAddr->termAddr->FracAddr->denom);
      }
      tmpNodeAddr = tmpNodeAddr->next;
    }
    printf("\n");
  } 
  else {
    printf("\n  No infix to print\n\n");
  }

  return;
}
void displayPostfix(ExprList exprList) {
  ExprNodeAddr tmpNodeAddr = 0;

  tmpNodeAddr = exprList;
  printf("\nPostfix: ");
  while (tmpNodeAddr) {
    if (tmpNodeAddr->termAddr->FracAddr == 0) {
      printf("%c ", tmpNodeAddr->termAddr->op);
    }
    else {
      printf("%d/%d ", tmpNodeAddr->termAddr->FracAddr->num,
        tmpNodeAddr->termAddr->FracAddr->denom);
    }
    tmpNodeAddr = tmpNodeAddr->next;
  }
  printf("\n");

  return;
}
ExprNodeAddr popEN(ExprNodeStack* exprNodeStackAddr) {
  ExprNodeAddr tmpPtr = 0;

  if (exprNodeStackAddr->exprListAddr == 0) {
    printf("\n\tThere are no nodes to remove\n");
  }
  else {
    tmpPtr = *(exprNodeStackAddr->exprListAddr);
    exprNodeStackAddr->exprListAddr = &tmpPtr->next;
  }
  exprNodeStackAddr->size--;
  exprNodeStackAddr->top = *(exprNodeStackAddr->exprListAddr);

  return tmpPtr;
}
int pushEN(ExprNodeStack* exprNodeStackAddr, ExprNodeAddr exprNodeAddr) {
  ExprListAddr exprListAddr = 0;
  exprListAddr = exprNodeStackAddr->exprListAddr;

  if (*exprListAddr) {
    exprNodeAddr->next = *exprListAddr;
  }
  *exprListAddr = exprNodeAddr;
  exprNodeStackAddr->size++;
  exprNodeStackAddr->top = exprNodeAddr;
  return 0;
}
ExprList* converToPostFix(ExprList* inFixExpr, ExprList* postFixExpr) {
  ExprNodeStack* exprNodeStackAddr = 0;
  ExprTermAddr exprTermAddr = 0;
  ExprNodeAddr exprNodeAddr = 0;
  FracAddr fractionAddr = 0;
  ExprNodeAddr tmpNodeAddr = 0;
  char op;

  printf("\n Converting to postfix\n\n");
  tmpNodeAddr = *inFixExpr;
  exprNodeStackAddr = (ExprNodeStack*) malloc(sizeof(ExprNodeStack));
  exprNodeStackAddr->exprListAddr = (ExprListAddr) malloc(sizeof(ExprList));
  *(exprNodeStackAddr->exprListAddr) = 0;
  exprNodeStackAddr->size = 0;
  exprNodeStackAddr->top = 0;
  exprTermAddr = createExprTerm(0, '(');
  exprNodeAddr = createExprNode(exprTermAddr);
  pushEN(exprNodeStackAddr, exprNodeAddr);
  exprTermAddr = createExprTerm(0, ')');
  exprNodeAddr = createExprNode(exprTermAddr);
  insertExprNode(&tmpNodeAddr, exprNodeAddr);
  postFixExpr = (ExprListAddr) malloc(sizeof(ExprList));
  (*postFixExpr) = 0;
  while (exprNodeStackAddr->size != 0) {
    if (tmpNodeAddr->termAddr->op == '0') {
      fractionAddr = tmpNodeAddr->termAddr->FracAddr;
      exprTermAddr = createExprTerm(fractionAddr, 0);
      exprNodeAddr = createExprNode(exprTermAddr);
      insertExprNode(postFixExpr, exprNodeAddr);
    }
    else if (tmpNodeAddr->termAddr->op == '(') {
      exprTermAddr = createExprTerm(0, '(');
      exprNodeAddr = createExprNode(exprTermAddr);
      pushEN(exprNodeStackAddr, exprNodeAddr);
    }
    else if (tmpNodeAddr->termAddr->op == '+' ||
      tmpNodeAddr->termAddr->op == '-') {
        while (exprNodeStackAddr->top->termAddr->op == '*' || 
          exprNodeStackAddr->top->termAddr->op == '/' || 
          exprNodeStackAddr->top->termAddr->op == '+' ||
          exprNodeStackAddr->top->termAddr->op == '-') {
            exprNodeAddr = popEN(exprNodeStackAddr);
            op = exprNodeAddr->termAddr->op;
            exprTermAddr = createExprTerm(0, op);
            exprNodeAddr = createExprNode(exprTermAddr);
            insertExprNode(postFixExpr, exprNodeAddr);
        }
        op = tmpNodeAddr->termAddr->op;
        exprTermAddr = createExprTerm(0, op);
        exprNodeAddr = createExprNode(exprTermAddr);
        pushEN(exprNodeStackAddr, exprNodeAddr);
    }
    else if (tmpNodeAddr->termAddr->op == '*' ||
      tmpNodeAddr->termAddr->op == '/') {
        while (exprNodeStackAddr->top->termAddr->op == '*' || 
          exprNodeStackAddr->top->termAddr->op == '/' ) {
            exprNodeAddr = popEN(exprNodeStackAddr);
            op = exprNodeAddr->termAddr->op;
            exprTermAddr = createExprTerm(0, op);
            exprNodeAddr = createExprNode(exprTermAddr);
            insertExprNode(postFixExpr, exprNodeAddr);
        }
        op = tmpNodeAddr->termAddr->op;
        exprTermAddr = createExprTerm(0, op);
        exprNodeAddr = createExprNode(exprTermAddr);
        pushEN(exprNodeStackAddr, exprNodeAddr);
    }
    else if (tmpNodeAddr->termAddr->op == ')') {
      while (exprNodeStackAddr->top->termAddr->op != '(') {
        exprNodeAddr = popEN(exprNodeStackAddr);
        op = exprNodeAddr->termAddr->op;
        exprTermAddr = createExprTerm(0, op);
        exprNodeAddr = createExprNode(exprTermAddr);
        insertExprNode(postFixExpr, exprNodeAddr);
      }
      popEN(exprNodeStackAddr);
    }
    tmpNodeAddr = tmpNodeAddr->next;
  }
  removeLast(inFixExpr);

  return postFixExpr;
}
void removeLast(ExprListAddr listAddr) {
  ExprNodeAddr tmpPtr = 0;
  ExprNodeAddr tmpPtr2 = 0;

  if (*listAddr == 0) {
    printf("\n\tThere are no nodes to remove\n");
  }
  else {
    tmpPtr = *listAddr;
    while (tmpPtr->next != 0) {
      tmpPtr2 = tmpPtr;
      tmpPtr = tmpPtr->next;
    }
    free(tmpPtr);
    tmpPtr2->next = 0; 
  }

  return;
}
ExprList createInfix() {
  ExprTermAddr exprTermAddr1 = 0;
  ExprNodeAddr exprNodeAddr1 = 0 ;
  ExprList exprList1 = 0;
  FracAddr fracAddr1 = 0;
  ExprList postFixExpr = 0;
  ExprListAddr postFixExprAddr = 0;
  char op;
  char option2;

  fracAddr1 = createFraction();
  exprTermAddr1 = createExprTerm(fracAddr1, '0');
  exprNodeAddr1 = createExprNode(exprTermAddr1);
  insertExprNode(&exprList1, exprNodeAddr1);
  do {
    do {
      printf("\n  If you want to enter another operator enter P\n"
        "  If you want to enter another fraction enter F\n"
        "  If you would like to end the postfix expression enter N: ");   
      scanf(" %c", &option2);
    } while (! (option2 == 'P' || option2 ==  'p' || option2 ==  'N' ||
      option2 == 'n'|| option2 ==  'F' || option2 == 'f'));
    if (option2 == 'P' || option2 == 'p') {
      do {
        printf("\nEnter an operator(+, -, *, /, ( or ) ): ");
        scanf(" %c", &op);
        if (! (op == '+' || op ==  '-' || op ==  '*' || op == '/'||
          op ==  '(' || op == ')')) {
            printf("\nEnter a valid operator\n");
        }
      }while (! (op == '+' || op ==  '-' || op ==  '*' || op == '/' ||
        op ==  '(' || op == ')'));
      exprTermAddr1 = createExprTerm(0, op);
      exprNodeAddr1 = createExprNode(exprTermAddr1);
      insertExprNode(&exprList1, exprNodeAddr1);
    }
    else if  (option2 == 'F' || option2 == 'f') {
      fracAddr1 = createFraction();
      exprTermAddr1 = createExprTerm(fracAddr1, '0');
      exprNodeAddr1 = createExprNode(exprTermAddr1);
      insertExprNode(&exprList1, exprNodeAddr1);
    }
  } while (option2 == 'P' || option2 == 'p' || option2 == 'F' ||
    option2 == 'f'); 

  return exprList1;
}
ExprList freeMemory(ExprList myList) {
  ExprNodeAddr node = 0;
  ExprNodeAddr temp = 0;

  node = myList;
  while (node) {
    temp = node;
    node = node->next;
    free(temp);
  }
  myList = 0;

  return myList;
}
void evaluateExpr(ExprList exprList) {
  ExprNodeStack* exprNodeStackAddr = 0;
  ExprNodeAddr tmpNodeAddr = 0;
  ExprTermAddr exprTermAddr = 0;
  ExprNodeAddr exprNodeAddr = 0;
  FracAddr fractionAddr1 = 0;
  FracAddr fractionAddr2 = 0;
  FracAddr fractionAddr3 = 0;

  tmpNodeAddr = exprList;
  exprNodeStackAddr = (ExprNodeStack*) malloc(sizeof(ExprNodeStack));
  exprNodeStackAddr->exprListAddr = (ExprListAddr) malloc(sizeof(ExprList));
  *(exprNodeStackAddr->exprListAddr) = 0;
  exprNodeStackAddr->size = 0;
  exprNodeStackAddr->top = 0;
  fractionAddr3 = (FracAddr) malloc(sizeof(struct Fraction));
  do {
    if (tmpNodeAddr->termAddr->op == 0) {
      fractionAddr1 = tmpNodeAddr->termAddr->FracAddr;
      exprTermAddr = createExprTerm(fractionAddr1, 0);
      exprNodeAddr = createExprNode(exprTermAddr);
      pushEN(exprNodeStackAddr, exprNodeAddr);
    }
    else if (tmpNodeAddr->termAddr->op == '+') {
      exprNodeAddr = popEN(exprNodeStackAddr);
      fractionAddr1 = exprNodeAddr->termAddr->FracAddr;
      exprNodeAddr = popEN(exprNodeStackAddr);
      fractionAddr2 = exprNodeAddr->termAddr->FracAddr;
      fractionAddr3->num = ((fractionAddr1->num * fractionAddr2->denom) + 
        (fractionAddr2->num * fractionAddr1->denom));
      fractionAddr3->denom = fractionAddr1->denom * fractionAddr2->denom;
      exprTermAddr = createExprTerm(fractionAddr3, 0);
      exprNodeAddr = createExprNode(exprTermAddr);
      pushEN(exprNodeStackAddr, exprNodeAddr);
    }
    else if (tmpNodeAddr->termAddr->op == '-') {
      exprNodeAddr = popEN(exprNodeStackAddr);
      fractionAddr1 = exprNodeAddr->termAddr->FracAddr;
      exprNodeAddr = popEN(exprNodeStackAddr);
      fractionAddr2 = exprNodeAddr->termAddr->FracAddr;
      fractionAddr3->num = ((fractionAddr2->num * fractionAddr1->denom) - 
        (fractionAddr1->num * fractionAddr2->denom));
      fractionAddr3->denom = fractionAddr1->denom * fractionAddr2->denom;
      exprTermAddr = createExprTerm(fractionAddr3, 0);
      exprNodeAddr = createExprNode(exprTermAddr);
      pushEN(exprNodeStackAddr, exprNodeAddr);
    }
    else if (tmpNodeAddr->termAddr->op == '*') {
      exprNodeAddr = popEN(exprNodeStackAddr);
      fractionAddr1 = exprNodeAddr->termAddr->FracAddr;
      exprNodeAddr = popEN(exprNodeStackAddr);
      fractionAddr2 = exprNodeAddr->termAddr->FracAddr;
      fractionAddr3->num = fractionAddr1->num * fractionAddr2->num;
      fractionAddr3->denom = fractionAddr1->denom * fractionAddr2->denom;
      exprTermAddr = createExprTerm(fractionAddr3, 0);
      exprNodeAddr = createExprNode(exprTermAddr);
      pushEN(exprNodeStackAddr, exprNodeAddr);
    }
    else if (tmpNodeAddr->termAddr->op == '/') {
      exprNodeAddr = popEN(exprNodeStackAddr);
      fractionAddr1 = exprNodeAddr->termAddr->FracAddr;
      exprNodeAddr = popEN(exprNodeStackAddr);
      fractionAddr2 = exprNodeAddr->termAddr->FracAddr;
      fractionAddr3->num = fractionAddr1->num * fractionAddr2->denom;
      fractionAddr3->denom = fractionAddr1->denom * fractionAddr2->num;
      exprTermAddr = createExprTerm(fractionAddr3, 0);
      exprNodeAddr = createExprNode(exprTermAddr);
      pushEN(exprNodeStackAddr, exprNodeAddr);
    }
    tmpNodeAddr = tmpNodeAddr->next;
  } while (tmpNodeAddr);
  exprNodeAddr = popEN(exprNodeStackAddr);
  fractionAddr3 = exprNodeAddr->termAddr->FracAddr;
  fractionAddr3 = gcdBF(fractionAddr3);
  displayPostfix(exprList);
  printf("= %d/%d\n", fractionAddr3->num, fractionAddr3->denom);

  return;
}
FracAddr gcdBF(FracAddr answer) { 
  int gcd = 1;
  int tempN = answer->num;
  int tempD = answer->denom;
  int i = 0;

  if (tempN < 0)
    tempN = -tempN;
  if (tempD < 0)
    tempD = -tempD;
  for (i = 2; i <= tempN && i <= tempD; i++) 
    if (answer->num % i == 0 && answer->denom % i == 0)
      gcd = i;
  answer->num = answer->num / gcd;
  answer->denom = answer->denom / gcd;

  return answer; 
}
/* OUTPUT
CIS 27 - C Programming
Laney College
Christopher Wong

Assignment Information --
  Assignment Number: Lab 06,
                     Coding Assignment -- Exercise #1
  Written by:        Christopher Wong
  Submitted Date:    4/29/2014

**************************************
*          EXPRESSIONS               *
* 1. Creating/Updating infix         *
* 2. Converting to postfix           *
* 3. Displaying infix                *
* 4. Displaying postfix              *
* 5. Evaluating expression           *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 7

  You should not be in this class!


**************************************
*          EXPRESSIONS               *
* 1. Creating/Updating infix         *
* 2. Converting to postfix           *
* 3. Displaying infix                *
* 4. Displaying postfix              *
* 5. Evaluating expression           *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 5
  Enter the denominator: 1

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: p

Enter an operator(+, -, *, /, ( or ) ): +

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: p

Enter an operator(+, -, *, /, ( or ) ): (

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: p

Enter an operator(+, -, *, /, ( or ) ): (

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: f
  Enter the numerator: 1
  Enter the denominator: 1

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: p

Enter an operator(+, -, *, /, ( or ) ): +

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: f
  Enter the numerator: 2
  Enter the denominator: 1

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: p

Enter an operator(+, -, *, /, ( or ) ): )

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: p

Enter an operator(+, -, *, /, ( or ) ): *

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: f
  Enter the numerator: 4
  Enter the denominator: 1

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: p

Enter an operator(+, -, *, /, ( or ) ): )

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: p

Enter an operator(+, -, *, /, ( or ) ): -

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: f
  Enter the numerator: 3
  Enter the denominator: 1

  If you want to enter another operator enter P
  If you want to enter another fraction enter F
  If you would like to end the postfix expression enter N: n

**************************************
*          EXPRESSIONS               *
* 1. Creating/Updating infix         *
* 2. Converting to postfix           *
* 3. Displaying infix                *
* 4. Displaying postfix              *
* 5. Evaluating expression           *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 2

 Converting to postfix


**************************************
*          EXPRESSIONS               *
* 1. Creating/Updating infix         *
* 2. Converting to postfix           *
* 3. Displaying infix                *
* 4. Displaying postfix              *
* 5. Evaluating expression           *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 3

Infix: 5/1 + ( ( 1/1 + 2/1 ) * 4/1 ) - 3/1

**************************************
*          EXPRESSIONS               *
* 1. Creating/Updating infix         *
* 2. Converting to postfix           *
* 3. Displaying infix                *
* 4. Displaying postfix              *
* 5. Evaluating expression           *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 4

Postfix: 5/1 1/1 2/1 + 4/1 * + 3/1 -

**************************************
*          EXPRESSIONS               *
* 1. Creating/Updating infix         *
* 2. Converting to postfix           *
* 3. Displaying infix                *
* 4. Displaying postfix              *
* 5. Evaluating expression           *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 5

Postfix: 5/1 1/1 2/1 + 4/1 * + 3/1 -
= 14/1

**************************************
*          EXPRESSIONS               *
* 1. Creating/Updating infix         *
* 2. Converting to postfix           *
* 3. Displaying infix                *
* 4. Displaying postfix              *
* 5. Evaluating expression           *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 6

  Have Fun!

*/
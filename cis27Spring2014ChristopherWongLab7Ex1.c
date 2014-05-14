/*
*Program Name: cis27Spring2014ChristopherWongLab7Ex1.c
*Discussion: Lab 7 Execise 1
*Written By: Christopher Wong
*/ 

#include <stdio.h>
#include <stdlib.h>

struct Fraction {
  int num;
  int denom;
};
struct BSTNode {
  struct Fraction* FracAddr;
  struct BSTNode* left;
  struct BSTNode* right;
};

typedef struct Fraction* FracAddr;
typedef struct BSTNode BSTNode;
typedef struct BSTNode* BSTNodeAddr;
typedef BSTNodeAddr* BSTAddr;

void classinfo(void);
void menu(void);
void displaymenu(BSTNodeAddr);
int insertFractionBSTYourName(BSTAddr, BSTNodeAddr); 
void displayFractionPreorderBSTYourName(BSTNodeAddr); 
void displayFractionPostorderBSTYourName(BSTNodeAddr);
void displayFractionInorderBSTYourName(BSTNodeAddr); 
FracAddr createFraction(void);
BSTNodeAddr createBSTNode(void);
BSTNodeAddr searchFractionBSTYourName(BSTNodeAddr);
BSTNodeAddr getSmallestFractionBSTYourName(BSTNodeAddr);
int removeFractionBSTYourname(BSTAddr);
int main () {

  classinfo();
  menu();

  return 0;
}
void classinfo() {
  printf("CIS 27 - C Programming"
    "\nLaney College"
    "\nChristopher Wong"
    "\n\nAssignment Information --"
    "\n  Assignment Number: Lab 07"
    "\n                     Coding Assignment -- Exercise #1"
    "\n  Written by:        Christopher Wong"
    "\n  Submitted Date:    5/13/2014\n");
  return;
}
void menu() {
  int option;
  BSTAddr bstAddr = 0;
  BSTNodeAddr bstNodeAddr;

  bstAddr = (BSTAddr) malloc(sizeof(BSTAddr));
  (*bstAddr) = 0;
  do {
    printf("\n**************************************"
      "\n*            BST                     *"
      "\n* 1. Insert Fraction                 *"
      "\n* 2. Display                         *"
      "\n* 3. Search for Fraction             *"
      "\n* 4. Remove a Node                   *"
      "\n* 5. Get and Display Smallest Node   *"
      "\n* 6. Quit                            *"
      "\n**************************************");
    printf("\nSelect the option (1 throuh 6): ");
    scanf("%d", &option);
    switch(option) {
    case 1:
      bstNodeAddr = createBSTNode();
      insertFractionBSTYourName(bstAddr, bstNodeAddr);
      break;
    case 2:
      if (*bstAddr == 0) {
        printf("\nThere are no fractions to display\n");
      }
      else {
        displaymenu(*bstAddr);
      }
      break;
    case 3:
      if (*bstAddr == 0) {
        printf("\nThere are no fractions to search for\n");
      }
      else {
        searchFractionBSTYourName(*bstAddr);
      }
      break;
    case 4:
      if (*bstAddr == 0) {
        printf("\nThere are no fractions to remove\n");
      }
      else {
        removeFractionBSTYourname(bstAddr);
      }
      break;
    case 5:
      if (*bstAddr == 0) {
        printf("\nThere are no fractions to get\n");
      }
      else {
        getSmallestFractionBSTYourName(*bstAddr);
      }
      break;
    case 6:
      printf("\n  Have Fun!\n\n");
      free(bstAddr);
      break;
    default:
      printf("\n  You should not be in this class!\n\n");
    }
  } while (option != 6);

  return;
}
BSTNodeAddr createBSTNode() {
  BSTNodeAddr bstNodeAddr = 0;
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
  bstNodeAddr = (BSTNodeAddr) malloc(sizeof(BSTNode));
  bstNodeAddr->FracAddr = frPtr;
  bstNodeAddr->left = 0;
  bstNodeAddr->right = 0;

  return bstNodeAddr;
}
int insertFractionBSTYourName(BSTAddr bstAddr, BSTNodeAddr bstNodeAddr) {
  BSTNodeAddr tmpNodeAddr = 0;
  BSTNodeAddr tmpNodeAddr2 = 0;
  if (*bstAddr) {
    tmpNodeAddr = *bstAddr;
    while (tmpNodeAddr) {
      if (tmpNodeAddr->FracAddr->num * bstNodeAddr->FracAddr->denom > bstNodeAddr->FracAddr->num * tmpNodeAddr->FracAddr->denom) {
        tmpNodeAddr2 = tmpNodeAddr;
        tmpNodeAddr = tmpNodeAddr->left;
      }
      else if (tmpNodeAddr->FracAddr->num * bstNodeAddr->FracAddr->denom < bstNodeAddr->FracAddr->num * tmpNodeAddr->FracAddr->denom) {
        tmpNodeAddr2 =tmpNodeAddr;
        tmpNodeAddr = tmpNodeAddr->right;
      }
      else {
        printf("\nDuplicate found\n");
        return 0;
      }
    }
    if (tmpNodeAddr2->FracAddr->num * bstNodeAddr->FracAddr->denom > bstNodeAddr->FracAddr->num * tmpNodeAddr2->FracAddr->denom) {
      tmpNodeAddr2->left = bstNodeAddr; 
    }
    else if (tmpNodeAddr2->FracAddr->num * bstNodeAddr->FracAddr->denom < bstNodeAddr->FracAddr->num * tmpNodeAddr2->FracAddr->denom) {
      tmpNodeAddr2->right = bstNodeAddr;  
    }
  }
  else {
    *bstAddr = bstNodeAddr;
  }
  return 1;
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
void displayFractionInorderBSTYourName(BSTNodeAddr bstNodeAddr) {
  if (bstNodeAddr) {
    displayFractionInorderBSTYourName(bstNodeAddr->left);
    printf("%d/%d\n", bstNodeAddr->FracAddr->num, bstNodeAddr->FracAddr->denom);
    displayFractionInorderBSTYourName(bstNodeAddr->right);
  }
  return;
}
void displayFractionPreorderBSTYourName(BSTNodeAddr bstNodeAddr) {
  if (bstNodeAddr) {
    printf("%d/%d\n", bstNodeAddr->FracAddr->num, bstNodeAddr->FracAddr->denom);
    displayFractionPreorderBSTYourName(bstNodeAddr->left);
    displayFractionPreorderBSTYourName(bstNodeAddr->right);
  }
  return;
}
void displayFractionPostorderBSTYourName(BSTNodeAddr bstNodeAddr) {
  if (bstNodeAddr) {
    displayFractionPostorderBSTYourName(bstNodeAddr->left);
    displayFractionPostorderBSTYourName(bstNodeAddr->right);
    printf("%d/%d\n", bstNodeAddr->FracAddr->num, bstNodeAddr->FracAddr->denom);
  }
  return;
}
void displaymenu(BSTNodeAddr bstNodeaddr) {
  int option;
  do {
    printf("\n**************************************"
      "\n*            BST                     *"
      "\n* 1. Display In Order                *"
      "\n* 2. Display Pre Order               *"
      "\n* 3. Display Post Order              *"
      "\n* 4. Return to main menu             *"
      "\n**************************************");
    printf("\nSelect the option (1 throuh 6): ");
    scanf("%d", &option);
    switch(option) {
    case 1:
      displayFractionInorderBSTYourName(bstNodeaddr);
      break;
    case 2:
      displayFractionPreorderBSTYourName(bstNodeaddr);
      break;
    case 3:
      displayFractionPostorderBSTYourName(bstNodeaddr);
      break;
    case 4:
      printf("\n  Returning to main menu\n\n");
      break;
    default:
      printf("\n  You should not be in this class!\n\n");
    }
  } while (option != 4);
  return;

}
BSTNodeAddr searchFractionBSTYourName(BSTNodeAddr bstNodeAddr) {
  BSTNodeAddr bstNodeAddr1 = 0;
  FracAddr fracAddr = 0;

  printf("\nEnter Fraction you would like to search for\n");
  fracAddr = createFraction();
  bstNodeAddr1 = bstNodeAddr;
  while (bstNodeAddr1) {
    if (bstNodeAddr1->FracAddr->num * fracAddr->denom > fracAddr->num * bstNodeAddr1->FracAddr->denom) {
      bstNodeAddr1 = bstNodeAddr1->left;
    }
    else if (bstNodeAddr1->FracAddr->num * fracAddr->denom < fracAddr->num * bstNodeAddr1->FracAddr->denom) {
      bstNodeAddr1 = bstNodeAddr1->right;
    }
    else if (bstNodeAddr1->FracAddr->num * fracAddr->denom == fracAddr->num * bstNodeAddr1->FracAddr->denom) {
      printf("\nFraction Node found\n");
      return bstNodeAddr1;
    }
  }
  printf("\nFraction is not in tree\n");

  return 0;
}
BSTNodeAddr getSmallestFractionBSTYourName(BSTNodeAddr bstNodeAddr) {
  BSTNodeAddr tmpBSTNodeAddr = 0;
  BSTNodeAddr tmpBSTNodeAddr2 = 0;

  tmpBSTNodeAddr = bstNodeAddr;
  while (tmpBSTNodeAddr) {
    tmpBSTNodeAddr2 = tmpBSTNodeAddr;
    tmpBSTNodeAddr= tmpBSTNodeAddr->left;
  }
  printf("\nThe Smallest Fraction is: %d/%d\n", tmpBSTNodeAddr2->FracAddr->num, tmpBSTNodeAddr2->FracAddr->denom);

  return tmpBSTNodeAddr2;
}
int removeFractionBSTYourname(BSTAddr bstAddr) {
  BSTNodeAddr bstNodeAddr1 = 0;
  BSTNodeAddr bstNodeAddr2 = 0;
  BSTNodeAddr bstNodeAddr3 = 0;
  BSTNodeAddr bstNodeAddr4 = 0;
  int direction = 10;

  FracAddr fracAddr = 0;
  printf("\nEnter Fraction you would like to remove\n");
  fracAddr = createFraction();
  bstNodeAddr1 = *bstAddr;
  while (bstNodeAddr1) {
    if (bstNodeAddr1->FracAddr->num * fracAddr->denom > fracAddr->num * bstNodeAddr1->FracAddr->denom) {
      bstNodeAddr2 = bstNodeAddr1;
      bstNodeAddr1 = bstNodeAddr1->left;
      direction = 0;
    }
    else if (bstNodeAddr1->FracAddr->num * fracAddr->denom < fracAddr->num * bstNodeAddr1->FracAddr->denom) {
      bstNodeAddr2 = bstNodeAddr1;
      bstNodeAddr1 = bstNodeAddr1->right;
      direction = 1;
    }
    else if (bstNodeAddr1->FracAddr->num * fracAddr->denom == fracAddr->num * bstNodeAddr1->FracAddr->denom) {
      if (bstNodeAddr1->left == 0 && bstNodeAddr1->right == 0) {
        if (direction == 10) {
          *bstAddr = 0;
        }
        else if (direction == 1) {
          bstNodeAddr2->right = 0;
          free(bstNodeAddr1);
          bstNodeAddr1 = 0;
        }
        else {
          bstNodeAddr2->left = 0;
          free(bstNodeAddr1);
          bstNodeAddr1 = 0;
        }
        return 1;
      }
      else if (bstNodeAddr1->left == 0 && bstNodeAddr1->right != 0 || bstNodeAddr1->left != 0 && bstNodeAddr1->right ==0) {
        if (bstNodeAddr1->left) {
          if (direction == 1) {
            bstNodeAddr2->right = bstNodeAddr1->left;
            free(bstNodeAddr1);
            bstNodeAddr1 = 0;
          }
          else if (direction = 10) {
            bstNodeAddr2 = bstNodeAddr1->left;
            (*bstAddr)->FracAddr->num = bstNodeAddr2->FracAddr->num;
            (*bstAddr)->FracAddr->denom = bstNodeAddr2->FracAddr->denom;
            (*bstAddr)->left = 0;
          }
          else {
            bstNodeAddr2->left = bstNodeAddr1->left;
            free(bstNodeAddr1);
            bstNodeAddr1 = 0;
          }
        }
        else if (bstNodeAddr1->right) {
          if (direction == 1) {
            bstNodeAddr2->right = bstNodeAddr1->right;
            free(bstNodeAddr1);
            bstNodeAddr1 = 0;
          }
          else if (direction = 10) {
            bstNodeAddr2 = bstNodeAddr1->right;
            (*bstAddr)->FracAddr->num = bstNodeAddr2->FracAddr->num;
            (*bstAddr)->FracAddr->denom = bstNodeAddr2->FracAddr->denom;
            (*bstAddr)->right = 0;
          }
          else {
            bstNodeAddr2->left = bstNodeAddr1->right;
            free(bstNodeAddr1);
            bstNodeAddr1 = 0;
          }
        }
        return 1;
      }
      else if (bstNodeAddr1->left != 0 && bstNodeAddr1->right !=0) {
        bstNodeAddr2 = bstNodeAddr1;
        bstNodeAddr3 = bstNodeAddr1->right;
        if (bstNodeAddr3->left == 0) {
          (*bstAddr)->FracAddr->num = bstNodeAddr3->FracAddr->num;
          (*bstAddr)->FracAddr->denom = bstNodeAddr3->FracAddr->denom;
          (*bstAddr)->right = 0;
          return 1;
        }
        else {
          while (bstNodeAddr3) {
            bstNodeAddr4 = bstNodeAddr2;
            bstNodeAddr2 = bstNodeAddr3;
            bstNodeAddr3 = bstNodeAddr3->left;
          }
          bstNodeAddr1->FracAddr->num = bstNodeAddr2->FracAddr->num;
          bstNodeAddr1->FracAddr->denom = bstNodeAddr2->FracAddr->denom;
          bstNodeAddr4->left = 0;
          return 1;
        }
      }

    }
  }
  printf("\nFraction is not in tree\n");
  return 0;
}
/*OUTPUT
CIS 27 - C Programming
Laney College
Christopher Wong

Assignment Information --
  Assignment Number: Lab 07
                     Coding Assignment -- Exercise #1
  Written by:        Christopher Wong
  Submitted Date:    5/13/2014

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 50
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 25
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 75
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 10
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 45
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 65
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 90
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 35
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 55
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 80
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 1
  Enter the numerator: 95
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 2

**************************************
*            BST                     *
* 1. Display In Order                *
* 2. Display Pre Order               *
* 3. Display Post Order              *
* 4. Return to main menu             *
**************************************
Select the option (1 throuh 6): 1
10/1
25/1
35/1
45/1
50/1
55/1
65/1
75/1
80/1
90/1
95/1

**************************************
*            BST                     *
* 1. Display In Order                *
* 2. Display Pre Order               *
* 3. Display Post Order              *
* 4. Return to main menu             *
**************************************
Select the option (1 throuh 6): 2
50/1
25/1
10/1
45/1
35/1
75/1
65/1
55/1
90/1
80/1
95/1

**************************************
*            BST                     *
* 1. Display In Order                *
* 2. Display Pre Order               *
* 3. Display Post Order              *
* 4. Return to main menu             *
**************************************
Select the option (1 throuh 6): 3
10/1
35/1
45/1
25/1
55/1
65/1
80/1
95/1
90/1
75/1
50/1

**************************************
*            BST                     *
* 1. Display In Order                *
* 2. Display Pre Order               *
* 3. Display Post Order              *
* 4. Return to main menu             *
**************************************
Select the option (1 throuh 6): 4

  Returning to main menu


**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 3

Enter Fraction you would like to search for
  Enter the numerator: 80
  Enter the denominator: 1

Fraction Node found

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 3

Enter Fraction you would like to search for
  Enter the numerator: 55
  Enter the denominator: 2

Fraction is not in tree

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 4

Enter Fraction you would like to remove
  Enter the numerator: 75
  Enter the denominator: 1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 2

**************************************
*            BST                     *
* 1. Display In Order                *
* 2. Display Pre Order               *
* 3. Display Post Order              *
* 4. Return to main menu             *
**************************************
Select the option (1 throuh 6): 1
10/1
25/1
35/1
45/1
50/1
55/1
65/1
80/1
90/1
95/1

**************************************
*            BST                     *
* 1. Display In Order                *
* 2. Display Pre Order               *
* 3. Display Post Order              *
* 4. Return to main menu             *
**************************************
Select the option (1 throuh 6): 2
50/1
25/1
10/1
45/1
35/1
80/1
65/1
55/1
90/1
95/1

**************************************
*            BST                     *
* 1. Display In Order                *
* 2. Display Pre Order               *
* 3. Display Post Order              *
* 4. Return to main menu             *
**************************************
Select the option (1 throuh 6): 3
10/1
35/1
45/1
25/1
55/1
65/1
95/1
90/1
80/1
50/1

**************************************
*            BST                     *
* 1. Display In Order                *
* 2. Display Pre Order               *
* 3. Display Post Order              *
* 4. Return to main menu             *
**************************************
Select the option (1 throuh 6): 4

  Returning to main menu


**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 5

The Smallest Fraction is: 10/1

**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 9

  You should not be in this class!


**************************************
*            BST                     *
* 1. Insert Fraction                 *
* 2. Display                         *
* 3. Search for Fraction             *
* 4. Remove a Node                   *
* 5. Get and Display Smallest Node   *
* 6. Quit                            *
**************************************
Select the option (1 throuh 6): 6

  Have Fun!

*/

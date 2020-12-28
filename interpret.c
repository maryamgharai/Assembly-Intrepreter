#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#pragma warning(disable:4996)   
//const char *fpath = "c://tmp//ex2.asm";
//int ax, bx, cx, dx;


int translateVar(char* argval,int *ax, int *bx, int *cx, int *dx) {
   
    if (argval == NULL) {
        printf("\n translateVar says argval is null");
        return(-1);
    }
    int intval = 0;
    //int *ax, *bx, *cx, *dx;
    if (strcmp(argval,  "ax") == 0) intval = *ax;
    else if (strcmp(argval,  "bx") == 0) intval = *bx;
    else if (strcmp(argval, "cx") == 0) intval = *cx;
    else if (strcmp(argval, "dx") == 0) intval = *dx;

    else if ((!isalpha(argval[0]))) {
        intval = atoi(argval);
        //sscanf(argval, "%d", &intval);
    }

        //intval = ((int)*argval - 48);
    /*if(intval>2^16){

        printf("Error, the value is bigger than 16 bit!"); //////////
    }*/


    return(intval);
}

//Copies values to corresponding register
void setRegister(char* argval,int val, int *ax, int *bx, int *cx, int *dx) {
    if (argval == NULL) {
        printf("\n setRegister says argval is null");
        return;
    }
    else if (strcmp(argval, "ax") == 0) (*ax) = val;
    else if (strcmp(argval, "bx") == 0) (*bx) = val;
    else if (strcmp(argval, "cx") == 0) (*cx) = val;
    else if (strcmp(argval, "dx") == 0) (*dx) = val;

}

int main(int argc, char* argv[])
{
    int ax=0;
    int bx=0;
    int cx=0;
    int dx=0;
    // Definitions
    const int jump_adjustment = -1; //-2//////////////
    //const bool _debugging = false; //////////
    FILE* fp = NULL;
    //void* memory;
    char* str;

    int idx=0, rows = 0;
    const int lineSize = 25;

    char marray[100][lineSize];

    //memory = malloc(sizeof(char*) * lineSize);
    //str = (char*)memory;


    //File open
    printf("%s", argv[1]);
    fp = fopen(argv[1], "r");//argv[1]
    if (fp == NULL)
    {
        printf("\n\tError opening file...");
        exit(0);
    }
    //else printf("File is open"); //////////

    //Reading the file
    while (!feof(fp) && idx < 100)
    {

        str = marray[idx];  //first element of each row is the address to that row 
        if (fgets(str, lineSize, fp) == NULL) {
           // printf("End of file reached"); //is this working? ////////
           
            break;
        }
        else {
            //printf("%s", str);////////////////
            //if(!strcmp(str, "\n") ==0)  /////////////////////
            
            idx++;
        }
        //str = str + lineSize;
        //memory = realloc(memory, rows * lineSize);
        //rows = idx; //////////////
    }
    rows = idx;
    //DONE - parsing the assembly file into an array of char (each is a line) 

    //going through the array line by line
    char ar[100]; //char ar[100][lineSize];/////////////////
 
    //int j = 0;
    //char word[7];
    //word = malloc(7 * sizeof * marray);
    //*word = NULL;

    //int dig[3];
    int r;
     //mov, add, sub, mul, div, jmp, je, jne, jg, jge, jl, jle, read ,print
    for (idx = 0; idx < rows; idx++) {
        if(marray[idx][0]=='\n'){
               continue;

           } ////////////////////////added
        memcpy(ar, marray[idx], lineSize); //Lets each round of loop to work with a fresh copy of source //marray , 100 *linesize//////////////////////////
           char* firstToken = strtok(ar, " \n"); //ar[idx]//////////////////////
        if (strcmp(firstToken, "read") == 0)
        {
            //if (_debugging) printf("\n==> read");
            
            int val;
            scanf("\n%d", &val);
            char* arg1 = strtok(NULL, " \n");
            setRegister(arg1, val, &ax, &bx, &cx, &dx);
        }
        else if (strcmp(firstToken, "jmp") == 0)
        {
            //if (_debugging) printf("\n==> jmp");
            char* arg1 = strtok(NULL, " \n");
            int arg1val = translateVar(arg1, &ax, &bx, &cx, &dx);
            idx = arg1val + jump_adjustment;

        }
        else if (strcmp(firstToken, "je") == 0)
        {
            //if (_debugging) printf("\n==> je");

            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            char* arg3 = strtok(NULL, " \n");
            int arg1val = translateVar(arg2, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg3, &ax, &bx, &cx, &dx);
            int arg3val = translateVar(arg1, &ax, &bx, &cx, &dx);

            if (arg1val == arg2val) {

                idx = arg3val + jump_adjustment;

            }

            else { continue; }
        }
        else if (strcmp(firstToken, "jne") == 0)
        {
            //if (_debugging) printf("\n==> jne");

            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            char* arg3 = strtok(NULL, " \n");
            int arg1val = translateVar(arg2, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg3, &ax, &bx, &cx, &dx);
            int arg3val = translateVar(arg1, &ax, &bx, &cx, &dx);

            if (arg1val != arg2val) {

                idx = arg3val + jump_adjustment;

            }

            else { continue; }
        }
        else if (strcmp(firstToken, "jg") == 0)
        {
           // if (_debugging) printf("\n==> jg");

            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            char* arg3 = strtok(NULL, " \n");
            int arg1val = translateVar(arg2, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg3, &ax, &bx, &cx, &dx);
            int arg3val = translateVar(arg1, &ax, &bx, &cx, &dx);

            if (arg1val > arg2val) {

                idx = arg3val + jump_adjustment;

            }

            else { continue; }
        }
        else if (strcmp(firstToken, "jge") == 0)
        {
           // if (_debugging) printf("\n==> jge");

            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            char* arg3 = strtok(NULL, " \n");
            int arg1val = translateVar(arg2, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg3, &ax, &bx, &cx, &dx);
            int arg3val = translateVar(arg1, &ax, &bx, &cx, &dx);

            if (arg1val >= arg2val) {

                idx = arg3val + jump_adjustment;

            }

            else { continue; }
        }
        else if (strcmp(firstToken, "jl") == 0)
        {
           // if (_debugging) printf("\n==> jl");

            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            char* arg3 = strtok(NULL, " \n");
            int arg1val = translateVar(arg2, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg3, &ax, &bx, &cx, &dx);
            int arg3val = translateVar(arg1, &ax, &bx, &cx, &dx);

            if (arg1val < arg2val) {

                idx = arg3val + jump_adjustment;

            }

            else { continue; }
        }
        else if (strcmp(firstToken, "jle") == 0)
        {

           // if (_debugging) printf("\n==> jle");
            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            char* arg3 = strtok(NULL, " \n");
            int arg1val = translateVar(arg2, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg3, &ax, &bx, &cx, &dx);
            int arg3val = translateVar(arg1, &ax, &bx, &cx, &dx);

            if (arg1val <= arg2val) { 

                idx = arg3val + jump_adjustment;

            }

            else { continue; }
        }

        else if (strcmp(firstToken, "mul") == 0)
        {
           // if (_debugging) printf("\n==> mul");

            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            int arg1val = translateVar(arg1, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg2, &ax, &bx, &cx, &dx);

            r = arg1val * arg2val;
            setRegister(arg2, r, &ax, &bx, &cx, &dx);
        }
        else if (strcmp(firstToken, "div") == 0)
        {
            //if (_debugging) printf("\n==> div");
            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            int arg1val = translateVar(arg1, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg2, &ax, &bx, &cx, &dx);

            r = arg1val / arg2val;
            setRegister(arg2, r, &ax, &bx, &cx, &dx);

        }



        else if (strcmp(firstToken, "add") == 0)
        {
            //if (_debugging) printf("\n==> add");

            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            int arg1val = translateVar(arg1, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg2, &ax, &bx, &cx, &dx);

            r = arg1val + arg2val;
            setRegister(arg2, r, &ax, &bx, &cx, &dx);
        }
        else if (strcmp(firstToken, "sub") == 0)
        {
            //if (_debugging) printf("\n==> sub");

            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            int arg1val = translateVar(arg1, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg2, &ax, &bx, &cx, &dx);

            r = arg2val - arg1val;
            setRegister(arg2, r, &ax, &bx, &cx, &dx);
        }
        else if (strcmp(firstToken, "mov") == 0)
        {
           // if (_debugging) printf("\n==> mov");

            char* arg1 = strtok(NULL, " \n");
            char* arg2 = strtok(NULL, " \n");
            int arg1val = translateVar(arg1, &ax, &bx, &cx, &dx);
            int arg2val = translateVar(arg2, &ax, &bx, &cx, &dx);

            arg2val = arg1val;
            setRegister(arg2, arg2val, &ax, &bx, &cx, &dx);
            
        }


        else if (strcmp(firstToken, "print") == 0)
        {

            char* arg1 = strtok(NULL, " \n");
            int arg1val = translateVar(arg1, &ax, &bx, &cx, &dx);


            printf("%d", arg1val); // (int)*arg1);
        }








       




                 

    }

   
    getchar();
    return(1);

}






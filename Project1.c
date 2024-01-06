
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

typedef struct term{
    char term[200]; // assume terms are not longer than 200
    double weight;
} term;

int countlines(char *filename)
{                              
    FILE *text = fopen("cities.txt","r");
    int n_ch = 0;
    int n_l = 0;
    n_l++;
    while(!feof(text))
        {
            n_ch = fgetc(text);
            if(n_ch == '\n')
            {
                n_l++;
            }
        }
    fclose(text);
    return n_l;
}

int compare_function(const void *name1, const void *name2)
{
    // const char *name1_ = *(const char **)name1;
    // const char *name2_ = *(const char **)name2;
    return strcmp(((term *)name1)->term, ((term *)name2)->term);
} 
     

void read_in_terms(term **terms, int *pnterms, char *filename)
{
    FILE *text = fopen(filename, "r");
    char temp[200];
    char whatever[200];
    if (!text){
        printf("File could not be opened");
        exit(1);
        }
    else {
        fgets(whatever, 200, text);
        // line[strlen(line)-1] = '\0';
        *pnterms = atoi(whatever);
    }
    char *gold;
    *terms = (term *)malloc(*pnterms * sizeof(term));
    for(int i = 0; i < *pnterms; i++)
    {
        fgets(temp, 200, text);
        gold = strtok(temp, "\t");
        (*terms)[i].weight = atof(gold);
        gold = strtok(NULL, "\t");
        gold[strlen(gold)-1] = '\0';
        strcpy((*terms)[i].term, gold);
    }
    fclose(text);
    qsort(*terms, *pnterms, sizeof(term), compare_function);
}


int main()
{   
    struct term *terms;
    int nterms = 93827;
    int *ntermss = &nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
}  





// #if !defined(AUTOCOMPLETE_H)
// #define AUTOCOMPLETE_H

typedef struct term{
    char term[200]; // assume terms are not longer than 200
    double weight;
} term;


void read_in_terms(struct term **terms, int *pnterms, char *filename);
int lowest_match(struct term *terms, int nterms, char *substr);
int highest_match(struct term *terms, int nterms, char *substr);
void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr);
// #endif
// #include "autocomplete.h"

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
    lowest_match(terms, nterms, "Tor");
    highest_match(terms, nterms, "Tor");
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");
    //free allocated blocks here -- not required for the project, but good practice
    return 0;
}




//    term *somestring = (term *)malloc((lengthofstring + 1) * sizeof(char));
//                 strncpy(terms, *somestring, lengthofstring)


// TESTING THE COMPARE FUNCTION
//   char *man[5] = {"ads", "dsae", "dsaeq", "asdq", "bdwqs"};
//     qsort(man, 5, sizeof(char *), compare_function);

//     for (int i = 0; i < 5; i++) {
//         printf("%s ", man[i]);
//     }


//                 for (temp; temp[counter] == " "; counter++);
//         {
//             int lengthofstring = strlen(temp);
//             if (counter = 0);
//                 temp = " ";
//             else if (counter % 2 == 1)
//                 {
//                 strcpy((*terms)(loop_ind).term, temp);
//                 counter++;
//                 }
//             else if (counter % 2 == 0)
//                 {
//                 strcpy((*terms)(loop_ind).weight, temp);
//                 counter++;
//                 }
//         }
//     }  


// int lowest_match(term *terms, int nterms, char *substr)
// {
//     {   
//         int i = 0;
//         strstr();
//         for(int temporary_term; substr[i] = terms[i]; i++)
//         if (strstr(sent, word) != NULL) 
//         {

//         }
//         else if (substr[0] != temp_term[0])
//         {
//             f++;
//         }
//         longest_match_index = i;
//         i++;
//     }  
//     return i;
// }

//     while (i < nterms)
//     {
//         char str[] = terms[i];
//         char alpha[] = *substr;

//         for (int i = 0; i < nterms; i++)
//         {
//             char *position_ptr = strchr(str, alpha[i]);
//             char *r_position_ptr = strrchr(str, alpha[i]);
//             int position = (position_ptr == NULL ? -1 : position_ptr - str);
//             int r_position = (r_position_ptr == NULL ? -1 : r_position_ptr - str);
//         }

// 	return 0;
// }
// }

// void read_in_terms(term **terms, int *pnterms, char *filename)
// {
//     // int counter = 0;
//     // *pnterms = countlines(filename) - 1;
//     FILE *text = fopen(filename, "r");
//     *terms = (term *)malloc(*pnterms * sizeof(char*));
//     char temp[200];
//     double temp_weight;
//     char temp_term[200];
//     while (fgets(temp, 200, text))
//     {
//         int lengthofstring = strlen(temp);
//         for(int i = 0; i < *pnterms; i++)
//         {
//             sscanf(temp, "%lf %[^\n]", &temp_weight, temp_term);
//             (*terms)[i].weight = (temp_weight);
//             strcpy((*terms)[i].term, temp_term);
//         }
//     fclose(text);
//     qsort(terms, *pnterms, sizeof(char *), compare_function);
//     }   
// }


//      for (temp; temp[counter] == " "; counter++);
//         {
//             int lengthofstring = strlen(temp);
//             if (counter = 0)
//                 {
//                 temp = ' ';
//                 }
//             else if (counter % 2 == 1)
//                 {
//                 strcpy((*terms)(loop_ind).term, temp);
//                 }
//             else if (counter % 2 == 0)
//                 {
//                 strcpy((*terms)(loop_ind).weight, temp);
//                 }
//   for (int i = 0; i < *pnterms; i++) 
//       {
//             sscanf(temp, "%lf %[^\n]", &temp_weight, temp_term);
//             (*terms)[i].weight = (temp_weight);
//             strcpy((*terms)[i].term, temp_term);
//         }





void read_in_terms(term **terms, int *pnterms, char *filename)
{
    FILE *fp = fopen(filename, "r");
    char line[200];
    if (fp == NULL){
        printf("File could not be opened");
        fclose(fp);
        exit(1);
        }
    else {
        fgets(line, sizeof(line), fp);
        line[strlen(line)-1] = '\0';
        *pnterms = atoi(line);
    }
    *terms = (term *)malloc(*pnterms * sizeof(term));
    int a;
    int b;
    int c; 
    char temporary_full[200];
    char temporary_weight[200];
    char temporary_term[200];
    for(int i = 0; i < *pnterms; i++)
    {
    a = 0;
    b = 0;
    c = 0;
        while (temporary_full[a] == ' ' || temporary_full[a] == '\t')
        {
            a++;
        }
        while (temporary_full[a] != ' ' && temporary_full[a] != '\t')
        {
            temporary_weight[b] = temporary_full[a];
            a++;
            b++;
        }
        temporary_weight[b] = '\0';
        (*terms)[i].weight = atof(temporary_weight);
        while (temporary_full[a] == ' ' || temporary_full[a] == '\t')
        {
            a++;
        }
        while (temporary_full[a] != ' ' && temporary_full[a] != '\t')
        {
            temporary_term[c] = temporary_full[a];
            a++;
            c++;
        }
        temporary_term[c] = '\0';
        strcpy((*terms)[i].term, temporary_term);
    }
    fclose(fp);
    qsort(terms, *pnterms, sizeof(term), compare_function);
}


// 1-3: DONE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct bst
{
    int day;
    char region_code[1000];
    int number_of_patients;
    struct bst* left;
    struct bst* right;
}node;
node* root = NULL;
int totalPatients = 0;
int countPeriod = 0;
node* makeNode(int day, char* region_code, int number_of_patients)
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->day = day;
    strcpy(newNode->region_code, region_code);
    newNode->number_of_patients = number_of_patients;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node* find(node* r, char* region_code, int day)
{
    if (r == NULL) return NULL;
    if (r->day == day && strcmp(r->region_code, region_code) == 0) return r;
    node* p = find(r->left, region_code, day);
    if (p != NULL) return p;
    return find(r->right, region_code, day);
}

void Insert(int day, char* region_code, int number_of_patients)
{
    node* p = find(root, region_code, day);
    if (p != NULL) return;
    if (root == NULL)
    {
        root = makeNode(day, region_code, number_of_patients);
        return;
    }
    node* temp = root;
    while (temp != NULL)
    {
        if (temp->day > day)
        {
            if (temp->left == NULL)
            {
                temp->left = makeNode(day, region_code, number_of_patients);
                return;
            }
            temp = temp->left;
        } else
        {
            if (temp->right == NULL)
            {
                temp->right = makeNode(day, region_code, number_of_patients);
                return;
            }
            temp = temp->right;
        }
    }
}


void queries(){
    freopen("input.txt", "r", stdin);
    char cmd[100];
    int day, number_of_patients, start_day, end_day;
    char region_code[1000];
    while (1)
    {
        scanf("%s", cmd);
        if (strcmp(cmd, "***") == 0) break;
        else if (strcmp(cmd, "$Update") == 0){
            scanf("%s %d %d", region_code, &day, &number_of_patients);
            node* p = find(root, region_code, day);
            if (p == NULL) {
                Insert(day, region_code, number_of_patients);
                totalPatients = totalPatients + number_of_patients;
            }
        }
        else if (strcmp(cmd, "$CountTotalPatients") == 0){
            printf("%d\n", totalPatients);
        }
        else if (strcmp(cmd, "$FindNumberPatients") == 0){
            scanf("%s %d", region_code, &day);
            node* p = find(root, region_code, day);
            if (p != NULL) printf("%d\n", p->number_of_patients);
            else printf("0\n");
        }
        else if (strcmp(cmd, "$CountNumberPatientsOfPeriod") == 0){
            scanf("%d %d", &start_day, &end_day);
            //CountPeriod(root, start_day, end_day);
        }
        else if (strcmp(cmd, "$CountNumberPatientsOfRegion") == 0){
            scanf("%s", region_code);
        }
    }
}
int main(int argc, char const *argv[])
{
    queries();
    return 0;
}

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;

#define NUM 100
#define WEIGHT_RANGE 100

int getWeight(int left[], int right[], int len, int weights[][NUM])
{
    int weight = 0;
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            weight += weights[left[i]][right[j]];
        }
    }
    return weight;
}

int swapWeight(int left[], int right[], int weights[][NUM],
               int current_weight, int l, int r, int len)
{
    int weight = current_weight;
    for(int i = 0; i < len; i++){
        if(i != r){
            weight -= weights[left[l]][right[i]];
            weight += weights[right[r]][right[i]];
        }
        if(i != l){
            weight -= weights[left[i]][right[r]];
            weight += weights[left[i]][left[l]];
        }
    }
    return weight;
}

void swap(int left[], int right[], int i, int j)
{
    int tmp = left[i];
    left[i] = right[j];
    right[j] = tmp;
}

int main()
{
    //Initialize Weight Matrix
    int weights[NUM][NUM] = {0};
    for(int i = 0; i < NUM; i++){
        for(int j = i+1; j < NUM; j++){
            weights[i][j] = rand() % WEIGHT_RANGE + 1;
            weights[j][i] = weights[i][j];
        }
    }

    //Initialize Left and Right vector
    int left_index[NUM / 2];
    int right_index[NUM / 2];
    for(int i = 0; i < NUM / 2; i++){
        left_index[i] = i;
        right_index[i] = i + NUM / 2;
    }

    double start, end;
    start = clock();

    int current_weight = getWeight(left_index, right_index, NUM / 2, weights);
    int flag;
    while(true){
        flag = 0;
        for(int i = 0; i < NUM / 2 && flag == 0; i++){
            for(int j = 0; j < NUM / 2 && flag == 0; j++){
                int new_weight = swapWeight(left_index, right_index, weights, 
                                            current_weight, i, j, NUM / 2);
                if(new_weight < current_weight){
                    current_weight = new_weight;
                    swap(left_index, right_index, i, j);
                    flag = 1; //break the loop
                }
            }
        }
        if(flag == 0) //get the min weight
            break;
    }

    end = clock();
    cout << difftime(end,start) / CLOCKS_PER_SEC << endl;
    cout << "Min weight: " << current_weight << endl;

    return 0;
}

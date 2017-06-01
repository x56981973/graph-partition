## 图划分问题

### 1. 问题描述
>一个有2n个点的完全图，每条边都有权值。寻找一种方案将所有点分成两部分，使得连接两部分的边（共n*n条）的权值最低。

### 2. 算法思路
>每次交换两部分中的一个点，如果新的划分的权值小于当前的划分，则保留当前划分。当检验n*n种交换方案后无法找到更低的权值，则认为当前划分满足要求。

### 3. 参数设置
>点数：共100个
>
>权值：随机（范围1-100）

### 4. 算法详述
#### 初始化权值矩阵
```
#define NUM 100
#define WEIGHT_RANGE 100

int weights[NUM][NUM] = {0};
for(int i = 0; i < NUM; i++){
    for(int j = i+1; j < NUM; j++){
        weights[i][j] = rand() % WEIGHT_RANGE + 1;
        weights[j][i] = weights[i][j];
    }
}
```

#### 初始化左右两部分的列表(默认按顺序划分)
```
int left_index[NUM / 2];
int right_index[NUM / 2];
for(int i = 0; i < NUM / 2; i++){
    left_index[i] = i;
    right_index[i] = i + NUM / 2;
}
```

#### 计算当前划分的权值
```
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
```

#### 计算交换一个点之后的新权值
说明：每次交换只更新部分权值，故无需遍历所有边就可得到新的权值

```
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
```

#### 更新算法
说明：循环遍历所有交换的可能，只要某一交换比当前更优，则进行交换。flag初始化为0，标识是否存在更优解，如果找到更优解，则置为1终止循环，重新开始找下一个.如果遍历完毕flag依然为0，则表示已无更优情况，算法结束。

```
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
```
### 5. 获取源代码
```

```


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "../inc/SC.h"
#include "../inc/definition.h"

using namespace std;

int main(int argc,char** argv){
    SC sc;
    srand(time(NULL));
    cout<<"program in"<<endl;
    vector<bool*> sum;
    int bb;
    char buf;
    // vector<int> C;
    // C.reserve(size);
    float buffer;
    

    float threshold_1[32] = {-0.09311132878065109, 0.01636984385550022, -1.1601179838180542, 1.0464071035385132, 1.1822867393493652, 1.316198706626892, -1.2384259700775146, 0.054702743887901306, -1.2490497827529907, -0.10826772451400757, 1.7383816242218018, 0.6806756258010864, 1.1886515617370605, -0.22215022146701813, -0.8769798278808594, 1.1012130975723267, 0.033998724073171616, 0.8128331899642944, -1.1804205179214478, -0.9115725755691528, -1.2905209064483643, -1.12577486038208, 0.009792732074856758, 0.05692753940820694, -1.2547390460968018, -0.8481188416481018, -1.2712393999099731, -0.9360234141349792, -1.1812881231307983, -1.2658339738845825, 1.3013828992843628, -0.6552966833114624};
    float threshold_2[32] = {-14.466394424438477, 7.169124126434326, 7.6124796867370605, -3.422462224960327, -12.81364631652832, 1.0367259979248047, -15.309078216552734, 0.8173356056213379, -13.388500213623047, -2.8168959617614746, -74.9836196899414, -19.821491241455078, -5.46647310256958, 1.3305840492248535, -19.099411010742188, 14.628715515136719, -5.3909592628479, -7.210825443267822, 15.642261505126953, 10.365299224853516, 0.6903009414672852, -10.747349739074707, -0.7748885154724121, 16.652774810791016, 45.145320892333984, -19.49041175842285, 15.762331008911133, 0.4253697395324707, 4.442461967468262, -12.98421859741211, 3.720792293548584, 17.38399314880371};
    float threshold_3[4] = {-2.493149518966675, -7.356795787811279, -7.115196228027344, -2.823887348175049};

    // bool* a = new bool[bit_len];
    // bool* b = new bool[bit_len];
    // bool* c = new bool[bit_len];
    // bool* d = new bool[bit_len];
    // a = sc.bit_gen(0.1);
    // b = sc.bit_gen(0.2);
    // d = sc.bit_gen(0.3);
    // sum.push_back(a);
    // sum.push_back(b);
    // sum.push_back(d);
    // c = sc.MUX_general(sum);
    // // for(size_t i = 0; i < bit_len; ++i)
    // // {
    // //     cout << a[i] << " " << b[i] << " " << c[i] << endl;
    // // }
    // cout << "hello : " << sc.print(a) << " " << sc.print(b) << " " << sc.print(c) << " " << (0.6) / 3. << endl;
    // return 0;
    
    float*** fc_weight;
    fc_weight = new float**[4];

    fc_weight[0] = new float*[64];
    for(size_t i = 0; i < 64; ++i){
        fc_weight[0][i] = new float[32];
        for(size_t j = 0; j < 32; ++j){
            fc_weight[0][i][j] = 0;
        }
    }
    
    fc_weight[1] = new float*[32];
    
    for(size_t i = 0; i < 32; ++i){
        fc_weight[1][i] = new float[32];
        for(size_t j = 0; j < 32; ++j){
            fc_weight[1][i][j] = 0;
        }
    }
    
    fc_weight[2] = new float*[32];
    
    for(size_t i = 0; i < 32; ++i){
        fc_weight[2][i] = new float[4];
        for(size_t j = 0; j < 4; ++j){
            fc_weight[2][i][j] = 0;
        }
    }

    // fc_weight[3] = new float*[32];
    
    // for(size_t i = 0; i < 32; ++i){
    //     fc_weight[3][i] = new float[4];
    //     for(size_t j = 0; j < 4; ++j){
    //         fc_weight[3][i][j] = 0;
    //     }
    // }

    fstream fc("fc.txt");
    if (!fc){
        cerr<<"error _fc_"<<endl;
        return 0;
    }
    for(size_t i = 0; i < 64; ++i){
        for(size_t j = 0; j < 10; ++j){
            fc >> buffer;
            // cout << buffer <<endl;
            fc_weight[0][i][j] = buffer;
        }
    }
    
    for(size_t i = 0; i < 10; ++i){
        for(size_t j = 0; j < 4; ++j){
            fc >> buffer;
            // cout << buffer << endl;
            fc_weight[1][i][j] = buffer;
        }
    }
    // for(size_t i = 0; i < 32; ++i){
    //     for(size_t j = 0; j < 4; ++j){
    //         fc >> buffer;
    //         // cout << buffer << endl;
    //         fc_weight[2][i][j] = buffer;
    //     }
    // }
    // for(size_t i = 0; i < 32; ++i){
    //     for(size_t j = 0; j < 4; ++j){
    //         fc >> buffer;
    //         // cout << buffer << endl;
    //         if(buffer == -1) fc_weight[3][i][j] = -1;
    //         if(buffer == 1) fc_weight[3][i][j] = 1;
    //     }
    // }

    fc.close();
    bool*** fc_neurons;
    fc_neurons = new bool**[5];
    
    fc_neurons[0] = new bool*[64];
    for(size_t i = 0; i < 64; ++i){
        fc_neurons[0][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[0][i][j] = 0;
        }
    }

    fc_neurons[1] = new bool*[32];
    for(size_t i = 0; i < 32; ++i){
        fc_neurons[1][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[1][i][j] = 0;
        }
    }

    fc_neurons[2] = new bool*[32];
    for(size_t i = 0; i < 32; ++i){
        fc_neurons[2][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[2][i][j] = 0;
        }
    }

    fc_neurons[3] = new bool*[32];
    for(size_t i = 0; i < 32; ++i){
        fc_neurons[3][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[3][i][j] = 0;
        }
    }

    fc_neurons[4] = new bool*[4];
    for(size_t i = 0; i < 4; ++i){
        fc_neurons[4][i] = new bool[bit_len];
        for(size_t j = 0; j < bit_len; ++j){
            fc_neurons[4][i][j] = 0;
        }
    }

    float** _fc_neurons;
    _fc_neurons = new float*[5];
    
    _fc_neurons[0] = new float[64];
    for(size_t i = 0; i < 64; ++i){
        _fc_neurons[0][i] = 0;
    }

    _fc_neurons[1] = new float[64];
    for(size_t i = 0; i < 64; ++i){
        _fc_neurons[1][i] = 0;
    }

    
    fstream labels_txt("labels-2.txt");
    if (!labels_txt){
        cerr<<"error"<<endl;
    }

    fstream inputs_txt("inputs.txt");
    if (!inputs_txt){
        cerr<<"error"<<endl;
    }
    
    int label = 0, max_cand = 0, correct_count = 0;
    float max = 0;
    // char b;
    for(size_t i = 0; i < 1168; ++i)
    {
        for(size_t j = 0; j < 64; ++j)
        {
            inputs_txt >> bb;
            // cout << "buffer = " << bb << endl;
            fc_neurons[0][j] = sc.bit_gen(bb / 128.0);
            _fc_neurons[0][j] = bb / 128.0;
        }
        // cout<<"\n";

        labels_txt >> label;
        

        //for convolution layers
        // cout << conv_neurons[0][0][0][0] << endl;
        cout<<"fc1"<<endl;
        fc_neurons[1] = sc.linear(fc_neurons[0], fc_weight[0], sum, 64, 10);
        _fc_neurons[1] = sc.linear(_fc_neurons[0], fc_weight[0], sum, 64, 10);
        for(size_t i = 0; i < 10; ++i){
        //     if(sc.print(fc_neurons[1][i]) < (threshold_1[i] / 64.0)) fc_neurons[1][i] = sc.bit_gen(-1);
        //     else fc_neurons[1][i] = sc.bit_gen(1);
            cout << sc.print(fc_neurons[1][i]) << " " << _fc_neurons[1][i] / 64. << endl;
        }
        cout<<"fc2"<<endl;
        fc_neurons[2] = sc.linear(fc_neurons[1], fc_weight[1], sum, 10, 4);
        _fc_neurons[2] = sc.linear(_fc_neurons[1], fc_weight[1], sum, 10, 4);
        // for(size_t i = 0; i < 32; ++i){
        //     if(sc.print(fc_neurons[2][i]) < threshold_2[i] / 32.0) fc_neurons[2][i] = sc.bit_gen(-1);
        //     else fc_neurons[2][i] = sc.bit_gen(1);
        //     // cout << sc.print(fc_neurons[2][i]) << endl;
        // }
        // fc_neurons[3] = sc.linear(fc_neurons[2], fc_weight[2], sum, 32, 4);
        // for(size_t i = 0; i < 4; ++i){
        //     fc_neurons[3][0] = sc.MUX(fc_neurons[3][0], sc.bit_gen(threshold_3[0] / 32.0));
        //     for(size_t j = 1; j < 4; ++j)
        //     {
        //         fc_neurons[3][j] = sc.MUX(fc_neurons[3][j], sc.bit_gen(threshold_3[j] / 32.0));
        //         fc_neurons[3][j] = sc.XNOR(fc_neurons[3][j], sc.bit_gen(-1));
        //     }
        // }

        max = sc.print(fc_neurons[2][0]);
        max_cand = 0;
        for(size_t j = 0; j < 4; ++j)
        {
            // cout << j + 1 << " : " << sc.print(fc_neurons[3][j]) << endl;
            if(sc.print(fc_neurons[2][j]) > max)
            {
                max = sc.print(fc_neurons[2][j]);
                max_cand = j;
            }
        }

        cout << "label is : " << label << " ;predict is : " << max_cand << endl;
        if(max_cand == label)
        {
            ++correct_count;
            // cout << "correct!!!" << endl;
        }
        // else cout << "wrong!!!" << endl;
        cout << "accuracy = " << (float)correct_count / (i + 1) << endl;
    }


    inputs_txt.close();
    labels_txt.close();
    // cout<<"5"<<endl;
    // conv_neurons[2] = sc.conv2d(conv_neurons[2], conv_weight[2], sum, 16, 128,128,3,1,1);
    // conv_neurons[2] = sc.conv2d(conv_neurons[2], conv_weight[3], sum, 16, 128,128,3,1,1);
    
    
    // conv_neurons[4] = sc.maxpool2d(conv_neurons[2], 16, 128, 2, 2);
    // conv_neurons[4] = sc.conv2d(conv_neurons[4], conv_weight[4], sum, 8, 128,128,3,1,1);
    // conv_neurons[4] = sc.conv2d(conv_neurons[4], conv_weight[5], sum, 8, 128,128,3,1,1);
    

    
    
    
//     double x_test[30][4] = {{6.1000, 2.8000, 4.7000, 1.2000},
//         {5.7000, 3.8000, 1.7000, 0.3000},
//         {7.7000, 2.6000, 6.9000, 2.3000},
//         {6.0000, 2.9000, 4.5000, 1.5000},
//         {6.8000, 2.8000, 4.8000, 1.4000},
//         {5.4000, 3.4000, 1.5000, 0.4000},
//         {5.6000, 2.9000, 3.6000, 1.3000},
//         {6.9000, 3.1000, 5.1000, 2.3000},
//         {6.2000, 2.2000, 4.5000, 1.5000},
//         {5.8000, 2.7000, 3.9000, 1.2000},
//         {6.5000, 3.2000, 5.1000, 2.0000},
//         {4.8000, 3.0000, 1.4000, 0.1000},
//         {5.5000, 3.5000, 1.3000, 0.2000},
//         {4.9000, 3.1000, 1.5000, 0.1000},
//         {5.1000, 3.8000, 1.5000, 0.3000},
//         {6.3000, 3.3000, 4.7000, 1.6000},
//         {6.5000, 3.0000, 5.8000, 2.2000},
//         {5.6000, 2.5000, 3.9000, 1.1000},
//         {5.7000, 2.8000, 4.5000, 1.3000},
//         {6.4000, 2.8000, 5.6000, 2.2000},
//         {4.7000, 3.2000, 1.6000, 0.2000},
//         {6.1000, 3.0000, 4.9000, 1.8000},
//         {5.0000, 3.4000, 1.6000, 0.4000},
//         {6.4000, 2.8000, 5.6000, 2.1000},
//         {7.9000, 3.8000, 6.4000, 2.0000},
//         {6.7000, 3.0000, 5.2000, 2.3000},
//         {6.7000, 2.5000, 5.8000, 1.8000},
//         {6.8000, 3.2000, 5.9000, 2.3000},
//         {4.8000, 3.0000, 1.4000, 0.3000},
//         {4.8000, 3.1000, 1.6000, 0.2000}};
//     float corr_answer[30] = {1, 0, 2, 1, 1, 0, 1, 2, 1, 1, 2, 0, 0, 0, 0, 1, 2, 1, 1, 2, 0, 2, 0, 2,
//         2, 2, 2, 2, 0, 0};
    
//     double train_data[120][4] = {{4.6000, 3.6000, 1.0000, 0.2000},
//         {5.7000, 4.4000, 1.5000, 0.4000},
//         {6.7000, 3.1000, 4.4000, 1.4000},
//         {4.8000, 3.4000, 1.6000, 0.2000},
//         {4.4000, 3.2000, 1.3000, 0.2000},
//         {6.3000, 2.5000, 5.0000, 1.9000},
//         {6.4000, 3.2000, 4.5000, 1.5000},
//         {5.2000, 3.5000, 1.5000, 0.2000},
//         {5.0000, 3.6000, 1.4000, 0.2000},
//         {5.2000, 4.1000, 1.5000, 0.1000},
//         {5.8000, 2.7000, 5.1000, 1.9000},
//         {6.0000, 3.4000, 4.5000, 1.6000},
//         {6.7000, 3.1000, 4.7000, 1.5000},
//         {5.4000, 3.9000, 1.3000, 0.4000},
//         {5.4000, 3.7000, 1.5000, 0.2000},
//         {5.5000, 2.4000, 3.7000, 1.0000},
//         {6.3000, 2.8000, 5.1000, 1.5000},
//         {6.4000, 3.1000, 5.5000, 1.8000},
//         {6.6000, 3.0000, 4.4000, 1.4000},
//         {7.2000, 3.6000, 6.1000, 2.5000},
//         {5.7000, 2.9000, 4.2000, 1.3000},
//         {7.6000, 3.0000, 6.6000, 2.1000},
//         {5.6000, 3.0000, 4.5000, 1.5000},
//         {5.1000, 3.5000, 1.4000, 0.2000},
//         {7.7000, 2.8000, 6.7000, 2.0000},
//         {5.8000, 2.7000, 4.1000, 1.0000},
//         {5.2000, 3.4000, 1.4000, 0.2000},
//         {5.0000, 3.5000, 1.3000, 0.3000},
//         {5.1000, 3.8000, 1.9000, 0.4000},
//         {5.0000, 2.0000, 3.5000, 1.0000},
//         {6.3000, 2.7000, 4.9000, 1.8000},
//         {4.8000, 3.4000, 1.9000, 0.2000},
//         {5.0000, 3.0000, 1.6000, 0.2000},
//         {5.1000, 3.3000, 1.7000, 0.5000},
//         {5.6000, 2.7000, 4.2000, 1.3000},
//         {5.1000, 3.4000, 1.5000, 0.2000},
//         {5.7000, 3.0000, 4.2000, 1.2000},
//         {7.7000, 3.8000, 6.7000, 2.2000},
//         {4.6000, 3.2000, 1.4000, 0.2000},
//         {6.2000, 2.9000, 4.3000, 1.3000},
//         {5.7000, 2.5000, 5.0000, 2.0000},
//         {5.5000, 4.2000, 1.4000, 0.2000},
//         {6.0000, 3.0000, 4.8000, 1.8000},
//         {5.8000, 2.7000, 5.1000, 1.9000},
//         {6.0000, 2.2000, 4.0000, 1.0000},
//         {5.4000, 3.0000, 4.5000, 1.5000},
//         {6.2000, 3.4000, 5.4000, 2.3000},
//         {5.5000, 2.3000, 4.0000, 1.3000},
//         {5.4000, 3.9000, 1.7000, 0.4000},
//         {5.0000, 2.3000, 3.3000, 1.0000},
//         {6.4000, 2.7000, 5.3000, 1.9000},
//         {5.0000, 3.3000, 1.4000, 0.2000},
//         {5.0000, 3.2000, 1.2000, 0.2000},
//         {5.5000, 2.4000, 3.8000, 1.1000},
//         {6.7000, 3.0000, 5.0000, 1.7000},
//         {4.9000, 3.1000, 1.5000, 0.2000},
//         {5.8000, 2.8000, 5.1000, 2.4000},
//         {5.0000, 3.4000, 1.5000, 0.2000},
//         {5.0000, 3.5000, 1.6000, 0.6000},
//         {5.9000, 3.2000, 4.8000, 1.8000},
//         {5.1000, 2.5000, 3.0000, 1.1000},
//         {6.9000, 3.2000, 5.7000, 2.3000},
//         {6.0000, 2.7000, 5.1000, 1.6000},
//         {6.1000, 2.6000, 5.6000, 1.4000},
//         {7.7000, 3.0000, 6.1000, 2.3000},
//         {5.5000, 2.5000, 4.0000, 1.3000},
//         {4.4000, 2.9000, 1.4000, 0.2000},
//         {4.3000, 3.0000, 1.1000, 0.1000},
//         {6.0000, 2.2000, 5.0000, 1.5000},
//         {7.2000, 3.2000, 6.0000, 1.8000},
//         {4.6000, 3.1000, 1.5000, 0.2000},
//         {5.1000, 3.5000, 1.4000, 0.3000},
//         {4.4000, 3.0000, 1.3000, 0.2000},
//         {6.3000, 2.5000, 4.9000, 1.5000},
//         {6.3000, 3.4000, 5.6000, 2.4000},
//         {4.6000, 3.4000, 1.4000, 0.3000},
//         {6.8000, 3.0000, 5.5000, 2.1000},
//         {6.3000, 3.3000, 6.0000, 2.5000},
//         {4.7000, 3.2000, 1.3000, 0.2000},
//         {6.1000, 2.9000, 4.7000, 1.4000},
//         {6.5000, 2.8000, 4.6000, 1.5000},
//         {6.2000, 2.8000, 4.8000, 1.8000},
//         {7.0000, 3.2000, 4.7000, 1.4000},
//         {6.4000, 3.2000, 5.3000, 2.3000},
//         {5.1000, 3.8000, 1.6000, 0.2000},
//         {6.9000, 3.1000, 5.4000, 2.1000},
//         {5.9000, 3.0000, 4.2000, 1.5000},
//         {6.5000, 3.0000, 5.2000, 2.0000},
//         {5.7000, 2.6000, 3.5000, 1.0000},
//         {5.2000, 2.7000, 3.9000, 1.4000},
//         {6.1000, 3.0000, 4.6000, 1.4000},
//         {4.5000, 2.3000, 1.3000, 0.3000},
//         {6.6000, 2.9000, 4.6000, 1.3000},
//         {5.5000, 2.6000, 4.4000, 1.2000},
//         {5.3000, 3.7000, 1.5000, 0.2000},
//         {5.6000, 3.0000, 4.1000, 1.3000},
//         {7.3000, 2.9000, 6.3000, 1.8000},
//         {6.7000, 3.3000, 5.7000, 2.1000},
//         {5.1000, 3.7000, 1.5000, 0.4000},
//         {4.9000, 2.4000, 3.3000, 1.0000},
//         {6.7000, 3.3000, 5.7000, 2.5000},
//         {7.2000, 3.0000, 5.8000, 1.6000},
//         {4.9000, 3.6000, 1.4000, 0.1000},
//         {6.7000, 3.1000, 5.6000, 2.4000},
//         {4.9000, 3.0000, 1.4000, 0.2000},
//         {6.9000, 3.1000, 4.9000, 1.5000},
//         {7.4000, 2.8000, 6.1000, 1.9000},
//         {6.3000, 2.9000, 5.6000, 1.8000},
//         {5.7000, 2.8000, 4.1000, 1.3000},
//         {6.5000, 3.0000, 5.5000, 1.8000},
//         {6.3000, 2.3000, 4.4000, 1.3000},
//         {6.4000, 2.9000, 4.3000, 1.3000},
//         {5.6000, 2.8000, 4.9000, 2.0000},
//         {5.9000, 3.0000, 5.1000, 1.8000},
//         {5.4000, 3.4000, 1.7000, 0.2000},
//         {6.1000, 2.8000, 4.0000, 1.3000},
//         {4.9000, 2.5000, 4.5000, 1.7000},
//         {5.8000, 4.0000, 1.2000, 0.2000},
//         {5.8000, 2.6000, 4.0000, 1.2000},
//         {7.1000, 3.0000, 5.9000, 2.1000}};


// int train_label[120] = {
//   0 ,0, 1, 0, 0, 2, 1, 0, 0, 0, 2, 1, 1, 0, 0, 1, 2, 2, 1, 2, 1, 2, 1, 0, 2, 1, 0, 0, 0, 1, 2, 0, 0, 0, 1, 0, 1,
//  2, 0, 1, 2, 0, 2, 2, 1, 1, 2, 1, 0, 1, 2, 0, 0, 1, 1, 0, 2, 0, 0, 1, 1, 2, 1, 2, 2, 1, 0, 0, 2, 2, 0, 0, 0, 1,
//  2, 0, 2, 2, 0, 1, 1, 2, 1, 2, 0, 2, 1, 2, 1, 1, 1, 0, 1, 1, 0, 1, 2, 2, 0, 1, 2, 2, 0, 2, 0, 1, 2, 2, 1, 2, 1,
//  1, 2, 2, 0, 1, 2, 0, 1, 2
// };
        
//     float corr_count = 0;
//     float max=0,temp=0,max_cand=0;

//     for(int k=0;k<30;k++)
//     {
//         for(int i=0;i<4;i++)
//         {
//             fc_neurons[0][i] = sc.bit_gen(x_test[k][i] / 10.0);
//         }
//         for(size_t i = 0; i < 4; ++i)
//         {
//             cout << sc.print(fc_neurons[0][i]) << endl;
//         }
//         fc_neurons[1] = sc.linear(fc_neurons[0],fc_weight[0], sum, 4, 10);
//         for(size_t i = 0; i < 10; ++i)
//         {
//             cout << sc.print(fc_neurons[1][i]) << endl;
//         }
//         fc_neurons[2] = sc.linear(fc_neurons[1],fc_weight[1], sum, 10, 3);
//         max = sc.print(fc_neurons[2][0]);
//         max_cand = 0;
//         for(size_t j = 0; j < 3; ++j)
//         {
//             cout << j + 1 << " : " << sc.print(fc_neurons[2][j]) << endl;
//             if(sc.print(fc_neurons[2][j]) > max)
//             {
//                 // max = sc.print(fc_neurons[3][j]);
//                 max_cand = j;
//             }
//         }

//         cout << "label is : " << corr_answer[k] << " ;predict is : " << max_cand << endl;
//         if(max_cand == corr_answer[k])
//         {
//             ++corr_count;
//             // cout << "correct!!!" << endl;
//         }
//         // else cout << "wrong!!!" << endl;
//         cout << "accuracy = " << (float)corr_count / (k + 1) << endl;
        
//     }
        

    return 0;
}




// fstream labels_txt("labels-2.txt");
//     if (!labels_txt){
//         cerr<<"error"<<endl;
//     }

//     fstream inputs_txt("inputs.txt");
//     if (!inputs_txt){
//         cerr<<"error"<<endl;
//     }
    
//     int label = 0, max_cand = 0, correct_count = 0;
//     float max = 0;
//     // char b;
//     for(size_t i = 0; i < 1168; ++i)
//     {
//         for(size_t j = 0; j < 64; ++j)
//         {
//             inputs_txt >> bb;
//             // cout << "buffer = " << bb << endl;
//             fc_neurons[0][j] = sc.bit_gen(bb / 128.0);
//         }
//         // cout<<"\n";

//         labels_txt >> label;
        

//         //for convolution layers
//         // cout << conv_neurons[0][0][0][0] << endl;
//         cout<<"fc1"<<endl;
//         fc_neurons[1] = sc.linear(fc_neurons[0], fc_weight[0], sum, 64, 32);
//         // for(size_t i = 0; i < 32; ++i){
//         //     if(sc.print(fc_neurons[1][i]) < (threshold_1[i] / 64.0)) fc_neurons[1][i] = sc.bit_gen(-1);
//         //     else fc_neurons[1][i] = sc.bit_gen(1);
            
//         // }
//         cout<<"fc2"<<endl;
//         fc_neurons[2] = sc.linear(fc_neurons[1], fc_weight[1], sum, 32, 32);
//         // for(size_t i = 0; i < 32; ++i){
//         //     if(sc.print(fc_neurons[2][i]) < threshold_2[i] / 32.0) fc_neurons[2][i] = sc.bit_gen(-1);
//         //     else fc_neurons[2][i] = sc.bit_gen(1);
//         //     // cout << sc.print(fc_neurons[2][i]) << endl;
//         // }
//         fc_neurons[3] = sc.linear(fc_neurons[2], fc_weight[2], sum, 32, 4);
//         // for(size_t i = 0; i < 4; ++i){
//         //     fc_neurons[3][0] = sc.MUX(fc_neurons[3][0], sc.bit_gen(threshold_3[0] / 32.0));
//         //     for(size_t j = 1; j < 4; ++j)
//         //     {
//         //         fc_neurons[3][j] = sc.MUX(fc_neurons[3][j], sc.bit_gen(threshold_3[j] / 32.0));
//         //         fc_neurons[3][j] = sc.XNOR(fc_neurons[3][j], sc.bit_gen(-1));
//         //     }
//         // }

//         max = sc.print(fc_neurons[3][0]);
//         max_cand = 0;
//         for(size_t j = 0; j < 4; ++j)
//         {
//             // cout << j + 1 << " : " << sc.print(fc_neurons[3][j]) << endl;
//             if(sc.print(fc_neurons[3][j]) > max)
//             {
//                 max = sc.print(fc_neurons[3][j]);
//                 max_cand = j;
//             }
//         }

//         cout << "label is : " << label << " ;predict is : " << max_cand << endl;
//         if(max_cand == label)
//         {
//             ++correct_count;
//             // cout << "correct!!!" << endl;
//         }
//         // else cout << "wrong!!!" << endl;
//         cout << "accuracy = " << (float)correct_count / (i + 1) << endl;
//     }


//     inputs_txt.close();
//     labels_txt.close();
    // cout<<"5"<<endl;
    // conv_neurons[2] = sc.conv2d(conv_neurons[2], conv_weight[2], sum, 16, 128,128,3,1,1);
    // conv_neurons[2] = sc.conv2d(conv_neurons[2], conv_weight[3], sum, 16, 128,128,3,1,1);
    
    
    // conv_neurons[4] = sc.maxpool2d(conv_neurons[2], 16, 128, 2, 2);
    // conv_neurons[4] = sc.conv2d(conv_neurons[4], conv_weight[4], sum, 8, 128,128,3,1,1);
    // conv_neurons[4] = sc.conv2d(conv_neurons[4], conv_weight[5], sum, 8, 128,128,3,1,1);
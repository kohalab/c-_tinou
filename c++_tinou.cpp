#include <iostream>
#include <float.h>
#include <string.h>

int sig (int a){
  //return ( (a * 1) * 1002 / ( (( (a >= 0) ? a : -a ))+1 ) );
  int b = ( (a * 1) * 2000 / ( (( (a >= 0) ? a : -a ))+1 ) );
  
  if(b > +1000)b = +1000;
  if(b < -1000)b = -1000;
  
  return b;
  
  if(a > 0){
    return 1000;
  }else{
    return -1000;
  }
  
  return a;
}

uint64_t xorshift_reg = 0x123456789ABCDEF;

int next(){
  xorshift_reg = xorshift_reg ^ (xorshift_reg << 13);
  xorshift_reg = xorshift_reg ^ (xorshift_reg >> 17);
  xorshift_reg = xorshift_reg ^ (xorshift_reg << 15);
  return (int)(xorshift_reg>>32);
}

class trainer {
  public:
    int input_length;
    int output_length;
    int input[100];
    int weight[100][100];
    int output[100];
    
    int run(int* ins,int* weis,int len);
    int train(int time,int* to);
    void calculat();
    void show();
};

int trainer::run(int* ins,int* weis,int len){
  int o = 0;
  for(int i = 0; i < len; i++){
    o += (ins[i]*weis[i])/100;
  }
  o /= len;
  
  return sig(o-50);
}

int trainer::train(int time,int* to){
  int allerror = 0;
  for(int t = 0; t < time; t++){
    //
    for(int i = 0; i < output_length; i++){
      //
      int out = run(input,weight[i],input_length);
      
      int error = to[i]-out;
      allerror += error;
      
      for(int w = 0; w < input_length; w++){
        weight[i][w] += error * input[w] / 100000;
      }
      //
    }
    //
  }
  return allerror;
}

void trainer::calculat(){
  for(int i = 0; i < output_length ;i++){
    output[i] = run(input,weight[i],input_length);
  }
}

void trainer::show(){
  for(int i = 0; i < output_length ;i++){
    printf("%d",output[i]);
    if(i < output_length-1)printf(",");
  }
  printf("\n");
}

int main () {
  
  for(int i = 0; i < 10000; i++){
    next();
  }
  
  trainer train;
  
  train.input_length = 8;
  train.output_length = 8;
  
  for(int i = 0; i < train.input_length; i++){
    train.input[i] = next()%1000;
  }
  
  for(int i = 0; i < train.input_length; i++){
    for(int f = 0; f < train.output_length; f++){
      train.weight[f][i] = next()%1000;
    }
  }
  
  int to[] = {-1000,+1000,+1000,+1000,-1000,-1000,+1000,+1000};
  
  train.show();
  
  for(int i = 0; i < 10; i++){
    int loss = train.train(10,to);
  
    printf("loss : %d\n",loss);
  }
  
  train.calculat();
  
  train.show();

  return 0;
}
#include "multimod.h"
#include "stdio.h"

int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
	int64_t res = 0;
	if (m <= 2147483647) {
       res =  ((a%m) * (b%m)) % m; 
	}
	else {
       int64_t a_m = a % m;
	   int64_t b_m = b % m;
	   if(a_m <= 2147483647 && b_m <=2147483647)
	   {
	       res = a_m * b_m % m;    
	   }
	   else {
	       int len_a_m = 1;
		   int len_b_m = 1;
		   int64_t temp = a_m;
		   while(temp/10 > 0) {
		       len_a_m ++;
			   temp /= 10;
		   }

		   temp = b_m;
		   while(temp/10 > 0) {
		       len_b_m ++;
			   temp /= 10;
		   }

	   char str_a_m[len_a_m+1];
	   str_a_m[len_a_m] = '\0';
	   char str_b_m[len_b_m+1];
	   str_b_m[len_b_m] = '\0';
	   char str_res[len_a_m + len_b_m+1];
	   char temp_res[len_a_m+len_b_m+1];
	   
	   for(int i = 0; i < len_a_m + len_b_m; i ++) {
	       str_res[i] = '0';
	   }
	   str_res[len_a_m + len_b_m] = '\0';
	   
	   for(int i = 0; i < len_a_m + len_b_m; i ++) {
	       temp_res[i] = '0';
	   }
	   temp_res[len_a_m + len_b_m] = '\0';

	   temp = a_m;
	   for(int i = 0; i < len_a_m; i ++) {
	       str_a_m[len_a_m - i - 1] = (temp % 10) + '0';
		   temp /= 10;
	   }

	   temp = b_m;
	   for(int i = 0; i < len_b_m; i ++) {
	       str_b_m[len_b_m - i - 1] = (temp % 10) + '0';
		   temp /= 10;
	   }

	   /*
	   printf("val a_m:%ld\n",a_m);
	   printf("str a_m:%s\n",str_a_m);
	   printf("val b_m:%ld\n",b_m);
	   printf("str b_m:%s\n",str_b_m);
	   printf("str res:%s\n",str_res);
	   printf("len a_m:%d\n",len_a_m);
	   printf("len b_m:%d\n",len_b_m);
	   */

	   for(int i = 0; i < len_b_m; i ++) { //对应于下面一行的每一位
//			   printf("up_bit%d@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n",i);

	           for(int i = 0; i < len_a_m + len_b_m; i ++) { //对应于上面一行的每一位
	               temp_res[i] = '0';
	           }
	           temp_res[len_a_m + len_b_m] = '\0'; //由于竖式实际上是将下面的数的每一位去乘上面的数，因此，先把储存乘出来结果的数组清空

	       char bit_b = str_b_m[len_b_m-1-i]; //竖式下面的那一行的每一位进行循环

		   for(int j = 0; j < len_a_m; j ++) {
//			   printf("down_bit%d-------------------------------------------------\n",j);

		       char bit_a = str_a_m[len_a_m-1-j]; //对下面竖式的每一位进行循环
			   int res = (bit_a - '0') * (bit_b - '0'); //计算两位数相乘的结果
//			   printf("res:%d\n",res);
			   
               if(res <= 9) {
			       if(temp_res[len_a_m+len_b_m-1-i-j] + res <= '9') {
			           temp_res[len_a_m+len_b_m-1-i-j] += res;
			       }	   //若乘出来的结果加到相应的temp_res位上，不产生进位，那么简单的temp_res位做加法即可
			       else {
			           temp_res[len_a_m+len_b_m-1-i-j] = res - 10 + temp_res[len_a_m+len_b_m-1-i-j];
                       temp_res[len_a_m+len_b_m-1-i-j-1] += 1;
			       }       //若产生进位，由于结果<=9那么至多进位为1，故前面的一位加1即可，后面的一位保留进位后的结果
			   }               
              
			   else {  //若相乘结果大于9，此时需额外考虑进位
				   int forward_bit = res/10;  //提取出相乘结果的十位
//			       printf("forward_bit:%d\n",forward_bit);
				   int left_bit = res%10;     //提取出相乘结果的个位
//			       printf("left_bit:%d\n",left_bit);
			       if(temp_res[len_a_m+len_b_m-1-i-j] + left_bit <= '9') { //若相乘结果的个位加到temp_res后不产生进位
			           temp_res[len_a_m+len_b_m-1-i-j] += left_bit;        //那么forward_bit就是进位，放到前一位即可
					   temp_res[len_a_m+len_b_m-1-i-j-1] += forward_bit;
			       }	   
			       else {                                                  //若相乘结果个位加到temp_res后产生进位 
					   forward_bit += 1;                                   //此时的进位至多为1，forward_bit加1是进位
					   temp_res[len_a_m+len_b_m-1-i-j] = temp_res[len_a_m+len_b_m-1-i-j] + left_bit - 10;
					   temp_res[len_a_m+len_b_m-1-i-j-1] += forward_bit;
			   }
		   }
		   }
	       //        printf("temp res:%s\n",temp_res);
		   
		   
		   for(int k = 0; k < len_a_m + len_b_m; k ++) {
		       int bit = temp_res[len_a_m + len_b_m-1-k] - '0';
			   if(str_res[len_a_m + len_b_m-1-k] + bit <= '9') {
			       str_res[len_a_m + len_b_m-1-k] += bit;
			   }
			   
			   else {
			       str_res[len_a_m + len_b_m-1-k] = str_res[len_a_m + len_b_m-1-k] + bit - 10;
				   str_res[len_a_m + len_b_m-1-k-1] += 1;

				   if(str_res[len_a_m + len_b_m-1-k-1] > '9') {
				       str_res[len_a_m + len_b_m-1-k-1] -= 10;
					   str_res[len_a_m + len_b_m-1-k-1-1] += 1;
				   }
				       if(str_res[len_a_m + len_b_m-1-k-1-1] > '9') {
				           str_res[len_a_m + len_b_m-1-k-1-1] -= 10;
					       str_res[len_a_m + len_b_m-1-k-1-1-1] += 1;
				       }
				           if(str_res[len_a_m + len_b_m-1-k-1-1-1] > '9') {
				               str_res[len_a_m + len_b_m-1-k-1-1-1] -= 10;
					           str_res[len_a_m + len_b_m-1-k-1-1-1-1] += 1;
				           }
				               if(str_res[len_a_m + len_b_m-1-k-1-1-1-1] > '9') {
				                   str_res[len_a_m + len_b_m-1-k-1-1-1-1] -= 10;
					               str_res[len_a_m + len_b_m-1-k-1-1-1-1-1] += 1;
				               }
				                   if(str_res[len_a_m + len_b_m-1-k-1-1-1-1-1] > '9') {
				                       str_res[len_a_m + len_b_m-1-k-1-1-1-1-1] -= 10;
					                   str_res[len_a_m + len_b_m-1-k-1-1-1-1-1-1] += 1;
				                   }                                                         //这些看似非常傻的操作实际上确实非常傻，主要是为了处理烧熟连续进位的情况
			   }

			   }
               //printf("temp multi:%s\n", str_res); 
	   }

	   char str_m[len_a_m+len_b_m+1];

	   for(int i = 0; i < len_a_m + len_b_m; i ++) { //对应于上面一行的每一位
	       str_m[i] = '0';
	   }
	   str_m[len_a_m + len_b_m] = '\0'; //由于竖式实际上是将下面的数的每一位去乘上面的数，因此，先把储存乘出来结果的数组清空

	   temp = m;
	   for(int i = 0; i < len_a_m+len_b_m; i ++) {
	       str_m[len_a_m - i - 1] = (temp % 10) + '0';
		   temp /= 10;
	   }
       printf("multi:%s\n", str_m); 
	   }
	   }
       
  // TODO: implement
  return res;
}


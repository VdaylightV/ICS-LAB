#include "stdio.h"
#include "stdint.h"
#include "assert.h"
#include "string.h"
#include "sys/time.h"

static inline int64_t str_to_int(char* str) {
	int64_t result = 0;
	int len = strlen(str);

	for(int i = 0; i < len; i ++) {
	    result *= 10;
		result = result + str[i] - '0';	
	}

	return result;
}

static inline char* multi(char a[], int len_a, char b[], int len_b, char res[], int len_res) {   
	   // len_a_m = len_a - 1; len_b_m = len_b - 1
	   // len_a_m+len_b_m+1 = len_a+len_b-1
       

	   char temp_res[len_a + len_b - 1];
	   for(int i = 0; i < len_b-1; i ++) { //对应于下面一行的每一位
	           for(int i = 0; i < len_a + len_b - 2; i ++) { //对应于上面一行的每一位
	               temp_res[i] = '0';
	           }
	           temp_res[len_a + len_b - 2] = '\0'; //由于竖式实际上是将下面的数的每一位去乘上面的数，因此，先把储存乘出来结果的数组清空
    //printf("--------Initial temp_res:%s----------\n",temp_res);
	       char bit_b = b[len_b-1-1-i]; //竖式下面的那一行的每一位进行循环
    //printf("------------OUTER LOOP---------------\n");
    //printf("---------OUTER LOOP BIT:%c-----------\n",bit_b);

		   for(int j = 0; j < len_a - 1; j ++) {

		       char bit_a = a[len_a-1-1-j]; //对下面竖式的每一位进行循环
			   int res = (bit_a - '0') * (bit_b - '0'); //计算两位数相乘的结果
			   
    //printf("------------INNER LOOP---------------\n");
    //printf("---------INNER LOOP BIT:%c-----------\n",bit_a);
               if(res <= 9) {
			       if(temp_res[len_a+len_b-2-1-i-j] + res <= '9') {
			           temp_res[len_a+len_b-2-1-i-j] += res;
			       }	   //若乘出来的结果加到相应的temp_res位上，不产生进位，那么简单的temp_res位做加法即可
			       else {
			           temp_res[len_a+len_b-2-1-i-j] = res - 10 + temp_res[len_a+len_b-2-1-i-j];
                       temp_res[len_a+len_b-2-1-i-j-1] += 1;
			       }       //若产生进位，由于结果<=9那么至多进位为1，故前面的一位加1即可，后面的一位保留进位后的结果
			   }               
              
			   else {  //若相乘结果大于9，此时需额外考虑进位
				   int forward_bit = res/10;  //提取出相乘结果的十位
				   int left_bit = res%10;     //提取出相乘结果的个位
			       if(temp_res[len_a+len_b-2-1-i-j] + left_bit <= '9') { //若相乘结果的个位加到temp_res后不产生进位
			           temp_res[len_a+len_b-2-1-i-j] += left_bit;        //那么forward_bit就是进位，放到前一位即可
					   temp_res[len_a+len_b-2-1-i-j-1] += forward_bit;
			       }	   
			       else {                                                  //若相乘结果个位加到temp_res后产生进位 
					   forward_bit += 1;                                   //此时的进位至多为1，forward_bit加1是进位
					   temp_res[len_a+len_b-2-1-i-j] = temp_res[len_a+len_b-2-1-i-j] + left_bit - 10;
					   temp_res[len_a+len_b-2-1-i-j-1] += forward_bit;
			   }
		   }
		   }
    //printf("---------TEMP RESULT:%s-----------\n",temp_res);
		   
		   
		   for(int k = 0; k < len_a + len_b-1; k ++) {
		       int bit = temp_res[len_a + len_b-2-1-k] - '0';
			   if(res[len_a + len_b-2-1-k] + bit <= '9') {
			       res[len_a + len_b-2-1-k] += bit;
			   }
			   
			   else {
			       res[len_a + len_b-2-1-k] = res[len_a + len_b-2-1-k] + bit - 10;
				   res[len_a + len_b-2-1-k-1] += 1;

				   if(res[len_a + len_b-2-1-k-1] > '9') {
				       res[len_a + len_b-2-1-k-1] -= 10;
					   res[len_a + len_b-2-1-k-1-1] += 1;
				   }
				       if(res[len_a + len_b-2-1-k-1-1] > '9') {
				           res[len_a + len_b-2-1-k-1-1] -= 10;
					       res[len_a + len_b-2-1-k-1-1-1] += 1;
				       }
				           if(res[len_a + len_b-2-1-k-1-1-1] > '9') {
				               res[len_a + len_b-2-1-k-1-1-1] -= 10;
					           res[len_a + len_b-2-1-k-1-1-1-1] += 1;
				           }
				               if(res[len_a + len_b-2-1-k-1-1-1-1] > '9') {
				                   res[len_a + len_b-2-1-k-1-1-1-1] -= 10;
					               res[len_a + len_b-2-1-k-1-1-1-1-1] += 1;
				               }
				                   if(res[len_a + len_b-2-1-k-1-1-1-1-1] > '9') {
				                       res[len_a + len_b-2-1-k-1-1-1-1-1] -= 10;
					                   res[len_a + len_b-2-1-k-1-1-1-1-1-1] += 1;
				                   }                                                         //这些看似非常傻的操作实际上确实非常傻，主要是为了处理烧熟连续进位的情况
			   }

			   }
	   }
    
    return res;
}

static inline int compare(char a[], int len_a, char m[], int len_m) { // 实际上默认len_a和len_m相等
   int bit_count_a = 0;
   while(a[bit_count_a] == '0') {
       bit_count_a ++;
   } 

   int bit_count_m = 0;
   while(m[bit_count_m] == '0') {
       bit_count_m ++;
   } 

   if(bit_count_a < bit_count_m) {
//	   printf(">\n");
       return 1; // 返回1表示a大
   }

   else if(bit_count_a > bit_count_m) {
//	   printf("<\n");
       return -1; // 返回-1表示b大
   }

   else {
       for(int i = bit_count_a; i < len_a-1; i ++) {
	       if(a[i] > m[i]) {
//	   printf(">\n");
		       return 1;
		   }

	       else if(a[i] < m[i]) {
//	   printf("<\n");
		       return -1;
		   }
	   }
//	   printf("=\n");
	   return 0;
   }
}

static inline char* minus(char* res, char* m, int len) { // 默认a>b才能减
    for(int i = 0; i < len-1; i ++) {
		int bit_res = res[len-1-1-i];
		int bit_m = m[len-1-1-i];
		int gap = bit_res-bit_m;

        if(gap >= 0) {
		    res[len-1-1-i] = '0' + gap;
		}
                   
		else {
            int index = 1;
			while(res[len-1-1-i-index] == '0') {
                index ++;
			}

            res[len-1-1-i-index] -= 1;
			    index --;
 
				for(; index > 0; index --) {
                    res[len-1-1-i-index] = '9';
				   }

				   res[len-1-1-i] = '0' + gap + 10;
	   }
       //printf("-----------temp res:%s-------------\n", res);
   }
   return res;
}

static inline char* back_bit(char* res, int len) {
	char new[len];
	for(int i = 0; i < len; i ++) {
		new[i] = '0';
	}
	new[len-1] = '\0';

	int index = 0;
	while(res[index] == '0') {
		index ++;
	}

	for(int i = 0; i < len-index - 1; i ++) {
		new[index + 1 + i] = res[index+i];
	}
    new[len-1] = '\0';

    for(int i = 0; i < len; i ++) {
        res[i] = new[i];
    }

	return res;

}

static inline char* minuspro(char* res, char* m, int len) { // 默认res和m字符串的长度相等
    int index_m = 0;
	while(m[index_m] == '0') {
        index_m ++;
	}

    int index_res = 0;
	while(res[index_res] == '0') {
        index_res ++;
	}

   char temp_m[len];
   temp_m[len-1] = '\0';

   for(int i = 0; i < len; i ++) {
	   temp_m[i] = '0';
   } 

   for(int i = 0; i < len - index_m - 1; i ++) {
       temp_m[index_res+i] = m[index_m+i];
   }

   char* minus_factor = temp_m;
   while(compare(res, len, m, len) >= 0) {
//	   printf("******OUTER:%s******\n",minus_factor);
//	   printf("******OUTER:%s******\n",res);
       while(compare(res, len, minus_factor, len) == 1) {
	       res = minus(res, minus_factor, len);
//		   printf("-------INNER:%s------\n",res); 
       } 
	   minus_factor = back_bit(minus_factor, len);
   }
   return res;

}

int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {

	int64_t res = 0;

//	struct timeval tv0;
//	gettimeofday(&tv0, NULL);
	//printf("%lds\t%ldms\n", tv0.tv_usec, tv0.tv_sec);
	
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
//		   printf("------------------\n");
//		   printf("a_m:%ld\n",a_m);
//		   printf("b_m:%ld\n",b_m);
	//	   printf("mul:%ld\n",a_m*b_m);
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
	   //char temp_res[len_a_m+len_b_m+1];
	   
	   for(int i = 0; i < len_a_m + len_b_m; i ++) {
	       str_res[i] = '0';
	   }
	   str_res[len_a_m + len_b_m] = '\0';
	   
	   /*
	   for(int i = 0; i < len_a_m + len_b_m; i ++) {
	       temp_res[i] = '0';
	   }
	   temp_res[len_a_m + len_b_m] = '\0';
       */

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

       char* str_res_final;
       str_res_final = multi(str_a_m, len_a_m+1, str_b_m, len_b_m+1, str_res, len_a_m+len_b_m+1);
//	   printf("res:%s\n",str_res_final);

       
	   char str_m[len_a_m+len_b_m+1];

	   for(int i = 0; i < len_a_m + len_b_m; i ++) { //对应于上面一行的每一位
	       str_m[i] = '0';
	   }
	   str_m[len_a_m + len_b_m] = '\0'; //由于竖式实际上是将下面的数的每一位去乘上面的数，因此，先把储存乘出来结果的数组清空

	   temp = m;
	   for(int i = 0; i < len_a_m+len_b_m; i ++) {
	       str_m[len_a_m + len_b_m - i - 1] = (temp % 10) + '0';
		   temp /= 10;
	   }

       //char* temp_res = str_res;   
	   /*
	   while(compare(str_res, len_a_m+len_b_m+1, str_m, len_a_m+len_b_m+1) >= 0) {
	       if(compare(str_res, len_a_m+len_b_m+1, str_m, len_a_m+len_b_m+1) == 0) {
		       res = 0;
		   }
		  
		   else {
			   temp_res = minus(temp_res, str_m, len_a_m+len_b_m+1);			   
	   //printf("temp left:%s\n",temp_res);
		       }
	   }
	   */
	  char* left = minuspro(str_res_final, str_m, len_a_m+len_b_m+1);
	  //printf("%s\n",left);
	  res = str_to_int(left);
	   

       //printf("mod_str:%s\n", str_m); 
       //printf("mod_val:%ld\n", m); 
	  // }
	   
	   }
	}
       
  // TODO: implement
 //	struct timeval tv1;
//	gettimeofday(&tv1, NULL);
//	printf("%ldms\n", tv1.tv_usec-tv0.tv_usec);
  printf("JJJJJJJJJJJJJJJJJJJ\n");
  return res;
}


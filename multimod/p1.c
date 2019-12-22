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

	   char str_a_m[len_a_m];
	   char str_b_m[len_b_m];
	   char str_res[len_a_m + len_b_m];
	   
	   for(int i = 0; i < len_a_m + len_b_m; i ++) {
	       str_res[i] = '0';
	   }
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
	   for(int i = 0; i < len_b_m; i ++) {
	       char bit_b = str_b_m[len_b_m-1-i];
		   for(int j = 0; j < len_a_m; j ++) {
		       char bit_a = str_a_m[len_a_m-1-j];
			   int res = (bit_a - '0') * (bit_b - '0');
			   
			   if(str_res[len_a_m+len_b_m-1-i-j] + res <= '9') {
			       str_res[len_a_m+len_b_m-1-i-j] += res;
			   }	   
			   else {
			       str_res[len_a_m+len_b_m-1-i-j] = res - ':' + str_res[len_a_m+len_b_m-1-i-j];
                   str_res[len_a_m+len_b_m-1-i-j-1] += 1;
			   }
		   }
	   }
	   }
	   }
       
       printf("multi:%s\n", str_res); 
  // TODO: implement
  return res;
}


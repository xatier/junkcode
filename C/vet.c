#include <stdio.h> 
#include <stdlib.h> 
 
int main (void) { 
    int i, j = 1, sum, check; 
    char inp[10], a[] = { 10, 11, 12, 13, 14, 15,
                          16, 17, 34, 18, 19, 20,
                          21, 22, 35, 23, 24, 25, 
                          26,27,28,29,32,30,31,33
                        }; 
                                            //因為規則不規律只好土法煉鋼QQ 
    while (inp[0] != 'q' && inp[0] != 'Q') { 
        scanf("%s", inp);                   //輸入並檢查是否結束 
 
        i = inp[0] - 'A';                        //計算加權後總和 
        sum = 9 * (a[i] - 10*(a[i]/10)) + a[i]/10; 
        for (j = 1; j < 9; j++) { 
            sum += j * (inp[9-j] - '0'); 
        } 
 
        check = sum % 10;                       //檢查檢查號碼 
        if (check == 58-inp[9]) { 
            printf("%s合格~0.0~\n", inp); 
        } 
        else { 
            printf("%s不合格~0.0~\n", inp); 
        } 
    } 
    return 0; 
} 


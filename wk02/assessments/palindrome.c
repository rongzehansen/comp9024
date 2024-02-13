/** Algorithm & Complexity Analysis
 *
 * isPalindrome(A):
 *
 * Input:  array A of n characters
 * Output: 0 or 1
 *
 * Statement                                # primitive operations
 * ----------------------------------------------------
 * lidx=0, ridx=n-1                         1
 * while ridx>lidx do                       n/2+1  
 *      if str[lidx++]!=str[ridx--] then    (2+2+1)*(n/2) = 5n/2
 *          return false
 *      end if
 * end while
 * return true                              1
 * ----------------------------------------------------
 * Total: 3n+1, which is O(n)
 *
 **/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPalindrome(char *str) {
    int lidx = 0;
    int ridx = strlen(str) - 1;
    
    while (ridx > lidx) {
        if (str[lidx++] != str[ridx--]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    char str[BUFSIZ];

    printf("Enter a word: ");
    scanf("%s", str);
    
    if (isPalindrome(str)) {
        printf("yes\n");
    } 
    else {
        printf("no\n");
    }
    return 0;
}

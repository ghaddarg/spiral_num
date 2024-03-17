#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define DEBUG 1
#ifdef DEBUG
#define ENTER(x, y)    do {\
                            printf("%s:ENTER(%d)\n", x, y);\
                       } while(0)
#define EXIT(x, y)    do {\
                            printf(x);\
                            printf(":EXIT(%d)\n", y);\
                         } while(0)
#else

#define ENTER(x, y)
#define EXIT(x, y)

#endif

enum state_t {
    STATE_START = 0,
    STATE_HORIZENTAL,
    STATE_VERTICAL,
    STATE_HORIZENTAL_OPPOSITE,
    STATE_VERTICAL_OPPOSITE,
    STATE_END
};

void print_matrix(int ** matrix, int size)
{
    if (!matrix)
        return;

    printf("[\n");
    for (int i = 0; i < size; ++i) {
        printf("\t[");
        for (int j = 0; j < size; ++j) {
            printf("%d, ", matrix[i][j]);
        }
        printf("],\n");
    }
    printf("]\n");
}

int ** solution(int n)
{
    ENTER(__func__, n);

    //XXX: dynamic allocation to be freed in main
    int ** ret = NULL;
    ret = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; ++i)
        ret[i] = (int *)malloc(sizeof(int) * n);
    
    enum state_t state = STATE_START;
    int count = 0, idx_h = 0, idx_v = 1;
    //bool flag = false, flag_2 = false;
    
    while (count < (n * n)) {
        
        switch(state) {
            
            case STATE_START: {
                
                state = STATE_HORIZENTAL;
                break;
            }
            
            case STATE_HORIZENTAL: {
                
                int i = idx_h;
                for (int j = idx_h; j < n - idx_h; ++j)
                    ret[i][j] = ++count;
                
                if (count >= (n * n))
                    state = STATE_END;
                else
                    state = STATE_VERTICAL;
                
                break;
            }
                
            case STATE_VERTICAL: {
                
                for (int i = idx_v; i <= n - idx_v; ++i)
                    ret[i][n - idx_v] = ++count;
                    
                state = STATE_HORIZENTAL_OPPOSITE;
                // ===> DEBUG FLAG <===
                /*printf("idx_h %d - idx_v %d\n", idx_h, idx_v);
                if (flag && flag_2)
                    state = STATE_END;*/
                // ===> DEBUG FLAG <===
                break;
            }
            
            case STATE_HORIZENTAL_OPPOSITE: {
                
                int i = n - idx_h - 1;
                for (int j = n - idx_h - 2; j >= idx_h ; --j)
                    ret[i][j] = ++count;
                state = STATE_VERTICAL_OPPOSITE;
                break;
            }
            
            case STATE_VERTICAL_OPPOSITE: {
                
                for (int i = n - idx_v - 1; i >= idx_v; --i)
                    ret[i][idx_v - 1] = ++count;
                ++idx_h;
                ++idx_v;
                state = STATE_HORIZENTAL;
                
                // ===> DEBUG FLAG <===
                /*if (flag)
                    flag_2 = true;
                flag = true;*/
                // ===> DEBUG FLAG <===
                
                break;
            }
                
            case STATE_END: {
                goto out;
                break;
            }
        }
    }
    
out:
    EXIT(__func__, ret != NULL);    
    return ret;
}

/*************************************/
/*              MAIN                 */
/*************************************/
int main(void)
{
    printf("HELLO SPIRAL NUM WORLD\n");
    int n = 6;
    int ** actual_output = NULL;
    bool fail = false;

    actual_output = solution(n);
    print_matrix(actual_output, n);

    char expected_outputt[6][6] = {
                                    {1,2,3,4,5,6},
                                    {20,21,22,23,24,7}, 
                                    {19,32,33,34,25,8}, 
                                    {18,31,36,35,26,9}, 
                                    {17,30,29,28,27,10}, 
                                    {16,15,14,13,12,11}
                                  };

    printf("Test: ");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (actual_output[i][j] != expected_outputt[i][j]) {
                fail = true;
                break;
            }
        }
    }

    if (fail)
        printf("FAIL\n");
    else
        printf("PASS\n");

    if (actual_output) {
        for (int i = 0; i < n; i++) {
            if (actual_output[i])
                free(actual_output[i]);
        }
        free(actual_output);
    }

    printf("GDBYE CHESS WORLD\n");
    return n;
}
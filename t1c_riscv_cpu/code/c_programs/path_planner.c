
/*
* EcoMender Bot (EB): Task 2B Path Planner
*
* This program computes the valid path from the start point to the end point.
* Make sure you don't change anything outside the "Add your code here" section.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#define V 32

#ifdef __linux__ // for host pc

    #include <stdio.h>

    void _put_byte(char c) { putchar(c); }

    void _put_str(char *str) {
        while (*str) {
            _put_byte(*str++);
        }
    }

    void print_output(uint8_t num) {
        if (num == 0) {
            putchar('0'); // if the number is 0, directly print '0'
            _put_byte('\n');
            return;
        }

        if (num < 0) {
            putchar('-'); // print the negative sign for negative numbers
            num = -num;   // make the number positive for easier processing
        }

        // convert the integer to a string
        char buffer[20]; // assuming a 32-bit integer, the maximum number of digits is 10 (plus sign and null terminator)
        uint8_t index = 0;

        while (num > 0) {
            buffer[index++] = '0' + num % 10; // convert the last digit to its character representation
            num /= 10;                        // move to the next digit
        }
        // print the characters in reverse order (from right to left)
        while (index > 0) { putchar(buffer[--index]); }
        _put_byte('\n');
    }

    void _put_value(uint8_t val) { print_output(val); }

#else  // for the test device

    void _put_value(uint8_t val) { }
    void _put_str(char *str) { }

#endif

// main function
int main(int argc, char const *argv[]) {

    #ifdef __linux__

        const uint8_t START_POINT   = atoi(argv[1]);
        const uint8_t END_POINT     = atoi(argv[2]);
        uint8_t NODE_POINT          = 0;
        uint8_t CPU_DONE            = 0;

    #else
        // Address value of variables for RISC-V Implementation
        #define START_POINT         (* (volatile uint8_t * ) 0x02000000)
        #define END_POINT           (* (volatile uint8_t * ) 0x02000004)
        #define NODE_POINT          (* (volatile uint8_t * ) 0x02000008)
        #define CPU_DONE            (* (volatile uint8_t * ) 0x0200000c)

    #endif

    // array to store the planned path
    uint8_t path_planned[32];
    // index to keep track of the path_planned array
    uint8_t idx = 0;

    /* Functions Usage

    instead of using printf() function for debugging,
    use the below function calls to print a number, string or a newline

    for newline: _put_byte('\n');
    for string:  _put_str("your string here");
    for number:  _put_value(your_number_here);

    Examples:
            _put_value(START_POINT);
            _put_value(END_POINT);
            _put_str("Hello World!");
            _put_byte('\n');
    */

    // ############# Add your code here #############
    // prefer declaring variable like this
    #ifdef __linux__
        uint32_t graph[32] ={20711,10312,2040506,3,3,3,1080910,7,7,7,1122527,2111321,121415,13,131617,15,151819,17,172022,121921,20,192324,22,222531,112426,25,112829,27,273031,29,242932,31};
        uint32_t temp = START_POINT;
        uint32_t nodes_visited[32];
        idx = 1;
        uint32_t len = 1;
        uint32_t best = START_POINT;
        uint32_t flag = 0;
        path_planned[0] = START_POINT;
        nodes_visited[0] = START_POINT;
        while(true){
            uint32_t neighbours = graph[temp];
            while(neighbours > 0){
                best = path_planned[idx - 1];
        uint32_t node = neighbours%100 - 1;
        neighbours /= 100;
        for(int i = 0;i<len;i++){
            if(node == nodes_visited[i]){ flag = 0;
               if( node == path_planned[idx - 2] && neighbours == 0 ){
                best = node;
                //nodes_visited[i] = nodes_visited[i+1]; len-=1;
                idx -= 2;
                nodes_visited[i] = nodes_visited[i+1]; }
             break;}
            else{ flag = 1;}
            }
        if(flag){ 
            
            if(node == END_POINT || abs(node - END_POINT)< abs(best - END_POINT)){ best = node;
            break;
            }
            best = node;
            }
        
    }
            temp = best;
    path_planned[idx] = temp;
    idx+=1;
    nodes_visited[len] = temp;
    len+=1;
    if(temp == END_POINT) break;     
            }
    #else
        uint32_t *graph = (uint32_t *) 0x02000010;
    #endif

    // ##############################################

    // the node values are written into data memory sequentially.
    for (int i = 0; i < idx; ++i) {
        NODE_POINT = path_planned[i];
    }
    // Path Planning Computation Done Flag
    CPU_DONE = 1;

    #ifdef __linux__    // for host pc

        _put_str("######### Planned Path #########\n");
        for (int i = 0; i < idx; ++i) {
            _put_value(path_planned[i]);
        }
        _put_str("################################\n");

    #endif

    return 0;
}




#include "poker.h"

int main() {
    srand((unsigned)time(NULL));


    const char* stats_file = "poker_stats.txt";
    load_stats_from_file(stats_file);

    
    P_card P1[5];
    P_card BoT[5];


    start_program(P1, BoT, stats_file);
    
   
    save_stats_to_file(stats_file);
    return 0;
}
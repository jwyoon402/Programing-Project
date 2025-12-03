#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>



typedef struct {
    char p_suit[10]; // 카드 문양
    int p_rank;      // 카드 숫자
} P_card;

typedef struct {    // 구조체 CR : 숫자가 몇 개 있는지와 그 숫자를 저장
    int cnt; 
    int rank; 
} CR;

void start_program(P_card* P, P_card* B, char* stats_file);

void menu(int* select);
void start_game(P_card* P, P_card* B);
void continue_game(P_card* P);
void end_game(P_card* P, P_card* B);

void print_poker_hand_explanations();

void player_card(P_card* P);
void sort_cards(P_card* P, int size);
int suit_value(const char* suit);
void print_hand(P_card* P);
void change_card(P_card* P, int a);

// 포커 족보 판별 함수
int is_flush(P_card* P);
int is_straight(P_card* P);
int count_rank(P_card* P, int num);
int check_hand(P_card* P);
void print_hand_result(int result);

void print_match_result(P_card* P, P_card* B, int player, int bot);
int compare_hands(P_card* P, P_card* B, int playerRank, int botRank);
int highest_suit_of_rank(P_card* P, int rank);
int build_tiebreaker(P_card* P, int hand_rank, int tiebreak[]);

//통계 작성 함수
void load_stats_from_file(const char* filename);
void save_stats_to_file(const char* filename);
void update_stats(int hand_rank, int winner);
void print_stats_console();

//나만의 기능
void Swap_cards(P_card* P, P_card* B);
void show_cards(P_card* B);

void use_item(P_card* P, P_card* B, int* item_count);
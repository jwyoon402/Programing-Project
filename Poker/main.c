#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "poker.h"

typedef struct {
	char p_suit[10]; //플레이어의 카드 문양
	int p_rank;	//플레이어의 카드
}P_card;

int main() {
	srand((unsigned)time(NULL));
	P_card P1[5];
	
	char suit[4][10] = { "spade", "diamond", "clover", "heart" };
	char* suit_p = suit;
	for (int i = 0;i < 5;i++) {
		P1[i].p_rank = rand() % 13 + 1;	// 플레이어 카드의 랭크 5개 넣기
		int j = rand() % 4;
		strcpy(P1[i].p_suit, suit_p + sizeof(suit[0]) * j);	//플레이어 카드의 문양 5개 선정
	}
	for (int i = 0;i < 5;i++) {
		printf("| %s %d |", P1[i].p_suit, P1[i].p_rank);	//플레이어의 카드 출력
	}
}
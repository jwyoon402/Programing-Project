#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char p_suit[10]; // 카드 문양
    int p_rank;      // 카드 숫자
} P_card;

void player_card(P_card* P);
void sort_cards(P_card* P, int size);
int suit_value(const char* suit);

// 포커 족보 판별 함수
int is_flush(P_card* P);
int is_straight(P_card* P);
int count_rank(P_card* P, int num);
int check_hand(P_card* P);
void print_hand_result(int result);

int main() {
    srand((unsigned)time(NULL));
    P_card P1[5];
    player_card(P1);

    // 정렬 실행
    sort_cards(P1, 5);

    // 출력
    for (int i = 0; i < 5; i++) {
        printf("| %s %d |", P1[i].p_suit, P1[i].p_rank);
    }
    printf("\n");

    int result = check_hand(P1);
    print_hand_result(result);

    return 0;
}

// 카드 5장 생성
void player_card(P_card* P) {
    char suit[4][10] = { "spade", "diamond", "clover", "heart" };
    for (int i = 0; i < 5; i++) {
        P[i].p_rank = rand() % 13 + 1; // 1~13
        int j = rand() % 4;
        strcpy(P[i].p_suit, suit[j]);
    }
}

// 문양 우선순위 반환
int suit_value(const char* suit) {
    if (strcmp(suit, "spade") == 0) return 0;
    if (strcmp(suit, "diamond") == 0) return 1;
    if (strcmp(suit, "clover") == 0) return 2;
    if (strcmp(suit, "heart") == 0) return 3;
    return 4; // 이외는 가장 뒤
}

// 버블 정렬
void sort_cards(P_card* P, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {

            // 1차 정렬: p_rank 오름차순
            if (P[j].p_rank > P[j + 1].p_rank) {
                P_card temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }

            // 같은 rank이면 문양 우선순위로 비교
            else if (P[j].p_rank == P[j + 1].p_rank) {
                if (suit_value(P[j].p_suit) > suit_value(P[j + 1].p_suit)) {
                    P_card temp = P[j];
                    P[j] = P[j + 1];
                    P[j + 1] = temp;
                }
            }

        }
    }
}

// ---- 포커 족보 판정 함수 ----

// 같은 문양인지 검사
int is_flush(P_card* P) {
    for (int i = 1; i < 5; i++) {
        if (strcmp(P[0].p_suit, P[i].p_suit) != 0)
            return 0;
    }
    return 1;
}

// 연속된 숫자인지 검사
int is_straight(P_card* P) {
    for (int i = 0; i < 4; i++) {
        if (P[i].p_rank + 1 != P[i + 1].p_rank)
            return 0;
    }
    return 1;
}

// 같은 숫자 카드 개수 계산
int count_rank(P_card* P, int num) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (P[i].p_rank == num) count++;
    }
    return count;
}

// 전체 족보 판정
int check_hand(P_card* P) {
    int straight = is_straight(P);
    int flush = is_flush(P);

    if (straight && flush && P[0].p_rank == 10) return 9;         // 로얄 스트레이트 플러쉬
    if (straight && flush) return 8;                              // 스트레이트 플러쉬

    for (int i = 1; i <= 13; i++)
        if (count_rank(P, i) == 4) return 7;                      // 포 카드

    int three = 0, pair = 0;
    for (int i = 1; i <= 13; i++) {
        int cnt = count_rank(P, i);
        if (cnt == 3) three++;
        if (cnt == 2) pair++;
    }

    if (three && pair) return 6;                                  // 풀 하우스
    if (flush) return 5;                                          // 플러쉬
    if (straight) return 4;                                       // 스트레이트
    if (three) return 3;                                          // 쓰리 카드
    if (pair == 2) return 2;                                      // 투페어
    if (pair == 1) return 1;                                      // 원페어

    return 0;                                                     // 하이카드
}

// 결과 출력
void print_hand_result(int result) {
    char* names[] = {
        "High Card", "One Pair", "Two Pair", "Three of a Kind",
        "Straight", "Flush", "Full House", "Four of a Kind",
        "Straight Flush", "Royal Straight Flush"
    };
    printf("\n▶ Hand: %s\n", names[result]);
}
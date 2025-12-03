#include "poker.h"

#define HAND_TYPES 10

int stats_hand_count[HAND_TYPES] = { 0 };
int stats_win_count[HAND_TYPES] = { 0 };
const char* stats_rank_name[HAND_TYPES] = {
    "High Card",
    "One Pair",
    "Two Pair",
    "Three of a Kind",
    "Straight",
    "Flush",
    "Full House",
    "Four of a Kind",
    "Straight Flush",
    "Royal Flush"
};

//프로그램 실행
//프로그램 시작
void start_program(P_card* P, P_card* B, char* stats_file) {
    int select = -1;
    int* menu_select = &select;
    int stop = 1;

    while (select) {
        stop = 1;
        if (select == 0) {
            printf("프로그램 종료.");
            return 0;
        }
        menu(menu_select);
        switch (select) {
        case 1:

            while (stop) {
                start_game(P, B);   //게임 시작
                end_game(P, B); //게임 결과

                printf("\n\n게임을 멈추려면 0을 입력하세요. 다시 한다면 자연수 입력: ");
                scanf("%d", &stop);
                system("cls");
            }
            break;

        case 2:
            print_poker_hand_explanations();    //게임 설명
            printf("\n\n돌아가려면 아무 정수나 입력하세요(): ");
            scanf("%d", &stop);
            system("cls");
            break;

        case 3:
            print_stats_console(stats_file);    //통계 출력

            printf("\n\n돌아가려면 아무 정수나 입력하세요(): ");
            scanf("%d", &stop);
            system("cls");
            break;

        case 4:
            printf("프로그램 종료.");
            return 0;

        default:
            printf("메뉴에 없는 번호를 입력하셨습니다. 다시 입력해주세요.");
            Sleep(3000);
            system("cls");
            break;
        }
    }
}

//게임 시작
void start_game(P_card* P, P_card* B) {
    int item[2]; 
    for (int i = 0;i < 2;i++) item[i] = rand() % 2;


    player_card(P); //랜덤 카드 생성
    player_card(B);


    printf("<현재 아이템 개수>\n");
    printf("▶ 1. 상대방과 덱 교체: %d개\n", item[0]);
    printf("▶ 2. 상대 덱 새로 만들기: %d개\n", item[1]);
    Sleep(3000);
    system("cls");


    continue_game(P);

    use_item(P, B, item);   //아이템 사용
    

    printf("그럼 결과는 !!");
    Sleep(3000);
    system("cls");

}

//게임 진행
void continue_game(P_card* P) {
    int a;
    int z = 5;
    while (z) {
        print_hand(P);  // 출력

        printf("교체할 카드를 알려주세요. (남은 횟수: %d) (교체종료: 0): ", z);
        scanf("%d", &a);
        system("cls");
        if (a == 0) break;
        
        switch (a) {
        case 1:
            change_card(P, a);
            break;
        case 2:
            change_card(P, a);
            break;
        case 3:
            change_card(P, a);
            break;
        case 4:
            change_card(P, a);
            break;
        case 5:
            change_card(P, a);
            break;
        default:
            break;
        }

        z--;
    }

    sort_cards(P, 5);  // 정렬 실행
}

//게임 결과
void end_game(P_card* P, P_card* B) {
    int tmp = 0;
    printf("<결과> \n");
    printf("플레이어: ");
    print_hand(P);  // 출력
    int result = check_hand(P);
    print_hand_result(result);

    printf("\n");
    printf("상대: ");
    print_hand(B);
    int bot_result = check_hand(B);
    print_hand_result(bot_result);

    printf("\n<승부 판정>\n");
    print_match_result(P, B, result, bot_result);
}

//주요 기능
// 카드 5장 생성
void player_card(P_card* P) {
    char suit[4][10] = { "♤", "◇", "♧", "♡" };

    for (int i = 0; i < 5; i++) {
        while (1) {
            int r = rand() % 13 + 2;
            int s = rand() % 4;

            int duplicate = 0;
            for (int j = 0; j < i; j++) {
                if (P[j].p_rank == r && strcmp(P[j].p_suit, suit[s]) == 0) {
                    duplicate = 1;
                    break;
                }
            }

            if (!duplicate) {
                P[i].p_rank = r;
                strcpy(P[i].p_suit, suit[s]);
                break; // 중복 아니면 루프 탈출
            }
        }
    }
    sort_cards(P, 5);   //버블 정렬
}

// 문양 우선순위 반환
int suit_value(const char* suit) {
    if (strcmp(suit, "♤") == 0) return 0;
    if (strcmp(suit, "◇") == 0) return 1;
    if (strcmp(suit, "♧") == 0) return 2;
    if (strcmp(suit, "♡") == 0) return 3;
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

void print_hand(P_card* P) {
    char p_rank_alpha[4] = { 'A', 'J','Q','K' };
    for (int i = 0; i < 5; i++) {
        switch (P[i].p_rank) {
        case 14:
            printf("| %s %c | ", P[i].p_suit, p_rank_alpha[0]);
            break;
        case 11:
            printf("| %s %c | ", P[i].p_suit, p_rank_alpha[1]);
            break;
        case 12:
            printf("| %s %c | ", P[i].p_suit, p_rank_alpha[2]);
            break;
        case 13:
            printf("| %s %c | ", P[i].p_suit, p_rank_alpha[3]);
            break;
        default:
            printf("| %s %d | ", P[i].p_suit, P[i].p_rank);
        }
    }
    printf("\n");
}

void change_card(P_card* P, int a) {
    char suit[4][10] = { "♤", "◇", "♧", "♡" };
    while (1) {
        int r = rand() % 13 + 2;
        int s = rand() % 4;

        int duplicate = 0;
        for (int i = 0; i < 5; i++) {
            if (P[i].p_rank == r && strcmp(P[i].p_suit, suit[s]) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            P[a - 1].p_rank = r;
            strcpy(P[a - 1].p_suit, suit[s]);
            break; // 중복 아니면 루프 탈출
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

    for (int i = 2; i <= 14; i++)
        if (count_rank(P, i) == 4) return 7;                      // 포 카드

    int three = 0, pair = 0;
    for (int i = 2; i <= 14; i++) {
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

// 족보 결과 출력
void print_hand_result(int result) {
    char* names[] = {
        "High Card", "One Pair", "Two Pair", "Three of a Kind",
        "Straight", "Flush", "Full House", "Four of a Kind",
        "Straight Flush", "Royal Straight Flush"
    };
    printf("▶ Hand: %s\n", names[result]);
}


// ------------------------------------------------------------
//  족보 비교
//  같은 족보면 각 숫자 빈도 기반 tiebreaker 생성
//  숫자 비교 후에도 같으면 문양(suit_value) 비교
// ------------------------------------------------------------

// rank 빈도 기반으로 비교 우선순위(tiebreaker)를 생성해주는 함수
// 예) 포카드 → [포카드 숫자, 킥커]
//     풀하우스 → [트리플 숫자, 페어 숫자]
//     투페어 → [높은 페어, 낮은 페어, 킥커]
//     그 외 → 숫자를 큰 순서대로 나열
int build_tiebreaker(P_card* P, int hand_rank, int tiebreak[]) {

    int counts[15] = { 0 }; // 2~14(=A) 카드 숫자 개수를 저장
    for (int i = 0; i < 5; i++) counts[P[i].p_rank]++;

    CR vec[13];
    int v = 0;
    CR tmp;

    // 큰 숫자부터 vec에 추가
    for (int r = 14; r >= 2; r--) {
        if (counts[r] > 0) {
            vec[v].cnt = counts[r];
            vec[v].rank = r;
            v++;
        }
    }

    // vec를 정렬 — 개수 큰 순(cnt desc) → 숫자 큰 순(rank desc)
    
    for (int i = 0; i < v - 1; i++) {
        for (int j = i + 1; j < v; j++) {
            if (vec[j].cnt > vec[i].cnt ||
                (vec[j].cnt == vec[i].cnt && vec[j].rank > vec[i].rank)) {
                tmp = vec[i];
                vec[i] = vec[j]; 
                vec[j] = tmp;
            }
        }
    }


    int idx = 0;
    // 포카드
    if (hand_rank == 7) {
        tiebreak[idx++] = vec[0].rank; // 4장의 숫자
        // 포카드의 킥커 찾기
        for (int r = 14; r >= 2; r--)
            if (counts[r] == 1) {
                tiebreak[idx++] = r;
                break;
            }
        return idx;
    }

    // 풀하우스
    else if (hand_rank == 6) {
        tiebreak[idx++] = vec[0].rank; // 트리플 숫자
        tiebreak[idx++] = vec[1].rank; // 페어 숫자
        return idx;
    }

    // 트리플
    else if (hand_rank == 3) {
        tiebreak[idx++] = vec[0].rank; // 트리플 숫자
        // 나머지 킥커 2개 큰 순
        for (int r = 14; r >= 2; r--)
            if (counts[r] == 1)
                tiebreak[idx++] = r;
        return idx;
    }

    // 투페어
    else if (hand_rank == 2) {
        // vec[0], vec[1]이 페어 두 개 → 이미 정렬되어 있음
        tiebreak[idx++] = vec[0].rank; // 높은 페어
        tiebreak[idx++] = vec[1].rank; // 낮은 페어

        // 킥커
        for (int r = 14; r >= 2; r--)
            if (counts[r] == 1) {
                tiebreak[idx++] = r;
                break;
            }
        return idx;
    }

    // 원페어
    else if (hand_rank == 1) {
        tiebreak[idx++] = vec[0].rank; // 페어 숫자
        // 나머지 3장 큰 순
        for (int r = 14; r >= 2; r--)
            if (counts[r] == 1)
                tiebreak[idx++] = r;
        return idx;
    }

    // 하이카드 / 플러시 / 스트레이트 / 스트레이트플러시 / 로열
    // 숫자를 높은 순서대로 비교
    else {
        for (int r = 14; r >= 2; r--)
            if (counts[r] > 0)
                tiebreak[idx++] = r;
        return idx;
    }
}

// 특정 숫자(rank)에 대해 **해당 숫자 카드 중에서 문양 순위가 가장 높은 것**을 반환
int highest_suit_of_rank(P_card* P, int rank) {
    int best = -1;
    for (int i = 0; i < 5; i++) {
        if (P[i].p_rank == rank) {
            int sv = suit_value(P[i].p_suit);
            if (sv > best) best = sv;
        }
    }
    return best;
}

// 두 핸드를 실제로 비교하는 함수
// 반환값: 1(플레이어 승), -1(상대 승), 0(무승부)
int compare_hands(P_card* P, P_card* B, int playerRank, int botRank) {

    // 1) 족보 자체가 다르면 큰 쪽이 즉시 승리
    if (playerRank > botRank) return 1;
    if (playerRank < botRank) return -1;

    // 2) 같은 족보일 때 tiebreaker 생성
    int tbP[5], tbB[5];
    int lenP = build_tiebreaker(P, playerRank, tbP);
    int lenB = build_tiebreaker(B, botRank, tbB);
    int len = (lenP < lenB ? lenP : lenB);

    // tiebreaker를 차례대로 비교
    for (int i = 0; i < len; i++) {
        if (tbP[i] > tbB[i]) return 1;
        if (tbP[i] < tbB[i]) return -1;
    }

    // 3) 숫자가 완벽히 모두 같으면 문양(suit) 비교
    int key_rank = tbP[0]; // 비교의 핵심이 되는 숫자
    int suitP = highest_suit_of_rank(P, key_rank);
    int suitB = highest_suit_of_rank(B, key_rank);

    if (suitP > suitB) return 1;
    if (suitP < suitB) return -1;

    // 4) 숫자도 문양도 완전히 동일 → 무승부
    return 0;
}

// 최종 출력 담당 함수
void print_match_result(P_card* P, P_card* B, int player, int bot) {
    int cmp = compare_hands(P, B, player, bot);

    if (cmp == 1) {
        printf("플레이어 승");
        update_stats(player, cmp);
    }
    else if (cmp == -1) {
        printf("상대의 승리");
        update_stats(player, cmp);
    }
    else {
        printf("무승부");
        update_stats(player, cmp);
    }
    
}


//통계 작성 관련 함수
// 한 판 결과로 통계 갱신 (hand_rank: 0..9, winner: 1=플레이어, -1=봇, 0=무승부)
void update_stats(int hand_rank, int winner) {
    if (hand_rank < 0 || hand_rank >= HAND_TYPES) return;
    stats_hand_count[hand_rank]++;
    if (winner == 1) stats_win_count[hand_rank]++;
}

// 파일에서 통계 읽기 (사람용 포맷 + ###DATA### 블록 지원)
void load_stats_from_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return; // 파일 없으면 초기값(0) 유지

    char line[512];
    int found_data = 0;

    // 초기화
    for (int i = 0; i < HAND_TYPES; ++i) {
        stats_hand_count[i] = 0;
        stats_win_count[i] = 0;
    }

    // DATA 블록을 찾아서(존재하면 그 뒤에서 숫자 읽음)
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "###DATA###", 10) == 0) {
            found_data = 1;
            break;
        }
    }
    if (!found_data) {
        fclose(f);
        return;
    }

    // DATA 블록 이후 읽기 (형식: id count wins)
    while (fgets(line, sizeof(line), f)) {
        int id, cnt, wins;
        if (sscanf(line, "%d %d %d", &id, &cnt, &wins) == 3) {
            if (id >= 0 && id < HAND_TYPES) {
                stats_hand_count[id] = cnt;
                stats_win_count[id] = wins;
            }
        }
    }

    fclose(f);
}

// 사람이 보기 좋게 저장하고, 마지막에 ###DATA### 블록을 덧붙여 다음 실행 시 로드 가능
void save_stats_to_file(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "파일 저장 실패: %s\n", filename);
        return;
    }

    fprintf(f, "=== Poker Statistics ===\n");
    fprintf(f, "%-2s  %-18s %-7s %-7s\n", "ID", "Rank Name", "Count", "Wins");
    fprintf(f, "-------------------------------------------------\n");
    for (int i = 0; i < HAND_TYPES; ++i) {
        fprintf(f, "%-2d  %-18s %-7d %-7d\n", i, stats_rank_name[i], stats_hand_count[i], stats_win_count[i]);
    }

    // DATA 블록 (기계가 읽기 쉬운 포맷)
    fprintf(f, "\n###DATA###\n");
    for (int i = 0; i < HAND_TYPES; ++i) {
        fprintf(f, "%d %d %d\n", i, stats_hand_count[i], stats_win_count[i]);
    }

    fclose(f);
}

// 콘솔에 현재 통계 보기
void print_stats_console() {
    // 콘솔에 표시
    printf("\n==============================\n");
    printf("      Poker Game Statistics\n");
    printf("   (Loaded from previous runs)\n");
    printf("==============================\n\n");

    printf("=== Current Poker Statistics ===\n");
    printf("%-2s  %-18s %-7s %-7s\n", "ID", "Rank Name", "Count", "Wins");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < HAND_TYPES; ++i) {
        printf("%-2d  %-18s %-7d %-7d\n", i, stats_rank_name[i], stats_hand_count[i], stats_win_count[i]);
    }
    printf("\n");
}

//메뉴와 설명
//게임 시작할 때 포커 족보에 대한 설명
void print_poker_hand_explanations() {

    printf("\n==============================\n");
    printf("       Poker Hand Guide\n");
    printf("==============================\n\n");

    printf("0. High Card\n");
    printf("   - 어떤 조합도 없을 때 가장 높은 카드로 승부합니다.\n\n");

    printf("1. One Pair\n");
    printf("   - 같은 숫자 2장이 있는 조합 (예: 7-7)\n\n");

    printf("2. Two Pair\n");
    printf("   - 페어가 두 개 있는 조합 (예: 5-5 과 K-K)\n\n");

    printf("3. Three of a Kind\n");
    printf("   - 같은 숫자 3장이 있는 조합 (예: 6-6-6)\n\n");

    printf("4. Straight\n");
    printf("   - 숫자 5장이 연속되는 조합 (예: 5-6-7-8-9)\n");
    printf("   - A는 1로도 가능 (A-2-3-4-5)\n\n");

    printf("5. Flush\n");
    printf("   - 카드 5장의 문양이 모두 같은 조합\n");
    printf("   - 숫자는 상관 없음\n\n");

    printf("6. Full House\n");
    printf("   - Three of a Kind + One Pair (예: 8-8-8 + 4-4)\n\n");

    printf("7. Four of a Kind\n");
    printf("   - 같은 숫자 4장 (포카드)\n\n");

    printf("8. Straight Flush\n");
    printf("   - 스트레이트 + 플러시 조합\n");
    printf("   - 숫자 연속 + 같은 무늬\n\n");

    printf("9. Royal Flush\n");
    printf("   - 10, J, Q, K, A 로 구성된 스트레이트 플러시\n");
    printf("   - 포커에서 가장 높은 조합\n\n");

    printf("==============================\n\n");

    printf("==========<게임 설명>=========\n\n");
    printf("1. 나와 상대방은 각자 5장의 카드를 갖는다.\n");
    printf("2. 내 카드는 최대 5개 교체할 수 있다.\n");
    printf("3. 아이템 1은 내 모든 카드와 상대의 모든 카드를 바꾸는 것이다.\n");
    printf("4. 아이템 2는 상대방의 카드 중 랜덤으로 한장을 보고난 후 상대의 카드 5장을 새로 할지 정할 수 있다.\n");
    printf("5. 카드 교환과 아이템 사용이 끝나면 승부 결과가 나온다.\n\n");
    printf("==============================\n\n");
}

//메뉴
void menu(int* select) {
    printf("[ M E N U ]\n\n");
    printf("▶ 1. Start\n\n");
    printf("▶ 2. poker hand explanations\n\n");
    printf("▶ 3. Result Statistics\n\n");
    printf("▶ 4. Exit\n\n");
    printf("선택할 메뉴를 선택해주세요: ");
    scanf("%d", select);
    system("cls");
}

//나만의 기능

// 아이템
void use_item(P_card* P, P_card* B, int* item_count) {
    int num_item;
    printf("<현재 아이템 개수>\n");
    printf("▶ 1. 상대방과 덱 교체: %d개\n", *(item_count));
    printf("▶ 2. 상대 덱 새로 만들기: %d개\n\n", *(item_count+1));
    if (*(item_count) > 0 || *(item_count+1) > 0) {
        printf("사용할 아이템의 번호를 입력해주세요.(사용 안함: 0)");
        scanf("%d", &num_item);
        system("cls");
        switch (num_item) {
        case 0:
            printf("아이템 미사용을 선택하셨습니다.");
            Sleep(2500);
            system("cls");
            break;
        case 1:
            if (*(item_count) > 0) {
                Swap_cards(P, B);
                printf("카드가 바뀌었습니다.");
                *(item_count) = 0;
                Sleep(3000);
            }
            else {
                printf("그 아이템은 가지고 있지 않습니다.");
                Sleep(2000);
            }
            system("cls");
            break;

        case 2:
            if (*(item_count + 1) > 0) {
                show_cards(B);
                *(item_count + 1) = 0;
            }
            else printf("그 아이템은 가지고 있지 않습니다.");
            Sleep(3000);
            system("cls");
            break;

        default:
            printf("잘못된 입력입니다. 아이템 사용을 건너뜁니다.\n");
            Sleep(2000);
            system("cls");
            break;
        }
    }
    else {
        printf("아이템은 현재 없습니다. 아이템 사용을 건너뜁니다.\n\n");
        Sleep(2500);
        system("cls");
    }
}

//상대 카드와 내 카드 바꾸기
void Swap_cards(P_card* P, P_card* B) {
    char suit[10];
    int rank;
    for (int i = 0;i < 5;i++) {
        rank = P[i].p_rank;
        (P+i)->p_rank = B[i].p_rank;
        (B+i)->p_rank = rank;
        
        strcpy(suit, P[i].p_suit);
        strcpy(P[i].p_suit, B[i].p_suit);
        strcpy(B[i].p_suit, suit);
    }
    print_hand(P);
}

//상대 카드 한 장 보고 바꾸기
void show_cards(P_card* B) {
    int answer;
    int show = rand() % 5;
    char p_rank_alpha[4] = { 'A', 'J','Q','K' };
    printf("상대방은 ");
    switch (B[show].p_rank) {
    case 14:
        printf("| %s %c | ", B[show].p_suit, p_rank_alpha[0]);
        break;
    case 11:
        printf("| %s %c | ", B[show].p_suit, p_rank_alpha[1]);
        break;
    case 12:
        printf("| %s %c | ", B[show].p_suit, p_rank_alpha[2]);
        break;
    case 13:
        printf("| %s %c | ", B[show].p_suit, p_rank_alpha[3]);
        break;
    default:
        printf("| %s %d | ", B[show].p_suit, B[show].p_rank);
    }
    printf("카드가 있습니다.\n\n");
    printf("바꾸시겠습니까?(Yes: 1, No: 1이 아닌 다른 정수) ");
    scanf("%d", &answer);
    system("cls");
    if (answer == 1) {
        printf("바꾸셨습니다.");
        Sleep(2000);
        system("cls");

        printf("바꾸기 전의 카드는 ");
        print_hand(B);
        printf("였습니다.");
        Sleep(4000);

        player_card(B);

    }
    else printf("바꾸지 않으셨습니다.");
}
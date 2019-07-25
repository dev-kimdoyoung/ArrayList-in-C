#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arraylist.h"
#include "boolean.h"

#define DEFAULT_SIZE 10         // 배열의 default 크기

int main(int argc, char** argv) {
    ArrayList *arraylist = NULL;
    createList(DEFAULT_SIZE);

    return 0;
}

// 최대 n개의 원소를 가지는 공백(empty) 리스트 l을 생성
ArrayList* createList(const int n) {
    ArrayList *arraylist = (ArrayList*)malloc(sizeof(ArrayList));

    // 메모리 할당에 성공하면
    if(arraylist != NULL) {
        arraylist->maxcount = n;        // 배열 최대 개수를 n으로 초기화
        arraylist->currentcount = 0;    // 현재 사용하는 배열 개수를 n으로 초기화
        arraylist->list = NULL;
    }
    // 메모리 할당에 실패하면
    else {
        printf("에러 : arraylist에 대한 동적 메모리 할당 실패\n");
        return NULL;
    }

    // list에 대한 동적 메모리 할당
    arraylist->list = (student*)calloc(arraylist->maxcount, sizeof(student));
    
    // 만약 메모리 할당 성공하면
    if(arraylist->list != NULL) {
        // 할당 받은 메모리 값을 0xFF로 초기화
        memset(arraylist->list, 0xFF, arraylist->maxcount * sizeof(ArrayList));
        for(int i = 0; i < DEFAULT_SIZE; i++) {
            arraylist->list[i].age = EOF;
        }
    }
    // 메모리 할당 실패하면
    else {
        // 에러 메시지 출력
        printf("에러 : list에 대한 동적 메모리 할당 실패");

        // list를 가리키고 있는 arraylist에 대한 메모리를 반환
        free(arraylist);
        arraylist = NULL;
    }
    return arraylist;
}


// 리스트 메모리 반납
void deleteList(ArrayList *arraylist) {

    // list 메모리 반환
    printf("list 메모리 반환 완료\n");
    memset(arraylist->list, 0xFF, arraylist->maxcount * sizeof(arraylist->list));
    free(arraylist->list);
    arraylist->list = NULL;
    
    // arraylist 메모리 반환
    printf("arraylist 메모리 반환 완료\n");
    memset(arraylist, 0xFF, sizeof(arraylist));
    free(arraylist);
    arraylist = NULL;
}


// 원소 추가 가능여부 판단
// 리스트 원소 개수가 최대 원소 개수가 같은지를 반환
_Bool isFull(ArrayList *arraylist) {
    // 만약 arraylist의 현재 원소 개수와 최대 원소 개수가 같다면
    if(arraylist->maxcount == arraylist->currentcount) {
        return TRUE;        // TRUE 리턴
    }
    // 다르다면
    else {
        return FALSE;       // FALSE 리턴
    }
}    


// 원소 추가
// 원소 e를 리스트 l의 특정 위치 p에 추가
_Bool addElement(ArrayList* arraylist, const int p, student student_data) {
    // 만약 arraylist에 메모리 공간이 부족하면
    if(isFull(arraylist) == TRUE) {
        // arraylist의 최대 원소 개수를 DEFAULT_SIZE(10)만큼 추가
        arraylist->maxcount += DEFAULT_SIZE;
        // 메모리 재할당
        arraylist->list = (student*)realloc(arraylist->list, arraylist->maxcount * sizeof(student));
        printf("메모리 재할당 완료\n");
    }
    
  // 해당 위치에 이미 데이터가 존재하면
    if(arraylist->list[p].age != EOF) {
        int count =  getListLength(arraylist);       // count : 현재 요소 개수
        if(count % 10 > 8) {
            arraylist->list = (student*)realloc(arraylist->list, arraylist->maxcount * sizeof(student));
            printf("메모리 재할당 완료\n");
        }

        // 기존에 있는 데이터 오른쪽으로 한 칸씩 shift 
        for(int i = count; i > p; i--) {
            strcpy(arraylist->list[i+1].name, arraylist->list[i].name);
            arraylist->list[i+1].age = arraylist->list[i].age;
            strcpy(arraylist->list[i+1].address, arraylist->list[i].address);
        }
        printf("데이터를 오른쪽으로 밀기\n");
    }

    // 입력받은 데이터를 arraylist에 저장
    strcpy(arraylist->list[p].name, student_data.name);
    arraylist->list[p].age = student_data.age;
    strcpy(arraylist->list[p].address, student_data.address);
    printf("list[%d]에 데이터 저장 완료\n", p);

    arraylist->currentcount += 1;
    printf("현재 노드 개수 : %d\n", arraylist->currentcount);
}

// 원소 제거
// 리스트의 위치 p에 있는 원소를 제거
_Bool removeElement(ArrayList *arraylist, const int p) {

    // 만약 중간 index의 데이터를 삭제하는 경우
    if(arraylist->list[p+1].age != EOF) {
        int count =  getListLength(arraylist);       // count : 현재 요소 개수
    
        strncpy(arraylist->list[p].name, "", 1);
        arraylist->list[p].age = -1;
        strncpy(arraylist->list[p].address, "", 1);
        arraylist->currentcount -= 1;
        printf("list[%d]의 원소 제거 완료\n", p);

        // 기존에 있는 데이터 왼쪽으로 한 칸씩 shift 
        for(int i = p; i < count + 1; i++) {
            strcpy(arraylist->list[i].name, arraylist->list[i+1].name);
            arraylist->list[i].age = arraylist->list[i+1].age;
            strcpy(arraylist->list[i].address, arraylist->list[i+1].address);
        }
        printf("데이터 왼쪽으로 한 칸씩 이동했음\n");
    }
    else {
        strncpy(arraylist->list[p].name, "", 1);
        arraylist->list[p].age = 0;
        strncpy(arraylist->list[p].address, "", 1);
        arraylist->currentcount -= 1;
        printf("list[%d]의 원소 제거 완료\n", p-1);
    }
}       


// 리스트 초기화
// 리스트의 모든 원소를 제거
_Bool clearList(ArrayList *arraylist) {
    for(int i = arraylist->currentcount - 1; i >= 0; i--) {
        strncpy(arraylist->list[i].name, "", 1);
        arraylist->list[i].age = -1;
        strncpy(arraylist->list[i].address, "", 1);
    }
    arraylist->currentcount = 0;
}


// 원소 개수
int getListLength(ArrayList *arraylist) {
    return arraylist->currentcount;
}


// 원소 반환
// 리스트의 위치 p에 있는 원소 출력
_Bool getElement(ArrayList *arraylist, const int p) {
    
    if(arraylist->list[p].age == -1) {
        printf("데이터가 존재하지 않습니다.\n");
        return FALSE;
    }
    printf("이름 : %s\n", arraylist->list[p].name);
    printf("나이 : %d\n", arraylist->list[p].age);
    printf("주소 : %s\n", arraylist->list[p].address);
    return TRUE;
}
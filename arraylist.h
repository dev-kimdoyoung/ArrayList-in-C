/*
    Array List(배열트리스트) 구현
 */
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct _student {
    char name[20];      // 이름
    int age;            // 나이
    char address[100];  // 주소
}student;

typedef struct _ArrayList {
    int currentcount;       // 배열의 현재 개수
    int maxcount;           // 배열의 최대 개수
    student *list;
}ArrayList;

// 최대 n개의 원소를 가지는 공백(empty) 리스트 l을 생성
ArrayList* createList(const int n);

// 리스트 메모리 반납
void deleteList(ArrayList *arraylist);

// 원소 추가 가능여부 판단
_Bool isFull(ArrayList* arrayList);    // 리스트 원소 개수가 최대 원소 개수가 같은지를 반환

// 원소 추가
_Bool addElement(ArrayList* arraylist, const int p, student student);      // 원소 e를 리스트 l의 특정 위치 p에 추가

// 원소 제거
_Bool removeElement(ArrayList* arraylist, const int p);       // 리스트의 위치 p에 있는 원소를 제거

// 리스트 초기화
_Bool clearList(ArrayList* arraylist);       // 리스트의 모든 원소를 제거

// 원소 개수
int getListLength(ArrayList* arraylist);    // 리스트의 원소 개수

// 원소 반환
_Bool getElement(ArrayList* arraylist, const int p);  // 리스트의 위치 p에 있는 원소를 반환
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 6

int queue[MAX];
int front = 0;
int rear = 0;
int itemCount = 0;

int peek() {
   return queue[front];
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == MAX;
}



int enqueue(int data) {

   if(!isFull()) {
        rear=rear+1;
        queue[rear]=data;

   itemCount++;}
}

int dequeue() {
   int data;
   if(!isEmpty()){
   data = queue[front];
   front=front+1;
   itemCount--;}
   return data;
}

int main() {
   int num, n;
   enqueue(3);
   enqueue(5);
   enqueue(9);
   enqueue(1);
   enqueue(12);
   enqueue(15);

   if(isFull()){
      printf("Queue is full!\n");
   }

   num = dequeue();
   

   printf("Element removed: %d\n",num);
   enqueue(16);
   enqueue(17);
   enqueue(18);
   printf("Element at front: %d\n",peek());

   
   
   
   printf("Queue:  ");

   while(!isEmpty()) {
      n = dequeue();
      printf("%d ",n);
   }
}

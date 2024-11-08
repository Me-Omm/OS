#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void bubbleSort (int arr[],int n){
  for(int i=0;i<n;i++){
    for(int j= 0 ; j<n-1 ;j++){
      if(arr[j]>arr[j+1]){
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
}

void displayArray (int arr[], int n){
  printf("\nDisaplaying Array!\n");
  for(int i = 0;i<n;i++){
    printf("%d \t",arr[i]);
  }
  printf("\nArray displayed successfully");
}

int main(int argc,char *argv[]){

  int arr[] = {5,1,60,30,50};
  int n = 5;
  
  int chid = fork();
  int ch = atoi(argv[1]);
  
  if(chid > 0){   //Parent Process
    printf("\nThis is Parent Process\n With ID : %d PPID : %d \n",getpid(),getppid());
    printf("\nGoing to Sort\n");
    printf("\nDisplaying Array before sorting\n");
    displayArray(arr,n);
    printf("\nSorting Array\n");
    bubbleSort(arr,n);
    printf("\n Parent going to sleep\n");
    
    if(ch == 1){ //orphan State
      sleep(10);
      wait(NULL);
    }
    else{
      sleep(1);
    }
    printf("\nDisplying Sorted Array\n");
    displayArray(arr,n);
    if(ch == 0){  //zombie State
      printf("Parent is exiting");
    }
  }
  else if(chid == 0){     //Child Process
    printf("\nTHis is Child Process\n With ID : %d PPID : %d \n",getpid(),getppid());
    printf("\nGoing to start sorting\n");
    printf("\nDispalying Array before Sorting\n");
    displayArray(arr,n);
    printf("\nSorting Array\n");
    bubbleSort(arr,n);
    printf("\nChild going to sleep\n");
    
    if(ch == 0){  //orphan state
      printf("\nTHis is Child Process\n With ID : %d PPID : %d \n",getpid(),getppid());
      sleep(10);
    }
    printf("\nDisaplying Sorted Array\n");
    displayArray(arr,n);
    if(ch == 1){
      printf("Child is exiting");
    }
    
  }
  
  return 0;
}

#include<stdio.h>
#include<stdlib.h>
int FIFO(int *refList,int refSize,int frameSize) {
        int *frameList,currentFrame = 0;
        frameList = (int*)malloc(sizeof(int)*frameSize);
        for(int i = 0;i < frameSize;i++) {
                frameList[i] = -1;
        }
        int pageFault = 0,frameIndex = 0,present = 0;
        for(int i = 0;i < refSize;i++){
                present = 0;
                for(int j = 0;j < frameSize;j++){
                        if(frameList[j] == refList[i])
                                present = 1;
                }
                if(present == 0) {
                        pageFault += 1;
						frameList[currentFrame%frameSize] = refList[i];
						currentFrame++;
                }
        }
        return pageFault;
}

int LRU(int *refList,int refSize,int frameSize) {
        int *frameList,currentFrame = 0,mIndex;
        frameList = (int*)malloc(sizeof(int)*frameSize);
        for(int i = 0;i < frameSize;i++) {
                frameList[i] = -1;
        }
        int pageFault = 0,frameIndex = 0,present = 0;
        for(int i = 0;i < refSize;i++){
                present = 0;
                for(int j = 0;j < frameSize;j++){
                        if(frameList[j] == refList[i])
                                present = 1;
                }
                if(present == 0 && currentFrame < frameSize) {
                        pageFault += 1;
                        
                        frameList[currentFrame] = refList[i];
                        currentFrame++;
                } else if(present == 0) {
                        pageFault += 1;
                        //check for least recently used
                        int *mark,mcount = 0;
                        mark = (int*)malloc(sizeof(int)*frameSize);
                        for(int x = 0;x < frameSize;x++) {
                                mark[x] = 0;
                        }
                        for(int k = i-1;k >= 0 ;k--){
                                for(int l = 0;l < frameSize;l++){
                                        if(refList[k] == frameList[l] && mark[l] != 1){
                                                mark[l] = 1;
                                                mcount++;
                                        }
                                }
                                if(mcount == frameSize-1) {
                                        for(mIndex = 0;mIndex < frameSize;mIndex++){
                                                if(mark[mIndex] == 0)
                                                        break;
                                        }
                                        break;
                                }
                        }
                        frameList[mIndex] = refList[i];
                }
        }
        return pageFault;
}


int optimal(int *refList,int refSize,int frameSize) {
        int *frameList,currentFrame = 0,mIndex;
        frameList = (int*)malloc(sizeof(int)*frameSize);
        for(int i = 0;i < frameSize;i++) {
                frameList[i] = -1;
        }
        int pageFault = 0,frameIndex = 0,present = 0;
        for(int i = 0;i < refSize;i++){
                present = 0;
                for(int j = 0;j < frameSize;j++){
                        if(frameList[j] == refList[i])
                                present = 1;
                }
                if(present == 0 && currentFrame < frameSize) {
                        pageFault += 1;
                        
                        frameList[currentFrame] = refList[i];
                        currentFrame++;
                } else if(present == 0) {
                        pageFault += 1;
                        //chek for least recently used
                        int *mark,mcount = 0;
                        mark = (int*)malloc(sizeof(int)*frameSize);
                        for(int x = 0;x < frameSize;x++) {
                                mark[x] = 0;
                        }
                        for(int k = i+1;k < refSize;k++){
                                for(int l = 0;l < frameSize;l++){
                                        if(refList[k] == frameList[l] && mark[l]!=1){
                                                mark[l] = 1;
                                                mcount++;
                                        }
                                }
                                if(mcount == frameSize-1) {
                                        for(mIndex = 0;mIndex < frameSize;mIndex++){
                                                if(mark[mIndex] == 0)
                                                        break;
                                        }
                                        break;
                                }
                        }
                        frameList[mIndex] = refList[i];
                }
        }
        return pageFault;

}

int main(){
   int *refList,refSize,frameSize,i,choice,pageFault=0;
   printf("\nEnter the reference list size");
   scanf("%d",&refSize);
   refList=(int*)malloc(refSize*sizeof(int));
   printf("\nEnter the reference List");
   for(i=0;i<refSize;i++){
      scanf("%d",&refList[i]);
   }
   do{
      printf("\n-------Menu---------");
      printf("\n1.FIFO\n2.LRU\n3.Optimal\n4.Exit\nEnter the choice:");
      scanf("%d",&choice);
      switch(choice){
         case 1:printf("\nEnter the frame size:");
                scanf("%d",&frameSize);
                pageFault=FIFO(refList,refSize,frameSize);
                printf("The page Fault is:%d",pageFault);
                break;
         case 2:printf("\nEnter the frame size:");
                scanf("%d",&frameSize);
                pageFault=LRU(refList,refSize,frameSize);
                printf("The page Fault is:%d",pageFault);
                break;
         case 3:printf("\nEnter the frame size:");
                scanf("%d",&frameSize);
                pageFault=optimal(refList,refSize,frameSize);
                printf("The page Fault is:%d",pageFault);
                break;
         case 4:exit(1);
         default:printf("Invalid choice");
         }
     }while(choice!=4);
     return 0;
}

import java.util.Arrays;

public class SelectionSort{

    public static void main(String[] args) {
        int arr[]=new int[]{6,0,5,41,-4,3,2};

        SelectionSort obj=new SelectionSort();
        System.out.println(Arrays.toString(obj.Ssort(arr)));
    }
    int[] Ssort(int[] arr) {

        for (int i = 0; i < arr.length; i++) {

            //find max item int the remaining array and swap it with correct last index.
            int last=arr.length-1 -i;
            int maxIndex= findmaxIndex(arr,last);

            //To swap max element with last element
            int temp=0;
            temp=arr[last];
            arr[last]=arr[maxIndex];
            arr[maxIndex]=temp;

        }
        return arr;
    }

    int findmaxIndex(int[] arr, int last) {

        //To get maximum element from array
        int max=0;
        for (int i = 0; i <=last; i++) {

            if(arr[i]>arr[max])
                max=i;
        }
        return max;
    }
}

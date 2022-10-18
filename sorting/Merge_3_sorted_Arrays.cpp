//Given three sorted arrays A, B and C of size N, M and P respectively. The task is to merge them into a single array which must be sorted in increasing order.
vector<int> mergeThree(vector<int>& A, vector<int>& B, vector<int>& C) 
    { 
        vector<int>v;
       int n=A.size();
       int m=B.size();
       int p=C.size();
       for(int i=0;i<n;i++)
       {
           v.push_back(A[i]);
       }
       for(int i=0;i<m;i++)
       {
           v.push_back(B[i]);
       }
       for(int i=0;i<p;i++)
       {
           v.push_back(C[i]);
       }
       
       sort(v.begin(),v.end());
       
       return v;
    } 

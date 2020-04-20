#include<iostream>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;

int parent(int i) { return (i-1)/2; } 
  
// to get index of left child of node at index i 
int left(int i) { return (2*i + 1); } 
  
// to get index of right child of node at index i 
int right(int i) { return (2*i + 2); }

//Create a node structure
struct Node
{
    char a;
    int f;
    Node* left;
    Node* right;
};

void swap(Node** a, Node** b)
{
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

//Restore property of min heap
void MinHeapify(Node** A, int i , int n)
{
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < n && A[l]->f < A[i]->f) 
        smallest = l; 
    if (r < n && A[r]->f < A[smallest]->f) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&A[i], &A[smallest]); 
        MinHeapify(A, smallest, n); 
    }   
}

void CreateMinHeap(Node** Heap, int n)
{
    int a = int(log2(n));
    int b = pow(2,a);
    for(int i = b-1; i >= 0; i--)
    {
        MinHeapify(Heap, i, n);
    }
}

Node* MakeParent(int a, Node* less, Node* high)
{
    Node* temp = new Node();
    temp->a = '\0';
    temp->f = a;
    temp->left = less;
    temp->right = high;
    return temp;
}

void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        cout<< arr[i]; 
  
    cout<<"\n"; 
}

void printCodes(Node* root, int* arr, int top)
{   
    if(root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    }

    if(root->right == NULL && root->left == NULL)
    {
        cout<<root->a<<" : ";
        printArr(arr, top);
    } 
}

void HuffmanCodes(char* A, int* f, int n)
{
    //craete an array of nodes and store the alphabets and their frequencies as leaves of the tree
    Node* Heap[n];
    for(int i = 0; i < n; i++)
    {
        Node* temp = new Node();
        temp->a = A[i];
        temp->f = f[i];
        temp->left = temp->right = NULL;
        Heap[i] = temp;
    }
    //create a heap from above array
    CreateMinHeap(Heap, n);
    int i = n - 1;
    while(i > 0)
    {
        Node* less = Heap[0];
        swap(&Heap[0], &Heap[i]);
        MinHeapify(Heap, 0, i);
        Node* high = Heap[0];
        swap(&Heap[0], &Heap[i-1]);
        MinHeapify(Heap, 0, i-1);
        //pick the two least elements in heap and add them
        //create a new node having frequency = addition and push it into heap
        int a = Heap[i]->f + Heap[i-1]->f;
        Node* p = MakeParent(a, less, high);
        Heap[i-1] = p;
        int k = i-1;
        while(k != 0 && Heap[parent(k)]->f > Heap[k]->f)
        {
            swap(&Heap[parent(k)], &Heap[k]);
            k = parent(k);
        }
        i--;
    }
    int arr[100], top = 0;
    //after loop completes first element in array will be the root node of the tree
    Node* root = Heap[0];
    printCodes(root, arr, top);
}


int main() 
{ 
  
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' }; 
    int freq[] = { 5, 9, 12, 13, 16, 45 }; 
  
    int size = sizeof(arr) / sizeof(arr[0]); 
  
    HuffmanCodes(arr, freq, size); 
  
    return 0; 
}
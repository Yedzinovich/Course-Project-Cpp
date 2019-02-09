#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

/**************************************************************************/
/* Programmer: Inna Yedzinovich                                           */
/* Date: 10/18/2017                                                       */
/* Purpose: Sort .txt file of integers using different sorting algorithms */
/**************************************************************************/

//this function ask the user to choose a sorting algorithm
void sortMenu(vector<int>&);

//this function creates six .txt files with numbers in ascendant,
// random and almost descendant orders
void numGenerator();

//this function print an information of the array
void printList(vector<int> h);

//this function rewrites an information from the .txt file to array
void rewriteFile(vector<int> h, string);

//this function opens .txt file and pushes an information into the array
void openFile(string, vector<int>&);

//this function performs swap of two integer elements
void swap(int *x, int *y);

//this function is an implementation of Selection Sort Algorithm
void selectionSort(vector<int>&);

//this function is an implementation of Insertion Sort Algorithm
void insertionSort (vector<int>&);

//this function is an implementation of Merge Sort Algorithm
void mergeSort(vector<int>&, int, int);

//this function merges two part of arrays
void merge(vector<int>&, int, int, int);

// This function takes last element as pivot, places
// the pivot element at its correct position in sorted
// array, and places all smaller (smaller than pivot)
// to left of pivot and all greater elements to right of pivot
int partition(vector<int>&, int, int);

//this function is an implementation of Quick Sort Algorithms
void quickSort(vector<int>&, int, int);

//this function creates a heap of the array
void heapDown(vector<int>&, int, int);

//this function is an implementation of Heap Sort Algorithms
void heapSort(vector<int>&, int);

//this function is am implementation of the Bubble Sort Algorithms
void bubbleSort(vector<int>&);

int swaps = 0;
int comparisons = 0;

//this is a main function
int main() {

    vector<int> myVector;
    //to generate six files
    numGenerator();

    //put the name of the file below
    string fileName = "NAME_OF_THE_FILE.txt";
    openFile( fileName, myVector );

    sortMenu(myVector);
    rewriteFile(myVector,fileName);

	cout << "Number of swaps " << swaps << endl;
	cout << "Number of comparisons " << comparisons << endl;
	return 0;
};

//********************************** functions implementation ********************//

void numGenerator() {

	srand(time(0));

	ofstream file;
	string arr[6][6] = { {"Inverse100.txt","100" }, {"Random100.txt","100"}, {"Almost100.txt","100"},
						 {"Inverse1000.txt","1000"}, {"Random1000.txt","1000"},{"Almost1000.txt" ,"1000"} };
	
	file.open(arr[0][0]);
	for (int i = 0; i <stoi(arr[0][1]); i++) 
		file << 100 - i << endl;	
	file.close();

	file.open(arr[3][0]);
	for (int i = 0; i < stoi(arr[3][1]); i++)
		file << 1000 - i << endl;
	file.close();
	
	file.open(arr[1][0]);
	for (int i = 0; i < stoi(arr[1][1]); i++)
		file << 1 + (rand() % 100) << endl;
	file.close();

	file.open(arr[4][0]);
	for (int i = 0; i < stoi(arr[4][1]); i++)
		file << 1 + (rand() % 1000) << endl;
	file.close();

	file.open(arr[2][0]);
	for (int i = 0; i <stoi(arr[2][1]); i++)
		if (i > 50 && i < 55)
			file << (rand() % 100) + 1 << endl;
		else
			file << i << endl;
	file.close();

	file.open(arr[5][0]);
	for (int i = 0; i <stoi(arr[5][1]); i++)
		if (i > 500 && i < 550)
			file << (rand() % 1000) + 1 << endl;
		else
			file << i << endl;
	file.close();
	
	cout << "Database was generated" << endl;

}
void openFile(string name,vector<int>& myVector ){

    int data;

    ifstream file(name);
    if (file.is_open()) {
        while(file>>data)
            myVector.push_back(data);
    }
    else
        cout<<"Error, unable to open the file"<<endl;

}
void rewriteFile(vector<int> myVec,string name) {

    ofstream file;
    file.open(name);
    for(int i=0;i<myVec.size();i++){
        file<<myVec[i]<<endl;
    }
    file.close();

}
void sortMenu(vector<int>& myVector){
    char input;

    do{
        cout<<"Make a selection:\n1-Selection Sort\n2-InsertionSort\n3-Merge Sort"
                "\n4-Quick Sort\n5-Heap Sort\n6-Bubble Sort"<<endl;
        cin>>input;
        switch(input){
            case '1': selectionSort(myVector);
                break;
            case '2': insertionSort(myVector);
                break;
            case '3': mergeSort(myVector,0,myVector.size()-1);
                break;
            case '4': quickSort(myVector,0, myVector.size()-1);
                break;
            case '5': heapSort(myVector, myVector.size());
                break;
            case '6': bubbleSort(myVector) ;
                break;
            default: cout<<"Wrong input";
                break;
        }

        cout<<"Sort has been performed"<<endl;
        cout<<"Would you like to continue: (Y/N)"<<endl;
        cin>>input;
    }
    while(tolower(input)!='n');
}
void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}
void printList(vector<int> myVector){

    for(int i = 0; i < myVector.size(); i++)
        cout << myVector[i] << endl;

}
void selectionSort(vector<int>& myVector) {

	int min;
	for (int i = 0; i < myVector.size()-1; i++) {
		
		min = i;
		for (int j = i+1; j < myVector.size(); j++) {
			if (myVector[j] < myVector[i]) {
				min = j;
			}
			comparisons++;
		}

		swap(&myVector[i], &myVector[min]);
		swaps++;
		
	}
}
void insertionSort(vector<int>& myVec){

    int j;
    for(int i = 1;i < myVec.size();i++){

        j = i;
        while( j > 0 && myVec[j] < myVec[j-1]){
            comparisons++;
            swaps++;

            swap(&myVec[j],&myVec[j-1]);
            j--;
        }
        comparisons++;
    }
}
void mergeSort(vector<int>& myVec, int first, int last){

    if(first<last){
        int middle=(first+last)/2;
        mergeSort(myVec,first,middle);
        mergeSort(myVec,middle+1,last);
        merge(myVec,first, middle,last);
    }
}
void merge(vector<int>& myVec, int first, int middle, int last){

    vector<int> temp(last+1);
    int lfirst = first;
    int llast = middle;
    int rfirst  = middle+1;
    int rleft = last;
    int walk=first;

    for(int i = first;i <=last;i++){
        if(lfirst>llast)
            temp[walk++]=myVec[rfirst++];
        else if (rfirst>rleft)
            temp[walk++]=myVec[lfirst++];
        else if(myVec[lfirst]<myVec[rfirst])
            temp[walk++] = myVec[lfirst++];
        else
            temp[walk++]=myVec[rfirst++];
        swaps++;
        comparisons++;

    }
    for(int i=first;i<=last;i++) {
        myVec[i] = temp[i];
        swaps++;
    }
}
int partition(vector<int>& myVec, int first, int last){

    int p=myVec[first];
    int walk=first+1;
    for(int i=first+1;i<=last;i++){
        if(myVec[i]<p) {
            swap(&myVec[walk++], &myVec[i]);
            swaps++;
        }
        comparisons++;
    }
    swap(&myVec[--walk],&myVec[first]);
    swaps++;
    return walk;
}
void quickSort(vector<int>& myVec, int first, int last){
    if(first < last){
        int pivot=partition(myVec,first,last);
        quickSort(myVec, first, pivot-1);
        quickSort(myVec, pivot+1, last);
    }
}
void heapDown(vector<int>& myVec, int top, int bottom){

    int largest = bottom;
    int l = 2*bottom + 1;
    int r = 2*bottom + 2;

    if (l < top && myVec[l] > myVec[largest])
        largest = l;

    if (r < top && myVec[r] > myVec[largest])
        largest = r;

    if (largest != bottom)
    {
        swap(&myVec[bottom], &myVec[largest]);
        swaps++;

        heapDown(myVec, top, largest);
    }

    comparisons++;
}
void heapSort(vector<int>& myVec, int n){

    for (int i = n / 2 - 1; i >= 0; i--)
        heapDown(myVec, n, i);

    for (int i=n-1; i>=0; i--)
    {
        swap(&myVec[0], &myVec[i]);
        swaps++;

        heapDown(myVec, i, 0);
    }
}
void bubbleSort(vector<int>& myVec){

    int n=myVec.size();

    bool ifSwapped;
    for (int i = 0; i < n-1; i++)
    {
        ifSwapped = false;
        for (int j = 0; j < n-i-1; j++)
        {
            if (myVec[j] > myVec[j+1])
            {
                comparisons++;
                swap(&myVec[j], &myVec[j+1]);
                swaps++;
                ifSwapped = true;
            }
        }

        // if nothing has beed swapped  - break
        if (ifSwapped == false)
            break;
    }
}

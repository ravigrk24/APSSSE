#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* intal_add(const char* intal1, const char* intal2)
{
    char* temp;
    int templen;
    char* myintal1 = strdup(intal1);//making copies to work with
    char* myintal2 = strdup(intal2);
    int len1 = strlen(myintal1);
    int len2 = strlen(myintal2);
    if(len1>len2)// convention is to keep intal2 as the larger one
    {
        temp = myintal1;
        myintal1 = myintal2;
        myintal2 = temp;
	
	//switching intal1 and intal2	

        templen = len1;
        len1 = len2;
        len2 = templen;
        
    }
	
    
    char* ans = (char*)malloc(sizeof(char)*(len2+2));//one for the extra carry and the other for null character
       
    int carry,sum, i, k,j = 0;
    carry = 0;
    ans[len2+1] = '\0';
    k = len2;  //index to track answer variable 
    int tempval1,tempval2;

    for(i = len1-1,j = len2-1;i>=0;i--,j--)//iterating through the smaller number
    {
        tempval1 = myintal1[i]-'0';//converting to integer representation
        tempval2 = myintal2[j] - '0';

        sum = tempval1 + tempval2 + carry;//computing sum

        carry = sum/10;//updateing carry

        sum = sum % 10;//updating sum

        ans[k] = sum + '0';//pushing to the result array

	k--;
	
        
    }
    for(;j>=0;j--)//remaining digits in the longer number 
    {	
        tempval2 = myintal2[j]-'0';
        sum = tempval2 + carry;
        carry = sum/10;
        sum = sum % 10;
        ans[k] = sum + '0';
	k--;
    }
    free(myintal1);
    free(myintal2);
    if(carry)//if an overflow present, only possible value is 1
    {
	
	ans[0] = '1';
	return ans;
    }
    else
    {	
	char* result = (char*)malloc(sizeof(char)*(len2+1));
	strcpy(result,ans+1);
	free(ans);

// 	return ans+1; 
	//avoiding the one extra space allocated
	return result;
    }
    
}

int intal_compare(const char* intal1, const char* intal2)
{
	int len1 = strlen(intal1);
	int len2 = strlen(intal2);
	
	//First try eliminating by length since all are positive

	if(len1 > len2)
	{
		return 1;
	}
	else if(len1 < len2)
	{
		return -1;
	}
	else
	{
		int result = strcmp(intal1,intal2);// use library function
		if(result==0)
			return 0;
		else if(result>0)
			return 1;
		else
			return -1;
			
	}
}



char* intal_diff(const char* intal1, const char* intal2)
{
	char *myintal2,*myintal1;

	int t = intal_compare(intal1,intal2);

	if(t==0)// equal numbers difference is 0
	{
		char* res = (char*)malloc(sizeof(char)*2);
		res[0]='0';
		res[1]='\0';
		return res;
	}
	if(t==1)//convention is to keeo myintal2 as the bigger number
	{
		myintal2 = strdup(intal1);
		myintal1 = strdup(intal2);
	}
	else
	{
		myintal2 = strdup(intal2);
		myintal1 = strdup(intal1);
	}
	int diff=0;
	int len1= strlen(myintal2);
	int len2= strlen(myintal1);
	int len;

	if(len1>len2)
		len = len1;
	else
		len = len2;

	char* res = (char*)malloc(sizeof(char)*(len+1));
	int k = len - 1;	
	int j = len2 - 1;
	int i = len1 - 1;
	
	
	int var1,var2;
	res[len]='\0';

	while(i>=0 && j>=0)//travers the number and perform subtraction
	{
		if(myintal2[i]=='0' && myintal1[j]=='0')
		{
			res[k--] = '0';
			i--;
			j--;
			continue;
		}
		var2 = myintal1[j] - '0';
		var1 = myintal2[i] - '0';
		
		if(var1 >= var2)// borrow not required
		{
			diff = var1 - var2;
		}
		else
		{
			int cur = i-1;
			while(myintal2[cur]=='0')//if 0 preceeds, find the first non-zero number to get borrow from
			{
				cur--;
			}
				int tr = myintal2[cur]-'0'-1;
				myintal2[cur] = '0' + tr;
				cur++;
			while(cur!=i)//making all the 0s as 9
			{
				myintal2[cur]='9';
				cur++;
			}
			diff = var1 + 10 - var2;//performing difference with the carry
		}
		res[k--] = '0' + diff;
		i--;
		j--;
	}

	while(i>=0)
	{
		res[k--] = myintal2[i];//copying the remaining digits
		i--;
	}
	int count = 0;//removing trailing zeroes
	free(myintal1);
	free(myintal2);
	while(res[count]=='0')
	{
		count++;
	}
	if(count>0)
	{
		char* result = (char*)malloc(sizeof(char)*(len+1-count));
		strcpy(result,res+count);
		free(res);
		return result;
	}
	return res;
	
	
	

}


char* intal_multiply(const char* intal1, const char* intal2)
{
	//convention again is to keep intval2 as the larger number
	char* myintal1 = strdup(intal1);
	char* myintal2 = strdup(intal2);
	if(intal_compare(intal1,intal2) >0)//intal1 is larger so swap
	{
		char* temp = myintal1;
		myintal1 = myintal2;
		myintal2 = temp;
		
	}
	char *sum = (char*)malloc(sizeof(char)*(2));//summing each product into one valriable
	sum="0";
	int len1 = strlen(intal1);
	int len2 = strlen(intal2);//bigger
	if(len1==1){
		if(intal1[0]=='0'){
			return sum;
		}
	}
	int i,j;
	int tempval1,tempval2;
	int prod,carry;
	int count = 0;
	for(i = len1-1;i>=0;i--)
	{
		char* tempres = (char*)malloc(sizeof(char)*(len2+2+count));
		tempres[len2+1+count]='\0';
		int mytemp = count;
		while(mytemp!=0)
		{
			tempres[len2+mytemp]='0';
			mytemp--;
		}
	
		carry = 0;
		
		int tempcount = len2;
		tempval1 = intal1[i] - '0';
		for(j = len2-1;j>=0;j--)
		{
			
			tempval2 = intal2[j] - '0';
			
			prod = (tempval1*tempval2) + carry;
			
			tempres[tempcount] = (prod%10) + '0';
			
			carry = prod/10;
			tempcount--;
			
		}
		char *yp = tempres;
		if(carry){
			tempres[tempcount] = carry + '0';
		}
		else
			tempres ++;
		
		sum = intal_add(sum,tempres);
		
		free(yp);
		count++;
	}
	free(myintal1);
	free(myintal2);
	int zerocount = 0;//removing trailing zeroes
	int length = strlen(sum);
	while(sum[zerocount]=='0')
	{
		zerocount++;
	}
	if(zerocount == length)
	{
		char* zero = (char*)malloc(sizeof(char)*2);
		zero[0] = '0';
		zero[1] = '\0';
		free(sum);
		return zero;	
	}
	else
	{
		char* result = (char*)malloc(sizeof(char)*(length+1-zerocount));
		strcpy(result,sum+zerocount);
		free(sum);
		return result;
	}

	

}

char* intal_mod(const char* intal1, const char* intal2)
{

	char* myintal1 = strdup(intal1);
	char* myintal2 = strdup(intal2);
	char* two = (char*)malloc(sizeof(char)*2);
	two[0] = '2';
	two[1] = '\0';
	char* startintal2 = strdup(intal2);
	while(1)
	{
		while(intal_compare(myintal1,myintal2)>0)
		{
			myintal1 = intal_diff(myintal1,myintal2);
			myintal2 = intal_multiply(myintal2,two);
		}
		if(intal_compare(myintal1,startintal2)<0)
		{
			free(myintal2);
			free(startintal2);
			return myintal1;
			
		}
		if(intal_compare(myintal1,myintal2)==0)
		{
			char* zero = (char*)malloc(sizeof(char)*2);
			zero[0] = '0';
			zero[1] = '\0';
			free(myintal1);
			free(myintal2);
			free(startintal2);
			return zero;
		}
		else
		{
			
			myintal2 = strdup(startintal2);
		}
	}
	
}

char* intal_pow(const char* intal1, unsigned int n)
{
	char* myintal1 = strdup(intal1);
	
	if(intal1[0]=='0')// if base is 0 return 0
	{
		free(myintal1);
		char* temp = (char*) malloc(sizeof(char)*2);
		temp[0] = '0';
		temp[1] = '\0';
		return temp;
	}
	else if(n == 0 || (myintal1[0]=='1' && strlen(myintal1)==1)) //if power is 0 or 1 return 1
	{
		free(myintal1);
		char* temp = (char*) malloc(sizeof(char)*2);
		temp[0]='1';
		temp[1] = '\0';
		
		return temp;
	}
	if(n%2 == 0)
	{
		char* res = intal_multiply(myintal1,myintal1);
		free(myintal1);	
		char* finalans = intal_pow(res,n/2);
		free(res);
		return  finalans;
	}
	else
	{
		char* res = intal_multiply(myintal1,myintal1);
		char* tempans = intal_pow(res,n/2);
		free(res);
		char* finalans = intal_multiply(myintal1,tempans);
		free(myintal1);
		return finalans;
		
	}
}

char* intal_gcd(const char* intal1, const char* intal2)
{
	char* myintal1 = strdup(intal1);
	char* myintal2 = strdup(intal2);
	char* temp = (char*) malloc(sizeof(char)*2);
	temp[0] = '0';
	temp[1] = '\0';
	if(myintal1[0]=='0' && myintal2[0]=='0')//either 0 return 0
	{
		free(myintal1);
		free(myintal2);
		return temp;
	}
	if(intal_compare(myintal1,temp)==0)
	{
		free(myintal1);
		return myintal2;
	}
	else if(intal_compare(myintal2,temp)==0)
	{
		free(myintal2);
		return myintal1;
	}
	if(intal_compare(myintal1,myintal2)==0)//if both are equal
	{
		free(myintal2);
		free(temp);
		return myintal1;
	}
	else
	{	
		char* a,*b;
		if(intal_compare(myintal1,myintal2)>0)//making a the larger one
		{
			b = myintal2;
			a = myintal1;
		}
		else
		{
			 b = myintal1;
			 a = myintal2;
		}
		
		while(intal_compare(b,"0")!= 0)
		{
			
			temp = b;
			b = intal_mod(a,b);
			char* dump = a;
			a = temp;
			free(dump);
		
		}
		
		free(b);
		return a;
	}
}

char* intal_fibonacci(unsigned int n)
{
	char* f0 = (char*)malloc(sizeof(char)*2);
	char* f1 = (char*)malloc(sizeof(char)*2);
	char* fn = (char*)malloc(sizeof(char)*2);
	f0[0] = '0';
	f0[1] = '\0';
	f1[0] = '1';
	f1[1] = '\0';
	fn[0] = '0';
	fn[1] = '\0';
	if(n == 0)
	{
		free(f1);
		free(fn);
		return f0;
	}
	if(n == 1)
	{
		free(f0);
		free(fn);
		return f1;
	}
	for(int i = 1;i<n;i++)
	{
		fn = intal_add(f0,f1);//f(n) = f(n-1) + f(n-2)
		f0 = f1;
		f1 = fn;
	}
		
	return fn;
}
char* intal_factorial(unsigned int n)
{
	int val = n;
	char* temp = (char*)malloc(sizeof(char)*2);
	temp[0]='1';
	temp[1]='\0';
	char* count = (char*)malloc(sizeof(char)*2);
	count[0]='1';
	count[1]='\0';
	while(val>0)
	{
		temp = intal_multiply(temp,count);//repeated multiplication
		count = intal_add(count,"1");
		val--;
	}
	return temp;
}
char* intal_bincoeff(unsigned int n, unsigned int k)
{
	if(n==0 || k==0 ||n==k)
	{
		char* start = (char*)malloc(sizeof(char)*2);
		start[0]='1';
		start[1]='\0';	
		return start;
	}
	char** table = (char**)malloc(sizeof(char*)*(k+1));
	for( int i = 0;i<=k;i++)
	{
		table[i] = (char*)malloc(sizeof(char)*2);
		table[i][0]='0';
		table[i][1]='\0';
	}
	char* start = (char*)malloc(sizeof(char)*2);
	start[0]='1';
	start[1]='\0';
	table[0] = start;
	if(k > n/2)
	{
		k = n-k;
	}
	int j;
	for(int i = 1;i<=n;i++)
	{
		if(i<k)
		{
			j = i;
		}
		else
		{
			j = k;
		}
		for(;j>0;j--)
		{
			table[j] = intal_add(table[j],table[j-1]);
		}
	}
	free(start);
	return table[k];
	
}
int intal_max(char **arr, int n)
{
	char* max = arr[0];
	int index = 0;
	for(int i =1;i<n;i++)
	{
		if(intal_compare(max,arr[i])<0)//linear searching for max
		{
			max = arr[i];
			index = i;
		}
	}
	
	return index;
}
int intal_min(char **arr, int n)
{
	char* min = arr[0];
	int index = 0;
	for(int i =1;i<n;i++)
	{
		if(intal_compare(min,arr[i])>0)//linear search for min
		{
			min = arr[i];
			index = i;
		}
	}
	
	return index;
}
int intal_search(char **arr, int n, const char* key)
{

	int index = 0;
	while(index<n && (intal_compare(arr[index],key)!=0) )//linear search
	{
		index+=1;
		
	}
	if(index>=n)
		return -1;
	return index;
}
int intal_binsearch(char **arr, int n, const char* key)
{
	int high = n-1;
	int low = 0;
	int mid;
	while(low<=high)//terminating condition
	{
		mid = low + (high-low)/2;
		
		
		if(intal_compare(arr[mid],key) == 0)//comparing with mid
		{
			if(mid == 0 || intal_compare(arr[mid-1],key) !=0 )//if only occurence
			{
				return mid;
			}
			else
			{
				high = mid-1;//finding first occurrence
			} 
		}
		else if(intal_compare(arr[mid],key)>0)
		{
			high = mid-1;
		}
		else
		{
			low = mid+1;
		}
	}
	return -1;
	
}
static int partition (char** arr, int low, int high) 
{ 
    char* pivotele = arr[high];    // pivot 
    int i = (low - 1); 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (intal_compare(arr[j],pivotele)<0) 
        { 
            i++;   
            char* t = arr[i];
	    arr[i] = arr[j];
	    arr[j] = t;
        } 
    } 
	char* t = arr[i+1];
	    arr[i+1] = arr[high];
	    arr[high] = t;
   
    return (i + 1); 
} 
static void quicksort(char** arr, int low, int high) 
{ 
    if (low < high) 
    { 
       
        int pele = partition(arr, low, high); //extract pivot element index        
        quicksort(arr, low, pele - 1); //sort the other halves
        quicksort(arr, pele + 1, high); 
    } 
} 

void intal_sort(char **arr, int n)
{
	int l = 0;
	int r = n-1;
	quicksort(arr,l,r);//calling static function quicksort
	return;
	
	
}


char* coin_row_problem(char **arr, int n)
{
	char** dptable = (char**)malloc(sizeof(char*)*(3));
	
	for(int i =0;i<3;i++)
	{
		dptable[i] = (char*)malloc(sizeof(char)*2);
		dptable[i][0] = '0';
		dptable[i][1] = '\0';
	}
	dptable[1] = arr[0];
	for(int i = 2;i<n+1;i++)
	{
		if(intal_compare(dptable[1],intal_add(arr[i-1],dptable[0]))>0)
		{
			
			dptable[0] = dptable[1];
		}
		else
		{
			
			char* tempsum = intal_add(arr[i-1],dptable[0]);
			dptable[0] = dptable[1];
			dptable[1] = tempsum;
			
		}
		
	}
	

	return dptable[1];	
}




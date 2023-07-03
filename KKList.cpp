#include<iostream>
#define bool int
#define true 1
#define TRUE 1
#define True 1
#define FALSE 0
#define False 0
#define false 0
using namespace std;
class Iterator
{
private:
int releaseIteratorAfterIteration;
Iterator *iterator;
public:
Iterator()
{
this->releaseIteratorAfterIteration=1;
this->iterator=NULL;
}
Iterator (Iterator *iterator)
{
this->releaseIteratorAfterIteration=1;
this->iterator=iterator;
}
Iterator(const Iterator &other)
{
this->releaseIteratorAfterIteration=1;
this->iterator=other.iterator;
}
virtual ~Iterator()
{
if(this->releaseIteratorAfterIteration==1) delete this->iterator;
}
void setReleaseIteratorAfterIteration(int releaseIteratorAfterIteration)
{
this->releaseIteratorAfterIteration=releaseIteratorAfterIteration;
}
Iterator &operator =(const Iterator &other)
{
this->iterator=other.iterator;
}
virtual int hasMoreElement()
{
if(iterator !=NULL) return this->iterator->hasMoreElement();
return 0;
}
virtual int next()
{
if(iterator !=NULL) return this->iterator->next();
return 0;
}
};
class Iterable
{
public:
virtual Iterator getIterator()=0;
};
class KKList : public Iterable
{
public:
virtual void add(int data,bool *success)=0;
virtual int get(int index,int *success) const=0;
virtual int getSize() const=0;
virtual void insertAt  (int index,int data,bool *success)=0;
virtual int removeAt (int index,int *success)=0;
virtual void update(int index,int data,int *success)=0;
virtual void removeAll()=0;
virtual void clear()=0;
};
class KKArrayList : public KKList
{
private:
int **ptr;
int size;
char allocationFlag;
int capacity;
bool addRow();
public:
class KKArrayListIterator :public Iterator
{
int index;
int size;
int **ptr;
public:
KKArrayListIterator(int **ptr,int size)
{
this->index=0;
this->size=size;
this->ptr=ptr;
}
KKArrayListIterator(const KKArrayListIterator &other)
{
this->index=other.index;
}
KKArrayListIterator &operator=(const KKArrayListIterator &other)
{
this->index=other.index;
return *this;
}
int hasMoreElement()
{
return index<size;
}
int next()
{
if(index==size) return 0;
int rowIndex=index/10;
int columnIndex=index%10;
int data=this->ptr[rowIndex][columnIndex];
index++;
return data;
}
};
Iterator getIterator()
{
KKArrayListIterator *tmArrayListIterator;
tmArrayListIterator=new KKArrayListIterator(this->ptr,this->size);
Iterator k(tmArrayListIterator);
k.setReleaseIteratorAfterIteration(0);
return k;
}
KKArrayList();
KKArrayList(int bufferSize);
KKArrayList(const KKArrayList &other);
KKArrayList  &operator =(const KKArrayList &other);
KKArrayList operator +(const KKArrayList &other);
virtual  ~KKArrayList();
void operator +=(const KKArrayList &other);
void add(int data,bool *success);
int get(int index,int *success) const;
int getSize() const ;
void insertAt(int index,int data,bool *success);
int removeAt(int index,int *success);
void update(int index,int data,int *success);
void removeAll();
void clear();
KKArrayList(const KKList &other);
KKArrayList & operator =(const KKList &other);
void operator +=(const KKList & other);
KKArrayList operator +(const KKList &other);
};
bool KKArrayList :: addRow()
{
if(capacity%100==0)
{
int numberOfPointers;
numberOfPointers=this->capacity/10;
int **tmp=new int*[numberOfPointers +10];
if(tmp==NULL) return false;
for(int e=0; e<numberOfPointers; e++) tmp[e]=this->ptr[e];
delete[] this->ptr;
this->ptr=tmp;
}
int i=this->capacity/10;
this->ptr[i]=new int[10];
if(this->ptr[i]==NULL) return false;
this->capacity=this->capacity+10;
return true;
}
void KKArrayList :: operator +=(const KKArrayList &other)
{
int succ;
for(int e=0; e<other.size ;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
void KKArrayList :: operator +=(const KKList &other)
{
int succ;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
KKArrayList KKArrayList :: operator +(const KKArrayList &other)
{
KKArrayList k;
int succ;
for(int e=0; e<this->size;e++) k.add(this->get(e,&succ),&succ);
for(int e=0; e<other.size ;e++) k.add(other.get(e,&succ),&succ);
return k;
}
KKArrayList KKArrayList :: operator +(const KKList &other)
{
KKArrayList k;
int succ;
for(int e=0;e<this->size;e++) k.add(this->get(e,&succ),&succ);
for(int e=0;e<other.getSize();e++) k.add(other.get(e,&succ),&succ);
return k;
}
KKArrayList & KKArrayList :: operator =(const KKArrayList &other)
{
if(other.allocationFlag==0)
{
this->size=0;
int succ;
for(int e=0; e<other.size ;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
else
{
int rows=this->capacity/10;
int j;
for(j=0; j<rows ;j++)
{
delete[]this->ptr[j];
}
delete[]this->ptr;
this->ptr=other.ptr;
this->capacity=other.capacity;
}
return *this;
}
KKArrayList  & KKArrayList :: operator =(const KKList &other)
{
this->size=0;
int e;
int succ;
for(e=0; e<other.getSize() ;e++)
{
this->add(other.get(e,&succ),&succ);
}
return *this;
}
KKArrayList :: KKArrayList()
{
this->ptr=new int *[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->size=0;
this->allocationFlag=0;
}
KKArrayList ::KKArrayList(int bufferSize)
{
this->allocationFlag=0;
if(bufferSize<=0)
{
this->ptr=new int*[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
}
else
{
int rows;
int numberOfPointers;
rows=bufferSize/10;
if(bufferSize%10!=0) rows++;
numberOfPointers=rows+(10 -(rows %10));
this->ptr=new int*[numberOfPointers];
for(int e=0; e<rows;e++)
{
this->ptr[e]=new int [10];
}
this->capacity=rows*10;
this->size=0;
}
}
KKArrayList :: KKArrayList (const KKArrayList &other)
{
this->allocationFlag=0;
int bufferSize=other.size ;
if(bufferSize<=0)
{
this->ptr=new int *[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->size=0;
}
else
{
int rows;
int numberOfPointers;
rows=bufferSize/10;
if(bufferSize%10!=0) rows++;
numberOfPointers=rows+(10-(rows%10));
this->ptr=new int *[numberOfPointers];
for(int e=0; e<rows;e++)
{
this->ptr[e]=new int [10];
}
this->capacity=rows*10;
this->size=0;
}
int succ;
for(int e=0; e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
KKArrayList :: KKArrayList(const KKList &other)
{
this->ptr=new int *[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
this->allocationFlag=0;
int e;
int succ;
for(e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
void KKArrayList :: add(int data,bool *success)                                                                                                                                                                                
{
if(success) *success=false;
if(this->size==this->capacity)
{
if(!addRow()) return;
}
int rowIndex,columnIndex;
rowIndex=size/10;
columnIndex=size%10;
this-> ptr[rowIndex][columnIndex]=data;
this->size++;
if(success )*success=true;
}
int KKArrayList :: get(int index,int *success) const 
{
if(success) *success=false;
if(index<0 || index>=this->size) return 0;
 int rowIndex=index/10;
int columnIndex=index%10;
if(success) *success=true;
return this->ptr[rowIndex][columnIndex];
}
int KKArrayList :: getSize() const 
{
return this->size;
}
void KKArrayList :: insertAt(int index,int data,bool *success)
{
if(success) *success=false;
if(index<0 || index>this->size) return;
if(index==this->size)
{
this->add(data,success);
return;
}
bool succ;
int k=this->get(this->size -1 ,&succ);
this->add(k,&succ);
if(succ == false) return;
int j;
j=this->size -3;
while(j>=index)
{
this->update(j+1,this->get(j,&succ),&succ);
j--;
}
this->update(index,data,&succ);
if(success) *success=true;
}
int KKArrayList ::removeAt(int index,int *success)
{
if(success) *success=false;
if(index<0 || index >=size) return 0;
bool succ;
int data=this->get(index,&succ);
int j;
int ep=this->size-2;
j=index;
while(j<=ep)
{
this->update(j,this->get(j+1,&succ),&succ);
j++;
}
this->size--;
if(success) *success=true;
return data;
}
void KKArrayList :: update(int index,int data,int *success)
{
if(success ) *success=false;
if(index<0 || index >=size) return ;
int rowIndex=index/10;
int columnIndex=index%10;
this->ptr[rowIndex][columnIndex]=data;
if(success) *success=true;
}
void KKArrayList :: removeAll()
{
this->size=0;
}
void KKArrayList :: clear()
{
this->size=0;
}
KKArrayList :: ~KKArrayList()
{
if(this->allocationFlag==0)
{
int rows=this->capacity/10;
int j;
for(j=0;j<rows;j++)
{
delete[]this->ptr[j];
}
delete[]this->ptr;
}
}

// KKForwardList implement starts here

class KKForwardList:public KKList
{
class KKNode
{
public:
int data;
KKNode *next;
KKNode()
{
this->next=NULL;
}
};
class KKForwardListIterator:public Iterator
{
KKNode *ptr;
public:
KKForwardListIterator()
{
this->ptr=NULL;
}
KKForwardListIterator(KKNode *ptr)
{
this->ptr=ptr;
}
KKForwardListIterator(const KKForwardListIterator &other)
{
this->ptr=other.ptr;
}
KKForwardListIterator &operator =(const KKForwardListIterator &other)
{
this->ptr=other.ptr;
return *this;
}
int hasMoreElement()
{
return this->ptr!=NULL;
}
int next()
{
if(this->ptr==NULL) return 0;
int data=this->ptr->data;
this->ptr=this->ptr->next;
return data;
}
};
public:
Iterator getIterator()
{
KKForwardListIterator *tmForwardListIterator;
tmForwardListIterator=new KKForwardListIterator(this->start);
Iterator k(tmForwardListIterator);
k.setReleaseIteratorAfterIteration(0);
return k;
}
private:
char allocationFlag;
KKNode *start,*end;
int size;
public:
KKForwardList();
KKForwardList(int bufferSize);
KKForwardList(const KKForwardList &other);
virtual ~KKForwardList();
KKForwardList &operator=(const KKForwardList &other);
void operator +=(const KKForwardList &other);
KKForwardList operator +(const KKForwardList &other);
void add(int data,bool *success);
int get(int index,int *success) const;
int getSize()const;
void insertAt(int index,int data,bool *success);
int removeAt(int index,bool *success);
void update(int index,int data,int *success);
void removeAll();
void clear();
KKForwardList(const KKList &other);
KKForwardList & operator =(const KKList &other);
KKForwardList operator +(const KKList &other);
void operator +=(const KKList &other);
};
KKForwardList :: KKForwardList()
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
}
KKForwardList ::KKForwardList(int bufferSize)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
}
KKForwardList :: KKForwardList(const KKForwardList  &other)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
int succ;
for(int e=0; e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
KKForwardList :: KKForwardList(const KKList &other)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
int succ;
for(int e=0; e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
KKForwardList :: ~KKForwardList()
{
if(this->allocationFlag==0)
{
this->clear();
}
}
KKForwardList  &KKForwardList :: operator =(const KKForwardList  &other)
{
this->clear();
if(other.allocationFlag==1)
{
this->size=other.size;
this->start=other.start;
this->end=other.end;
}
else
{
int succ;
for(int e=0 ; e<other.getSize() ;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
return *this;
}
KKForwardList & KKForwardList :: operator =(const KKList &other)
{
this->clear();
int succ;
for(int e=0; e<other.getSize() ;e++)
{
this->add(other.get(e,&succ),&succ);
}
return *this;
}
void KKForwardList :: operator +=(const KKForwardList  &other)
{
int k;
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&k),&k);
}
void KKForwardList :: operator +=(const KKList &other)
{
int k;
for(int e=0; e<other.getSize() ; e++) this->add(other.get(e,&k),&k);
}
KKForwardList  KKForwardList :: operator +(const KKForwardList  &other)
{
KKForwardList k;
k+=(*this);
k+=other;
return k;
}
KKForwardList KKForwardList :: operator +(const KKList &other)
{
KKForwardList k;
k+=(*this);
k+=other;
return k;
}
void KKForwardList :: add(int data,bool *success)
{
if(success ) *success=false;
KKNode *t;
t=new KKNode;
if(t==NULL) return ;
t->data=data;
if(this->start==NULL)
{
this->start=this->end=t;
}
else
{
this->end->next=t;
this->end=t;
}
this->size++;
if(success) *success=true;
}
int KKForwardList :: get(int index,int *success) const
{
if(success ) *success=false;
if(index<0 || index >=this->size) return 0;
KKNode *t;
int x;
t=this->start;
for(x=0; x<index;x++) t=t->next;
if(success) *success=true;
return t->data;
}
int KKForwardList :: getSize() const
{
return this->size;
}
void KKForwardList :: insertAt(int index,int data,bool *success)
{
if(success) *success=false;
if(index<0 || index >=this->size) return ;
if(index==this->size)
{
this->add(data,success);
return;
}
KKNode *gg;
gg=new KKNode;
if(gg==NULL) return;
gg->data=data;
int x;
KKNode *t,*j;
for(x=0;x<index;x++)
{
t=t->next;
}
if(t==this->start)
{
gg->next=this->start;
this->start=gg;
}
else
{
gg->next=t;
j->next=gg;
}
this->size++;
if(success) *success=true;
}
int KKForwardList :: removeAt(int index,int *success)
{
return 0;
}
void KKForwardList :: update(int index,int data,int *success)
{
if(success) *success;
if(index<0 || index>=this->size) return;
KKNode *t;
int x;
for(t=this->start, x=0; x<index; x++ ,t=t->next);
t->data=data;
if(success) *success=true;
}
void KKForwardList :: removeAll()
{
clear();
}
void KKForwardList :: clear()
{
KKNode *t;
while(this->start!=NULL)
{
t=this->start;
this->start=this->start->next;
delete t;
}
this->end=NULL;
this->size=0;
}
int main()
{
cout<<"Now iterating on KKArrayList"<<endl;
KKArrayList list1;
int k;
list1.add(100,&k);
list1.add(123,&k);
list1.add(21521,&k);
list1.add(658,&k);
list1.add(3427473,&k);
list1.add(743,&k);
Iterator iterator1=list1.getIterator();
Iterator iterator2=list1.getIterator();
Iterator iterator3=list1.getIterator(); 
cout<<iterator1.next()<<endl;
cout<<iterator1.next()<<endl;
cout<<iterator1.next()<<endl;
cout<<"************************"<<endl;
cout<<iterator1.next()<<endl;
cout<<iterator1.next()<<endl;
cout<<iterator1.next()<<endl;
cout<<"***********************"<<endl;
cout<<"Now iterating on KKForwardList"<<endl; 
KKForwardList list2;
list2.add(100,&k);
list2.add(123,&k);
list2.add(21521,&k);
list2.add(658,&k);
list2.add(3427473,&k);
list2.add(743,&k);
iterator1=list2.getIterator();
iterator2=list2.getIterator();
iterator3=list2.getIterator(); 
cout<<iterator2.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<"************************"<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator2.next()<<endl; 
return 0;
}
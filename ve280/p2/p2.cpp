#include <iostream>
#include <cstdlib>
#include "p2.h"

using namespace std;

static list_t list_follow(int elt, list_t list)
//Effects: Return a new list consisiting of the new element following the elements of the original list.
{
	if (list_isEmpty(list)) return list_make(elt,list);
	else if (size(list)==1) return list_make(list_first(list),list_make(elt,list_make()));
	     else return list_make(list_first(list),list_follow(elt,list_rest(list)));
}

static bool tree_hasIncreasingPath(tree_t tree)
//Effects: Return true if and only if there is a "root-to-leaf" path such that all elements along the path form a monotonically increasing sequence.
{
	if (depth(tree)<2) return true;
	else if (!tree_isEmpty(tree_left(tree))) {if ((tree_hasIncreasingPath(tree_left(tree)))&&(tree_elt(tree)<=tree_elt(tree_left(tree)))) return true;
	     					 else if (!tree_isEmpty(tree_right(tree))) {if ((tree_hasIncreasingPath(tree_right(tree)))&&(tree_elt(tree)<=tree_elt(tree_right(tree)))) return true;
						      					    else return false;}}
	     else if ((tree_hasIncreasingPath(tree_right(tree)))&&(tree_elt(tree)<=tree_elt(tree_right(tree)))) return true;
		  else return false;
}

static bool tree_hasDecreasingPath(tree_t tree)
//Effects: Return true if and only if there is a "root-to-leaf" path such that all elements along the path form a monotonically decreasing sequence.
{
	if (depth(tree)<2) return true;
	else if (!tree_isEmpty(tree_left(tree))) {if ((tree_hasDecreasingPath(tree_left(tree)))&&(tree_elt(tree)>=tree_elt(tree_left(tree)))) return true;
	     					 else if (!tree_isEmpty(tree_right(tree))) {if ((tree_hasDecreasingPath(tree_right(tree)))&&(tree_elt(tree)>=tree_elt(tree_right(tree)))) return true;
						      					    else return false;}}
	     else if ((tree_hasDecreasingPath(tree_right(tree)))&&(tree_elt(tree)>=tree_elt(tree_right(tree)))) return true;
		  else return false;
}

static int tree_MinPathSum(tree_t tree)
//Effects: Return the minimum sum from all sums of "root-to-leaf" path.
{
	if (tree_isEmpty(tree)) return 0;
	else if (tree_MinPathSum(tree_left(tree))<tree_MinPathSum(tree_right(tree))) return (tree_elt(tree)+tree_MinPathSum(tree_left(tree)));
	     else return (tree_elt(tree)+tree_MinPathSum(tree_right(tree)));
}

static int tree_min(tree_t tree){
	int a,b,c;
	a=tree_elt(tree);
	if ((tree_isEmpty(tree_left(tree)))&&(tree_isEmpty(tree_right(tree)))) return a;
	else if (tree_isEmpty(tree_left(tree))) {b=tree_min(tree_right(tree)); if (a<b) return a; else return b;}
	     else if (tree_isEmpty(tree_right(tree))) {b=tree_min(tree_left(tree)); if (a<b) return a; else return b;}
		  else {
			b=tree_min(tree_left(tree)); c=tree_min(tree_right(tree));
			if ((a<b)&&(a<c)) return a;
			else if (b<c) return b;
			     else return c;}
}

static bool tree_checkSorted(tree_t tree)
//Effects: Return true if the tree is a sorted binary tree.
{
	if (tree_isEmpty(tree)) return true;
	else if ((tree_isEmpty(tree_left(tree)))&&(tree_isEmpty(tree_right(tree)))) return true;
	     else if (tree_isEmpty(tree_left(tree))) {if ((tree_checkSorted(tree_right(tree)))&&(tree_elt(tree)<=tree_min(tree_right(tree)))) return true;else return false;}
		  else if (tree_isEmpty(tree_right(tree))) {if ((tree_checkSorted(tree_left(tree)))&&(tree_elt(tree)>tree_max(tree_left(tree)))) return true;else return false;}
		       else if ((tree_checkSorted(tree_right(tree)))&&(tree_elt(tree)<=tree_min(tree_right(tree)))&&(tree_checkSorted(tree_left(tree)))&&(tree_elt(tree)>tree_max(tree_left(tree)))) return true;
			    else return false;
}

int size(list_t list){
	if (list_isEmpty(list)) return 0;
	else return (1+size(list_rest(list)));
}


bool memberOf(list_t list, int val){
	if (list_isEmpty(list)) return false;
	else if (list_first(list)==val) return true;
	     else if (list_isEmpty(list_rest(list))) return false;
	           else return memberOf(list_rest(list),val);
}


int dot(list_t v1, list_t v2){
	if ((list_isEmpty(v1))||(list_isEmpty(v2))) {
        cerr << "error: user passed empty list where non-empty requried\n";
        exit(0);}	
        if ((list_isEmpty(list_rest(v1)))||(list_isEmpty(list_rest(v2)))) return list_first(v1)*list_first(v2);
	else return (list_first(v1)*list_first(v2)+dot(list_rest(v1),list_rest(v2)));
}


bool isIncreasing(list_t v){
	if (size(v)<2) return true;
	else if (list_first(v)>list_first(list_rest(v))) return false;
	     else return (isIncreasing(list_rest(v)));
}


list_t reverse(list_t list){
	if (size(list)<2) return list;
	else return list_follow(list_first(list),reverse(list_rest(list)));
}


list_t append(list_t first, list_t second){
	if (list_isEmpty(second)) return first;
	else return append(list_follow(list_first(second),first),list_rest(second));
}
bool isArithmeticSequence(list_t v){
	if (size(v)<3) return true;
	else if ((list_first(v)-list_first(list_rest(v)))==(list_first(list_rest(v))-list_first(list_rest(list_rest(v))))) return isArithmeticSequence(list_rest(v));
	     else return false;
}

list_t filter_odd(list_t list){
	if (list_isEmpty(list)) return list;
	else if (list_first(list)%2==1) return append(list_make(list_first(list),list_make()),filter_odd(list_rest(list)));
	     else return filter_odd(list_rest(list));
}


list_t filter(list_t list, bool (*fn)(int)){
	if (list_isEmpty(list)) return list;
	else if (fn(list_first(list))) return append(list_make(list_first(list),list_make()),filter(list_rest(list),fn));
	     else return append(list_make(),filter(list_rest(list),fn));
}


list_t unique(list_t list){
	if (size(list)<2) return list;
	else if (memberOf(list_rest(reverse(list)),list_first(reverse(list)))) return unique(reverse(list_rest(reverse(list))));
	     else return list_follow(list_first(reverse(list)),unique(reverse(list_rest(reverse(list)))));
}


list_t insert_list(list_t first, list_t second, unsigned int n){
	if (n>size(first)) {cerr << "error: user passed wrong number n that is larger than the number of elements in the list first\n";
        exit(0);}
	if (n>0) return append(list_make(list_first(first),list_make()),insert_list(list_rest(first),second,n-1));
	else return append(second,first);
}


list_t chop(list_t list, unsigned int n){
	if (n>size(list)) {cerr << "error: user passed wrong number n that is larger than the number of elements in the list\n";
	exit(0);}	
	if (n==0) return list;
	else return chop(reverse(list_rest(reverse(list))),n-1);
}


//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int tree_sum(tree_t tree){
	if (tree_isEmpty(tree)) return 0;
	else return (tree_elt(tree)+tree_sum(tree_left(tree))+tree_sum(tree_right(tree)));
}


bool tree_search(tree_t tree, int val){
	if (tree_isEmpty(tree)) return false;
	else if ((tree_elt(tree)==val)||(tree_search(tree_left(tree),val))||(tree_search(tree_right(tree),val))) return true;
	     else return false; 

}


int depth(tree_t tree){
	if (tree_isEmpty(tree)) return 0;
	else if (depth(tree_left(tree))>depth(tree_right(tree))) return (1+depth(tree_left(tree)));
	     else return (1+depth(tree_right(tree)));
}


int tree_max(tree_t tree){
	if (tree_isEmpty(tree)) {
        cerr << "Error: user passed empty tree\n";
        exit(0);}
	int a,b,c;
	a=tree_elt(tree);
	if (tree_isEmpty(tree_left(tree))) b=0;
	else b=tree_max(tree_left(tree));
	if (tree_isEmpty(tree_right(tree))) c=0;
	else c=tree_max(tree_right(tree));
	if ((a>b)&&(a>c)) return a;
	else if (b>c) return b;
	     else return c;	
}


list_t traversal(tree_t tree){
	if (tree_isEmpty(tree)) return list_make();
	else return append(append(traversal(tree_left(tree)),list_make(tree_elt(tree),list_make())),traversal(tree_right(tree)));
}

bool tree_hasMonotonicPath(tree_t tree){
	if ((tree_hasIncreasingPath(tree))||(tree_hasDecreasingPath(tree))) return true;
	else return false;
}

bool tree_allPathSumGreater(tree_t tree, int sum){
	if (tree_isEmpty(tree)) {
        cerr << "Error: user passed empty tree\n";
        exit(0);}
	int min;
	min=tree_MinPathSum(tree);
	if (min>sum) return true;
	else return false;
}


bool covered_by(tree_t A, tree_t B){
	if (tree_isEmpty(A)) return true;
	else if ((tree_elt(A)==tree_elt(B))&&(covered_by(tree_left(A),tree_left(B)))&&(covered_by(tree_right(A),tree_right(B)))) return true;
	     else return false;
}
       

bool contained_by(tree_t A, tree_t B){
	if (covered_by(A,B)) return true;
	else if ((covered_by(A,tree_left(B)))||(covered_by(A,tree_right(B)))) return true;
	     else return false;
}
      

tree_t insert_tree(int elt, tree_t tree){
	if (!tree_checkSorted(tree)) {
	cerr << "Error: user passed unsorted tree.\n";
	exit(0);}
	if (tree_isEmpty(tree)) return tree_make(elt,tree,tree);
	else if (elt<tree_elt(tree)) return tree_make(tree_elt(tree),insert_tree(elt,tree_left(tree)),tree_right(tree));
	     else return tree_make(tree_elt(tree),tree_left(tree),insert_tree(elt,tree_right(tree)));
}



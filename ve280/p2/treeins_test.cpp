#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

static bool tree_equal(tree_t t1, tree_t t2)
    // EFFECTS: returns true iff t1 == t2
{
    if(tree_isEmpty(t1) && tree_isEmpty(t2))
    {
        return true;
    }
    else if(tree_isEmpty(t1) || tree_isEmpty(t2))
    {
        return false;
    }
    else
    {
        return ((tree_elt(t1) == tree_elt(t2)) 
            && tree_equal(tree_left(t1), tree_left(t2))
            && tree_equal(tree_right(t1), tree_right(t2)));
    }
}

int main()
{
	tree_t t,t1;
	t=tree_make();
	t1=tree_make(1,tree_make(1,t,t),t);
cout<<insert_tree(4,t1);
    /*tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));

    tree_t candidate = insert_tree(3, start);
    tree_print(end);
    cout << endl;
    cout << endl;

    tree_print(candidate);
    cout << endl;

    if(tree_equal(candidate, end))
    {
        cout << "Success!\n";
        return 0;
    }
    else
    {
        cout << "Failed\n";
        return -1;
    }
	tree_t t0,t;
	t0=tree_make();
	t=tree_make(6,tree_make(7,tree_make(3,t0,t0),t0),tree_make(8,tree_make(7,t0,t0),t0));
	tree_print(t);
	cout<<tree_hasMonotonicPath(t)<<endl;
	t=insert_tree(2,t);
	tree_print(t);
	t=insert_tree(5,t);
	tree_print(t);
	t=insert_tree(10,t);
	tree_print(t);*/

}

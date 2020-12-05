#include "avlTree.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//Constructors
AVLTree::AVLTree()
    : root(0)
{
}
AVLTree::AVLTree(int k)
{
    root = nullptr;
    this->k = k;
}

//Destructor
AVLTree::~AVLTree()
{
    removeAll(root);
}

//Recursive helper for destructor
void AVLTree::removeAll(Node* n)
{
    if (n) {
        removeAll(n->left);
        removeAll(n->right);
        delete n;
    }
}

//Utilities:

void AVLTree::printNode(Node* n)
{
    cout << "******************" << endl;
    if (!n) {
        cout << "NODE IS NULL!" << endl;
        return;
    }
    cout << "NODE IS: " << n->a << "." << n->b << endl;
    if (n->parent)
        cout << "NODE's PARENT IS: " << n->parent->a << "." << n->parent->b << endl;
    else
        cout << "NODE DOESN'T HAVE A PARENT" << endl;
    if (n->left)
        cout << "NODE's LEFT IS: " << n->left->a << "." << n->left->b << endl;
    else
        cout << "NODE DOESN'T HAVE A LEFT" << endl;
    if (n->right)
        cout << "NODE's RIGHT IS: " << n->right->a << "." << n->right->b << endl;
    else
        cout << "NODE DOESN'T HAVE A RIGHT" << endl;
    cout << "******************" << endl;
}

//Prints:
void AVLTree::in_order()
{
    if (!root)
        return;
    in_order(root);
    cout << endl;
}

void AVLTree::in_order(Node* n)
{
    if (n->left) {
        in_order(n->left);
        cout << " ";
    }
    cout << n->a << "." << n->b;
    if (n->right) {
        cout << " ";
        in_order(n->right);
    }
}

void AVLTree::pre_order()
{
    if (!root) { //cout<<"NO ROOT!"<<endl;
        return;
    }
    pre_order(root);
    cout << endl;
}

void AVLTree::pre_order(Node* n)
{
    if (n) {
        if (n == root)
            cout << n->a << "." << n->b;
        else {
            cout << " " << n->a << "." << n->b;
        }
        pre_order(n->left);
        pre_order(n->right);
    }
}

void AVLTree::rotateLeft(Node* problemNode)
{
    Node*& rightNode = problemNode->right; //make a copy of the right node
    Node* rightNodeTemp = problemNode->right;
    //If not Root:
    if (problemNode->parent) {
        Node*& problemParent = problemNode->parent; //set problem node parent temp
        //check for Double Rotation:
        if ((rightNodeTemp->left != nullptr || rightNodeTemp->right != nullptr) //If either or isn't null continue checking
            && ((rightNodeTemp->left != nullptr && rightNodeTemp->right != nullptr //if the left and the right one aren't null
                    && (getHeight(rightNodeTemp->left) > getHeight(rightNodeTemp->right))) //and the left is bigger than the right, there's a double rotation
                   || (rightNodeTemp->left != nullptr && rightNode->right == nullptr)) // or if the left one isn't null but the right one is
            ) {

            Node* rightLeftNodeTemp = problemNode->right->left; //set a node copy for the right left node, it'll become the new "root" of this mini tree
            Node* rlnAdoptChildRight = nullptr; //child to adopt on the right (in the case of k>1 )
            Node* rlnAdoptChildLeft = nullptr; //child to adopt on the left  (in the case of k>1 )
            //set the the parent's right to the right left node
            if (problemParent->left == problemNode)
                problemParent->left = rightLeftNodeTemp; //set problem node parent LEFT to problem node left
            else
                problemParent->right = rightLeftNodeTemp; //set problem node parent RIGHT  to problem node left
            rightLeftNodeTemp->parent = problemParent; //set the right left node's parent to the problem parent to complete the mutual
            if (rightLeftNodeTemp->right) { //this means there is a child/tree on the right that has to be adopted
                rlnAdoptChildRight = rightLeftNodeTemp->right; //initialize our right child adopt variable to this
            }
            if (rightLeftNodeTemp->left) { //this means there is a child/tree on the left that has to be adopted
                rlnAdoptChildLeft = rightLeftNodeTemp->left; //initialize our right child adtoip variable to this
            }

            rightLeftNodeTemp->left = problemNode; //set the left of that rln node to the problem node
            problemNode->parent = rightLeftNodeTemp; //set the parent of problemNode to rln

            rightLeftNodeTemp->right = rightNodeTemp; //set the rln right to right node temp
            rightNodeTemp->parent = rightLeftNodeTemp; //set the parent of right node temp to rln

            if (rlnAdoptChildRight)
                rightNodeTemp->left = rlnAdoptChildRight; //if there was a child to adopt on right, it goes on the left side of right node temp
            else
                rightNodeTemp->left = nullptr;
            if (rlnAdoptChildLeft)
                problemNode->right = rlnAdoptChildLeft; //if there was a child to adopt on left, it goes on the right side of problem node
            else
                problemNode->right = nullptr;
            return;
        } //end of double rotation check

        if (problemParent->left == problemNode)
            problemParent->left = rightNodeTemp; //set problem node parent LEFT to problem node left
        else
            problemParent->right = rightNodeTemp; //set problem node parent RIGHT  to problem node left

        rightNodeTemp->parent = problemParent; //set the problem node right parent to the problem node's parent
        if (rightNodeTemp->left) { //if the problem node's right child has a left child, it needs to get adopted
            Node* childToAdopt = rightNodeTemp->left; //create a ref. for the child to adopt
            childToAdopt->parent = problemNode; //set the adopted child's parent to the problem node
            rightNodeTemp->left = problemNode; //set the right node's left to problem node
            problemNode->right = childToAdopt; //set the problem Node right to the child to adopt
            problemNode->parent = rightNodeTemp; //set the problem node's parent to the problem node's right child
            return; //done rotating
        }
        else { //if no child to adopt,
            problemNode->parent = rightNodeTemp; //problem node's parent becomes right node
            rightNodeTemp->left = new Node();
            rightNodeTemp->left = problemNode;
            problemNode->right = nullptr; //problem node's right becomes nullptr because there's no child to adopt
            // rightNode->left = new Node();
            // rightNode->left = problemNode;
            // pre_order(); //do a preorder print to check
            // cout<<"ROTATION FINISHED"<<endl<<endl;
            return; //done rotating
        }
    }

    //IF ROOT:
    //cout<<"Rotating Root to the LEFT"<<endl;
    if ((rightNodeTemp->left != nullptr || rightNodeTemp->right != nullptr) //If either or isn't null continue checking
        && ((rightNodeTemp->left != nullptr && rightNodeTemp->right != nullptr //if the left and the right one aren't null
                && (getHeight(rightNodeTemp->left) > getHeight(rightNodeTemp->right))) //and the left is bigger than the right, there's a double rotation
               || (rightNodeTemp->left != nullptr && rightNode->right == nullptr)) // or if the left one isn't null but the right one is
        ) {

        Node* rightLeftNodeTemp = problemNode->right->left; //set a node copy for the right left node, it'll become the new "root" of this mini tree
        Node* rlnAdoptChildRight = nullptr; //child to adopt on the right (in the case of k>1 )
        Node* rlnAdoptChildLeft = nullptr; //child to adopt on the left  (in the case of k>1 )
        if (rightLeftNodeTemp->right) { //this means there is a child/tree on the right that has to be adopted
            rlnAdoptChildRight = rightLeftNodeTemp->right; //initialize our right child adopt variable to this
        }
        if (rightLeftNodeTemp->left) { //this means there is a child/tree on the left that has to be adopted
            rlnAdoptChildLeft = rightLeftNodeTemp->left; //initialize our right child adtoip variable to this
        }

        rightLeftNodeTemp->left = problemNode; //set the left of that rln node to the problem node
        problemNode->parent = rightLeftNodeTemp; //set the parent of problemNode to rln

        rightLeftNodeTemp->right = rightNodeTemp; //set the rln right to right node temp
        rightNodeTemp->parent = rightLeftNodeTemp; //set the parent of right node temp to rln

        if (rlnAdoptChildRight)
            rightNodeTemp->left = rlnAdoptChildRight; //if there was a child to adopt on right, it goes on the left side of right node temp
        else
            rightNodeTemp->left = nullptr;
        if (rlnAdoptChildLeft)
            problemNode->right = rlnAdoptChildLeft; //if there was a child to adopt on left, it goes on the right side of problem node
        else
            problemNode->right = nullptr;

        root = rightLeftNodeTemp; //set rln to root
        rightLeftNodeTemp->parent = nullptr; //get rid of it's parent if any
        //pre_order();
        return;
    } //end of double rotation check

    if (rightNodeTemp->left) { //problem node right child had a left child that needs to be adopted
        Node*& childToAdopt = rightNodeTemp->left; //set a temp variable for child to adopt
        childToAdopt->parent = problemNode; //problem node becomes the new parent of the adopted node
        problemNode->right = childToAdopt; //problem node right child is equal to child that needs to be adopted
        // problemNode->parent = new Node();               //create a new node for parent cause it used to be root and there was no parent
        problemNode->parent = rightNodeTemp; //problem node parent becomes right node
        rightNodeTemp->left = problemNode; //right node's left becomes problemNode
        rightNodeTemp->parent = nullptr; //right node's parent becomes a nullptr because it is the new root
        root = rightNodeTemp; //set right node to the new root
        //pre_order(); //do a preorder print to check
        //cout<<"ROTATION FINISHED"<<endl<<endl;
        return; //done with rotation
    }
    else { //if no child needs to be adopted
        rightNodeTemp->parent = nullptr; //right node's parent is nullptr because it becomes the new root
        rightNodeTemp->left = problemNode; //right node's left becomes the problem node
        problemNode->parent = new Node(); //create a new node for parent cause it used to be root and there was no parent
        problemNode->parent = rightNodeTemp; //problem node's parent becomes right node
        problemNode->right = nullptr; //get rid of any connection problem node had to the right
        root = rightNodeTemp;
        return; //done with rotation
    }
}

void AVLTree::rotateRight(Node* problemNode)
{
    Node*& leftNode = problemNode->left; //make a copy of the left node
    Node* leftNodeTemp = problemNode->left;

    //If not Root:
    if (problemNode->parent) {
        Node*& problemParent = problemNode->parent; //set problem node parent temp
        if ((leftNodeTemp->right != nullptr || leftNodeTemp->left != nullptr) //If either or isn't null continue checking
            && ((leftNodeTemp->right != nullptr && leftNodeTemp->left != nullptr //if the left and the right one aren't null
                    && (getHeight(leftNodeTemp->right) > getHeight(leftNodeTemp->left))) //and the left is bigger than the right, there's a double rotation
                   || (leftNodeTemp->right != nullptr && leftNodeTemp->left == nullptr)) // or if the left one isn't null but the right one is
            ) {

            Node* leftRightNodeTemp = problemNode->left->right; //set a node copy for the left right node, it'll become the new "root" of this mini tree
            Node* lrnAdoptChildRight = nullptr; //child to adopt on the right (in the case of k>1 )
            Node* lrnAdoptChildLeft = nullptr; //child to adopt on the left  (in the case of k>1 )

            //set the the parent's right to the right left node
            if (problemParent->left == problemNode)
                problemParent->left = leftRightNodeTemp; //set problem node parent LEFT to problem node left
            else
                problemParent->right = leftRightNodeTemp; //set problem node parent RIGHT  to problem node left

            leftRightNodeTemp->parent = problemParent; //set the left right node's parent to the problem parent to complete the mutual
            if (leftRightNodeTemp->right) { //this means there is a child/tree on the right that has to be adopted
                lrnAdoptChildRight = leftRightNodeTemp->right; //initialize our right child adopt variable to this
            }
            if (leftRightNodeTemp->left) { //this means there is a child/tree on the left that has to be adopted
                lrnAdoptChildLeft = leftRightNodeTemp->left; //initialize our right child adtoip variable to this
            }

            leftRightNodeTemp->right = problemNode; //set the right of that lrn node to the problem node
            problemNode->parent = leftRightNodeTemp; //set the parent of problemNode to lrn

            leftRightNodeTemp->left = leftNodeTemp; //set the lrn left to left node temp
            leftNodeTemp->parent = leftRightNodeTemp; //set the parent of left node temp to lrn

            if (lrnAdoptChildLeft)
                leftNodeTemp->right = lrnAdoptChildRight; //if there was a child to adopt on left, it goes on the right side of left node temp
            else
                leftNodeTemp->right = nullptr;
            if (lrnAdoptChildRight)
                problemNode->left = lrnAdoptChildLeft; //if there was a child to adopt on right, it goes on the left side of problem node
            else
                problemNode->left = nullptr;

            return;
        } //end of double rotation check

        if (problemParent->left == problemNode)
            problemParent->left = leftNodeTemp; //set problem node parent LEFT to problem node left
        else
            problemParent->right = leftNodeTemp; //set problem node parent RIGHT  to problem node left
        leftNodeTemp->parent = problemParent; //set the problem node right parent to the problem node's parent
        if (leftNode->right) { //if the problem node's left child has a right child, it needs to get adopted
            Node*& childToAdopt = leftNodeTemp->right; //create a ref. for the child to adopt
            childToAdopt->parent = problemNode; //set the adopted child's parent to the problem node
            problemNode->left = childToAdopt; //set the problem Node left to the child to adopt
            problemNode->parent = leftNodeTemp; //set the problem node's parent to the problem node's left child
            leftNodeTemp->right = problemNode; //set the left node's right to problem node
            return; //done rotating
        }
        else { //if no child to adopt,
            problemNode->parent = leftNodeTemp; //problem node's parent becomes right node
            leftNodeTemp->right = problemNode;
            problemNode->left = nullptr; //problem node's left becomes nullptr because there's no child to adopt
            return; //done rotating
        }
    }

    //IF ROOT:
    // cout<<"Rotating Root to the RIGHT"<<endl;

    if ((leftNodeTemp->right != nullptr || leftNodeTemp->left != nullptr) //If either or isn't null continue checking
        && ((leftNodeTemp->right != nullptr && leftNodeTemp->left != nullptr //if the left and the right one aren't null
                && (getHeight(leftNodeTemp->right) > getHeight(leftNodeTemp->left))) //and the left is bigger than the right, there's a double rotation
               || (leftNodeTemp->right != nullptr && leftNodeTemp->left == nullptr)) // or if the left one isn't null but the right one is
        ) {

        Node* leftRightNodeTemp = problemNode->left->right; //set a node copy for the left right node, it'll become the new "root" of this mini tree
        Node* lrnAdoptChildRight = nullptr; //child to adopt on the right (in the case of k>1 )
        Node* lrnAdoptChildLeft = nullptr; //child to adopt on the left  (in the case of k>1 )

        if (leftRightNodeTemp->right) { //this means there is a child/tree on the right that has to be adopted
            lrnAdoptChildRight = leftRightNodeTemp->right; //initialize our right child adopt variable to this
        }
        if (leftRightNodeTemp->left) { //this means there is a child/tree on the left that has to be adopted
            lrnAdoptChildLeft = leftRightNodeTemp->left; //initialize our right child adtoip variable to this
        }

        leftRightNodeTemp->right = problemNode; //set the right of that lrn node to the problem node
        problemNode->parent = leftRightNodeTemp; //set the parent of problemNode to lrn

        leftRightNodeTemp->left = leftNodeTemp; //set the lrn left to left node temp
        leftNodeTemp->parent = leftRightNodeTemp; //set the parent of left node temp to lrn

        if (lrnAdoptChildLeft)
            leftNodeTemp->right = lrnAdoptChildLeft; //if there was a child to adopt on left, it goes on the right side of left node temp
        else
            leftNodeTemp->right = nullptr;
        if (lrnAdoptChildRight)
            problemNode->left = lrnAdoptChildRight; //if there was a child to adopt on right, it goes on the left side of problem node
        else
            problemNode->left = nullptr;

        root = leftRightNodeTemp; //set lrn to root
        leftRightNodeTemp->parent = nullptr; //get rid of it's parent if any
        return;
    } //end of double rotation check

    if (leftNodeTemp->right) { //problem node left child had a right child that needs to be adopted
        Node*& childToAdopt = leftNodeTemp->right; //set a temp variable for child to adopt
        childToAdopt->parent = problemNode; //problem node becomes the new parent of the adopted node
        problemNode->left = childToAdopt; //problem node left child is equal to child that needs to be adopted
        problemNode->parent = new Node(); //create a new node for parent cause it used to be root and there was no parent
        problemNode->parent = leftNodeTemp; //problem node parent becomes left node
        leftNodeTemp->right = problemNode; //left node's right become a nullptr cause problem node adopted it on it's right
        leftNodeTemp->parent = nullptr; //left node's parent becomes a nullptr because it is the new root
        root = leftNodeTemp; //set left node to the new root
        return; //done with rotation
    }
    else { //if no child needs to be adopted
        leftNodeTemp->parent = nullptr; //left node's parent is nullptr because it becomes the new root
        leftNodeTemp->right = problemNode; //left node's right becomes the problem node
        problemNode->parent = leftNodeTemp; //problem node's parent becomes left node
        problemNode->left = nullptr; //get rid of any connection problem node had to the left
        root = leftNodeTemp; //set left node to the new root
        return; //done with rotation
    }
}

int getMax(int a, int b)
{
    return (a > b) ? a : b;
}

int AVLTree::getHeight(Node* n)
{
    if (n == nullptr)
        return 0;
    if ((n->left == nullptr && n->right == nullptr))
        return 1;
    return getMax(getHeight(n->left), getHeight(n->right)) + 1;
}

bool AVLTree::balanceCheck(Node* n)
{
    if (!n)
        return false;
    int leftHeight = getHeight(n->left);
    int rightHeight = getHeight(n->right);
    if (n == root) {
        if (abs(leftHeight - rightHeight) <= this->k) {
            return true; //this is where you force it to stop
        }
        else if (leftHeight > rightHeight) {
            rotateRight(n);
            return balanceCheck(n);
        }
        rotateLeft(n);
        return balanceCheck(n);
    }

    if (abs(leftHeight - rightHeight) <= this->k) {
        return balanceCheck(n->parent);
    }
    else if (leftHeight > rightHeight) {
        rotateRight(n);
        return balanceCheck(n->parent);
    }
    rotateLeft(n);
    return balanceCheck(n->parent);
} //end of balance check

double AVLTree::numify(int a, int b)
{
    return (a * 10) + (b * 1);
}

//Searches:
bool AVLTree::approx_search(int a, int b)
{
    if (!root) {
        return 0;
    }
    Node* approx_node = approx_searcher(a, b, root);
    cout << "closest to " << a << "." << b << " is " << approx_node->a << "." << approx_node->b << endl;
    return approx_searcher(a, b, root);
}

//Recursive helper for approx_search
AVLTree::Node* AVLTree::approx_searcher(int a, int b, Node* n)
{
    if (!root) {
        return nullptr;
    }
    if (a == n->a && b == n->b) {
        return n;
    }

    if (a == n->a) {
        if (b < n->b) {
            if (n->left) {
                return approx_searcher(a, b, n->left);
            }
            else {
                if (n->parent) {
                    int differenceBetweenCurrent = abs(numify(n->a, n->b) - numify(a, b));
                    int differenceBetweenParent = abs(numify(n->parent->a, n->parent->b) - numify(a, b));
                    return (differenceBetweenCurrent <= differenceBetweenParent) ? n : n->parent;
                }
                return n;
            }
        }
        else {
            if (n->right) {
                return approx_searcher(a, b, n->right);
            }
            else {
                if (n->parent) {
                    int differenceBetweenCurrent = abs(numify(n->a, n->b) - numify(a, b));
                    int differenceBetweenParent = abs(numify(n->parent->a, n->parent->b) - numify(a, b));
                    return (differenceBetweenCurrent <= differenceBetweenParent) ? n : n->parent;
                }
                return n;
            }
        }
    }
    else {

        if (a < n->a) {
            if (n->left) {
                return approx_searcher(a, b, n->left);
            }
            else {
                if (n->parent) {
                    int differenceBetweenCurrent = abs(numify(n->a, n->b) - numify(a, b));
                    int differenceBetweenParent = abs(numify(n->parent->a, n->parent->b) - numify(a, b));
                    return (differenceBetweenCurrent <= differenceBetweenParent) ? n : n->parent;
                }
                return n;
            }
        }
        else {
            if (n->right) {
                return approx_searcher(a, b, n->right);
            }
            else {
                if (n->parent) {
                    int differenceBetweenCurrent = abs(numify(n->a, n->b) - numify(a, b));
                    int differenceBetweenParent = abs(numify(n->parent->a, n->parent->b) - numify(a, b));
                    return (differenceBetweenCurrent <= differenceBetweenParent) ? n : n->parent;
                }
                return n;
            }
        }
    }
}

//Search

bool AVLTree::search(int a, int b)
{
    if (!root) {
        cout << a << "." << b << " not found" << endl;
        return false;
    }
    return searcher(a, b, root);
}

AVLTree::Node* AVLTree::searcher(int a, int b, Node* n)
{
    Node* temp = approx_searcher(a, b, n);

    if (temp == nullptr) {
        cout << a << "." << b << " not found" << endl;
        return nullptr;
    }

    if (temp->a == a & temp->b == b) {
        cout << a << "." << b << " found" << endl;
        return temp;
    }
    cout << a << "." << b << " not found" << endl;
    return nullptr;
}

//Insert value
bool AVLTree::insert(int a, int b)
{
    //if root is null, set this to value to root
    if (!root) {
        root = new Node(a, b);
        cout << a << "." << b << " inserted" << endl;
        return true;
    }
    return balanceCheck(insert(a, b, root));
}

//Recursive Helper for insert
AVLTree::Node* AVLTree::insert(int a, int b, Node* n)
{

    if (a == n->a && b == n->b) {
        return 0;
    }

    if (a == n->a) {
        if (b < n->b) {
            if (n->left) {
                return insert(a, b, n->left);
            }
            else {
                n->left = new Node(a, b);
                n->left->parent = n;
                cout << a << "." << b << " inserted" << endl;
                return n;
            }
        }
        else {
            if (n->right) {
                return insert(a, b, n->right);
            }
            else {
                n->right = new Node(a, b);
                n->right->parent = n;
                cout << a << "." << b << " inserted" << endl;
                return n;
            }
        }
    }
    else {

        if (a < n->a) {
            if (n->left) {
                return insert(a, b, n->left);
            }
            else {
                n->left = new Node(a, b);
                n->left->parent = n;
                cout << a << "." << b << " inserted" << endl;
                return n;
            }
        }
        else {
            if (n->right) {
                return insert(a, b, n->right);
            }
            else {
                n->right = new Node(a, b);
                n->right->parent = n;
                cout << a << "." << b << " inserted" << endl;
                return n;
            }
        }
    }

} //end of insert function

//get successor
AVLTree::Node* AVLTree::getPredecessor(Node* n)
{
    Node* temp = 0;
    if (n->left != nullptr) {
        temp = n->left;
        while (temp->right != nullptr) {
            temp = temp->right;
        } //end of while
        return temp;
    }
    else {
        Node* temp2 = root;
        while (numify(n->a, n->b) != numify(temp2->a, temp2->b)) {
            if (numify(n->a, n->b) >= numify(temp2->a, temp2->b)) {
                temp = temp2;
                temp2 = temp2->right;
            } //end of if check
            else {
                temp2 = temp2->left;
            }
        } //end of second while
        return temp;
    }
    return root;
}

//get successor
AVLTree::Node* AVLTree::getSuccessor(Node* n)
{
    Node* temp = 0;
    if (n->right != nullptr) {
        temp = n->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        } //end of while
        return temp;
    }
    else {
        Node* temp2 = root;
        while (numify(n->a, n->b) != numify(temp2->a, temp2->b)) {
            if (numify(n->a, n->b) <= numify(temp2->a, temp2->b)) {
                temp = temp2;
                temp2 = temp2->left;
            } //end of if check
            else {
                temp2 = temp2->right;
            }
        } //end of second while
        return temp;
    }
    return root;
}

AVLTree::Node* AVLTree::deleteBalanceChecker(Node* n)
{
    if (n == nullptr) {
        return nullptr;
    }
    if (n->left == nullptr && n->right == nullptr) {
        return n;
    }
    if (n->left != nullptr && n->right == nullptr) {
        deleteBalanceChecker(n->left);
    }
    if (n->right != nullptr && n->left == nullptr)
        deleteBalanceChecker(n->right);
    if (n->right && n->left) {
        if (getHeight(n->right) > getHeight(n->left))
            deleteBalanceChecker(n->right);
        else if (getHeight(n->left) > getHeight(n->right))
            deleteBalanceChecker(n->left);
    }
    return deleteBalanceChecker(n->right);
}

bool AVLTree::deleteBalanceCheck(Node* n)
{
    if (nullptr)
        return false; //this should only happen if the one thing delete was a sole root
    return balanceCheck(deleteBalanceChecker(n));
}

//remove function
bool AVLTree::remove(int a, int b)
{
    if (!root)
        return false;
    return deleteBalanceCheck(remove(a, b, approx_searcher(a, b, root)));
}

//recursive function for remove
AVLTree::Node* AVLTree::remove(int a, int b, Node* n)
{
    if (a == n->a && b == n->b) { //we found  the node, so we proceed to delete
        Node* successorNode = getSuccessor(n); //first thing we do is get the sucessor
        Node* temp = n; //make a copy of the n
        if (n->parent) { //IF there is a parent (aka it's not root)
            Node* parentTemp = n->parent; //save the parent (if it has one)
            if (successorNode == nullptr) { //if that sucessor is a nullptr, we are able to delete it right off the bat
                if (temp->left) { //if it has anything on the left, make sure you don't throw that away, it won't have anything on the right
                    n->parent->right = temp->left; //set the node's parent's right to that
                    temp->left->parent = n->parent; //set the left child's parent to node's parent
                    cout << n->a << "." << n->b << " deleted" << endl;

                    n->left = nullptr; //remove everything from n then eventually delete it:
                    n->right = nullptr;
                    n->parent = nullptr;
                    delete n;
                    return parentTemp; //return the parent to the delete balance check
                }
                parentTemp->right = nullptr; //if there was no left child/tree to take care of, we just delete it
                cout << n->a << "." << n->b << " deleted" << endl;

                n->left = nullptr;
                n->right = nullptr;
                n->parent = nullptr;
                delete n;
                return parentTemp; //return parent temp
            } //end of if the sucessor is null
            //if it reaches here, there IS a successor:
            if (n->left) { //if n has a left child/tree that needs to be adopted do that

                Node* nLeftTemp = n->left; //recrusively add it to the bottom of the left of the sucessor
                if (successorNode == parentTemp) {
                    successorNode->left = nLeftTemp;
                    nLeftTemp->parent = successorNode;
                }

                else if (successorNode->left) {
                    Node* snrTemp = successorNode->left; //set a temp of the successor node left for iterating
                    while (snrTemp) {
                        if (snrTemp->left == nullptr) { //if it reaches a nullptr
                            snrTemp->left = new Node(); //create a new node there
                            snrTemp->left = nLeftTemp; //set the new node to the n left
                            nLeftTemp->parent = snrTemp; //and set the parent of that n left to that thing
                        }
                    }
                } //end of checking if the successor node has a left
                else {
                    //if it gets here, then the sucessor node didn't have a left, so we can just stick it on there without a while loop
                    successorNode->left = nLeftTemp;
                    nLeftTemp->parent = successorNode;
                }
            } //end of checking if there was a left to adopt in general

            //if it reaches here, there was no left child so we can just focus on check if there's a right before doing deletion

            if (n->right && n->right != successorNode) { //if there is something to the right but it's not the successor node, there's a right tree to be adopted
                Node* nRightTemp = n->right;
                Node* snParentTemp = n->parent;
                if (successorNode->right) {
                    Node* snrTemp = successorNode->right; //set a temp of the successor node left for iterating
                    while (snrTemp) {
                        if (snrTemp->right == nullptr) { //if it reaches a nullptr
                            snrTemp->right = new Node(); //create a new node there
                            snrTemp->right = nRightTemp; //set the new node to the n left
                            nRightTemp->parent = snrTemp; //and set the parent of that n left to that thing
                            snParentTemp->left = nullptr;
                        }
                    }
                } //end of checking if the successor node has a left
                else {
                    //if it gets here, then the sucessor node didn't have a left, so we can just stick it on there without a while loop
                    successorNode->right = new Node();
                    successorNode->right = nRightTemp;
                    nRightTemp->parent = successorNode;
                    snParentTemp->left = nullptr;
                }
            } //end of if there's a right child/tree

            //check if it was a left or right child of it's parent

            if (successorNode != parentTemp) { //only do this if successor node is not equal to parent temp
                if (parentTemp->right == n)
                    parentTemp->right = successorNode; //its the right child set the right of that parent equal to the sucessor node
                else
                    parentTemp->left = successorNode; //it was the left child  set the left of that parent equal to the sucessor node
                successorNode->parent = parentTemp; //in either case, set the succesor node parent to the parent temp
            }

            if (successorNode == parentTemp && (n->left == nullptr && n->right == nullptr)) { //if the successor node is equal to the parent temp and there was no kids
                if (parentTemp->right == n)
                    parentTemp->right = nullptr; //its the right child set the right of that parent equal to the sucessor node
                else
                    parentTemp->left = nullptr;
            }
            //do normal deletion
            cout << n->a << "." << n->b << " deleted" << endl;

            n->left = nullptr;
            n->right = nullptr;
            n->parent = nullptr;
            delete n;
            return parentTemp; //at the end return parent temp

        } //end of if we got an actual parent

        //if here, that means that its a ROOT
        Node* predecessorNode = getPredecessor(n);
        if (predecessorNode == nullptr && successorNode == nullptr) { //first check if the successor node is a nullptr
            cout << n->a << "." << n->b << " deleted" << endl;
            n->left = nullptr;
            n->right = nullptr;
            delete n;
            root = nullptr;
            delete root;
            return nullptr;
        }
        //if we reach here, there is a predecessor node and a successor node, we first check if the root had a left child/tree
        if (n->left) { //if n has a left child/tree that needs to be adopted do that
            Node* nLeftTemp = n->left; //recrusively add it to the bottom of the left of the sucessor
            if (predecessorNode->left) {
                Node* pnlTemp = predecessorNode->left; //set a temp of the predecessor node left for iterating
                while (pnlTemp) {
                    if (pnlTemp->left == nullptr) { //if it reaches a nullptr
                        pnlTemp->left = new Node(); //create a new node there
                        pnlTemp->left = nLeftTemp; //set the new node to the n left
                        nLeftTemp->parent = pnlTemp; //and set the parent of that n left to that thing
                        nLeftTemp->right = nullptr;
                    }
                }
            } //end of checking if the successor node has a left
            else {
                //if it gets here, then the predecessor node didn't have a left, so we can just stick it on there without a while loop
                if (predecessorNode != nLeftTemp) {
                    predecessorNode->left = nLeftTemp;
                    nLeftTemp->parent = predecessorNode;
                    nLeftTemp->right = nullptr;
                }
            }
        } //end of checking if there was a left to adopt in general
        //if it reached here, there was no child to the left, so we now check if it had a right

        if (n->right) { //if there is something to the right but it's not the successor node, there's a right tree to be adopted
            Node* nRightTemp = n->right;
            if (predecessorNode->right) {
                Node* pnrTemp = predecessorNode->right; //set a temp of the predecessor node right for iterating
                while (pnrTemp) {
                    if (pnrTemp->right == nullptr) { //if it reaches a nullptr
                        pnrTemp->right = new Node(); //create a new node there
                        pnrTemp->right = nRightTemp; //set the new node to the n left
                        nRightTemp->parent = pnrTemp; //and set the parent of that n left to that thing
                    }
                }
            } //end of checking if the successor node has a left
            else {
                //if it gets here, then the sucessor node didn't have a left, so we can just stick it on there without a while loop
                if (predecessorNode->right != nRightTemp) {
                    predecessorNode->right = nRightTemp;
                    nRightTemp->parent = predecessorNode;
                }
            }
        } //end of if there's a right child/tree

        predecessorNode->parent = nullptr; //in either case, set the succesor node parent to the nullptr since it's the root
        root = predecessorNode; //set the root to the successor node
        //do normal deletion
        cout << n->a << "." << n->b << " deleted" << endl;
        n->left = nullptr;
        n->right = nullptr;
        n->parent = nullptr;
        delete n;
        return predecessorNode; //at the end return parent temp

    } //end of making sure we got the actual node
    return nullptr;
}

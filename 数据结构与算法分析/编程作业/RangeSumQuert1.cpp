#include <iostream>
#include <cstdint>
#include <ctime>
#include <assert.h>
using namespace std;

struct Node
{ 
   int64_t key;//关键字 
   int64_t ocurrence;
   int64_t sum;
   int priority;//随机优先级
   Node* left;//左节点
   Node* right;//右节点
};
Node* root;//Treap的根结点

//左旋转
void rotate_left(Node* &node)
{
    Node* x = node->right;
    node->right = x->left;
    x->left = node;
    node = x;

    node->left->sum = (node->left->left ? node->left->left->sum : 0) +  (node->left->right ? node->left->right->sum : 0) + node->left->key * node->left->ocurrence;
    node->sum = (node->right ? node->right->sum : 0) + node->left->sum + node->key * node->ocurrence;
    // cout << "rotate_right\n"; 
    // int64_t tmp = (node->right ? node->right->sum : 0);
    // cout << "sum1: " << node->sum << " sum2: " << tmp << " sum3: " << node->left->sum << endl;
}

//右旋转
void rotate_right(Node* &node)
{   // 右旋转，注意这里传的是Node *&，因为需要修改node的值
    Node* x = node->left;
    node->left = x->right;
    x->right = node;
    node = x;
    // 维持sum的性质
    node->right->sum = node->right->key * node->right->ocurrence+ (node->right->left ? node->right->left->sum : 0) +  (node->right->right ? node->right->right->sum : 0);
    node->sum = node->right->sum + (node->left ? node->left->sum : 0) + node->key * node->ocurrence;
    // cout << "rotate_right\n"; 
    // int64_t tmp = (node->left ? node->left->sum : 0);
    // cout << "sum1: " << node->sum << "sum2: " << node->right->sum << " sum3: " << tmp << endl;
}

//插入操作
void treap_insert(Node* &root, int64_t key, int priority)
{
    //根为NULL，则直接创建此结点为根结点
    if (root == NULL)
    {
        root = (Node*)new Node;
        root->left = NULL;
        root->right = NULL;
        root->priority = priority;
        root->key = key;
        root->sum = key;
        root->ocurrence = 1;
        return;
    }
    else if (key == root->key)
    {
        root->ocurrence += 1;
        root->sum += key;
        return;
    }
    //向左插入结点
    else if (key < root->key)
    {
        treap_insert(root->left, key, priority);
        root->sum += key;
        if (root->left->priority < root->priority)
        rotate_right(root);
    }
    //向右插入结点
    else 
    {
        treap_insert(root->right, key, priority);
        root->sum += key;
        if (root->right->priority < root->priority)
        rotate_left(root);
    }
}

int64_t treap_delete(Node *root, int64_t key)
{
    if (root == NULL)
        return 0;
    else if (key == root->key)
    {
        int64_t oc = root->ocurrence;
        if (oc > 0) {root->ocurrence -= 1; root->sum -= key;}
        return oc;
    }
    else if (key < root->key)
    {
        int64_t oc = treap_delete(root->left, key);
        if (oc > 0) {root->sum -= key;}
        return oc;
    }
    else if (key > root->key)
    {
        int64_t oc = treap_delete(root->right, key);
        if (oc > 0) {root->sum -= key;}
        return oc;
    }
}

//中序遍历
void in_order_traverse(Node* root)
{
  if (root!= NULL)
  {
    in_order_traverse(root->left);
    cout << "key: " << root->key << "  ocurrence: " << root->ocurrence << "  sum: " << root->sum 
    << "priority: " << root->priority << endl; 
    in_order_traverse(root->right);
  }
}

int64_t findl(Node *root, int64_t x)
{
    if (!root)
        return 0;
    else if (root->key < x)
        return (root->left ? root->left->sum : 0) + root->key * root->ocurrence + findl(root->right, x);
    else if (root->key == x)
        return (root->left ? root->left->sum : 0) + root->key * root->ocurrence;
    else if (root->key > x)
        return findl(root->left, x);
}

int64_t findr(Node *root, int64_t x)
{
    if (!root)
        return 0;
    else if (root->key > x)
        return (root->right ? root->right->sum : 0) + root->key * root->ocurrence + findr(root->left, x);
    else if (root->key == x)
        return (root->right ? root->right->sum : 0);
    else if (root->key < x)
        return findr(root->right, x);
}

int64_t opt3(Node *root, int64_t l, int64_t r)
{
    while (root) 
    {
        if (root->key > l && root->key <= r) 
        {
            int64_t t1 = findl(root->left, l);
            int64_t t2 = findr(root->right, r);
            return root->sum - t1 - t2;
        } 
        else if (root->key <= l) 
            root = root->right;
        else if (root->key > r) 
            root = root->left;
    }
    return 0;
    
}


int main()
{
    int64_t Q, P, res, lans = 0;
    cin >> Q >> P;
    int i, pri;
    for (i = 0; i < Q; i++) {
        int opt;
        int64_t arg1, arg2;
        cin >> opt;
        switch (opt)
        {
        case 0:
            // 获取参数
            cin >> arg1;
            arg1 = (arg1 + lans) % P;
            pri = rand();
            treap_insert(root, arg1, pri);
            // in_order_traverse(root);
            break;
        case 1:
            cin >> arg1;
            arg1 = (arg1 + lans) % P;
            res = treap_delete(root, arg1);
            cout << res << endl;
            // in_order_traverse(root);
            break;
        case 2:
            cin >> arg1 >> arg2;
            arg1 = (arg1 + lans) % P;
            arg2 = (arg2 + lans) % P;
            if (arg1 > arg2) {
                int64_t tmp = arg1;
                arg1 = arg2;
                arg2 = tmp;
            }
            res = opt3(root, arg1, arg2);
            lans = res;
            cout << res << endl;
            // in_order_traverse(root);
            break;
        default:
            break;
        }
    }

  
}
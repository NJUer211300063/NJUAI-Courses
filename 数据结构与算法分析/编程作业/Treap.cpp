/**************************************************************
 *This is my Treap!!! 
 **************************************************************/

#include <iostream>
#include <queue>
using namespace std;

/*节点类定义*/
struct Node
{ 
   int key;//关键字 
   int priority;//随机优先级
   Node* left;//左节点
   Node* right;//右节点
};

/*树堆类*/
class Treap
{
private:
    void rotate_r(Node* &node);
    void rotate_l(Node* &node);
public:
    Node *root;
    Treap();
    ~Treap();
    void insert(Node* &root, int key, int priority);
    Node *remove(Node* &root, int key);
    void in_order_traverse(Node* root);
};

Treap::Treap()
{
}

Treap::~Treap()
{   
    queue<Node *> q;
    Node *node = this->root;
    q.push(node);
    while (node)
    {
        Node *tmp = q.front();
        q.push(tmp->left); q.push(tmp->right);
        q.pop();
        free(tmp);
    }
}

//左旋转
void Treap::rotate_l(Node* &node)
{
    Node* x = node->right;
    node->right = x->left;
    x->left =node;
    node = x;
}

//右旋转
void Treap::rotate_r(Node* &node)
{
    Node* x = node->left;
    node->left = x->right;
    x->right = node;
    node = x;
}

void Treap::insert(Node* &root, int key, int priority)
{
    if (root = NULL)
    {
        root = (Node *)new Node;
        root->left = root->right = NULL;
        root->priority = priority;
        root->key = key;
        return;
    } else if (key < root->key)
    {
        this->insert(root->left, key, priority);
        if (root->left->priority < root->priority)
            this->rotate_l(root);
        return;
    } else 
    {
        this->insert(root->right, key, priority);
        if (root->right->priority < root->priority)
            this->rotate_l(root);
        return;
    }
   
   
}

Node *Treap::remove(Node* &root, int key)
{
    if (root != NULL)
    {
        if (key < root->key)
            return this->remove(root->left, key);
        else if (key > root->key)
            return this->remove(root->right, key);
        else
        {
            //左孩子为空
            if (root->left == NULL)
            {
                root = root->right;
                return root;
            }
            //右孩子为空
            else if (root->right == NULL)
            {
                root = root->left;
                return root;
            }
            //左右孩子均不为空
            else
            {
                //先旋转，然后再删除
                if (root->left->priority < root->right->priority)
                {
                    this->rotate_r(root);
                    return this->remove(root->right, key);
                }
                else
                {
                    this->rotate_l(root);
                    return this->remove(root->left,key);
                }
            }
        }
    }
}

void Treap::in_order_traverse(Node* root)
{
  if (root!= NULL)
  {
    in_order_traverse(root->left);
    cout << "key: " << root->key  << "priority: " << root->priority << endl; 
    in_order_traverse(root->right);
  }
}

int main() 
{
    Treap mytreap;
    mytreap.insert(mytreap.root, 32, 12);
    mytreap.insert(mytreap.root, 33, 10);
    mytreap.insert(mytreap.root, 40, 12);
    mytreap.remove(mytreap.root, 32);
    mytreap.in_order_traverse(mytreap.root);
}







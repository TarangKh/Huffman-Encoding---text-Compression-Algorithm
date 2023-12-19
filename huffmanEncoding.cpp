#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// return frequency map for input string
unordered_map<char, int> make_freq_map(string &s)
{
    unordered_map<char, int> map;
    for (int i = 0; i < s.size(); i++)
    {
        map[s[i]]++;
    }
    return map;
}

// tree node structure
class Node
{
public:
    string data;
    int freq;
    Node *left;
    Node *right;
    Node()
    {
        data = "";
        freq = 0;
        left = right = NULL;
    }
 
};

// custom comparator for priority queue
class Mycomparater
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

unordered_map<string, string> encoded;

// char search function   - follow preorder travsrsal
void encoder(Node *root, string s)
{
    if (root->left == NULL && root->right == NULL)
    {
        ::encoded[root->data] = s;
        return;
    }
    if (root == NULL)
        return;
    encoder(root->left, s + "0");
    // s.pop_back();
    encoder(root->right, s + "1");
    // s.pop_back();
}

void preorder(Node *root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// main encoder function
string encode_string(string &s)
{
    unordered_map<char, int> map = make_freq_map(s);            // calling map function
    priority_queue<Node *, vector<Node *>, Mycomparater> pq;    //  declaring priority queue    
    // feeding data into queue
    for (auto i : map)
    {
        // cout << i.first << " : " << i.second << endl;
        Node *new_node = new Node();
        new_node->data = i.first;
        new_node->freq = i.second;
        pq.push(new_node);
    }

    // creating huffman binary tree
    while (pq.size() != 1)
    {
        Node *first = pq.top();
        pq.pop();
        Node *second = pq.top();
        pq.pop();
        Node *new_node = new Node();
        new_node->data = first->data + second->data;
        new_node->freq = first->freq + second->freq;
        new_node->left = first;
        new_node->right = second;
        pq.push(new_node);
    }

    Node *root = pq.top();
  
    // cout << pq.size() <<endl;
    encoder(root, "");           // calling encoder function 
    // preorder(root);
    string ans = "";  

    // creating ecoded string from encoded character map
    for (int i=0; i<s.size(); i++) {
        string st;
        st += s[i];
        ans += encoded[st];
    }

    // return final encoded string
    return ans;
}

string decode_string(string s, Node* root) {
    static string str = "";
    static Node* R = root;
    if (root->left == NULL && root->right == NULL) {
        str += root->data;
        return decode_string(s, R);
    }
    if (s == "") return str;
    if (s[0] == '0') return decode_string((s.size() > 1? s.substr(1): ""), root->left);
    else return decode_string((s.size() > 1? s.substr(1): ""), root->right);

}


// int main()
// {

//     string s = "aaaabbbccd";

//     cout << s << endl;
//     string enc = encode_string(s);
//     cout << enc << endl;
//     return 0;
// }

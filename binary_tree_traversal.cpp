//
//  binary_tree_traversal.cpp
//  
//
//  Created by Alice on 10/21/18.
//

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* Leetcode 94: Inorder Traversal*/
/* method 1 (disadvantage: modify the original binary tree) */
vector<int> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> s;
    vector<int> inorder;
    
    if (root == NULL) return inorder;
    s.push(root);
    
    while (!s.empty()){
        TreeNode* cur = s.top();
        
        if (cur->left != NULL){
            s.push(cur->left);
            cur->left = NULL;
        }
        else{
            inorder.push_back(cur->val);
            s.pop();
            if (cur->right != NULL){
                s.push(cur->right);
                cur->right = NULL;
            }
        }
    }
    return inorder;
}

/* method 2 */
vector<int> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> s;
    vector<int> inorder;
    TreeNode* cur = root;
    
    while (!s.empty() || cur != NULL){
        
        if (cur != NULL){
            s.push(cur);
            cur = cur->left;
        }
        else{
            /* case: no more left child for the current node */
            TreeNode* ancestor = s.top();
            inorder.push_back(ancestor->val);
            s.pop();
            
            cur = ancestor->right;
        }
    }
    return inorder;
}

/* Leetcode 144: Preorder Traversal */
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> preorder;
    stack<TreeNode*> s;
    if (root == NULL) return preorder;
    s.push(root);
    while (!s.empty()){
        TreeNode* cur = s.top();
        preorder.push_back(cur->val);
        s.pop();
        if (cur->right != NULL) s.push(cur->right);
        if (cur->left != NULL) s.push(cur->left);
    }
    return preorder;
}

/* Leetcode 145: Postorder Traversal */
vector<int> postorderTraversal(TreeNode* root) {
    deque<int> postorder;
    stack<TreeNode*> s;
    if (root == NULL) return {};
    s.push(root);
    
    while (!s.empty()){
        TreeNode* cur = s.top();
        s.pop();
        
        postorder.push_front(cur->val);
        if (cur->left) s.push(cur->left);
        if (cur->right) s.push(cur->right);
    }
    return vector<int> (postorder.begin(), postorder.end());
}


/* Leetcode 889: construct binary tree from Preorder and Postorder Traversal */
TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    int size = pre.size();
    if (!size) return NULL;
    stack<TreeNode*> s;
    TreeNode* root = new TreeNode(pre[0]);
    s.push(root);
    
    for (int i = 1, j = 0; i < size; i++){
        TreeNode* cur = new TreeNode(pre[i]);
        
        while (s.top()->val == post[j]){
            s.pop();
            j++;
        }
        if (s.top()->left == NULL) s.top()->left = cur;
        else s.top()->right = cur;
        
        s.push(cur);
    }
    return root;
}

/* Leetcode 105: construct binary tree from Preorder and Inorder Traversal */
TreeNode* helper(vector<int>& preorder, vector<int>& inorder, int prestart, int instart, int inend){
    if (prestart >= preorder.size() || instart > inend)
        return NULL;
    
    int inindex = -1;
    for (int i = instart; i <= inend; i++){
        if (inorder[i] == preorder[prestart]){
            inindex = i;
            break;
        }
    }
    TreeNode* root = new TreeNode(preorder[prestart]);
    root->left = helper(preorder, inorder, prestart + 1, instart, inindex - 1);
    root->right = helper(preorder, inorder, prestart + inindex - instart + 1, inindex + 1, inend);
    
    return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return helper(preorder, inorder, 0, 0, inorder.size());
}

/* Leetcode 106: construct binary tree from Inorder and PostOrder Traversal */
TreeNode* helper(vector<int>& inorder, vector<int>& postorder, int postend, int instart, int inend){
    if (postend < 0 || instart > inend)
        return NULL;
    
    int size = inorder.size();
    int inindex = -1;
    
    for (int i = 0; i < size; i++){
        if (inorder[i] == postorder[postend]){
            inindex = i;
            break;
        }
    }
    TreeNode* root = new TreeNode(postorder[postend]);
    root->right = helper(inorder, postorder, postend - 1, inindex + 1, inend);
    root->left = helper(inorder, postorder, postend - 1 - (inend - inindex), instart, inindex - 1);
    
    return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    return helper(inorder, postorder, postorder.size() - 1, 0, inorder.size() - 1);
}

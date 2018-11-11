//
//  Union_find.cpp
//  
//
//  Created by Alice on 11/7/18.
//

class Unionfind{
public:
    int union_count;
    vector<int> id;
    vector<int> size;
    
    Unionfind(int len){
        union_count = len;
        id = vector<int> (len);
        size = vector<int> (len);
        
        for (int i = 0; i < len; i++){
            id[i] = i;
            size[i] = 1;
        }
    }
    
    bool find(int p, int q){
        return root(p) == root(q);
    }
    
    void unions(int p, int q){
        int pi = root(p), qi = root(q);
        if (size[pi] < size[qi]){
            id[pi] = qi;
            size[qi] += size[pi];
        }
        else{
            id[qi] = pi;
            size[pi] += size[qi];
        }
        union_count--;
    }
    
    int root(int i){
        while (i != id[i]){
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }
};

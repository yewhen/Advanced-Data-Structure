class LRUCache {
private:
	class LRUCacheItem{
	public:
		int val;
		int key;
		LRUCacheItem* prev;
		LRUCacheItem* next;
		LRUCacheItem (int key, int val) : val(val), key(key), prev(NULL), next(NULL) {}
		
	};
	int capacity;
	unordered_map<int, LRUCacheItem*> entries;
	LRUCacheItem* head;
	LRUCacheItem* tail;
	
	void moveToHead(LRUCacheItem* entry){
		/* start is the actual head */
		LRUCacheItem* start = this->head->next;
		if (entry == start || entry == NULL) return;
		
		LRUCacheItem* next = entry->next;
		LRUCacheItem* prev = entry->prev;
		
		/* remove entry from original position */
		if (next != NULL) next->prev = prev;
		if (prev != NULL) prev->next = next;
		
		/* add entry between dummy head and start */
		start->prev = entry;
		this->head->next = entry;
		
		/* modify entry pointer */
		entry->prev = this->head;
		entry->next = start;
	}
public:
	LRUCache(int capacity) {
		this->capacity = capacity;
		this->head = new LRUCacheItem (-1, -1);
		this->tail = new LRUCacheItem (-1, -1);
		this->head->next = tail;
		this->tail->prev = head;
	}
	
	int get(int key) {
		if (this->entries.find(key) == this->entries.end()) return -1;
		LRUCacheItem* entry = this->entries[key];
		moveToHead(entry);
		
		return entry->val;
	}
	
	void put(int key, int value) {
		LRUCacheItem* entry;
		if (this->entries.find(key) != this->entries.end()){
			entry = this->entries[key];
			entry->val = value;

		}
		else{
			entry = new LRUCacheItem(key, value);
			if (this->entries.size() == this->capacity){
				LRUCacheItem* end = this->tail->prev;
				LRUCacheItem* endPrev = end->prev;
				this->entries.erase(end->key);
				endPrev->next = this->tail;
				this->tail->prev = endPrev;
				
				end->prev = end->next = NULL;
				delete end;
			}
			this->entries[key] = entry;
		}
		moveToHead(entry);
	}
};


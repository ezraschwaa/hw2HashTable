/*
 * Implementation for a generic cache object.
 * Data is given as blobs (void *) of a given size,
 * and indexed by a string key.
 */

//Notes:
//We add the brackets to make it a definition
//adding 'cahce::' attributes the function to the class
//g++ -c -Wextra -pedantic -Wall cache.cc

#include "cache.hh"
#include <unordered_map>
#include <cstring>
using namespace std;

class Cache::Impl {
  index_type maxmem_;
  evictor_type evictor_;
  hash_func hasher_;
  index_type memused_;
  string biggest_;
  unordered_map<string, void*> map_;

public:
  Impl(index_type maxmem, evictor_type evictor, hash_func hasher)
    : maxmem_(maxmem), evictor_(evictor), hasher_(hasher), memused_(0), biggest_(""), map_()
  {

  }

  ~Impl() = default;
  
  void evict() {
      // if mem used exceeds max mem evict the biggest element
      map_.erase(biggest_);
  }

  void set(key_type key, val_type val, index_type size)
  {
    // check if memory used has exceeded max value also check if there is enough memory for the incoming value
    if (memused_ + size>= maxmem_) {

       evict();
    }
    // assign value in unordered map
    map_[key] = new val_type[size];
    // deep copy values into cache
    memcpy(map_[key],val,size);
    // increase memory used
    memused_ += size;
    // keep track of biggest cache entry
    if (biggest_ == "") {
       biggest_ = key;
    } else {
       // if new entry is greater than previous entry replace the key
       if (map_[biggest_] < *static_cast<const int*>(size) ){
          biggest_ = key;
       }
    }
  }

  val_type get(key_type key, index_type& val_size) const
  {
    //We can't use map_[key] because that is shorthand for map_.operator[](key) 
    //which wants to modify map_.  Because we have const it means
    //
    // why can't we use map_.operator[](key)?
    // what does auto mean in C++
    auto search = map_.find(key);
    // unordered map search in c++
    if (search != map_.end()){
      return search->second;
    } else {
      return NULL;
    }
  }

  void del(key_type key)
  {
    // remove key from mapping don't we need to modify memused here?
    map_.erase(key);
    
  }
  index_type space_used() const
  {
    return memused_;
  }
};

// Create a new cache object with a given maximum memory capacity.
Cache::Cache(index_type maxmem,
evictor_type evictor,
hash_func hasher)
  : pImpl_(new Impl(maxmem, evictor, hasher))
{

}

Cache::~Cache()
{
}


// Add a <key, value> pair to the cache.
// If key already exists, it will overwrite the old value.
// Both the key and the value are to be deep-copied (not just pointer copied).
// If maxmem capacity is exceeded, sufficient values will be removed
// from the cache to accomodate the new value.
void 
Cache::set(key_type key, val_type val, index_type size)
{
  pImpl_->set(key,val,size);
}

// Retrieve a pointer to the value associated with key in the cache,
// or NULL if not found.
// Sets the actual size of the returned value (in bytes) in val_size.
Cache::val_type 
Cache::get(key_type key, index_type& val_size) const
{
  return pImpl_->get(key,val_size);
}

// Delete an object from the cache, if it's still there
void 
Cache::del(key_type key)
{
  pImpl_->del(key);
}

// Compute the total amount of memory used up by all cache values (not keys)
Cache::index_type 
Cache::space_used() const
{
  return pImpl_->space_used();
}

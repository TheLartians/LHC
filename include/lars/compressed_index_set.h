#pragma once 

#include <lars/unused.h>

#include <list>
#include <ostream>
#include <assert.h> 

namespace lars{

  template <class Index> struct IndexRange{
    Index first;
    Index last;
    IndexRange(Index f,Index l):first(f),last(l){}
  };
  
  template <class Index> class CompressedIndexSet{
  private:
    std::list<IndexRange<Index>> _index_ranges;
    
  public:
    
    class Iterator{
    private:
      friend CompressedIndexSet<Index>;
      typename std::list<IndexRange<Index>>::const_iterator it;
      Index offset = 0;
    public:
      Index operator*(){ return it->first + offset; }
      void operator++(){ if(**this < it->last) offset++; else{ ++it; offset = 0; } }
      bool operator!=(const Iterator &other){ return it != other.it || offset != other.offset; }
    };
    
    Iterator begin()const{ Iterator it; it.it = index_ranges().begin(); return it; }
    Iterator end()const{ Iterator it; it.it = index_ranges().end(); return it; }
    size_t count()const{ size_t res = 0; for(auto r:this->index_ranges()) res += r.last - r.first + 1; return res;  }
    
    void insert_index_range(Index first,Index last);
    void remove_index_range(Index first,Index last);
    
    void insert_index(Index i){ insert_index_range(i,i); }
    void remove_index(Index i){ remove_index_range(i,i); }
    
    const auto &index_ranges()const{ return _index_ranges; }
    void clear(){ _index_ranges.clear(); }
    
    Index min()const{ assert(index_ranges().size() > 0); return index_ranges().front().first; }
    Index max()const{ assert(index_ranges().size() > 0); return index_ranges().back().last; }
    
    void add_indices(const CompressedIndexSet<Index> &other){ for(auto &r:other.index_ranges()) insert_index_range(r.first, r.last); }
    void remove_indices(const CompressedIndexSet<Index> &other){ for(auto &r:other.index_ranges()) remove_index_range(r.first, r.last); }
    void unite(const CompressedIndexSet<Index> &other){ add_indices(other); }
    void intersect(const CompressedIndexSet<Index> &other){ CompressedIndexSet<Index> tmp; tmp.insert_index_range(min(),max()); tmp.remove_indices(other); remove_indices(tmp); }
  };
  
  
  template <class Index> void CompressedIndexSet<Index>::insert_index_range(Index first,Index last){
    assert(last >= first);
    
    auto it = _index_ranges.begin(),end = _index_ranges.end();
    for(;it != end;++it){
      // TODO: replace linear search with faster algorithm
      if(it->last + 1 >= first) break;
    }
    
    if(it == end){
      _index_ranges.emplace_back(first,last);
      return;
    }
    
    if(first + 1 >= it->first){ // begin is inside
      it->first = std::min(first,it->first);
      if(last > it->last){ // end is right
        it->last = last;
      }else{ // end is inside
        return;
      }
    }else{ // begin is left
      if(last < it->first){ // end is left
        _index_ranges.emplace(it, first,last);
        end = _index_ranges.end();
      }else{
        if(last > it->last){ // end is right
          it->first = first;
          it->last = last;
        }
        else{ // end is inside
          it->first = first;
          return;
        }
      }
    }
    
    auto next = it; ++next;
    auto invalid = next;
    while(invalid != end && invalid->first <= last + 1){
      ++invalid;
    }
    if(invalid != next){
      auto before = invalid; before--;
      it->last = std::max(last,before->last);
      _index_ranges.erase(next,invalid);
    }
    
  }
  
  template <class Index> void CompressedIndexSet<Index>::remove_index_range(Index first,Index last){
    assert(last >= first);
    
    auto it = _index_ranges.begin(),end = _index_ranges.end();
    
    while(it != end){
      if(it->last >= first){ // end is right of begin
        if(it->first > last){ // begin is right of end
          break;
        }
        else{ // begin is left of end
          if(it->first < first){ // begin is left of interval
            if(it->last > last){ // end is right of interval
              auto next = it; ++next;
              _index_ranges.emplace(next, last+1, it->last);
              it->last = first - 1;
            }
            else{
              if(it->first >= first){
                it = _index_ranges.erase(it);
                continue;
              }
              else{
                it->last = first - 1;
              }
            }
          }
          else{
            if(it->last <= last){
              it = _index_ranges.erase(it);
              continue;
            }
            else{
              it->first = last + 1;
            }
          }
        }
      }
      ++it;
    }
  }
  
  
  template <class Char, class Traits, class Index> std::basic_ostream<Char, Traits> & operator<<(std::basic_ostream<Char, Traits> &stream, const IndexRange<Index> &range){
    if(range.first != range.last) stream << '[' << range.first << ',' << range.last << ']'; else stream << '{' << range.first << '}';
    return stream;
  }
  
  template <class Char, class Traits, class Index> std::basic_ostream<Char, Traits> & operator<<(std::basic_ostream<Char, Traits> &stream, const CompressedIndexSet<Index> &indices){
    stream << '{';
    for(auto &r:indices.index_ranges()){
      stream << r;
      if(&r != &indices.index_ranges().back()) stream << ',';
    }
    stream << '}';
    return stream;
  }
  
}

#ifndef AKEALX_GRX
#define AKEALX_GRX

// Akai Keisanki Algorithm eXperiments - Graph eXperiments

#include <vector>
#include <algorithm>

class DisjointSet
{
protected:

  void addSubTree(const unsigned long& i, const unsigned long& c = 1)
  {
    subtree[i] += c;
    if (parent[i] != i) addSubTree(parent[i], c);
  }

public:

  std::vector<unsigned long> parent;
  std::vector<unsigned long> subtree;

  DisjointSet ()
  {}

  DisjointSet (const unsigned long& size)
  {
    parent.resize(size);
    subtree.resize(size);
    for (unsigned long i = 0; i < size; i++)
    {
      parent[i] = i;
      subtree[i] = 1;
    }
  }

  void addChild(const unsigned long& p)
  {
    parent.push_back(p);
    subtree.push_back(1);
    addSubTree(p);
  }

  unsigned long find (const unsigned long& i)
  {
    if (parent[i] == i) return i;
    return find(parent[i]);
  }

  void unite(const unsigned long& i, const unsigned long& j)
  {
    unsigned long fi = find(i);
    unsigned long fj = find(j);

    if (subtree[fi] > subtree[fj])
    { fj ^= fi; fi ^= fj; fj ^= fi; }

    parent[fj] = fi;
    addSubTree(fi, subtree[fj]);
  }

  void collapse(const unsigned long& i)
  {
    parent[i] = i;
    parent[find(i)] = i;
    for (unsigned long p : parent)
      if (find(i) == find(p))
      {
        parent[p] = i;
      }
  }

  void compress()
  {
    for (unsigned long p : parent)
      parent[p] = find(p);
  }
}

#endif

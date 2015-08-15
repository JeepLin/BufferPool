
#ifndef ___BUFFER_POOL_H
#define ___BUFFER_POOL_H

typedef unsigned int UINT;

struct Node
{
  char name[10];
  UINT score;
  UINT age;
  char dsp[1024];
}*Pnode;

class BufferPool
{
private:
  UINT m_uMaxBufferNum;
  UINT m_uCurBusyBufferNum;
public:
  BufferPool(UINT uNum);
  Pnode GetNode();
  void RealseNode(Pnode pnode);
  void DestroyPool();
};
#endif


#ifndef ___BUFFER_POOL_H
#define ___BUFFER_POOL_H

#include <pthread.h>
#include <stdlib.h>

typedef unsigned int UINT;

struct Node
{
  char name[10];
  UINT score;
  UINT age;
  char dsp[1024];
  Node* next;
}*Pnode;

class BufferPool
{
private:
  UINT m_uMaxBufferNum;
  UINT m_uCurBusyBufferNum;
  Pnode m_pHead;
  Pnode m_pDestroyNode;
  pthread_mutex_t m_mutex;
  pthread_cond_t m_cond;
public:
  BufferPool(UINT uNum);
  Pnode GetNode();
  void RealseNode(Pnode pnode);
  void DestroyPool();
};

#endif

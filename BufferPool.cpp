#include "BufferPool.h"


BufferPool::BufferPool(UINT uNum)
{
  m_pHead= NULL;
  m_pDestroyHead= NULL;
  m_uMaxBufferNum= uNum;
  m_uCurBusyBufferNum= 0;
  
  if(uNum!= 0)
  {
    m_pHead= (Pnode)malloc(uNum*sizeof(Node));
    assert(m_pHead== NULL);
    m_pDestroyHead= m_pHead;
    
    for(UINT num= 0; num< uNum-1; num++)
    {
      m_pHead[num].next= &m_pHead[num+ 1];    
    }
  }
  
  pthread_mutex_init(&m_mutex,NULL);
  pthread_cond_init(&m_cond,NULL);
}

Pnode BufferPool::GetNode()
{
  pthread_mutex_lock(&m_mutex);
  
  while(m_pHead== NULL)
  {
    pthread_cond_wait(&m_cond,&m_mutex);
  }
  
  Pnode pRet= m_pHead;
  m_pHead= m_pHead->next;
  m_uCurBusyBufferNum++;
  pthread_mutex_unlock(&m_mutex);
  return pRet;
}

void BufferPool::RealseNode(Pnode pnode)
{
  pthread_mutex_lock(&m_mutex);
  pnode->next= m_pHead;
  m_pHead= pnode;
  m_uCurBusyBufferNum--;
  if(pnode->next== NULL)
  {
    pthread_cond_signal(&m_cond);
  }
  pthread_mutex_unlock(&m_mutex);
}

void BufferPool::DestroyPool()
{
  if(m_pDestroyHead!= NULL)
  {
    free(m_pDestroyHead);
  }
}

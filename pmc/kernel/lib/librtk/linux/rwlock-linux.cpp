#include "../precomp.h"
#pragma hdrstop

#if defined(__LINUX__)
CRWLock::CRWLock()
{
	 pthread_rwlock_init(&LockData, NULL);
}

CRWLock::~CRWLock()
{
	 pthread_rwlock_destroy(&LockData);
}

void CRWLock::ReadLock()
{
	 pthread_rwlock_rdlock(&LockData);
}

void CRWLock::WriteLock()
{
	 pthread_rwlock_wrlock(&LockData);
}

void CRWLock::Release()
{
	 pthread_rwlock_unlock(&LockData);
}

#endif

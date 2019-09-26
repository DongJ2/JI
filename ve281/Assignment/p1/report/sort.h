#ifndef __SORT_H__
#define __SORT_H__

void bubble(long int *a, int len);

void insertion(long int *a, int len);

void selection(long int *a, int len);

void mergesort(long int *a, int left, int right);

void merge(long int *a, int left, int mid, int right);

void quick_extra(long int *a, int left, int right);

void quick_inplace(long int *a, int left, int right);

int partition_ex(long int *a, int left, int right);

int partition_in(long int *a, int left, int right);

#endif // __SORT_H__

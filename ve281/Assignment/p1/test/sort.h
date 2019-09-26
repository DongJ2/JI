#ifndef __SORT_H__
#define __SORT_H__

void bubble(int *a, int len);

void insertion(int *a, int len);

void selection(int *a, int len);

void mergesort(int *a, int left, int right);

void merge(int *a, int left, int mid, int right);

void quick_extra(int *a, int left, int right);

void quick_inplace(int *a, int left, int right);

int partition_ex(int *a, int left, int right);

int partition_in(int *a, int left, int right);

#endif // __SORT_H__

// time.c
#include "philo.h"

//現在時刻を取得する関数
long get_current_time() {
    struct timeval tv;                         // 1. 時刻を格納する構造体を定義
    gettimeofday(&tv, NULL);                   // 2. 現在時刻を取得してtvに格納
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // 3. 秒とマイクロ秒をミリ秒に変換
}



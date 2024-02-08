//
// Created by jonyl on 2023/11/8.
//

#include "CountDown.h"

int CountDown(){
    target_date.tm_year = countdown_year - 1900;  //count from 1900
    target_date.tm_mon = countdown_month - 1;  // tm_mon is 0-11
    target_date.tm_mday = countdown_day;

    time_t current_time = time(nullptr);
    // 转换为tm结构体以便操作
    tm* current_date = localtime(&current_time);

    // 转换目标日期和当前日期为time_t格式
    time_t target_day = mktime(&target_date);
    time_t current_day = mktime(current_date);
    // 计算差值
    double difference = difftime(target_day, current_day);
    // 将差值转换为天数
    int days_left = difference / (60 * 60 * 24);

    return days_left;
}
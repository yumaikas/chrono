#include <janet.h>
#include "date.h"

#define JDOC(x) x
using namespace date;



struct chrono_ymd {
    int32_t y;
    int32_t m;
    int32_t d;
};

struct chrono_ym {
    int32_t y;
    int32_t m;
};

int32_t janet_int_field(JanetDictView dict, const char *key) {
    Janet maybe_val = janet_dictionary_get(dict.kvs, dict.cap, janet_ckeywordv(key));
    if (!janet_checktype(maybe_val, JANET_NUMBER)) {
        janet_panicf("Expected an integer for field %s, got a %t", key, maybe_val);
    }
    return (int32_t)janet_unwrap_number(maybe_val);
}

chrono_ymd date_from_dict(JanetDictView date) {
    chrono_ymd ymd;
    ymd.y = janet_int_field(date, "year");
    ymd.m = janet_int_field(date, "month");
    ymd.d = janet_int_field(date, "month-day");
    return ymd;
}

chrono_ym ym_from_dict(JanetDictView date) {
    chrono_ym ymd;
    ymd.y = janet_int_field(date, "year");
    ymd.m = janet_int_field(date, "month");
    return ymd;
}

static Janet j_add_days(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    JanetDictView date = janet_getdictionary(argv, 0);
    int32_t days_to_add = janet_getinteger(argv, 1);

    chrono_ymd ymd = date_from_dict(date);
    auto curr_date = year{ymd.y}/ymd.m/ymd.d;

    auto days_duration = std::chrono::floor<days>((sys_days)curr_date);
    days_duration += days(days_to_add);
    auto new_date = year_month_day{(sys_days)days_duration};
    
    JanetKV *dt = janet_struct_begin(3);
    janet_struct_put(dt, janet_ckeywordv("year"), janet_wrap_number((int32_t)(int)new_date.year()));
    janet_struct_put(dt, janet_ckeywordv("month"), janet_wrap_number((int32_t)(unsigned)new_date.month()));
    janet_struct_put(dt, janet_ckeywordv("month-day"), janet_wrap_number((int32_t)(unsigned)new_date.day()));
    return janet_wrap_struct(janet_struct_end(dt));
}

static Janet j_add_months(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    JanetDictView date = janet_getdictionary(argv, 0);
    int32_t months_to_add = janet_getinteger(argv, 1);

    chrono_ymd ymd = date_from_dict(date);
    auto curr_date = year{ymd.y}/ymd.m/ymd.d;
    curr_date += months{months_to_add};

    auto days_duration = std::chrono::floor<days>((sys_days)curr_date);
    auto new_date = year_month_day{(sys_days)days_duration};

    JanetKV *dt = janet_struct_begin(3);
    janet_struct_put(dt, janet_ckeywordv("year"), janet_wrap_number((int32_t)(int)new_date.year()));
    janet_struct_put(dt, janet_ckeywordv("month"), janet_wrap_number((int32_t)(unsigned)new_date.month()));
    janet_struct_put(dt, janet_ckeywordv("month-day"), janet_wrap_number((int32_t)(unsigned)new_date.day()));
    return janet_wrap_struct(janet_struct_end(dt));
}

static Janet j_add_years(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    JanetDictView date = janet_getdictionary(argv, 0);
    int32_t years_to_add = janet_getinteger(argv, 1);

    chrono_ymd ymd = date_from_dict(date);
    auto curr_date = year{ymd.y}/ymd.m/ymd.d;
    curr_date += years{years_to_add};

    auto days_duration = std::chrono::floor<days>((sys_days)curr_date);
    auto new_date = year_month_day{(sys_days)days_duration};

    JanetKV *dt = janet_struct_begin(3);
    janet_struct_put(dt, janet_ckeywordv("year"), janet_wrap_number((int32_t)(int)new_date.year()));
    janet_struct_put(dt, janet_ckeywordv("month"), janet_wrap_number((int32_t)(unsigned)new_date.month()));
    janet_struct_put(dt, janet_ckeywordv("month-day"), janet_wrap_number((int32_t)(unsigned)new_date.day()));
    return janet_wrap_struct(janet_struct_end(dt));
}

// (nth-weekday-of year-month nth weekday)
static Janet j_nth_weekday_of_month(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);

    JanetDictView year_month = janet_getdictionary(argv, 0);
    int32_t nth = janet_getinteger(argv, 1);
    int32_t wd = janet_getinteger(argv, 2);

    if (nth > 5 || nth < 0) {
        janet_panicf("Invalid nth argument %d, it should be between 0 and 5", nth);
    }
    if (wd > 6 || wd < 0) {
        janet_panicf("Invalid weekday argument %d, it should be between 0 and 6", wd);
    }

    chrono_ym ym = ym_from_dict(year_month);
    auto ym_wd = year{ym.y}/month{(unsigned)ym.m}/weekday_indexed(weekday{(unsigned)wd}, nth);
    auto curr_date = year_month_day{ym_wd};

    JanetKV *dt = janet_struct_begin(3);
    janet_struct_put(dt, janet_ckeywordv("year"), janet_wrap_number((int32_t)(int)curr_date.year()));
    janet_struct_put(dt, janet_ckeywordv("month"), janet_wrap_number((int32_t)(unsigned)curr_date.month()));
    janet_struct_put(dt, janet_ckeywordv("month-day"), janet_wrap_number((int32_t)(unsigned)curr_date.day()));
    return janet_wrap_struct(janet_struct_end(dt));
}

static const JanetReg cfuns[] = {
    {"add-days", j_add_days, JDOC(
            "`(add-days date days-to-add)`\n"
            "\n" 
            "Add a number of days to a given date, returning a year/month/day struct.\n"
            "\n"
            "date: A dictionary that contains at least a year, month and month-day field. An os/date can be used.\n"
            "days-to-add: An integer number of days to add\n"
            )},
    {"add-months", j_add_months, JDOC(
            "`(add-months date months-to-add)`\n"
            "\n" 
            "Add a number of months to a given date, returning a year/month/day struct.\n"
            "\n"
            "date: A dictionary that contains at least a year, month and month-day field. An os/date can be used.\n"
            "months-to-add: An integer number of months to add\n"
            )},
    {"add-years", j_add_years, JDOC(
            "`(add-years date years-to-add)`\n"
            "\n" 
            "Add a number of months to a given date, returning a year/month/day struct.\n"
            "\n"
            "date: A dictionary that contains at least a year, month and month-day field. An os/date can be used.\n"
            "years-to-add: An integer number of years to add\n"
            )},
     {"nth-weekday-of", j_nth_weekday_of_month, JDOC(
            "`(nth-weekday-of year-month nth weekday)`\n"
            "\n" 
            "Compute the nth weekday of a given month and year\n"
            "\n"
            "year-month: A dictionary that contains at least a year and a month. Can be an os/date.\n"
            "nth: the index of the weekday in the month, 0 representing the first instance of the day.\n"
            "weekday: The nth day of the week, 0 -> Sunday, 1 -> Sunday ... 6 -> Saturday\n"
            )},
    {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
    // Janet docstr = janet_wrap_string("chrono: A date math library");
    // janet_table_put(env, janet_ckeywordv("doc"), docstr);
    janet_cfuns(env, "chrono", cfuns);
}

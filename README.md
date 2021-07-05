# chrono: std::chrono and howard hinnant's date math exposed to Janet

## About

This library exposes a date math and repeating patterns library built atop std::chrono and <https://howardhinnant.github.io/date/date.html>. It does require support for C++ 20 to compile.

To see more details, check out [api.md](api.md). 

## Example

```janet
(import chrono)
(chrono/add-days {:year 2021 :month 7 :month-day 5 } 3) # { :year 2021 :month 7 :month-day 8 }
```

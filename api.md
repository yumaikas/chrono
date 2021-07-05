### add-months
`(add-months date months-to-add)`

Add a number of months to a given date, returning a year/month/day struct.

date: A dictionary that contains at least a year, month and month-day field. An os/date can be used.
months-to-add: An integer number of months to add


### nth-weekday-of
`(nth-weekday-of year-month nth weekday)`

Compute the nth weekday of a given month and year

year-month: A dictionary that contains at least a year and a month. Can be an os/date.
nth: the index of the weekday in the month, 0 representing the first instance of the day.
weekday: The nth day of the week, 0 -> Sunday, 1 -> Sunday ... 6 -> Saturday


### add-days
`(add-days date days-to-add)`

Add a number of days to a given date, returning a year/month/day struct.

date: A dictionary that contains at least a year, month and month-day field. An os/date can be used.
days-to-add: An integer number of days to add


### add-years
`(add-years date years-to-add)`

Add a number of months to a given date, returning a year/month/day struct.

date: A dictionary that contains at least a year, month and month-day field. An os/date can be used.
years-to-add: An integer number of years to add



(use testament)
(print (os/cwd))

(import ../build/chrono :as chrono)

(defmacro ymd [y m d] ~{:year ,y :month ,m :month-day ,d} )
(defmacro ym [y m] ~{:year ,y :month ,m})

(def Sunday 0)
(def Monday 1)
(def Tuesday 2)
(def Wednesday 3)
(def Thursday 4)
(def Friday 5)
(def Saturday 6)

(exercise! 
  [] 

  (deftest date-addition 

    (assert-equal (ymd 2021 1 23) (chrono/add-days (ymd 2021 1 20) 3))
    (assert-equal (ymd 2022 1 20) (chrono/add-days (ymd 2021 1 20) 365))
    (assert-equal (ymd 2022 1 20) (chrono/add-days (ymd 2021 1 20) 365))

    (assert-equal (ymd 2021 2 20) (chrono/add-months (ymd 2021 1 20) 1))
    (assert-equal (ymd 2021 3 28) (chrono/add-months (ymd 2021 2 28) 1))
    (assert-equal (ymd 2021 3 1) (chrono/add-months (ymd 2020 2 29) 12))

    (assert-equal (ymd 2021 3 1) (chrono/add-years (ymd 2020 2 29) 1))

    (assert-equal (ymd 2021 4 4) (chrono/nth-weekday-of (ym 2021 4) 1 Sunday))
    (assert-equal (ymd 2021 4 4) (chrono/nth-weekday-of (ym 2021 4) 1 Sunday))
    )
  )

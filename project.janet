(declare-project 
      :name "chrono"
      :description "A library that exposes some date math based on C++'s chrono and Howard Hinnant's date.h")

(declare-native :name "chrono" :source @["chrono.cpp"])


(phony "docs" ["build"] 
       (def out @"# Chrono: date math for janet")
       (buffer/push out "\n\n")
       (each kv (filter |(= (type ($ 0)) :symbol) (pairs (require "./build/chrono")))
         (pp (type (kv 0)))
         (pp (kv 0))
         (buffer/push out "### " (kv 0) "\n")
         (buffer/push out (get-in kv [1 :doc]) "\n\n"))
       (spit "api.md" out))

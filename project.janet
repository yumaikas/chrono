(declare-project 
      :name "chrono"
      :author "Andrew Owen <yumaikas94@gmail.com>"
      :url "https://github.com/yumaikas/chrono"
      :description "A library that exposes some date math based on C++'s chrono and Howard Hinnant's date.h")

(def cppflags (match (os/which) 
                :windows []
                # Hoping this works on osx and bsd
                _ ["-std=c++20"]))

(declare-native :cppflags cppflags :name "chrono" :source @["chrono.cpp"])

(phony "docs" ["build"] 
       (def out @"")
       (def docs (require "./build/chrono"))
       (buffer/push out "# " (docs :doc))
       (buffer/push out "\n\n")
       (each kv (filter |(= (type ($ 0)) :symbol) (pairs docs))
         (buffer/push out "### " (kv 0) "\n")
         (buffer/push out (get-in kv [1 :doc]) "\n\n"))
       (spit "api.md" out))

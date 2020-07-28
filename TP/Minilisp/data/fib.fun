fib_util [a] [b] [i] : (if (= i 0) b (fib_util (+ a b) a (- i 1)))

fib [n] : (fib_util 1 0 n)

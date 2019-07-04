if = R<U 2 1, U 4 2>
pow = R<S<N, Z>, S<mul, U 3 3, U 3 1>>//R<S<N, Z>, S<R<Z, S<R<U 1 1, S<N, U 3 3>>, U 3 1, U 3 3>>, U 3 3, U 3 1>>
mul = R<Z, S<add, U 3 1, U 3 3>>//R<Z, S<R<U 1 1, S<N, U 3 3>>, U 3 1, U 3 3>>
add = R<U 1 1, S<N, U 3 3>>
even = S<R<S<N, Z>, S<not, U 3 3>>, Z, U 1 1> //S<R<S<N, Z>, S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, U 3 3>>, Z, U 1 1>
not = S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>
prime = S<eq, S<R<Z, S<add, S<divisible, U 3 1, U 3 2>, U 3 3>>, U 1 1, U 1 1>, S<N, Z>>
//S<S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 1 1, S<N, U 3 3>>, R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, S<R<U 1 1, S< S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>>>, S<R<Z, S<R<U 1 1, S<N, U 3 3>>, S<S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 2 1, S<R<U 2 1, U 4 2>, U 4 4, S<R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 4 4, U 4 2>, S<S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>>, U 4 4, U 4 2>>>, U 2 1, U 2 2, U 2 1>>, U 3 1, U 3 2>, U 3 3>>, U 1 1, U 1 1>, S<N, Z>>
eq = S<not, abs> //S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 1 1, S<N, U 3 3>>, R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, S<R<U 1 1, S< S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>>>
abs = S<add, sub, subrev> //S<R<U 1 1, S<N, U 3 3>>, R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, S<R<U 1 1, S< S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>>
sub = R<U 1 1, S<pred, U 3 3>>//R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>
subrev = S<sub, U 2 2, U 2 1>//S<R<U 1 1, S< S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>
pred = S<R<Z, U 3 2>, Z, U 1 1>
divisible = S<not, mod>//S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 2 1, S<R<U 2 1, U 4 2>, U 4 4, S<R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 4 4, U 4 2>, S<S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>>, U 4 4, U 4 2>>>, U 2 1, U 2 2, U 2 1>>
mod = S<R<U 2 1, S<if, U 4 4, S<sub, U 4 4, U 4 2>, S<grOrEq, U 4 4, U 4 2>>>, U 2 1, U 2 2, U 2 1>
//S<R<U 2 1, S<R<U 2 1, U 4 2>, U 4 4, S<R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 4 4, U 4 2>, S<S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>>, U 4 4, U 4 2>>>, U 2 1, U 2 2, U 2 1>
grOrEq = S<not, subrev> //S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>>

S<if, S<N,S<N, Z>>, S<R<Z, S<if, U 3 3, S<if, U 3 3, S<if, S<N, S<N, U 3 3>>, U 3 2, S<eq, U 3 3, S<add, U 3 1, U 3 1>>>,S<prime, U 3 2>>,S<even, U 3 3>>>, U 1 1, S<pow, S<N,S<N, Z>>, S<N, U 1 1>>>, U 1 1>//short version

S<R<U 2 1, U 4 2>, S<N,S<N, Z>>, S<R<Z, S<R<U 2 1, U 4 2>, U 3 3, S<R<U 2 1, U 4 2>, U 3 3, S<R<U 2 1, U 4 2>, S<N, S<N, U 3 3>>, U 3 2, S<S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 1 1, S<N, U 3 3>>, R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, S<R<U 1 1, S< S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>>>, U 3 3, S<R<U 1 1, S<N, U 3 3>>, U 3 1, U 3 1>>>, S<S<S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 1 1, S<N, U 3 3>>, R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, S<R<U 1 1, S< S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>>>, S<R<Z, S<R<U 1 1, S<N, U 3 3>>, S<S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 2 1, S<R<U 2 1, U 4 2>, U 4 4, S<R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 4 4, U 4 2>, S<S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, S<R<U 1 1, S<S<R<Z, U 3 2>, Z, U 1 1>, U 3 3>>, U 2 2, U 2 1>>, U 4 4, U 4 2>>>, U 2 1, U 2 2, U 2 1>>, U 3 1, U 3 2>, U 3 3>>, U 1 1, U 1 1>, S<N, Z>>, U 3 2>>,S<S<R<S<N, Z>, S<S<R<S<N, Z>, S<Z, U 3 1>>, Z, U 1 1>, U 3 3>>, Z, U 1 1>, U 3 3>>>, U 1 1, S<R<S<N, Z>, S<R<Z, S<R<U 1 1, S<N, U 3 3>>, U 3 1, U 3 3>>, U 3 3, U 3 1>>, S<N,S<N, Z>>, S<N, U 1 1>>>, U 1 1>//long version

C(mux, I(1,0), C(R(Z, C(mux, C(even, I(3,0)), C(mux, C(prime, I(3,1)), C(mux,
C(eq, I(3,0), C(add, I(3,2), I(3,2))), I(3,1), C(S, C(S, I(3,0)))), I(3,0)),
I(3,0))), C(pow, konst(2), C(S, I(1,0))), I(1,0)), konst(2))//java version

S<R<U 2 2, U 4 3>, U 1 1, S<R<Z, S<R<U 2 2, U 4 3>, S<S<R<S<N, Z>, S<S<R<S<N, Z>, S<Z, U 3 1>>, U 1 1, Z>, U 3 1>>, U 1 1, Z>, U 3 1>, S<R<U 2 2, U 4 3>, S<S<S<S<R<S<N, Z>, S<Z, U 3 1>>, U 1 1, Z>, S<R<U 1 1, S<N, U 3 1>>, S<R<U 1 1, S<S<R<Z, U 3 2>, U 1 1, Z>, U 3 1>>, U 2 2, U 2 1>, R<U 1 1, S<S<R<Z, U 3 2>, U 1 1, Z>, U 3 1>>>>, S<R<Z, S<R<U 1 1, S<N, U 3 1>>, S<S<S<R<S<N, Z>, S<Z, U 3 1>>, U 1 1, Z>, S<R<U 2 1, S<R<U 2 2, U 4 3>, S<S<S<R<S<N, Z>, S<Z, U 3 1>>, U 1 1, Z>, R<U 1 1, S<S<R<Z, U 3 2>, U 1 1, Z>, U 3 1>>>, U 4 1, U 4 4>, S<S<R<U 1 1, S<S<R<Z, U 3 2>, U 1 1, Z>, U 3 1>>, U 2 2, U 2 1>, U 4 1, U 4 4>, U 4 1>>, U 2 1, U 2 1, U 2 2>>, U 3 3, U 3 2>, U 3 1>>, U 1 1, U 1 1>, S<N, Z>>, U 3 2>, S<R<U 2 2, U 4 3>, S<S<S<R<S<N, Z>, S<Z, U 3 1>>, U 1 1, Z>, S<R<U 1 1, S<N, U 3 1>>, S<R<U 1 1, S<S<R<Z, U 3 2>, U 1 1, Z>, U 3 1>>, U 2 2, U 2 1>, R<U 1 1, S<S<R<Z, U 3 2>, U 1 1, Z>, U 3 1>>>>, U 3 1, S<R<U 1 1, S<N, U 3 1>>, U 3 3, U 3 3>>, U 3 2, S<N, S<N, U 3 1>>>, U 3 1>, U 3 1>>, S<S<R<S<N, Z>, S<R<Z, S<R<U 1 1, S<N, U 3 1>>, U 3 1, U 3 3>>, U 3 3, U 3 1>>, U 2 2, U 2 1>, S<N, S<N, Z>>, S<N, U 1 1>>, U 1 1>, S<N, S<N, Z>>>//java.toString() version

//Gödel numbering functions sketches
//len = S<len2, Z, U 1 1> (num)
//len2 = S<if, U 2 1, S<len2, S<N, U 2 1>, U 2 2>, S<divisible, U 2 2, S<NthPrime, U 2 1>>> (counter, num)

//charAt = S<charAt2, Z, U 2 1, U 2 2> (s, n)
//charAt2 = S<if, U 3 1, S<charAt2, S<N, U 3 1>, S<div, U 3 2, S<NthPrime, S<pred, U 3 3>>>, U 3 3>>, S<divisible, U 3 2, S<NthPrime, S<pred, U 3 3>>>> (counter, s, n)

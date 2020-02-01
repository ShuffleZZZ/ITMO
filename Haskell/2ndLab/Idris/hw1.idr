module hw1

import Data.Vect
import Data.Fin

swap: Vect n a -> Fin n -> Fin n -> Vect n a
swap vect i j = set i (at j vect) (set j (at i vect) vect)
	where 
		set: Fin n -> a -> Vect n a -> Vect n a
		set FZ val (x :: xs) = val ::  xs
		set (FS ind) val (x :: xs) = x :: (set ind val xs)

		at: Fin n -> Vect n a -> a
		at FZ (x :: xs) = x
		at (FS ind) (x :: xs) = at ind xs

i : Fin 4
i = 0
j : Fin 4
j = 1


--plus_fin: Fin a -> Fin b -> Fin (a + b)
--plus_fin FZ FZ = FZ
--plus_fin (FS a) FZ = FS (plus_fin a FZ)
--plus_fin FZ (FS b) = FS (plus_fin FZ b)
--plus_fin (FS a) (FS b) = FS (plus_fin a (FS b))

--mul_fin: Fin a -> Fin b -> Fin (a * b)
--mul_fin FZ b = FZ
--mul_fin (FS a) b = plus_fin a (mul_fin a b)

c : Fin 3
c = 2
d : Fin 4
d = 0


dec_fin: Fin (S a) -> Fin a
dec_fin (FS a) = a

a : Fin 4
a = 3
b : Fin 5
b = 2


nat_min: Nat -> Nat -> Nat
nat_min Z (S b) = Z
nat_min (S a) Z = Z
nat_min (S a) (S b) = S (nat_min a b)
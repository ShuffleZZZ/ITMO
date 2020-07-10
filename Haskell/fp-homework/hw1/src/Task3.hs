{-# LANGUAGE InstanceSigs #-}

module Task3
  ( Tree(..)

  , find
  , fromList
  , insert
  , isEmpty
  , size
  , toList
  ) where

import Data.List.NonEmpty (NonEmpty((:|)))

-- | Tree implementation with empty leafs and nonempty list
-- of similar objects as a node value.
data Tree a
  = Leaf  -- ^ leaf with no children and value inside.
  | Node (Tree a) (NonEmpty a) (Tree a)  -- ^ Node with 2 children and value.

-- | Checks whether the 'Tree' is empty.
isEmpty
  :: Tree a  -- ^ 'Tree' to check
  -> Bool  -- ^ 'True' on 'Leaf' and 'False' otherwise
isEmpty Leaf = True
isEmpty _    = False

-- | Returns the size of the given 'Tree'.
size
  :: Tree a  -- ^ 'Tree' to get a size of
  -> Int  -- ^ resulting size
size Leaf            = 0
size (Node l list r) = size l + length list + size r

-- | Finds the given element in a 'Tree'.
find
  :: Ord a  -- ^ invariant of BST
  => Tree a  -- ^ the 'Tree' to find the element in
  -> a  -- ^ element to find
  -> Bool  -- ^ 'True' on success and 'False' otherwise
find Leaf                _     = False
find (Node l (x :| _) r) value =
  case compare value x of
    LT -> find l value
    EQ -> True
    GT -> find r value

-- | Inserts the element into given 'Tree'.
insert
  :: Ord a  -- ^ invariant of BST
  => Tree a  -- ^ the 'Tree' to insert the element in
  -> a  -- ^ element to insert
  -> Tree a  -- ^ 'Tree' with inserted element
insert Leaf                      value = Node Leaf (value :| []) Leaf
insert (Node l list@(x :| xs) r) value =
  case compare value x of
    LT -> Node (insert l value) list r
    EQ -> Node l (value :| (x : xs)) r
    GT -> Node l list (insert r value)

-- | Makes a 'Tree' out of a list.
fromList
  :: Ord a  -- ^ invariant of BST
  => NonEmpty a  -- ^ given list
  -> Tree a  -- ^ resulting 'Tree'
fromList = foldl insert Leaf

-- | Unfolds tree to a list.
toList
  :: Ord a  -- ^ invariant of BST
  => Tree a  -- ^ given Tree
  -> [a]  -- ^ resulting list
toList = foldr (:) []

instance Foldable Tree where
  -- | Implementation of mapping each element to a monoid for a 'Tree'.
  foldMap
    :: Monoid m  -- ^ Monoid to combine elements of the same type
    => (a -> m)  -- ^ element to monoid mapping function
    -> Tree a  -- ^ 'Tree' to apply foldMap on
    -> m  -- ^ resulting monoid
  foldMap _ Leaf            = mempty
  foldMap f (Node l list r) = foldMap f l <> foldMap f list <> foldMap f r

  -- | Right-associative fold implementation for 'Tree'.
  foldr
    :: (a -> b -> b)  -- ^ binary operator to apply during folding
    -> b  -- ^ return value in case of 'Leaf' 'Tree'
    -> Tree a  -- ^ 'Tree' to fold
    -> b  -- ^ the result of folding
  foldr _ z Leaf            = z
  foldr f z (Node l list r) = foldr f (foldr f (foldr f z r) list) l


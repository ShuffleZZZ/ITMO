{-# LANGUAGE BangPatterns #-}

module Task1
  ( Point(..)

  , crossProduct
  , doubleArea
  , minus
  , perimeter
  , plus
  , scalarProduct
  ) where

-- | Point in double dimension.
data Point = Point
  { x :: !Int  -- ^ first coordinate
  , y :: !Int  -- ^ second coordinate
  } deriving (Show)

-- | Plus operation for 'Point' type.
plus
  :: Point  -- ^ first argument
  -> Point  -- ^ second argument
  -> Point  -- ^ resulting 'Point'
plus a b = Point (x a + x b) (y a + y b)

-- | Minus operation for 'Point' type.
minus
  :: Point  -- ^ first argument
  -> Point  -- ^ second argument
  -> Point  -- ^ resulting 'Point'
minus a b = Point (x a - x b) (y a - y b)

-- | Scalar product operation for 'Point' type.
scalarProduct
  :: Point  -- ^ first argument
  -> Point  -- ^ second argument
  -> Int  -- ^ resulting scalar
scalarProduct a b = x a * x b + y a * y b

-- | Cross product operation for 'Point' type.
crossProduct
  :: Point  -- ^ first argument
  -> Point  -- ^ second argument
  -> Int  -- ^ resulting determinant
crossProduct a b = x a * y b - y a * y b

-- | Calculates the perimeter of polygon without crossings.
perimeter
  :: [Point]  -- ^ 'List' of polygon's vertices in counterclock-wise order
  -> Double  -- ^ resulting perimeter
perimeter = iteratePolygon $! distance

-- | Calculates the double area of polygon without crossings.
doubleArea
  :: [Point]  -- ^ 'List' of polygon's vertices in counterclock-wise order
  -> Int  -- ^ resulting double area
doubleArea = iteratePolygon $! crossProduct

-- | Calculates the distance between two given 'Points'.
distance
  :: Point  -- ^ first point
  -> Point  -- ^ second point
  -> Double  -- ^ resulting distance
distance a b = zeroDistance $ minus a b

-- | Calculates the distance between given 'Point' and start of coordinates.
-- Corresponds to @distance a (Point 0 0)@.
zeroDistance
  :: Point  -- ^ point
  -> Double  -- ^ resulting distance
zeroDistance a = sqrt $! fromIntegral $! x a * x a + y a * y a

-- | Folds given Polygon with given function, that translate two Points
-- to the number value.
iteratePolygon
  :: (Num a)  -- ^ number constraint to perform arithmetical operations
  => (Point -> Point -> a)  -- ^ function to fold with
  -> [Point]  -- ^ 'List' of polygon's vertices in counterclock-wise order
  -> a  -- ^ resulting number
iteratePolygon _ [] = 0
iteratePolygon func polygon@(a : _) =
  fst $ foldr (\b (!acc, c) -> (acc + func b c, b)) (0, a) polygon

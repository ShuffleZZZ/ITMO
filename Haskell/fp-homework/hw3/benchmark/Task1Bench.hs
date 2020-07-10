module Task1Bench
  ( fastDoubleArea
  , fastPerimeter
  , slowDoubleArea
  , slowPerimeter
  ) where

import Control.DeepSeq (NFData)
import Criterion.Main (Benchmark, bench, nf)

import Task1 (Point(..), doubleArea, perimeter)
import Task1Naive (Point(..), naiveDoubleArea, naivePerimeter)

sizeList :: [Int]
sizeList = [100000, 1000000, 10000000]

fastPolygons :: [[Task1.Point]]
fastPolygons = map generate sizeList
  where generate l = map (\x -> Task1.Point x x) [0 .. l]

slowPolygons :: [[Task1Naive.Point]]
slowPolygons = map generate sizeList
  where generate l = map (\x -> Task1Naive.Point x x) [0 .. l]

fastPerimeter :: [Benchmark]
fastPerimeter = map (benchmark perimeter) fastPolygons

fastDoubleArea :: [Benchmark]
fastDoubleArea = map (benchmark doubleArea) fastPolygons

slowPerimeter :: [Benchmark]
slowPerimeter = map (benchmark naivePerimeter) slowPolygons

slowDoubleArea :: [Benchmark]
slowDoubleArea = map (benchmark naiveDoubleArea) slowPolygons

benchmark :: NFData b => ([a] -> b) -> [a] -> Benchmark
benchmark f polygon =
  bench ("10^" ++ (show $ ((flip (-) 1) . length) $ show $ length polygon))
    $ nf f polygon
